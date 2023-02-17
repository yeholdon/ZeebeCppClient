#include "gateway.grpc.pb.h"
#include "zeebe_adapter_process.h"
#include "zeebe_client.h"
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <vector>
#include "zeebe_adapter_process.h"
#include "zeebe_worker.h"

void workEcho() {
    std::cout << "hello zeebe!" << std::endl;
}

int main() {

    auto channel = grpc::CreateChannel("localhost:26500", grpc::InsecureChannelCredentials()); 
    std::shared_ptr<Gateway::Stub> stub(new Gateway::Stub(channel));

    ZeebeCpp::ZeebeAdapterProcess process(stub);
    ZeebeCpp::ProcessInfo processInfo;
    auto status = process.deployProcess("sample.bpmn", "../sample.bpmn", processInfo);
    ZeebeCpp::ProcessInstanceInfo processInstanceInfo;
    if (status == 0)
        for (int i = 0; i < 10; ++i) {
            process.runProcess(processInfo.processDefinitionkey,
                              "camunda-cloud-quick-start-advanced", "",
                              processInstanceInfo);
        }
    
    return 0;
}
