cmake_minimum_required(VERSION 3.5)

project(ZeebeGwClient LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)



set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#假设已经安装好grpc了
find_package(Threads REQUIRED)

set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)


# Find gRPC installation
# Looks for gRPCConfig.cmake file installed by gRPC's cmake installation.
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP gRPC::grpc++)

foreach(_target test_main test_create)

add_executable(${_target} "${_target}.cc"
  ${hw_proto_srcs}
  ${hw_grpc_srcs}
  gateway.grpc.pb.cc
  gateway.pb.cc
  zeebe_client.cc
  zeebe_adapter_job.cc
  zeebe_adapter_process.cc
  zeebe_adapter_message.cc
  zeebe_worker.cc
  )

target_link_libraries(${_target}
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

target_include_directories(${_target} 
  PRIVATE
  ${PROJECT_SOURCE_DIR}
)

endforeach()

