#include "iotp_device.h"




void DeviceCreate(IoTPDevice **device,IoTPConfig *config);
void Deviceconnect(IoTPDevice **device,IoTPConfig *config);
void DeviceSendEvent(IoTPDevice *device,IoTPConfig *config);
void DisconnectDevice(IoTPDevice *device,IoTPConfig *config);

