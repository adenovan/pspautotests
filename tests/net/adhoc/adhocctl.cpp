// WARNING: This test doesn't actually work yet. SendRequest comes back with some DNS error on the real PSP.


#include <common.h>
#include <pspnet.h>
#include <pspnet_adhocctl.h>
#include <psputility_netmodules.h>
#include <iostream>
#include <string>


extern "C" int main(int argc, char *argv[]) {
    int ctlinit,ctlterm,ctlcreate,ctlconnect;

    int stacksize = 5120;
    int priority = 30;
    struct productStruct prod;

    std::string groupname;

	checkpointNext("Load Module first adhocctl test");
	checkpoint("sceUtilityLoadNetModule common: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_COMMON));
	checkpoint("sceUtilityLoadNetModule adhoc: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_ADHOC));
	checkpoint("sceUtilityLoadNetModule inet: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_INET));

    checkpointNext("calling ctl term without init");
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());
    

	checkpointNext("Init and term all zeros product");
    memset(&prod,0,sizeof(prod));
    checkpoint("SceNetAdhocctlInit: %08x", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod));  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());
    
    checkpointNext("Init create and term 9 character product with japan region code first NPJH50588");

    strncpy(prod.product, "NPJH50588", 9);
    
    checkpoint("SceNetAdhocctlInit: %08x", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod)); 
    checkpoint("SceNetAdhocctlCreate: %08x groupname R01", ctlcreate = sceNetAdhocctlCreate("R01"));  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());

    checkpointNext("Init and term 8 character product");    
    memset(&prod,0,sizeof(prod));
    strncpy(prod.product,"NPJH5058",8);
    checkpoint("SceNetAdhocctlInit: %08x", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod));  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());


    checkpointNext("Cleanup module first Test");    
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_INET));
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_ADHOC));
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_COMMON));




	checkpointNext("Load Module for second adhocctl test");
	checkpoint("sceUtilityLoadNetModule common: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_COMMON));
	checkpoint("sceUtilityLoadNetModule adhoc: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_ADHOC));
	checkpoint("sceUtilityLoadNetModule inet: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_INET));


    checkpointNext("Init Twice 9 character product");
    
    strncpy(prod.product, "ULUS10391", 9);
    stacksize = 8192;
    priority = 48;
    
    checkpoint("First SceNetAdhocctlInit: %08x", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod));  
    checkpoint("Second SceNetAdhocctlInit: %08x", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod)); 
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());

    checkpointNext("Cleanup module second Test");    
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_INET));
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_ADHOC));
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_COMMON));




	checkpointNext("Load Module third adhocctl test");
	checkpoint("sceUtilityLoadNetModule common: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_COMMON));
	checkpoint("sceUtilityLoadNetModule adhoc: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_ADHOC));
	checkpoint("sceUtilityLoadNetModule inet: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_INET));


    stacksize = 5120;
    priority = 30;
    strncpy(prod.product, "NPJH50588", 9);

    groupname = "R01";

    checkpoint("SceNetAdhocctlInit: %08x stacksize %d priority %d", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority);  
    checkpoint("SceNetAdhocctlCreate: %08x groupname %s", ctlcreate = sceNetAdhocctlCreate(groupname.c_str()),groupname.c_str());  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());



    checkpointNext("Keep Product Name change stack size and priority");

    stacksize = 8192;
    priority = 48;
    groupname = "R02";
    checkpoint("SceNetAdhocctlInit: %08x stacksize %d priority %d", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority);  
    checkpoint("SceNetAdhocctlCreate: %08x groupname %s", ctlcreate = sceNetAdhocctlCreate(groupname.c_str()),groupname.c_str());  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());



    checkpointNext("Cleanup module third Test");    
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_INET));
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_ADHOC));
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_COMMON));



	checkpointNext("Load Module again for fourth adhocctl test");
	checkpoint("sceUtilityLoadNetModule common: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_COMMON));
	checkpoint("sceUtilityLoadNetModule adhoc: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_ADHOC));
	checkpoint("sceUtilityLoadNetModule inet: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_INET));


    checkpointNext("Initialize fourth working adhoc");
    stacksize = 5120;
    priority = 30;
    strncpy(prod.product, "NPJH50588", 9);
    groupname = "R01";

    checkpoint("SceNetAdhocctlInit: %08x stacksize %d priority %d product %s", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("SceNetAdhocctlCreate: %08x groupname %s", ctlcreate = sceNetAdhocctlCreate(groupname.c_str()),groupname.c_str());  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());

    checkpointNext("Change product id fourth working adhoc stacksize and priority with same groupname");
    strncpy(prod.product, "ULUS10391", 9);
    stacksize = 8192;
    priority = 48;
    checkpoint("SceNetAdhocctlInit: %08x stacksize %d priority %d product %s", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("SceNetAdhocctlCreate: %08x groupname %s", ctlcreate = sceNetAdhocctlCreate(groupname.c_str()),groupname.c_str());  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());

    checkpointNext("Change product id fourth working adhoc stacksize and priority with same different groupname");
    strncpy(prod.product, "ULUS10391", 9);
    stacksize = 8192;
    priority = 48;
    groupname = "MHP2Q000";
    checkpoint("SceNetAdhocctlInit: %08x stacksize %d priority %d product %s", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("SceNetAdhocctlCreate: %08x groupname %s", ctlcreate = sceNetAdhocctlCreate(groupname.c_str()),groupname.c_str());  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());

    checkpointNext("Reinit product id back to original and change stack size");
    strncpy(prod.product, "NPJH50588", 9);
    stacksize = 5120;
    priority = 30;
    checkpoint("SceNetAdhocctlInit: %08x stacksize %d priority %d product %s", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("SceNetAdhocctlCreate: %08x groupname %s", ctlcreate = sceNetAdhocctlCreate(groupname.c_str()),groupname.c_str());  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());



    checkpointNext("Call SceNetAdhocctlInit Twice");
    strncpy(prod.product, "NPJH50588", 9);
    stacksize = 5120;
    priority = 30;
    checkpoint("SceNetAdhocctlInit: %08x stacksize %d priority %d product %s", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("SceNetAdhocctlInit: %08x stacksize %d priority %d product %s", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("SceNetAdhocctlCreate: %08x groupname %s", ctlcreate = sceNetAdhocctlCreate(groupname.c_str()),groupname.c_str());  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());


    checkpointNext("Change product second times after twice init");
    strncpy(prod.product, "ULUS10391", 9);
    stacksize = 8192;
    priority = 48;
    groupname = "MHP2Q000";
    checkpoint("SceNetAdhocctlInit: %08x stacksize %d priority %d product %s", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("SceNetAdhocctlCreate: %08x groupname %s", ctlcreate = sceNetAdhocctlCreate(groupname.c_str()),groupname.c_str());  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());


    checkpointNext("Cleanup module fourth test try");    
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_INET));
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_ADHOC));
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_COMMON));



	checkpointNext("Load Module again for fifth adhocctl test");
	checkpoint("sceUtilityLoadNetModule common: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_COMMON));
	checkpoint("sceUtilityLoadNetModule adhoc: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_ADHOC));
	checkpoint("sceUtilityLoadNetModule inet: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_INET));

    checkpointNext("Initialize fifth working adhoc");
    stacksize = 5120;
    priority = 30;
    strncpy(prod.product, "NPJH50588", 9);
    groupname = "R01";

    checkpoint("SceNetAdhocctlInit: %08x stacksize %d priority %d product %s", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("SceNetAdhocctlCreate: %08x groupname %s", ctlcreate = sceNetAdhocctlCreate(groupname.c_str()),groupname.c_str());  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());

    checkpointNext("Change product id fourth working adhoc stacksize and priority with same groupname");
    strncpy(prod.product, "ULUS10391", 9);
    stacksize = 8192;
    priority = 48;
    checkpoint("SceNetAdhocctlInit: %08x stacksize %d priority %d product %s", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("SceNetAdhocctlCreate: %08x groupname %s", ctlcreate = sceNetAdhocctlCreate(groupname.c_str()),groupname.c_str());  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());

    checkpointNext("Change product id fourth working adhoc stacksize and priority with same different groupname");
    strncpy(prod.product, "ULUS10391", 9);
    stacksize = 8192;
    priority = 48;
    groupname = "MHP2Q000";
    checkpoint("SceNetAdhocctlInit: %08x stacksize %d priority %d product %s", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("SceNetAdhocctlCreate: %08x groupname %s", ctlcreate = sceNetAdhocctlCreate(groupname.c_str()),groupname.c_str());  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());

    checkpointNext("Reinit product id back to original and change stack size");
    strncpy(prod.product, "NPJH50588", 9);
    stacksize = 5120;
    priority = 30;
    checkpoint("SceNetAdhocctlInit: %08x stacksize %d priority %d product %s", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("SceNetAdhocctlCreate: %08x groupname %s", ctlcreate = sceNetAdhocctlCreate(groupname.c_str()),groupname.c_str());  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());



    checkpointNext("Call SceNetAdhocctlInit Twice and term twice");
    strncpy(prod.product, "NPJH50588", 9);
    stacksize = 5120;
    priority = 30;
    checkpoint("SceNetAdhocctlInit: %08x stacksize %d priority %d product %s", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("SceNetAdhocctlInit: %08x stacksize %d priority %d product %s", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("SceNetAdhocctlCreate: %08x groupname %s", ctlcreate = sceNetAdhocctlCreate(groupname.c_str()),groupname.c_str());  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());

    checkpointNext("Change product second times after twice init and term twice");
    strncpy(prod.product, "ULUS10391", 9);
    stacksize = 8192;
    priority = 48;
    groupname = "MHP2Q000";
    checkpoint("SceNetAdhocctlInit: %08x stacksize %d priority %d product %s", ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("SceNetAdhocctlCreate: %08x groupname %s", ctlcreate = sceNetAdhocctlCreate(groupname.c_str()),groupname.c_str());  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());


    checkpointNext("Cleanup module fifth test try");    
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_INET));
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_ADHOC));
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_COMMON));



    checkpointNext("six Adhoc ctl testing the groupname loading module");  
    checkpoint("sceUtilityLoadNetModule common: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_COMMON));
	checkpoint("sceUtilityLoadNetModule adhoc: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_ADHOC));
	checkpoint("sceUtilityLoadNetModule inet: %08x", sceUtilityLoadNetModule(PSP_NET_MODULE_INET));

    stacksize = 8192;
    priority = 48;
    strncpy(prod.product, "ULUS10391", 9);
    checkpoint("SceNetAdhocctlInit: %08x stacksize : %d priority : %d product %s" , ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("SceNetAdhocctlCreate: %08x groupname $s", ctlcreate = sceNetAdhocctlCreate(groupname.c_str()),groupname.c_str());  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());


    groupname = "MHP2Q002";
    checkpointNext("Reinit again after term with no params change");
    checkpoint("SceNetAdhocctlInit: %08x stacksize : %d priority : %d product %s" , ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("SceNetAdhocctlCreate: %08x groupname %s", ctlcreate = sceNetAdhocctlCreate(groupname.c_str()),groupname.c_str());  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());


    groupname = "MHP2Q002";
    checkpointNext("What happens if we call create two times?");
    checkpoint("SceNetAdhocctlInit: %08x stacksize : %d priority : %d product %s" , ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("SceNetAdhocctlCreate: %08x groupname %s", ctlcreate = sceNetAdhocctlCreate(groupname.c_str()),groupname.c_str());  
    checkpoint("SceNetAdhocctlCreate: %08x groupname %s", ctlcreate = sceNetAdhocctlCreate(groupname.c_str()),groupname.c_str()); 
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());

    
    groupname = "MHP2Q0021";
    checkpointNext("Longer group name than 8 character");
    checkpoint("SceNetAdhocctlInit: %08x stacksize : %d priority : %d product %s" , ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("SceNetAdhocctlCreate: %08x groupname %s groupnamelength %d", ctlcreate = sceNetAdhocctlCreate(groupname.c_str()),groupname.c_str(),groupname.length());  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());

    groupname = "MHP2Q00211";
    checkpoint("SceNetAdhocctlInit: %08x stacksize : %d priority : %d product %s" , ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("SceNetAdhocctlCreate: %08x groupname %s groupnamelength %d", ctlcreate = sceNetAdhocctlCreate(groupname.c_str()),groupname.c_str(),groupname.length());  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());

    groupname = "MHP2Q002112";
    checkpoint("SceNetAdhocctlInit: %08x stacksize : %d priority : %d product %s" , ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("SceNetAdhocctlCreate: %08x groupname %s groupnamelength %d", ctlcreate = sceNetAdhocctlCreate(groupname.c_str()),groupname.c_str(),groupname.length());  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());

    groupname = "MHP2Q0021123";
    checkpoint("SceNetAdhocctlInit: %08x stacksize : %d priority : %d product %s" , ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("SceNetAdhocctlCreate: %08x groupname %s groupnamelength %d", ctlcreate = sceNetAdhocctlCreate(groupname.c_str()),groupname.c_str(),groupname.length());  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());

    groupname = "MHP2Q00211234";
    checkpoint("SceNetAdhocctlInit: %08x stacksize : %d priority : %d product %s" , ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("SceNetAdhocctlCreate: %08x groupname %s groupnamelength %d", ctlcreate = sceNetAdhocctlCreate(groupname.c_str()),groupname.c_str(),groupname.length());  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());

    groupname = "MHP2Q002112345";
    checkpoint("SceNetAdhocctlInit: %08x stacksize : %d priority : %d product %s" , ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("SceNetAdhocctlCreate: %08x groupname %s groupnamelength %d", ctlcreate = sceNetAdhocctlCreate(groupname.c_str()),groupname.c_str(),groupname.length());  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());
    

    groupname = "MHP2Q002";
    checkpointNext("Can we call connect after create?");
    checkpoint("SceNetAdhocctlInit: %08x stacksize : %d priority : %d product %s" , ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("SceNetAdhocctlCreate: %08x groupname %s groupnamelength %d", ctlcreate = sceNetAdhocctlCreate(groupname.c_str()),groupname.c_str(),groupname.length()); 
    checkpoint("sceNetAdhocctlConnect: %08x groupname %s groupnamelength %d", ctlconnect = sceNetAdhocctlConnect(groupname.c_str()),groupname.c_str(),groupname.length());  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());

    
    checkpointNext("we call connect without someone creating the control");
    checkpoint("SceNetAdhocctlInit: %08x stacksize : %d priority : %d product %s" , ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("sceNetAdhocctlConnect: %08x groupname %s groupnamelength %d", ctlconnect = sceNetAdhocctlConnect(groupname.c_str()),groupname.c_str(),groupname.length());  
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());


    checkpointNext("we call create after connect in the control");
    checkpoint("SceNetAdhocctlInit: %08x stacksize : %d priority : %d product %s" , ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("sceNetAdhocctlConnect: %08x groupname %s groupnamelength %d", ctlconnect = sceNetAdhocctlConnect(groupname.c_str()),groupname.c_str(),groupname.length());
    checkpoint("SceNetAdhocctlCreate: %08x groupname %s groupnamelength %d", ctlcreate = sceNetAdhocctlCreate(groupname.c_str()),groupname.c_str(),groupname.length());
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());


    checkpointNext("we call create with null parameter");
    checkpoint("SceNetAdhocctlInit: %08x stacksize : %d priority : %d product %s" , ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("SceNetAdhocctlCreate: %08x groupname %s", ctlcreate = sceNetAdhocctlCreate(NULL),NULL);
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());

    checkpointNext("we call connect with null parameter");
    checkpoint("SceNetAdhocctlInit: %08x stacksize : %d priority : %d product %s" , ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    checkpoint("sceNetAdhocctlConnect: %08x groupname %s", ctlconnect = sceNetAdhocctlConnect(NULL),NULL);
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());


    checkpointNext("call create without init");
    checkpoint("SceNetAdhocctlCreate: %08x groupname %s groupnamelength %d", ctlcreate = sceNetAdhocctlCreate(groupname.c_str()),groupname.c_str(),groupname.length());

    checkpointNext("call connect without init");
    checkpoint("sceNetAdhocctlConnect: %08x groupname %s groupnamelength %d", ctlconnect = sceNetAdhocctlConnect(groupname.c_str()),groupname.c_str(),groupname.length());

    checkpointNext("Cleanup exit");    
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_INET));
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_ADHOC));
	checkpoint("sceUtilityUnloadModule: %08x", sceUtilityUnloadNetModule(PSP_NET_MODULE_COMMON));

    
    
    checkpointNext("call init without library linked");
    checkpoint("SceNetAdhocctlInit: %08x stacksize : %d priority : %d product %s" , ctlinit = sceNetAdhocctlInit(stacksize, priority, &prod),stacksize,priority,prod.product);  
    
    checkpointNext("call create when module unloaded");
    checkpoint("SceNetAdhocctlCreate: %08x groupname %s groupnamelength %d", ctlcreate = sceNetAdhocctlCreate(groupname.c_str()),groupname.c_str(),groupname.length());

    checkpointNext("call connect when module unloaded");
    checkpoint("sceNetAdhocctlConnect: %08x groupname %s groupnamelength %d", ctlconnect = sceNetAdhocctlConnect(groupname.c_str()),groupname.c_str(),groupname.length());


    checkpointNext("call Term when module unloaded");
    checkpoint("sceNetAdhocctlTerm: %08x", ctlterm = sceNetAdhocctlTerm());

    // etc...
	return 0;
}
