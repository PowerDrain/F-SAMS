#ifndef CONTROL_H
#define CONTROL_H

#include <string>
using namespace std;

class Control {

public:
	Control();
	// Public control methods
	string fire_event(int zoneID);
	string fire_test_event(int zoneID);
	string security_event(int zoneID);
	string security_test_event(int zoneID);
	void turn_off(int zoneID, string password);
	void turn_off(int zoneID, string password, string alarm_type);

private:
	// Private methods
	void audible_alarm(int zoneID);
	void dir_indicator(int zoneID);
	bool only_alarm(string alarm_type);
	void lock_doors(int zoneID);
	void call_cops();
	void call_FD();
	void sprink_on(int zoneID);
	void power_off(int zoneID);
	void find_peps(int zoneID);
	void log_alarm(int zoneID, string alarm_type);
	// Private methods used to turn off system
	bool password_ok(string password);
	void disable_alarm(int zoneID);
	void disable_alarm(int zoneID, string alarm_type);
	void disable_audio_alarm(int zoneID);
	void deact_directional(int zoneID);
	void sprink_off(int zoneID);
	void power_on(int zoneID);
	void unlock(int zoneID);
	void syslog(string event);

};

#endif
