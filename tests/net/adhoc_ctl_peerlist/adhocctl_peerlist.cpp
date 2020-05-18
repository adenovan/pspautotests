// WARNING: This test doesn't actually work yet. SendRequest comes back with some DNS error on the real PSP.


#include <common.h>
#include <pspthreadman.h>
#include <pspnet.h>
#include <pspnet_adhoc.h>
#include <pspnet_adhocctl.h>
#include <psputility_netmodules.h>
#include <iostream>
#include <string>


extern "C" int main(int argc, char *argv[]) {
    int ctlinit,ctlterm,ctlcreate,ctlconnect;
    int netinit,netterm;
    int adhoc_init,adhoc_term;
    int getLocalEther,getPeerList;

    int stacksize = 5120;
    int priority = 30;
    struct productStruct prod;

    std::string groupname;

    unsigned char mac[6];
    memset(&mac,0,sizeof(mac));


    //net param based on mhfu
    int poolsize = 131072;
    int calloutprio = 32;
    int calloutstack = 0;
    int netintrprio = 32;
    int netintrstack = 0;
    int buff_size = 0;

    buff_size = 152;
    checkpoint("SceNetAdhocctlGetPeerList : %08x buffsize %d",getPeerList = sceNetAdhocctlGetPeerList(&buff_size,NULL),buff_size);


	checkpointNext("Load Module first adhocctl test");
	checkpoint("sceUtilityLoadNetModule common: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_COMMON));
	checkpoint("sceUtilityLoadNetModule adhoc: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_ADHOC));
	checkpoint("sceUtilityLoadNetModule inet: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_INET));

    buff_size = 152;
    checkpoint("SceNetAdhocctlGetPeerList : %08x buffsize %d",getPeerList = sceNetAdhocctlGetPeerList(&buff_size,NULL),buff_size);

    checkpoint("sceNetInit : %08x",netinit = sceNetInit(poolsize,calloutprio,calloutstack,netintrprio,netintrstack));

    buff_size = 152;
    checkpoint("SceNetAdhocctlGetPeerList : %08x buffsize %d",getPeerList = sceNetAdhocctlGetPeerList(&buff_size,NULL),buff_size);


    checkpointNext("Init NPJH50588");
    checkpoint("sceNetAdhocInit: %08x",adhoc_init = sceNetAdhocInit());

    buff_size = 152;
    checkpoint("SceNetAdhocctlGetPeerList : %08x buffsize %d",getPeerList = sceNetAdhocctlGetPeerList(&buff_size,NULL),buff_size);


    memset(&prod,0,sizeof(prod));
    strncpy(prod.product, "NPJH50588", 9);
    checkpoint("SceNetAdhocctlInit: %08x", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod)); 

    buff_size = 152;
    checkpoint("SceNetAdhocctlGetPeerList : %08x buffsize %d",getPeerList = sceNetAdhocctlGetPeerList(&buff_size,NULL),buff_size);

    checkpoint("SceNetAdhocctlGetPeerList : %08x buffsize %d",getPeerList = sceNetAdhocctlGetPeerList(NULL,NULL),NULL);

    //checkpoint("SceNetAdhocctlCreate: %08x groupname R01", ctlcreate = sceNetAdhocctlCreate("R01")); 
    checkpoint("sceNetAdhocctlConnect: %08x groupname R01", ctlconnect = sceNetAdhocctlConnect("R01"));  
    sceKernelDelayThread(500000);

    checkpoint("SceNetAdhocctlGetPeerList : %08x buffsize %d",getPeerList = sceNetAdhocctlGetPeerList(NULL,NULL),NULL);

    
    int i = 0;

    while(i<=1000){
        buff_size = 0;
        checkpoint("SceNetAdhocctlGetPeerList : %08x buffsize %d",getPeerList = sceNetAdhocctlGetPeerList(&buff_size,NULL),buff_size);
        if(getPeerList == 0){
                //struct SceNetAdhocctlPeerInfo * info = (SceNetAdhocctlPeerInfo *)buf;
                checkpoint("Buffsize after call %d i = %d",buff_size,i);        
                i++;
                // checkpoint("Peer info Next %p",info->next);
                // checkpoint("Peer Info nickname %s", info->nickname);
                // checkpoint("Peer Info mac %02X:%02X:%02X:%02X:%02X:%02X ",info->mac[0],info->mac[1],info->mac[2],info->mac[3],info->mac[4],info->mac[5]);
                // checkpoint("Peer Info unknown %02X:%02X:%02X:%02X:%02X:%02X ",info->unknown[0],info->unknown[1],info->unknown[2],info->unknown[3],info->unknown[4],info->unknown[5]);
                // checkpoint("Peer info timestamp %ul" ,info->timestamp);
                // checkpointNext(NULL);
        }
        sceKernelDelayThread(1000);
    }

    i = 0;

    while(i<=1000){
            char * buf = (char*)malloc(i);
            buff_size = i;
            if(buf != NULL){
                checkpoint("with buffer SceNetAdhocctlGetPeerList : %08x buffsize %d",getPeerList = sceNetAdhocctlGetPeerList(&buff_size,buf),buff_size);
                if(getPeerList == 0){
                    checkpoint("Buffsize after call %d i = %d",buff_size,i);    
                    if(buff_size >=152){
                        struct SceNetAdhocctlPeerInfo * info = (SceNetAdhocctlPeerInfo *)buf;
                        checkpoint("Peer info Next %p",info->next);
                        checkpoint("Peer Info nickname %s", info->nickname);
                        checkpoint("Peer Info mac %02X:%02X:%02X:%02X:%02X:%02X ",info->mac[0],info->mac[1],info->mac[2],info->mac[3],info->mac[4],info->mac[5]);
                        checkpoint("Peer Info unknown %02X:%02X:%02X:%02X:%02X:%02X ",info->unknown[0],info->unknown[1],info->unknown[2],info->unknown[3],info->unknown[4],info->unknown[5]);
                        checkpoint("Peer info timestamp %ul" ,info->timestamp);
                        checkpointNext(NULL);
                    }    
                    free(buf);
                    i++;
                }
            }

        sceKernelDelayThread(1000);
    }


    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());
    


    checkpointNext("Cleanup module");    
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());
    checkpoint("sceNetAdhocTerm: %08x",adhoc_term = sceNetAdhocTerm());
    checkpoint("sceNetTerm: %08x",netterm = sceNetTerm());
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_INET));
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_ADHOC));
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_COMMON));

    // etc...
	return 0;
}
