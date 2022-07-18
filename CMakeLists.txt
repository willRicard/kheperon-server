cmake_minimum_required(VERSION 3.10)

project(KheperonServer)

find_package(protobuf REQUIRED)
find_package(gRPC CONFIG REQUIRED)

find_path(KHEPERA_INCLUDE_DIR PATHS khepera.h)
find_library(KHEPERA_LIBRARY khepera)

get_filename_component(kheperon_proto "protos/kheperon.proto" ABSOLUTE)
get_filename_component(kheperon_proto_path "${kheperon_proto}" PATH)

set(kheperon_proto_srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/kheperon.pb.cc")
set(kheperon_proto_hdrs "${CMAKE_CURRENT_SOURCE_DIR}/src/kheperon.pb.h")
set(kheperon_grpc_srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/kheperon.grpc.pb.cc")
set(kheperon_grpc_hdrs "${CMAKE_CURRENT_SOURCE_DIR}/src/kheperon.grpc.pb.h")

find_program(PROTOBUF_PROTOC protoc)
find_program(GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)

add_custom_command(
  OUTPUT "${kheperon_proto_srcs}" "${kheperon_proto_hdrs}" "${kheperon_grpc_srcs}" "${kheperon_grpc_hdrs}"
  COMMAND protoc
  ARGS --grpc_out "${CMAKE_CURRENT_SOURCE_DIR}/src"
       --cpp_out "${CMAKE_CURRENT_SOURCE_DIR}/src"
       -I "${kheperon_proto_path}"
       --plugin=protoc-gen-grpc="${GRPC_CPP_PLUGIN_EXECUTABLE}"
       "${kheperon_proto}"
  DEPENDS "${kheperon_proto}"
)

add_custom_target(kheperon-proto ALL DEPENDS
  ${kheperon_proto_srcs}
  ${kheperon_proto_hdrs}
  ${kheperon_grpc_srcs}
  ${kheperon_grpc_hdrs}
)

add_executable(kheperon-server
  ${kheperon_proto_srcs}
  ${kheperon_proto_hdrs}
  ${kheperon_grpc_srcs}
  ${kheperon_grpc_hdrs}
  src/kheperon.h
  src/main.cc
)

target_include_directories(kheperon-server PUBLIC
  ${KHEPERA_INCLUDE_DIR}
)

target_link_libraries(kheperon-server PUBLIC
  gRPC::grpc++
  ${KHEPERA_LIBRARY}
)
