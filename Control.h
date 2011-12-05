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
	void fire_event(int); // DONE!
	void fire_test_event(int); // DONE!
	void security_event(int); // DONE!
	void security_test_event(int); // DONE!
	void turn_off(int, string); // DONE!
	void turn_off(int, string, string); // DONE!
	void clear_bldg(); // DONE!
	void active_alarms(); // DONE!

private:
	// PRIVATE METHODS
	bool only_alarm(string); // DONE!
	bool repeat_alarm(string, int); // DONE!
	void call_cops(); // DONE!
	void call_FD(); // DONE!
	bool floor_occupied(int); // DONE!
	bool password_ok(string); // DONE!
	void disable_alarm(int); // DONE!
	void disable_alarm(int, string); // DONE!

	void audible_alarm(int); // DONE!
	void disable_audio_alarm(int); // DONE!

	void dir_indicator(int); // DONE!
	void deact_directional(int); // DONE!

	void sprink_on(int); // DONE!
	void sprink_off(int); // DONE!

	void power_on(int); // DONE!
	void power_off(int); // DONE!

	void lock_doors(int); // DONE!
	void unlock_doors(int); // DONE!

	// SYSTEM LOGGING
	void syslog(string); // DONE!
	void log_alarm(int, string); // DONE!
	string zoneString(int); // DONE!

};

#endif
