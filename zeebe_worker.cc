#include "zeebe_worker.h"
#include "gateway.pb.h"
#include "zeebe_adapter_job.h"
#include "zeebe_client.h"
#include <cstdlib>
#include <grpc/status.h>
#include <grpcpp/channel.h>
#include <grpcpp/support/status.h>
#include <memory>

using namespace gateway_protocol;


namespace ZeebeCpp {

ZeebeWorker::ZeebeWorker(const std::shared_ptr<ZeebeClient> &client, const std::shared_ptr<ZeebeAdapterJob> adapterJob, 
    const std::string &name, 
    const TaskInfo &taskInfo, const JobHandler &jobHandler) 
    : client_(client), adapterJob_(adapterJob), name_(name), taskInfo_(taskInfo), jobHandler_(jobHandler) {}

void ZeebeWorker::stop() {
    running_ = false;
}

bool ZeebeWorker::start() {
    running_ = true;
    thread_.reset(new std::thread(&ZeebeWorker::work, this));
    return true;
}

bool ZeebeWorker::isRunning() {
    return running_;
}

std::shared_ptr<ZeebeAdapterJob> ZeebeWorker::adapterJob() {
    return adapterJob_;
}

std::string ZeebeWorker::name() {
    return name_;
}

TaskInfo ZeebeWorker::taskInfo() {
    return taskInfo_;
}

JobHandler ZeebeWorker::jobHandler() {
    return jobHandler_;
}

void ZeebeWorker::setJobHandler(const JobHandler &jobHandler) {
    jobHandler_ = jobHandler;
}

void ZeebeWorker::work() {
    while (running_)
    {
        std::cout << "debugging..." << std::endl;
        std::vector<ActivatedJobInfo> activatedJobs;
        auto status = adapterJob_->activateJobs(taskInfo_.typeName, name_, taskInfo_.timeout, taskInfo_.maxJobsToActivate, taskInfo_.fetchVariables, taskInfo_.requestTimeout, activatedJobs);
        for (auto &job : activatedJobs)
        {
            if (jobHandler_) jobHandler_();
            adapterJob_->completeJob(job.key, job.variables);
        }
    }
}


} // namespace ZeebeCpp
