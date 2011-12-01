#ifndef MESSAGING_H
#define MESSAGING_H

#include <string>
using namespace std;

class Messaging {

public:
	string FIRE_TEST_EVENT;
	string SECURITY_TEST_EVENT;

	string ACTIVATE_AUDIBLE_ALARM;
	string ACTIVATE_DIRECTIONAL_INDICATORS;

	string ALARM_TYPE_FIRE;
	string ALARM_TYPE_SECURITY;
	string ELLIPSIS;

	// DEFAULT CONSTRUCTOR
	Messaging::Messaging() {
		FIRE_TEST_EVENT					= "Fire Test event triggered in Zone ";
		SECURITY_TEST_EVENT				= "Security Test event triggered in Zone ";

		ACTIVATE_AUDIBLE_ALARM			= "Audible alarm activated in Zone ";
		ACTIVATE_DIRECTIONAL_INDICATORS	= "Directional Indicators activated in Zone ";

		ALARM_TYPE_FIRE					= "Fire";
		ALARM_TYPE_SECURITY				= "Security";
		ELLIPSIS						= " ...";
	}

};

#endif