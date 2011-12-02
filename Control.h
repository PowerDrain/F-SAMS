#ifndef CONTROL_H
#define CONTROL_H

#include <string>
#include <sstream>
#include <iostream>
#include <time.h>
#include "Messaging.h"
#include "Database.h"
using namespace std;

class Control {

	Messaging msg;
	Database *db;

public:
	// DEFAULT CONSTRUCTOR / DESTRUCTOR
	Control();
	~Control();

	// PUBLIC CONTROL METHODS
	void initBldg();
	void fire_event(int);
	void fire_test_event(int); // DONE!
	string security_event(int zoneID);
	void security_test_event(int); // DONE!
	void turn_off(int zoneID, string password); // DONE!
	void turn_off(int zoneID, string password, string alarm_type); // DONE!

private:
	// PRIVATE METHODS
	bool only_alarm(string alarm_type); // DONE!
	void call_cops(); // DONE!
	void call_FD(); // DONE!
	void find_peps(int zoneID);
	bool password_ok(string password); // DONE!
	void disable_alarm(int zoneID); // DONE!
	void disable_alarm(int zoneID, string alarm_type); // DONE!

	void audible_alarm(int); // DONE!
	void disable_audio_alarm(int zoneID); // DONE!

	void dir_indicator(int); // DONE!
	void deact_directional(int zoneID); // DONE!

	void sprink_on(int zoneID); // DONE!
	void sprink_off(int zoneID); // DONE!

	void power_on(int zoneID); // DONE!
	void power_off(int zoneID); // DONE!

	void lock_doors(int zoneID); // DONE!
	void unlock_doors(int zoneID); // DONE!

	// SYSTEM LOGGING
	void syslog(string); // DONE!
	void log_alarm(int zoneID, string alarm_type); // DONE!
	string zoneString(int); // DONE!

};

#endif
