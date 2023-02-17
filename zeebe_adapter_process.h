#ifndef ZEEBE_ADAPTER_PROCESS_H_
#define ZEEBE_ADAPTER_PROCESS_H_

#include "gateway.grpc.pb.h"
#include "gateway.pb.h"
#include "zeebe_adapter_base.h"
#include "zeebe_process.h"

namespace ZeebeCpp {


class ZeebeAdapterProcess : public ZeebeAdapterBase {
  public: 

    ZeebeAdapterProcess(std::shared_ptr<gateway_protocol::Gateway::Stub> stub)
        : ZeebeAdapterBase(stub){}
    ZeebeAdapterProcess(ZeebeAdapterProcess &&) = default;
    ZeebeAdapterProcess(const ZeebeAdapterProcess &) = default;
    ZeebeAdapterProcess &operator=(ZeebeAdapterProcess &&) = default;
    ZeebeAdapterProcess &operator=(const ZeebeAdapterProcess &) = default;
    ~ZeebeAdapterProcess() = default;

    // 部署资源（流程图）
    int deployProcess(const std::string &bpmnName, const std::string &bpmnPath, ProcessInfo &processInfo);
    // 
    int publishMessage(const std::string &msgName, const std::string &correlationKey);

    int runProcess(const int64_t processDefinitionkey, const std::string &bpmnProcessId, const std::string &variables, ProcessInstanceInfo &pocessInstanceInfo);

    // CreateProcessInstanceWithResultResponse runProcessWithResult(const std::string &bpmnProcessId, const std::string &variables);

    int cancelProcessInstance(int64_t processInstanceKey);


  private:
    ProcessInfo makeProcessInfo(gateway_protocol::ProcessMetadata &processMetadata);
    ProcessInstanceInfo makeProcessInstanceInfo(gateway_protocol::CreateProcessInstanceResponse &processInsInfo);

};

}

#endif // ZEEBE_ADAPTER_PROCESS_H_