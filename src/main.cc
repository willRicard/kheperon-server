#include "kheperon.h"

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include <khepera/khepera.h>

int main(int argc, char **argv) {
  int rc = kb_init(argc, argv);
  if (rc < 0) {
    std::cout << "Error initializing libkhepera" << std::endl;
    return 1;
  }

  std::string server_address("0.0.0.0:50051");
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
