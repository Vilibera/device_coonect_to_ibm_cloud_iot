#include <stdio.h>
#include <signal.h>
#include "configs.h"
#include "memory.h"
#include <stdlib.h>
#include <unistd.h>
#include "logscleanup.h"
#include "iotp_device.h"
#include <libubus.h>
#include "invoke.h"
#include <syslog.h>
#include <libubox/blobmsg_json.h>
#include <sys/resource.h>
#include <string.h>
#include <argp.h> 


IoTPConfig *config = NULL;
IoTPDevice *device = NULL;

volatile int interrupt = 0;




/* Signal handler - to support CTRL-C to quit */
void sigHandler(int signo) 
{
    signal(SIGINT, NULL);
    syslog(LOG_INFO, "Received signal: %d\n", signo);
    interrupt = 1;
}

void MQTTTraceCallback (int level, char * message)
{
    if ( level > 0 )
        syslog(LOG_INFO, "%s\n", message? message:"NULL");
    
}




void DeviceCreate(IoTPDevice **device,IoTPConfig *config)
{
    int rc =0;
    rc = IoTPDevice_create(device, config);
    if ( rc != 0 ) {
        syslog(LOG_ERR, " Failed to configure IoTP device: rc= %d\n", rc);
        CleanAll(*device,config,rc);
    }
}


void Deviceconnect(IoTPDevice **device,IoTPConfig *config)
{
    int rc = 0;
    rc = IoTPDevice_connect(*device);
    if ( rc != 0 ) {
        syslog(LOG_ERR,"Authentication failed, please try again");
        CleanAll(device, config,rc);
    }
} 
void DeviceSendEvent(IoTPDevice *device,IoTPConfig *config)
{   int i=0;
    int rc=0;
    struct ubus_context *ctx;
    struct MemoryD memory={0,0};
    rc = ConnectUbus(&ctx);
    if(rc){
        syslog(LOG_ERR, "Failed to connect to ubus\n");
        //goto cleanup;
        CleanAll(device,config,rc);
    }
    while(!interrupt){
        char data[255];
        rc = getmemoryinfo(&ctx, &memory);
        if(rc){
            syslog(LOG_ERR, "No memory received");
            //goto freeubus;
            CleanAll(device,config,rc);
        }

        syslog(LOG_INFO,"Data sent to ibm cloud iot platform is successfully");
        sprintf(data,"{\"Memory usage\":\"%0.2f MB / %0.2f MB\"}",((memory.total_memory-memory.free_memory)/1000000.0),memory.total_memory/1000000.0);
        rc = IoTPDevice_sendEvent(device,"status", data, "json", QoS0, NULL);
    }

    freeubus:
        ubus_free(ctx);
    // cleanup:
    //     CleanAll(device, config);
}


void DisconnectDevice(IoTPDevice *device,IoTPConfig *config)
{
    int rc=0;
    rc = IoTPDevice_disconnect(device);
    if ( rc != IOTPRC_SUCCESS ) {
        syslog(LOG_ERR, "Failed to disconnect from  Watson IoT Platform: rc=%d\n", rc);
        CleanAll(device, config,rc);
    }
   
        

}
