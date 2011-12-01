#include "Control.h"

// DEFAULT CONSTRUCTOR
Control::Control() {
	// Initialize messaging
	msg = Messaging::Messaging();
	
	// Initialize database
	db = new Database("Database.sqlite");
	//db->query("CREATE TABLE floor (id INTEGER PRIMARY KEY, name TEXT, createDt INTEGER);");
	//db->query("DROP TABLE floor;");
}

// DEFAULT DESTRUCTOR
Control::~Control() {
	db->close();
}

// Inialize the building layout
void Control::initBldg() {

	/* Floor information [DATABASE ALREADY CONTAINS THIS INFORMATION -- DO NOT UNCOMMENT!]
	db->query("INSERT INTO floor (id, name, createDt) VALUES (1, 'Floor 1', datetime('now'));");
	db->query("INSERT INTO floor (id, name, createDt) VALUES (2, 'Floor 2', datetime('now'));");
	db->query("INSERT INTO floor (id, name, createDt) VALUES (3, 'Floor 3', datetime('now'));");
	*/

	//db->query("UPDATE floor SET createDt = datetime('now') WHERE id = 3;");

	vector<vector<string> > result = db->query("SELECT id, name, datetime(createDt) FROM floor;");
	for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
	{
		vector<string> row = *it;
		cout << "Values: (id=" << row.at(0) << ", name=" << row.at(1) << ", createDt=" << row.at(2) << ")" << endl;
	}
}
	
// PUBLIC CONTROL METHODS
void Control::fire_event(int zoneID) {

	string al_type = "fire";
		
	//Logging alarm in database
	log_alarm(zoneID, al_type);
		
	//Activating Audible Alarm
	audible_alarm(zoneID);
		
	//Activating Directional Indicators
	dir_indicator(zoneID);
		
	//Check if this is the only alarm
	//No real checks for people, UI will
	//auto update with no people and the 
	//session log will reflect that the
	//sprinklers are on and the power is off
	if (only_alarm(al_type)) {
			//Wait for 2 minutes, checking for a second alarm
			double time = 0;
			while (time < 2){
				if (!only_alarm(al_type)) {
						break;
				}
				// time = updated time
				//Check for people in the zone
				find_peps(zoneID);
			}
	}
		
	//notify athorities
	call_FD();
		
	//While alarm is active
	//This may cause a dely in the return statement, REVISIT this
	//Check for people in the zone
	find_peps(zoneID);
		
	//syslog("Timestamp: Fire event triggered in zone X");
	//Will will write this data to the session log, this does not
	//have to be a return String to the UI.
	
	//return ("Fire event triggered, system responding. . .");
}
	
void Control::fire_test_event(int zoneID) {
		
	// Activate Audible Alarm
	audible_alarm(zoneID);
		
	// Activate Directional Indicators
	dir_indicator(zoneID);

	// Create log information
	syslog(msg.FIRE_TEST_EVENT + zoneString(zoneID) + msg.ELLIPSIS);
}
	
string Control::security_event(int zoneID){
	string al_type = "security";
		
	//Logging alarm in database
	log_alarm(zoneID, al_type);
		
	//Activating Audible Alarm
	audible_alarm(zoneID);
		
	//Activating Directional Indicators
	lock_doors(zoneID);
		
	//Check if this is the only alarm
	if (only_alarm(al_type)) {
			//Wait for 2 minutes, checking for a second alarm
			double time = 0;
			while (time < 2){
				if (!only_alarm(al_type)) {
						break;
				}
			}
	}
		
	//notify athorities
	call_cops();
		
	//syslog("Timestamp: Security event triggered in zone X");
	return ("Security event triggered, system responding. . .");
}
	
void Control::security_test_event(int zoneID){
		
	// Activating Audible Alarm
	audible_alarm(zoneID);
		
	// Activating Directional Indicators
	lock_doors(zoneID);

	// Create log information	
	syslog(msg.SECURITY_TEST_EVENT + zoneString(zoneID) + msg.ELLIPSIS);
}
	
//Turns off all alarms in zone
void Control::turn_off(int zoneID, string password){
	if (password_ok(password)){
		disable_alarm(zoneID);
		disable_audio_alarm(zoneID);
		deact_directional(zoneID);
		sprink_off(zoneID);
		power_on(zoneID);
		unlock(zoneID);
		//syslog("Timestamp: Alarm resloved in zone X");
	} else {
		//error, password is incorrect
	}
}
	
//Turns off specific alarm in zone
void Control::turn_off(int zoneID, string password, string alarm_type){
	if (password_ok(password)){
		disable_alarm(zoneID, alarm_type);
		disable_audio_alarm(zoneID);
		deact_directional(zoneID);
		sprink_off(zoneID);
		power_on(zoneID);
		unlock(zoneID);
		//syslog("Timestamp: Alarm resloved in zone X");
	} else {
		//error, password is incorrect
	}
}
	
// PRIVATE METHODS
void Control::audible_alarm(int zoneID){
	// Turn on audio alarm

	// Create log information		
	syslog(msg.ACTIVATE_AUDIBLE_ALARM + zoneString(zoneID) + msg.ELLIPSIS);
}
	
void Control::dir_indicator(int zoneID){
	// Turn on directional indicators

	// Create log information		
	syslog(msg.ACTIVATE_DIRECTIONAL_INDICATORS + zoneString(zoneID) + msg.ELLIPSIS);
}
	
bool Control::only_alarm(string alarm_type) {
	bool retVal = true;
	//Check data base for existing alarm of this type.
	//If another alarm exists then retVal = false;
	return retVal;
}
	
void Control::lock_doors(int zoneID){
	//Lock all doors in zone passed
}
	
void Control::call_cops(){
	//Call Athorities
}
	
void Control::call_FD(){
	//Call Fire Department
}
	
void Control::sprink_on(int zoneID){
	//Turn sprinklers on in zone passed
}
	
void Control::power_off(int zoneID){
	//Turn power off in zone passed
}
	
void Control::find_peps(int zoneID){
	//Check database for people in zone
	//if (people are in zone)
	//do nothing
	//else
	power_off(zoneID);
	sprink_on(zoneID);
}
	
// Private methods used to turn off system
bool Control::password_ok(string password){
	//Check the database and verify that the password is correct
	//If the password is correct then
	return true;
	//else
	//return false;
}

void Control::disable_alarm(int zoneID){
	//Disables alarm in zone passed
}
	
void Control::disable_alarm(int zoneID, string alarm_type){
	//Disables specific alarm in zone passed
}
	
void Control::disable_audio_alarm(int zoneID){
	//Disabled audio alarm in zone passed
}
	
void Control::deact_directional(int zoneID){
	//Disabled directional indicators in zone passed
}
	
void Control::sprink_off(int zoneID){
	//Turns off sprinklers to zone passed
}
	
void Control::power_on(int zoneID){
	//Turns power back on in zone passed
}
	
void Control::unlock(int zoneID){
	//Unlocks the doors in zone passed
}
	
// SYSTEM LOGGING
void Control::syslog(string toConsole) {
	std::cout << toConsole << std::endl;
}
	
void Control::log_alarm(int zoneID, string alarm_type) {
	//Write to database the zone and alarm type
	//so the system can check if more than one alarm
	//is triggered at a time
}

string Control::zoneString(int zoneID) {
	stringstream ssLog;
	ssLog << zoneID;
	return ssLog.str();
}
