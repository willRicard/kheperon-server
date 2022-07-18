#include "kheperon.grpc.pb.h"

class KheperonImpl final : public Kheperon::Service {
  grpc::Status EnumSections(grpc::ServerContext *context,
                            const EnumRequest *request,
                            SectionConfigs *response) override {
    SectionConfig *config = response->add_configs();
    config->set_name("Hello");

    return grpc::Status::OK;
  }
};
