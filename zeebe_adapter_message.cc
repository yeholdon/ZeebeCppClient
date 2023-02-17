#include "zeebe_adapter_message.h"
#include "gateway.grpc.pb.h"
#include "gateway.pb.h"
#include <cstdlib>
#include <fstream>
#include <grpc/status.h>
#include <grpcpp/support/status.h>
#include <sstream>

using namespace ::gateway_protocol;

namespace ZeebeCpp {

using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;

int ZeebeAdapterMessage::publishMessage(const std::string &msgName, const std::string &correlationKey, const int64_t time2Live, const std::string &messageId, const std::string &variables) {
    PublishMessageRequest request;
    PublishMessageResponse response;
    request.set_name(msgName);
    request.set_correlationkey(correlationKey);
    request.set_timetolive(time2Live);
    request.set_messageid(messageId);
    request.set_variables(variables);
    ClientContext context;
    auto status = stub()->PublishMessage(&context, request, &response);
    return status.error_code();
}

} // namespace ZeebeCpp
