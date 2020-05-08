// WARNING: This test doesn't actually work yet. SendRequest comes back with some DNS error on the real PSP.


#include <common.h>
#include <pspnet.h>
#include <pspnet_adhocctl.h>
#include <psputility_netmodules.h>


extern "C" int main(int argc, char *argv[]) {
    int ctlinit,ctlterm,ctlcreate;

    int stacksize = 5120;
    int priority = 30;
    struct productStruct prod;

	checkpointNext("Init:");
	checkpoint("sceUtilityLoadNetModule common: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_COMMON));
	checkpoint("sceUtilityLoadNetModule adhoc: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_ADHOC));
	checkpoint("sceUtilityLoadNetModule inet: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_INET));

    checkpointNext("calling ctl term without init");
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());
    

	checkpointNext("Init and term all zeros product");
    memset(&prod,0,sizeof(prod));
    checkpoint("SceNetAdhocctlInit: %08x", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod));  // 1, 0 = unknown but works
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());
    
    checkpointNext("Init create and term 9 character product with japan region code first NPJH50588");
    prod.product[0] = 'N';
    prod.product[1] = 'P';
    prod.product[2] = 'J';
    prod.product[3] = 'H';
    prod.product[4] = '5';
    prod.product[5] = '0';
    prod.product[6] = '5';
    prod.product[7] = '8';
    prod.product[8] = '8';
    checkpoint("SceNetAdhocctlInit: %08x", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod));  // 1, 0 = unknown but works
    checkpoint("SceNetAdhocctlCreate: %08x groupname R01", ctlcreate = sceNetAdhocctlCreate("R01"));  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());

    checkpointNext("Init and term 8 character product");
    prod.product[0] = 'U';
    prod.product[1] = 'L';
    prod.product[2] = 'U';
    prod.product[3] = 'S';
    prod.product[4] = '1';
    prod.product[5] = '0';
    prod.product[6] = '3';
    prod.product[7] = '9';
    prod.product[8] = 0;
    checkpoint("SceNetAdhocctlInit: %08x", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod));  // 1, 0 = unknown but works
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());


    checkpointNext("Init Twice 9 character product");
    prod.product[0] = 'U';
    prod.product[1] = 'L';
    prod.product[2] = 'U';
    prod.product[3] = 'S';
    prod.product[4] = '1';
    prod.product[5] = '0';
    prod.product[6] = '3';
    prod.product[7] = '9';
    prod.product[8] = '1';
    checkpoint("First SceNetAdhocctlInit: %08x", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod));  // 1, 0 = unknown but works
    checkpoint("Second SceNetAdhocctlInit: %08x", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod)); 
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());


    //looks like we cannot change it on runtime or the product not listed in us region?
    checkpointNext("change stack size to 8192  and priority to 48 product ULUS10391 param then init");
    stacksize = 8192;
    priority = 48;
    prod.product[0] = 'U';
    prod.product[1] = 'L';
    prod.product[2] = 'U';
    prod.product[3] = 'S';
    prod.product[4] = '1';
    prod.product[5] = '0';
    prod.product[6] = '3';
    prod.product[7] = '9';
    prod.product[8] = '1';

    checkpoint("SceNetAdhocctlInit: %08x", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod));  
    checkpoint("SceNetAdhocctlCreate: %08x groupname MHP2Q000", ctlcreate = sceNetAdhocctlCreate("MHP2Q000"));  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());



    checkpointNext("Use the first inited product id again region code NPJH50588 but change stacksize and priority./a");
    prod.product[0] = 'N';
    prod.product[1] = 'P';
    prod.product[2] = 'J';
    prod.product[3] = 'H';
    prod.product[4] = '5';
    prod.product[5] = '0';
    prod.product[6] = '5';
    prod.product[7] = '8';
    prod.product[8] = '8';
    checkpoint("SceNetAdhocctlInit: %08x", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod));  // 1, 0 = unknown but works
    checkpoint("SceNetAdhocctlCreate: %08x groupname R02", ctlcreate = sceNetAdhocctlCreate("R02"));  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());


    checkpointNext("Reuse the first inited adhoc ctl params that worked");
    stacksize = 5120;
    priority = 30;
    prod.product[0] = 'N';
    prod.product[1] = 'P';
    prod.product[2] = 'J';
    prod.product[3] = 'H';
    prod.product[4] = '5';
    prod.product[5] = '0';
    prod.product[6] = '5';
    prod.product[7] = '8';
    prod.product[8] = '8';
    checkpoint("SceNetAdhocctlInit: %08x", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod));  // 1, 0 = unknown but works
    checkpoint("SceNetAdhocctlCreate: %08x groupname R01", ctlcreate = sceNetAdhocctlCreate("R01"));  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());


    checkpointNext("Cleanup module first try");    
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_INET));
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_ADHOC));
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_COMMON));


    checkpointNext("Load Module again and try to reinitiate the working adhocctl");  
    checkpoint("sceUtilityLoadNetModule common: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_COMMON));
	checkpoint("sceUtilityLoadNetModule adhoc: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_ADHOC));
	checkpoint("sceUtilityLoadNetModule inet: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_INET));



    checkpointNext("Try to cleanup by unload module and set the ctl again");
    stacksize = 8192;
    priority = 48;
    prod.product[0] = 'U';
    prod.product[1] = 'L';
    prod.product[2] = 'U';
    prod.product[3] = 'S';
    prod.product[4] = '1';
    prod.product[5] = '0';
    prod.product[6] = '3';
    prod.product[7] = '9';
    prod.product[8] = '1';
    checkpoint("SceNetAdhocctlInit: %08x stacksize : %d priority : %d product %s" , ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("SceNetAdhocctlCreate: %08x groupname MHP2Q000", ctlcreate = sceNetAdhocctlCreate("MHP2Q000"));  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());


    checkpointNext("Reinit again after term with no params change");
    checkpoint("SceNetAdhocctlInit: %08x stacksize : %d priority : %d product %s" , ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("SceNetAdhocctlCreate: %08x groupname MHP2Q002", ctlcreate = sceNetAdhocctlCreate("MHP2Q002"));  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());


    checkpointNext("Cleanup exit");    
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_INET));
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_ADHOC));
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_COMMON));
    // etc...
	return 0;
}
