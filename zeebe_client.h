
/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef ZEEBE_CLIENT_H_
#define ZEEBE_CLIENT_H_

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
#include <grpcpp/security/credentials.h>
#include "gateway.grpc.pb.h"
#include "zeebe_adapter_job.h"
#include "zeebe_adapter_process.h"
#include "zeebe_adapter_message.h"


using grpc::Channel;

using namespace gateway_protocol;

namespace ZeebeCpp {

class ZeebeWorker;


class ZeebeClient : public std::enable_shared_from_this<ZeebeClient> {
  public:
    ZeebeClient(std::shared_ptr<Channel> channel);
    
    std::shared_ptr<ZeebeWorker> newJobWorker(const std::string &name, const TaskInfo &taskInfo, const JobHandler &jobHandler);
    std::shared_ptr<ZeebeAdapterJob> adapterJob() { return adapterJob_; }
    std::shared_ptr<ZeebeAdapterProcess> adapterProcess() { return adapterProcess_; }
    std::shared_ptr<ZeebeAdapterMessage> adapterMessage() { return adapterMessage_; }

  private:
    std::shared_ptr<Gateway::Stub> stub_;
    std::shared_ptr<ZeebeAdapterJob> adapterJob_;
    std::shared_ptr<ZeebeAdapterProcess> adapterProcess_;
    std::shared_ptr<ZeebeAdapterMessage> adapterMessage_; 
};

}

#endif // ZEEBE_CLIENT_H_