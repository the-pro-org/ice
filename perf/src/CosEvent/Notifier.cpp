// Notifier.cpp,v 1.4 2003/11/02 23:27:21 dhinton Exp

#include "orbsvcs/CosEventChannelAdminS.h"
#include "ace/OS_NS_unistd.h"
#include "ace/Date_Time.h"
#include "PerfC.h"
#include "PerfS.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Notifier
{
public:

    Notifier(void);
    int run (int argc, char* argv[]);
};

int
main (int argc, char* argv[])
{
    Notifier notifier;
    return notifier.run (argc, argv);
}

Notifier::Notifier (void)
{
}

int
Notifier::run (int argc, char* argv[])
{
    vector<string> iors;
    for(int i = 1; i < argc; i++)
    {
	if(strlen(argv[i]) > 3 && argv[i][0] == 'I' && argv[i][1] == 'O' && argv[i][2] == 'R')
	{
	    iors.push_back(argv[i]);
	}
    }

    ACE_DECLARE_NEW_CORBA_ENV;
    ACE_TRY
    {
	CORBA::ORB_var orb = CORBA::ORB_init (argc, argv, "" ACE_ENV_ARG_PARAMETER);
	ACE_TRY_CHECK;
	
	if (argc <= 1)
	{
	    ACE_ERROR ((LM_ERROR, "Usage: Notifier <event_channel_ior>\n"));
	    return 1;
	}

	vector<Perf::Sync_var> syncs;
	for(vector<string>::const_iterator p = iors.begin(); p != iors.end(); ++p)
	{
	    CORBA::Object_var object = orb->string_to_object (p->c_str() ACE_ENV_ARG_PARAMETER);
	    ACE_TRY_CHECK;
	    
	    Perf::Sync_var sync = Perf::Sync::_narrow(object.in() ACE_ENV_ARG_PARAMETER);
	    ACE_TRY_CHECK;
	    
	    syncs.push_back(Perf::Sync::_duplicate(sync.in()));
	}

	for(vector<Perf::Sync_var>::const_iterator p = syncs.begin(); p != syncs.end(); ++p)
	{
	    (*p)->notify();
	    ACE_TRY_CHECK;	
	}

	ACE_TRY_CHECK;	
    }
    ACE_CATCHANY
    {
	ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Notifier::run");
	return 1;
    }
    ACE_ENDTRY;
    return 0;
}

// ****************************************************************

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)
#elif defined(ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)
#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */
