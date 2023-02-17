#ifndef ZEEBE_ADAPTER_BASE_H_
#define ZEEBE_ADAPTER_BASE_H_

#include <grpcpp/security/credentials.h>

#include "gateway.pb.h"
#include <cstdlib>
#include <grpc/status.h>
#include <grpcpp/channel.h>
#include <grpcpp/support/status.h>
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include "gateway.grpc.pb.h"
#include <memory>

namespace ZeebeCpp {


class ZeebeAdapterBase
{
public:
    ZeebeAdapterBase(std::shared_ptr<gateway_protocol::Gateway::Stub> stub)
        : stub_(stub) {}
    ZeebeAdapterBase(ZeebeAdapterBase &&) = default;
    ZeebeAdapterBase(const ZeebeAdapterBase &) = default;
    ZeebeAdapterBase &operator=(ZeebeAdapterBase &&) = default;
    ZeebeAdapterBase &operator=(const ZeebeAdapterBase &) = default;
    ~ZeebeAdapterBase() = default;

    std::shared_ptr<gateway_protocol::Gateway::Stub> stub() {
            return stub_;
        }
private:
  // std::shared_ptr<::grpc::Channel> channel_;
    std::shared_ptr<gateway_protocol::Gateway::Stub> stub_;
};

} // namespace ZeebeCpp

#endif // ZEEBE_ADAPTER_BASE_H_

