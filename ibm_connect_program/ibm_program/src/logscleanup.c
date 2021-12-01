#include <syslog.h>
#include "iotp_device.h"

void closelogs(int rc) 
{
    closelog();
    if(rc==239)
        syslog(LOG_ERR,"Input field is empty, error code: %d",rc);
    else
        exit(rc);
}

void CleanAll(IoTPDevice *device,IoTPConfig *config,int rc)
{
    syslog(LOG_INFO,"ibm_program is cleaning up");
   /* Destroy client */
    IoTPDevice_destroy(device);
    /* Clear configuration */
    IoTPConfig_clear(config);
    closelogs(rc);
}
