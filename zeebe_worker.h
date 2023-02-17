#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <sys/_types/_int64_t.h>
#include <thread>


#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include "gateway.grpc.pb.h"
#include "zeebe_adapter_job.h"
#include "zeebe_client.h"


using grpc::Channel;

using namespace gateway_protocol;

namespace ZeebeCpp {

class ZeebeWorker
{
public:

    ZeebeWorker(const std::shared_ptr<ZeebeClient> &client,
        const std::shared_ptr<ZeebeAdapterJob> adapterJob, const std::string &name,
        const TaskInfo &taskInfo, const JobHandler &jobHandler = {});


    void setJobHandler(const JobHandler &jobHandler);
    bool start();
    void stop();
    bool isRunning();

    std::shared_ptr<ZeebeAdapterJob> adapterJob();
    std::string name();
    TaskInfo taskInfo();
    JobHandler jobHandler();
private:
    std::shared_ptr<ZeebeClient> client_;
    const std::string name_;
    TaskInfo taskInfo_;
    JobHandler jobHandler_;
    std::shared_ptr<ZeebeAdapterJob> adapterJob_;
    std::unique_ptr<std::thread> thread_;
    std::atomic_bool running_;
    virtual void work();
};

class ZeebeWorkerChild : public ZeebeWorker {
public:
    ZeebeWorkerChild(const std::shared_ptr<ZeebeClient> &client, const std::shared_ptr<ZeebeAdapterJob> adapterJob, 
    const std::string &name, 
    const TaskInfo &taskInfo, const JobHandler &jobHandler = nullptr) 
    : ZeebeWorker(client, adapterJob, name, taskInfo, jobHandler) {}

    void loop(const std::string &vars)
    {
        std::cout << vars << std::endl;
    }
private:
    void work() override {
        while (isRunning())
        {

            std::cout << "debugging..." << std::endl;
            std::vector<ActivatedJobInfo> activatedJobs;
            auto status = adapterJob()->activateJobs(taskInfo().typeName, name(), taskInfo().timeout, taskInfo().maxJobsToActivate, taskInfo().fetchVariables, taskInfo().requestTimeout, activatedJobs);
            for (auto &job : activatedJobs)
            {
                if (jobHandler()) jobHandler()();
                std::cout << job.variables << std::endl;
                job.variables = "{\"result\":\"Pong\"}";
                adapterJob()->completeJob(job.key, job.variables);
            }
    
        }


    }

    
};

} // namespace ZeebeCpp
