
#include "zeebe_adapter_process.h"
#include "gateway.grpc.pb.h"
#include "gateway.pb.h"
#include <cstdlib>
#include <fstream>
#include <grpc/status.h>
#include <grpcpp/support/status.h>
#include <sstream>

using namespace ::gateway_protocol;

namespace ZeebeCpp {

using grpc::ClientContext;
using grpc::Status;

int ZeebeAdapterProcess::deployProcess(const std::string &bpmnName, const std::string &bpmnPath, 
                                       ProcessInfo &processInfo) {
    ::gateway_protocol::DeployResourceRequest request;
    ::gateway_protocol::DeployResourceResponse response;
    auto resource = request.add_resources();
    std::cout << request.resources_size() << std::endl;
    resource->set_name(bpmnName);
    std::ifstream processFile(bpmnPath);
    if (!processFile.is_open()) {
        std::cout << "Failed to open" << bpmnPath << std::endl;
    }
    std::stringstream process;
    process << processFile.rdbuf();
    // std::cout << process.str() << std::endl;
    resource->set_content(process.str());

    ClientContext context;

    Status status = stub()->DeployResource(&context, request, &response);
    if (!status.ok()) {
        std::cout << "Deploy resource " << resource->name() << " failed!"
                  << std::endl;
        std::cout << status.error_details() << std::endl;
    } else {
        std::cout
            << "success deploying! A list of deployed bpmn processes below:"
            << std::endl;
        auto deploys = response.deployments();
        uint16_t count = 0;
        for (auto deploy : deploys) {
            if (!deploy.has_process()) {
                std::cout << "error return type if 'oneof' type." << std::endl;
                return status.error_code();
            }
            
            auto process = deploy.process();
            processInfo = makeProcessInfo(process);
            std::cout << count
                      << ": bpmn process id: " << process.bpmnprocessid()
                      << ", version: " << process.version()
                      << ", process definition key: "
                      << process.processdefinitionkey()
                      << ", resource name: " << process.resourcename()
                      << std::endl;
        }
    }
    return status.error_code();
}

int ZeebeAdapterProcess::runProcess(const int64_t processDefinitionKey,
                                    const std::string &bpmnProcessId,
                                    const std::string &variables,
                                    ProcessInstanceInfo &processInstanceInfo) {
    CreateProcessInstanceRequest request;
    CreateProcessInstanceResponse response;
    request.set_processdefinitionkey(processDefinitionKey);
    request.set_bpmnprocessid(bpmnProcessId);
    request.set_version(-1);
    request.set_variables(variables);
    request.clear_startinstructions();
    ClientContext context;

    Status status = stub()->CreateProcessInstance(&context, request, &response);
    if (!status.ok()) {
        std::cout << "run process " << bpmnProcessId << " failed!" << std::endl;
        std::cout << status.error_details() << std::endl;
    } else {
        processInstanceInfo = makeProcessInstanceInfo(response);
        std::cout << "success running! The instance info below:" << std::endl;
        std::cout << ": bpmn process id: " << response.bpmnprocessid()
                  << ", version: " << response.version()
                  << ", process definition key: "
                  << response.processdefinitionkey()
                  << ", process instance key: " << response.processinstancekey()
                  << std::endl;
    }
    return status.error_code();
}

int ZeebeAdapterProcess::cancelProcessInstance(int64_t processInstanceKey) {
    CancelProcessInstanceRequest request;
    request.set_processinstancekey(processInstanceKey);
    CancelProcessInstanceResponse response;
    ClientContext context;
    auto status = stub()->CancelProcessInstance(&context, request, &response);
    if (!status.ok()) {
        std::cout << "cancel process " << processInstanceKey << " failed!" << std::endl;
        std::cout << status.error_details() << std::endl;
    } 
    return status.error_code(); 
}

ProcessInfo ZeebeAdapterProcess::makeProcessInfo(
    gateway_protocol::ProcessMetadata &process) {

    ProcessInfo processInfo;
    processInfo.bpmnProcessId = process.bpmnprocessid();
    processInfo.processDefinitionkey = process.processdefinitionkey();
    processInfo.version = process.version();
    processInfo.processName = process.resourcename();

    return processInfo;
}

ProcessInstanceInfo ZeebeAdapterProcess::makeProcessInstanceInfo(
    gateway_protocol::CreateProcessInstanceResponse &ins) {

    ProcessInstanceInfo processInsInfo;
    processInsInfo.bpmnProcessId = ins.bpmnprocessid();
    processInsInfo.processDefinitionkey = ins.processdefinitionkey();
    processInsInfo.version = ins.version();
    processInsInfo.processInstanceKey = ins.processinstancekey();

    return processInsInfo;
}

} // namespace ZeebeCpp
