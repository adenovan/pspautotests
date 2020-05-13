// WARNING: This test doesn't actually work yet. SendRequest comes back with some DNS error on the real PSP.


#include <common.h>
#include <pspnet.h>
#include <pspnet_adhoc.h>
#include <pspnet_adhocctl.h>
#include <psputility_netmodules.h>
#include <iostream>
#include <string>
#include <pspctrl.h>

extern "C" int main(int argc, char *argv[]) {
    int ctlinit,ctlterm,ctlcreate;
    int adhocinit , getPeerList, adhocterm;

    int stacksize = 5120;
    int priority = 30;
    struct productStruct prod;
    std::string groupname;

    int buff_size = 0;
    void * buf = malloc(2584);
    memset(buf,0,2584);


    

	checkpointNext("Load Module first adhocctl test");
	checkpoint("sceUtilityLoadNetModule common: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_COMMON));
	checkpoint("sceUtilityLoadNetModule adhoc: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_ADHOC));
	checkpoint("sceUtilityLoadNetModule inet: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_INET));

    memset(&prod,0,sizeof(prod));
    strncpy(prod.product, "NPJH50588", 9);
    
    checkpoint("sceNetAdhocInit: %08x",adhocinit = sceNetAdhocInit());
    checkpoint("sceNetAdhocctlInit: %08x", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod)); 
    checkpoint("sceNetAdhocctlCreate: %08x groupname R01", ctlcreate = sceNetAdhocctlCreate("R01"));  

	SceCtrlData buttonInput;
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
    while(running){
        sceCtrlPeekBufferPositive(&buttonInput, 1); 
        if(buttonInput.Buttons != 0) {
            if(buttonInput.Buttons & PSP_CTRL_CROSS){
                getPeerList = sceNetAdhocctlGetPeerList(&buff_size,buf);
                checkpointNext("SceNetAdhocctlGetPeerList : %08x",getPeerList);
            }

            if(buttonInput.Buttons & PSP_CTRL_TRIANGLE){
                running = false;
            }; 
        }
    }

    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());
    checkpoint("sceNetAdhocTerm : %08x", adhocterm = sceNetAdhocTerm());
  
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_INET));
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_ADHOC));
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_COMMON));


    // etc...
	return 0;
}
