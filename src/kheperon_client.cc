#include "kheperon.grpc.pb.h"

#include <memory>

#include <grpcpp/grpcpp.h>

int main(int argc, char **argv) {
  std::string target_str("0.0.0.0:50051");

  std::shared_ptr<grpc::Channel> channel =
      grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials());

  std::unique_ptr<Kheperon::Stub> stub = Kheperon::NewStub(channel);

  EnumRequest request;
  request.set_secret("toto");

  SectionConfigs configs;

  grpc::ClientContext context;
  grpc::Status status = stub->EnumSections(&context, request, &configs);

  if (!status.ok()) {
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
  }

  for (int i = 0; i < configs.configs_size(); ++i) {
    const SectionConfig config = configs.configs(i);
    std::cout << config.name() << std::endl;

    for (int j = 0; j < config.devices_size(); ++j) {
      const DeviceConfig device = config.devices(j);
      std::cout << "\t" << device.name();

      for (int k = 0; k < device.classes_size(); ++k) {
        const DeviceClass kclass = device.classes(k);
        std::cout << "(" << kclass.address() << "|" << kclass.device_name()
                  << ")";
      }

      std::cout << std::endl;
    }
  }

  return 0;
}
