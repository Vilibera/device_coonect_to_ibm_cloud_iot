# OpenWrt → IBM Watson IoT Platform connector

A C daemon and its LuCI web interface that connect an **OpenWrt router** to **IBM Watson IoT Platform** as a device. The daemon then publishes the router's memory usage (total, free, shared, buffered, read from procd's `system info` over ubus) as device events over MQTT.

## Components
| Directory | What it is |
|---|---|
| `ibm_connect_program/ibm_program` | The daemon (C). Uses the IBM IoT C SDK, reads router data through ubus, and has a procd init script. |
| `ibm_connect_program/libibm` | OpenWrt package for the IBM Watson IoT Platform C client library. |
| `ibm_connect_program/luci-app-ibm` | LuCI page where you enter the Org ID, Type ID, Device ID and Auth Token. |

## Build
Copy the three directories into the `package/` directory of an OpenWrt SDK and run:

```sh
make menuconfig     # select ibm_program and luci-app-ibm
make package/ibm_program/compile V=s
make package/luci-app-ibm/compile V=s
```

## Usage
1. Register a device type and device in IBM Watson IoT Platform and note the credentials.
2. On the router, open **Services → ibm_program** in LuCI, enter the Org ID, Type ID, Device ID and Auth Token, and enable the service.
3. Or run it by hand:
   ```sh
   ibm_program -o <orgId> -t <typeId> -d <deviceId> -a <authToken>
   ```

More details are in `HowUse.odt`.

## Tech
C · OpenWrt · MQTT · IBM Watson IoT · ubus · UCI · LuCI (Lua) · procd
