#ifndef ZEEBE_ADAPTER_JOB_H_
#define ZEEBE_ADAPTER_JOB_H_

#include "gateway.grpc.pb.h"
#include "zeebe_adapter_base.h"
#include <sys/_types/_int32_t.h>
#include <sys/_types/_int64_t.h>
#include "zeebe_task.h"
#include "zeebe_job.h"

namespace ZeebeCpp {



class ZeebeAdapterJob : public ZeebeAdapterBase {
  public:
    ZeebeAdapterJob(std::shared_ptr<gateway_protocol::Gateway::Stub> stub)
        : ZeebeAdapterBase(stub) {}
    ZeebeAdapterJob(ZeebeAdapterJob &&) = default;
    ZeebeAdapterJob(const ZeebeAdapterJob &) = default;
    ZeebeAdapterJob &operator=(ZeebeAdapterJob &&) = default;
    ZeebeAdapterJob &operator=(const ZeebeAdapterJob &) = default;
    ~ZeebeAdapterJob() = default;

    int activateJobs(const std::string &typeName, const std::string &workerName,
                     const int64_t timeoutMs, const int32_t maxJobs2Acti,
                     const std::vector<std::string> &fetchVars,
                     const int64_t reqTimeout, std::vector<ActivatedJobInfo> &actiJobsInfo);
    
    int completeJob(const int64_t jobKey, const std::string &variables);

    int failJob(const int64_t jobKey, const int32_t retries, 
                const std::string errorMessage, const int64_t retryBackoff);

  private:
    ActivatedJobInfo makeActivatedJobInfo(const gateway_protocol::ActivatedJob &job) {
        ActivatedJobInfo jobInfo;
        jobInfo.processInstanceKey = job.processinstancekey();
        jobInfo.key = job.key();
        jobInfo.processDefinitionVersion = job.processdefinitionversion();
        jobInfo.bpmnProcessId = job.bpmnprocessid();
        jobInfo.processDefinitionKey = job.processdefinitionkey();
        jobInfo.elementId = job.elementid();
        jobInfo.elementInstanceKey = job.elementinstancekey();
        jobInfo.customHeaders = job.customheaders();
        jobInfo.retries = job.retries();
        jobInfo.deadline = job.deadline();
        jobInfo.variables = job.variables();

        return jobInfo;
    }
};

typedef std::function<void ()> JobHandler;

} // namespace ZeebeCpp

#endif // ZEEBE_ADAPTER_JOB_H_
