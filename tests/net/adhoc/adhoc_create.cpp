// WARNING: This test doesn't actually work yet. SendRequest comes back with some DNS error on the real PSP.
#include <common.h>
#include <pspthreadman.h>
#include <pspnet.h>
#include <pspnet_adhoc.h>
#include <pspnet_adhocctl.h>
#include <psputility_netmodules.h>
#include <iostream>
#include <string>
#include <pspctrl.h>


extern "C" int main(int argc, char *argv[]) {
    int ctlinit,ctlterm,ctlcreate,ctlconnect,ctlscan,ctlscaninfo,netinit,netterm;
    int adhocinit , getPeerList, adhocterm;

    int stacksize = 5120;
    int priority = 30;
    struct productStruct prod;
    std::string groupname;

    int buff_size = 2584;
    char * buf = (char *)malloc(2584);
    memset(buf,0,2584);



  
    struct SceNetAdhocctlScanInfo * scan_buf = (struct SceNetAdhocctlScanInfo *)malloc(sizeof(SceNetAdhocctlScanInfo));
    int scan_size = sizeof(SceNetAdhocctlScanInfo);

	// Previous Buttons
	uint32_t prev_buttons = 0;
	
	// Current Buttons
	uint32_t curr_buttons = 0;

    bool running = true;
    
    ctlinit = sceNetAdhocInit();


    checkpoint("Error : %s",strerror(ctlinit));
	checkpointNext("Load Module all net module test");
	checkpoint("sceUtilityLoadNetModule common: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_COMMON));
	checkpoint("sceUtilityLoadNetModule adhoc: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_ADHOC));
	checkpoint("sceUtilityLoadNetModule inet: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_INET));

    memset(&prod,0,sizeof(prod));
    strncpy(prod.product, "NPJH50588", 9);
    
    //net param based on mhfu
    int poolsize = 131072;
    int calloutprio = 32;
    int calloutstack = 0;
    int netintrprio = 32;
    int netintrstack = 0;
    
    checkpoint("sceNetInit : %08x",netinit = sceNetInit(poolsize,calloutprio,calloutstack,netintrprio,netintrstack));
    checkpoint("sceNetAdhocInit: %08x",adhocinit = sceNetAdhocInit());
    checkpoint("sceNetAdhocctlInit: %08x", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod)); 
    
    checkpoint("Pad CROSS to get peer List");
    checkpoint("Pad TRIANGLE to exit the test and send all buffer to host");
    checkpoint("Pad L_TRIGGER join control as creator maybe (host)");
    checkpoint("Pad R_TRIGGER join control as connector maybe (client)");
    
    checkpoint("Pad UP to Start Scan");
    checkpoint("Pad DOWN to Stop Scan");    
    checkpoint("Starting User PAD Input Loop");
    checkpointNext("Result of User Pad");

	SceCtrlData button_input;
    while(running){

        //move button
        prev_buttons = curr_buttons;
        sceCtrlPeekBufferPositive(&button_input, 1); 

        // register current button
        curr_buttons = button_input.Buttons;

        if((prev_buttons & PSP_CTRL_LTRIGGER) == 0 && (curr_buttons & PSP_CTRL_LTRIGGER) != 0) {
            checkpoint("sceNetAdhocctlCreate: %08x groupname R01", ctlcreate = sceNetAdhocctlCreate("R01"));  
            checkpoint("Joining as Creator");
            checkpointNext(NULL);
        }


        if((prev_buttons & PSP_CTRL_RTRIGGER) == 0 && (curr_buttons & PSP_CTRL_RTRIGGER) != 0) {
            checkpoint("sceNetAdhocctlConnect: %08x groupname R01", ctlconnect = sceNetAdhocctlConnect("R01"));  
            checkpoint("Joining as Connector");
            checkpointNext(NULL);
        }

        //this a tap and thats what we looking for
        if((prev_buttons & PSP_CTRL_CROSS) == 0 && (curr_buttons & PSP_CTRL_CROSS) != 0) {
            buff_size = 2584;
            getPeerList = sceNetAdhocctlGetPeerList(&buff_size,buf);
            checkpoint("SceNetAdhocctlGetPeerList : %08x",getPeerList);
            checkpointNext(NULL);
        }

        if((prev_buttons & PSP_CTRL_UP) == 0 && (curr_buttons & PSP_CTRL_UP) != 0) {
            ctlscan = sceNetAdhocctlScan();
            checkpoint("SceNetAdhocctlScan : %08x",ctlscan);
            checkpointNext(NULL);
        }

        if((prev_buttons & PSP_CTRL_DOWN) == 0 && (curr_buttons & PSP_CTRL_DOWN) != 0) {
            scan_size = sizeof(SceNetAdhocctlScanInfo);
            ctlscaninfo = sceNetAdhocctlGetScanInfo(&scan_size,scan_buf);
            checkpoint("sceNetAdhocctlGetScanInfo : %08x",ctlscaninfo);
            checkpoint("scan buf %s",scan_buf->name);
            checkpointNext(NULL);
        }

        if((prev_buttons & PSP_CTRL_SQUARE) == 0 && (curr_buttons & PSP_CTRL_SQUARE) != 0) {
        }



        if((prev_buttons & PSP_CTRL_TRIANGLE) == 0 && (curr_buttons & PSP_CTRL_TRIANGLE) != 0) {
            running = false;
        }
        
        // neeed to delay thread so adhoctl module start the networking part
        sceKernelDelayThread(1000);
        //checkpointNext("In the Loop");
    }
    
    checkpointNext(NULL);
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());
    checkpoint("sceNetAdhocTerm : %08x", adhocterm = sceNetAdhocTerm());
    checkpoint("sceNetTerm : %08x",netterm = sceNetTerm());
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_INET));
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_ADHOC));
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_COMMON));


    // etc...
	return 0;
}
