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
	void fire_test_event(int);
	string security_event(int zoneID);
	void security_test_event(int);
	void turn_off(int zoneID, string password);
	void turn_off(int zoneID, string password, string alarm_type);

private:
	// PRIVATE METHODS
	void audible_alarm(int);
	void dir_indicator(int);
	bool only_alarm(string alarm_type);
	void lock_doors(int zoneID);
	void call_cops();
	void call_FD();
	void sprink_on(int zoneID);
	void power_off(int zoneID);
	void find_peps(int zoneID);
	// Private methods used to turn off system
	bool password_ok(string password);
	void disable_alarm(int zoneID);
	void disable_alarm(int zoneID, string alarm_type);
	void disable_audio_alarm(int zoneID);
	void deact_directional(int zoneID);
	void sprink_off(int zoneID);
	void power_on(int zoneID);
	void unlock(int zoneID);
	// SYSTEM LOGGING
	void syslog(string);
	void log_alarm(int zoneID, string alarm_type);
	string zoneString(int);

};

#endif
