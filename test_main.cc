#include "gateway.grpc.pb.h"
#include "zeebe_adapter_process.h"
#include "zeebe_client.h"
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <vector>
#include "zeebe_adapter_job.h"
#include "zeebe_worker.h"
#include <functional>

void workEcho() {
    std::cout << "hello zeebe!" << std::endl;
}

int main() {
    // ZeebeCpp::ZeebeClient client(grpc::CreateChannel(
    //     "localhost:26500", grpc::InsecureChannelCredentials()));
    // ZeebeCpp::ProcessInfo processInfo;
    // auto status = client.deployProcess("sample.bpmn", processInfo);
    // ZeebeCpp::ProcessInstanceInfo processInstanceInfo;
    // if (status == 0)
    //     for (int i = 0; i < 10; ++i) {
    //         client.runProcess(processInfo.processDefinitionkey,
    //                           "camunda-cloud-quick-start-advanced", "",
    //                           processInstanceInfo);
    //     }
    

    auto channel = grpc::CreateChannel("localhost:26500", grpc::InsecureChannelCredentials()); 
    std::shared_ptr<Gateway::Stub> stub(new Gateway::Stub(channel));


    ZeebeCpp::ZeebeAdapterJob job(stub);
    std::vector<ZeebeCpp::ActivatedJobInfo> jobsinfo;
    auto status = job.activateJobs("test-worker", "worker1", 1, 5, std::vector<std::string>(), -1, jobsinfo);
    if (status != 0) {
        std::cout << "error." << std::endl;
    }
    std::cout << "job number: " << jobsinfo.size() << std::endl;
    for (auto jobInfo : jobsinfo) {
        std::cout << jobInfo.key << std::endl;
        status = job.completeJob(jobInfo.key, "{\"result\":\"Ping\"}");
    }
    // status = job.completeJob(jobinfo.key, "");
    if (status != 0) {
        std::cout << "complete job error." << std::endl;
    }

    auto client = std::shared_ptr<ZeebeCpp::ZeebeClient>(new ZeebeCpp::ZeebeClient(channel));
    ZeebeCpp::TaskInfo taskInfo;
    taskInfo.typeName = "test-worker";
    taskInfo.timeout = 1;
    taskInfo.maxJobsToActivate = 5;
    taskInfo.requestTimeout = 10000;
    // auto worker = client->newJobWorker("worker0", taskInfo, std::bind(workEcho));
    auto worker = new ZeebeCpp::ZeebeWorkerChild(client, client->adapterJob(), "worker1", taskInfo);
    worker->setJobHandler(std::bind(&ZeebeCpp::ZeebeWorkerChild::loop, worker, "dfg"));
    std::cout << "test." << std::endl;
    worker->start();
    while (1)
    {
        
    }
    
    return 0;
}
