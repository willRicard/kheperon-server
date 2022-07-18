#include "kheperon.h"

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

int main(int argc, char **argv) {
  std::string server_address("127.0.0.1:50051");
  KheperonImpl service;

  grpc::EnableDefaultHealthCheckService(true);

  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << " Server listening on " << server_address << std::endl;

  server->Wait();

  return 0;
}
