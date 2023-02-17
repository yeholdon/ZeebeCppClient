#ifndef ZEEBE_ADAPTER_MESSAGE_H_
#define ZEEBE_ADAPTER_MESSAGE_H_

#include "gateway.grpc.pb.h"
#include "zeebe_adapter_base.h"
#include <sys/_types/_int32_t.h>
#include <sys/_types/_int64_t.h>

namespace ZeebeCpp {

class ZeebeAdapterMessage : public ZeebeAdapterBase {
  public:
    ZeebeAdapterMessage(std::shared_ptr<gateway_protocol::Gateway::Stub> stub)
        : ZeebeAdapterBase(stub) {}
    ZeebeAdapterMessage(ZeebeAdapterMessage &&) = default;
    ZeebeAdapterMessage(const ZeebeAdapterMessage &) = default;
    ZeebeAdapterMessage &operator=(ZeebeAdapterMessage &&) = default;
    ZeebeAdapterMessage &operator=(const ZeebeAdapterMessage &) = default;
    ~ZeebeAdapterMessage() = default;

    int publishMessage(const std::string &msgName, const std::string &correlationKey, const int64_t time2Live, const std::string &messageId, const std::string &variables); 

  private:
};

} // namespace ZeebeCpp

#endif // ZEEBE_ADAPTER_MESSAGE_H_
