#include "kheperon.grpc.pb.h"

#include <khepera/khepera.h>

extern "C" {
static int on_section(const char *name, kb_section_config_t *section,
                       void *context) {
  SectionConfigs *configs = reinterpret_cast<SectionConfigs *>(context);
  SectionConfig *config = configs->add_configs();
  config->set_name(name);
  return 0;
}
}

class KheperonImpl final : public Kheperon::Service {
  grpc::Status EnumSections(grpc::ServerContext *context,
                            const EnumRequest *request,
                            SectionConfigs *response) override {
    SectionConfig *config = response->add_configs();

    kb_enum_section(on_section, response);

    return grpc::Status::OK;
  }
};
