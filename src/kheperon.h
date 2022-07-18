#include "kheperon.grpc.pb.h"

#include <cstring>

#include <khepera/khepera.h>

static const int kDefined = 1;

extern "C" {
static int on_device(const char *name, kb_device_config_t *device,
                     void *context) {
  SectionConfig *config = reinterpret_cast<SectionConfig *>(context);
  DeviceConfig *dev_cfg = config->add_devices();
  dev_cfg->set_name(name);

  for (int i = 0; i < KB_DEVICE_MAX_CLASS; ++i) {
    if (device->kclass[i].defined == kDefined) {
      DeviceClass *kclass = dev_cfg->add_classes();
      kclass->set_address(device->kclass[i].address);
      kclass->set_device_name(device->kclass[i].device_name);
    }
  }

  return 0;
}

static int on_section(const char *name, kb_section_config_t *section,
                      void *context) {
  SectionConfigs *configs = reinterpret_cast<SectionConfigs *>(context);
  SectionConfig *config = configs->add_configs();
  config->set_name(name);

  kb_enum_device(name, on_device, config);

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
