#include "zeebe_client.h"
#include "gateway.pb.h"
#include "zeebe_adapter_job.h"
#include "zeebe_adapter_message.h"
#include <cstdlib>
#include <fstream>
#include <grpc/status.h>
#include <grpcpp/support/status.h>
#include <sstream>
#include "zeebe_worker.h"

// using namespace ::gateway_protocol;

namespace ZeebeCpp {

using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;

ZeebeClient::ZeebeClient(std::shared_ptr<Channel> channel)
    : stub_(new Gateway::Stub(channel)), adapterJob_(new ZeebeAdapterJob(stub_))
    , adapterProcess_(new ZeebeAdapterProcess(stub_))
    , adapterMessage_(new ZeebeAdapterMessage(stub_)) {}

std::shared_ptr<ZeebeWorker>  ZeebeClient::newJobWorker(const std::string &name, 
    const TaskInfo &taskInfo, 
    const JobHandler &jobHandler
    ) {
    std::shared_ptr<ZeebeWorker> worker(new ZeebeWorker(shared_from_this(), adapterJob_ ,name, taskInfo, jobHandler));
    return worker;
}


} // namespace ZeebeCpp
