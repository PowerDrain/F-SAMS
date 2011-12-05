#ifndef MESSAGING_H
#define MESSAGING_H

#include <string>
using namespace std;

class Messaging {

public:
	string FIRE_EVENT;
	string FIRE_TEST_EVENT;
	string SECURITY_EVENT;
	string SECURITY_TEST_EVENT;
	string DISABLE_ALARM;
	string DISABLE_ALARM_TYPE;

	string CLEAR_BUILDING;
	string CALL_POLICE_WARNING;
	string CALL_POLICE;
	string CALL_FIRE_DEPARTMENT_WARNING;
	string CALL_FIRE_DEPARTMENT;
	string ACTIVATE_AUDIBLE_ALARM;
	string DEACTIVATE_AUDIBLE_ALARM;
	string ACTIVATE_DIRECTIONAL_INDICATORS;	
	string DEACTIVATE_DIRECTIONAL_INDICATORS;
	string SPRINKLER_ON;
	string SPRINKLER_OFF;
	string POWER_ON;
	string POWER_OFF;
	string DOORS_LOCKED;
	string DOORS_UNLOCKED;

	string ALARM_TYPE_FIRE;
	string ALARM_TYPE_FIRE_TEST;
	string ALARM_TYPE_SECURITY;
	string ALARM_TYPE_SECURITY_TEST;
	string CORRECT_PASSWORD;
	string INCORRECT_PASSWORD;
	string ELLIPSIS;

	// DEFAULT CONSTRUCTOR
	Messaging::Messaging() {
		FIRE_EVENT							= "Fire event triggered in Zone ";
		FIRE_TEST_EVENT						= "Fire Test event triggered in Zone ";
		SECURITY_EVENT						= "Security event triggered in Zone ";
		SECURITY_TEST_EVENT					= "Security Test event triggered in Zone ";
		DISABLE_ALARM						= "All alarms DISABLED in Zone ";
		DISABLE_ALARM_TYPE					= "alarms DISABLED in Zone ";

		CLEAR_BUILDING						= "The building is clear of people";
		CALL_POLICE_WARNING					= "The Police Station will be called in 2 MINUTES via 9-1-1";
		CALL_POLICE							= "Contacting the Police Station via 9-1-1";
		CALL_FIRE_DEPARTMENT_WARNING		= "The Fire Department will be called in 2 MINUTES via 9-1-1";
		CALL_FIRE_DEPARTMENT				= "Contacting the Fire Department via 9-1-1";
		ACTIVATE_AUDIBLE_ALARM				= "Audible alarm ACTIVATED in Zone ";
		DEACTIVATE_AUDIBLE_ALARM			= "Audible alarm DEACTIVATED in Zone ";
		ACTIVATE_DIRECTIONAL_INDICATORS		= "Directional Indicators ACTIVATED in Zone ";
		DEACTIVATE_DIRECTIONAL_INDICATORS	= "Directional Indicators DEACTIVATED in Zone ";
		SPRINKLER_ON						= "Sprinkler System turned ON in Zone ";
		SPRINKLER_OFF						= "Sprinkler System turned OFF in Zone ";
		POWER_ON							= "Power turned ON in Zone ";
		POWER_OFF							= "Power turned OFF in Zone ";
		DOORS_LOCKED						= "Doors LOCKED in Zone ";
		DOORS_UNLOCKED						= "Doors UNLOCKED in Zone ";

		ALARM_TYPE_FIRE						= "Fire";
		ALARM_TYPE_FIRE_TEST				= "Fire Test";
		ALARM_TYPE_SECURITY					= "Security";
		ALARM_TYPE_SECURITY_TEST			= "Security Test";
		CORRECT_PASSWORD					= "Password accepted";
		INCORRECT_PASSWORD					= "Incorrect password entered";
		ELLIPSIS							= "...";
	}

};

#endif