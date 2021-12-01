#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "iotp_device.h"
#include <libubus.h>
#include "invoke.h"
#include "logscleanup.h"
#include <syslog.h>
#include <libubox/blobmsg_json.h>
#include <sys/resource.h>
#include <string.h>
#include <argp.h> 
#include "arguments.h"
#include "configs.h"
#include "deviceConnections.h"

#define OPT_ABORT  1            /* –abort */

static struct argp_option options[] = {
  {"orgId",    'o',"OrgId", 0,  "Org id" },
  {"typeId",   't',"TypeID", 0,  "Type id" },
  {"DeviceId", 'd',"DeviceId", 0,  "DeviceId"},
  {"AuthToken",'a',"AuthToken", 0,  "Auth token" },
  {"abort",    OPT_ABORT, 0, 0, "Abort before showing any output"},
  { 0 }
};

void sigHandler(int signo);
static error_t parse_opt (int key, char *arg, struct argp_state *state);

const char *argp_program_version ="ibm_program - 1.0.0-1";
const char *argp_program_bug_address ="<viliusbernikas@teltonika.lt>";

static char doc[] ="IBM_program";

static char args_doc[] = "ARG1 [STRING...]";

static struct argp argp = { options, parse_opt, args_doc, doc }; 

int main(int argc,char *argv[])
{

    struct arguments args = {0};
    
    argp_parse(&argp,argc,argv,0,0,&args);

    IoTPConfig *config = NULL;
    IoTPDevice *device = NULL;
 
    signal(SIGINT, sigHandler);
    signal(SIGTERM, sigHandler);
    CreateConfigs(&config, args);

    DeviceCreate(&device,config);
    Deviceconnect(&device,config);

  
    DeviceSendEvent(device,config);
      
    DisconnectDevice(device,config);
    CleanAll(device,config,EXIT_SUCCESS);
    exit(0);

}


static error_t parse_opt (int key, char *arg, struct argp_state *state)
{
    struct arguments *arguments = state->input;
    switch (key){
        case 'o': 
        {   
            arguments->orgid = arg;
            break;
          
        }
        case 't':
        {
             arguments->typeid = arg;
             break;
            
        }
        case 'd':
        {
            arguments->devid = arg;
            break;
           
        }
        case 'a':
        {
            arguments->authtoken = arg;
            break;
          
        }
        // case ARGP_KEY_NO_ARGS:
        // {
        //     argp_usage (state);
        //     break;
        // }

    
 }
 return 0;
} 