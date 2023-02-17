#include "zeebe_adapter_job.h"
#include "gateway.grpc.pb.h"
#include "gateway.pb.h"
#include <cstdlib>
#include <fstream>
#include <grpc/status.h>
#include <grpcpp/support/status.h>
#include <ostream>
#include <sstream>

using namespace ::gateway_protocol;

namespace ZeebeCpp {

using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;

int ZeebeAdapterJob::activateJobs(const std::string &typeName, const std::string &workerName, const int64_t timeoutMs, const int32_t maxJobs2Acti, const std::vector<std::string> &fetchVars, const int64_t reqTimeout, std::vector<ActivatedJobInfo> &actiJobsInfo) {

    ActivateJobsRequest request;
    ActivateJobsResponse response;
    request.set_type(typeName);
    request.set_worker(workerName);
    request.set_timeout(timeoutMs);
    request.set_maxjobstoactivate(maxJobs2Acti);
    request.set_requesttimeout(reqTimeout);
    request.clear_fetchvariable();

    ClientContext context;
    std::unique_ptr<ClientReader<ActivateJobsResponse> > reader(
        stub()->ActivateJobs(&context, request));
    
    while (reader->Read(&response)) {
        ActivatedJobInfo jobInfo;
        auto jobs = response.jobs();
        for (auto job : jobs) {
            jobInfo.key = job.key();
            actiJobsInfo.push_back(jobInfo); 
        }
    }
    Status status = reader->Finish();
    if (status.ok()) {
      std::cout << "activate jobs succeeded." << std::endl;
    } else {
      std::cout << "activate jobs failed." << std::endl;
        std::cout << status.error_details() << std::endl;
    }
    return status.error_code(); 
}

int ZeebeAdapterJob::completeJob(const int64_t jobKey, const std::string &variables) {

    CompleteJobRequest request;
    CompleteJobResponse response;
    request.set_jobkey(jobKey);
    request.set_variables(variables);
    ClientContext context;
    auto status = stub()->CompleteJob(&context, request, &response);
    if (status.ok()) {
      std::cout << "complete jobs succeeded." << std::endl;
    } else {
      std::cout << "complete jobs failed." << std::endl;
        std::cout << status.error_details() << std::endl;
    }

    return status.error_code();
}

int ZeebeAdapterJob::failJob(const int64_t jobKey, const int32_t retries, const std::string errorMessage, const int64_t retryBackoff) {

    FailJobRequest request;
    FailJobResponse response;
    request.set_jobkey(jobKey);
    request.set_retries(retries);
    request.set_retrybackoff(retryBackoff);
    request.set_errormessage(errorMessage);
    ClientContext context;
    auto status = stub()->FailJob(&context, request, &response);

    return status.error_code();
}

} // namespace ZeebeCpp
