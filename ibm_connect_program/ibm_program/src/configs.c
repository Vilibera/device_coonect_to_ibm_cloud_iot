#include <stdio.h>
#include <signal.h>
#include "arguments.h"
#include <stdlib.h>
#include <unistd.h>
#include "iotp_device.h"
#include "logscleanup.h"
#include <libubus.h>
#include "invoke.h"
#include <syslog.h>
#include "logscleanup.h"
#include <libubox/blobmsg_json.h>
#include <sys/resource.h>
#include <string.h>
#include <argp.h> 


void CreateConfigs(IoTPConfig **config,struct arguments args)
{
    int rc=0;
    rc = IoTPConfig_create(config, NULL);
        ConfigsCheck(rc,*config);
    rc=IoTPConfig_setProperty(*config, "identity.orgId" , args.orgid);
        ConfigsCheck(rc,*config);
    rc=IoTPConfig_setProperty(*config, "identity.typeId" , args.typeid);
        ConfigsCheck(rc,*config);
    rc=IoTPConfig_setProperty(*config, "identity.DeviceId" , args.devid);
        ConfigsCheck(rc,*config);
    rc=IoTPConfig_setProperty(*config, "auth.token" , args.authtoken);
        ConfigsCheck(rc,*config); 
}
void ConfigsCheck(int rc,IoTPConfig *config)
{
    int test=1007;
    if(rc==test){
        syslog(LOG_ERR, "Please fill all input fields rc=%d\n", rc);
        IoTPConfig_clear(config);
        closelogs(rc);
    }
    else if(rc!=0){
        syslog(LOG_ERR, "Failed to initialize configuration: rc=%d\n", rc);
        IoTPConfig_clear(config);
        closelogs(rc);
        
    }

}

