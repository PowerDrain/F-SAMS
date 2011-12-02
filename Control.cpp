#include "Control.h"

// DEFAULT CONSTRUCTOR
Control::Control() {
	// Initialize messaging
	msg = Messaging::Messaging();
	
	// Initialize database
	db = new Database("Database.sqlite");
}

// DEFAULT DESTRUCTOR
Control::~Control() {
	db->close();
}

// Inialize the building layout
void Control::initBldg() {

	/* Table Creation [DATABASE ALREADY CONTAINS THIS INFORMATION -- DO NOT UNCOMMENT!]
	db->query("CREATE TABLE floor (id INTEGER PRIMARY KEY, name TEXT, createDt INTEGER);");  
	db->query("CREATE TABLE zone (id INTEGER PRIMARY KEY, name TEXT, createDt INTEGER);");
	db->query("CREATE TABLE admin (id INTEGER PRIMARY KEY, username TEXT, password TEXT);");
	db->query("CREATE TABLE alarm (id INTEGER PRIMARY KEY AUTOINCREMENT, zoneID INTEGER, type TEXT, createDt INTEGER, resolveDt INTEGER);");

	// MISC. QUERIES
	db->query("UPDATE floor SET createDt = datetime('now') WHERE id = 3;");
	db->query("DROP TABLE <tablename>;");
	*/

	/* Initial table information [DATABASE ALREADY CONTAINS THIS INFORMATION -- DO NOT UNCOMMENT!]
	db->query("INSERT INTO floor (id, name, createDt) VALUES (1, 'Floor 1', datetime('now'));");
	db->query("INSERT INTO floor (id, name, createDt) VALUES (2, 'Floor 2', datetime('now'));");
	db->query("INSERT INTO floor (id, name, createDt) VALUES (3, 'Floor 3', datetime('now'));");
	*/

	/* Poop out a specific table */
	cout << "Alarms: " << endl;
	vector<vector<string> > result = db->query("SELECT * FROM alarm;");
	for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
	{
		vector<string> row = *it;
		cout << "ID: " << row.at(0) << ", Zone ID: " << row.at(1) << ", Type: " << row.at(2) << ", Created: " << row.at(3) << ", Resolved: " << row.at(4) <<endl;
	}
	cout << endl;
	
}
	
// PUBLIC CONTROL METHODS
void Control::fire_event(int zoneID) {

	string al_type = msg.ALARM_TYPE_FIRE;
		
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
	log_alarm(zoneID, msg.ALARM_TYPE_FIRE_TEST);
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
	log_alarm(zoneID, msg.ALARM_TYPE_FIRE_TEST);
}
	
void Control::turn_off(int zoneID, string password) {
	//Turns off all alarms in zone
	if (password_ok(password)) {

		disable_alarm(zoneID);
		disable_audio_alarm(zoneID);
		deact_directional(zoneID);
		sprink_off(zoneID);
		power_on(zoneID);
		unlock_doors(zoneID);

		// Create log information -- password correct
		syslog(msg.CORRECT_PASSWORD + msg.ELLIPSIS);
	} else {
		// Create log information -- password incorrect
		syslog(msg.INCORRECT_PASSWORD + msg.ELLIPSIS);
	}
}
	
void Control::turn_off(int zoneID, string password, string alarm_type) {
	//Turns off specific alarm in zone
	if (password_ok(password)) {

		disable_alarm(zoneID, alarm_type);
		disable_audio_alarm(zoneID);
		deact_directional(zoneID);
		sprink_off(zoneID);
		power_on(zoneID);
		unlock_doors(zoneID);
		
		// Create log information -- password correct
		syslog(msg.CORRECT_PASSWORD + msg.ELLIPSIS);
	} else {
		// Create log information -- password incorrect
		syslog(msg.INCORRECT_PASSWORD + msg.ELLIPSIS);
	}
}
	
// PRIVATE METHODS	
bool Control::only_alarm(string alarm_type) {
	// Check database for existing alarm of this type.
	string activeAlarm;
	string strquery = "SELECT count(*) FROM alarm WHERE (type = " + alarm_type + ") AND (resolveDt != 0);";
	char *query = strdup(strquery.c_str());
	vector<vector<string> > result = db->query(query);
	for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
	{
		vector<string> row = *it;
		activeAlarm = row.at(0);
	}
	//If the password is correct then return true
	return (activeAlarm == "0");
}
	
void Control::call_cops() {
	// Call Police

	// Create log information		
	syslog(msg.CALL_POLICE + msg.ELLIPSIS);
}
	
void Control::call_FD() {
	// Call Fire Department

	// Create log information		
	syslog(msg.CALL_FIRE_DEPARTMENT + msg.ELLIPSIS);
}
	
void Control::find_peps(int zoneID){
	//Check database for people in zone
	//if (people are in zone)
	//do nothing
	//else
	power_off(zoneID);
	sprink_on(zoneID);
}

bool Control::password_ok(string password) {
	//Check the database and verify that the password is correct
	string adminPassword;
	vector<vector<string> > result = db->query("SELECT password FROM admin;");
	for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
	{
		vector<string> row = *it;
		adminPassword = row.at(0);
	}
	//If the password is correct then return true
	return (password == adminPassword);
}

void Control::disable_alarm(int zoneID){
	//Disables alarm in zone passed
	string strquery = "UPDATE alarm SET resolveDt = datetime('now') WHERE (zoneID = " + zoneString(zoneID) + ") AND (resolveDt == 0);";
	char *query = strdup(strquery.c_str());
	db->query(query);

	// Create log information		
	syslog(msg.DISABLE_ALARM + zoneString(zoneID) + msg.ELLIPSIS);
}
	
void Control::disable_alarm(int zoneID, string alarm_type) {
	// Disables specific alarm in zone passed
	string strquery = "UPDATE alarm SET resolveDt = datetime('now') WHERE (zoneID = " + zoneString(zoneID) + ") AND (type = " + alarm_type + ") AND (resolveDt == 0);";
	char *query = strdup(strquery.c_str());
	db->query(query);

	// Create log information		
	syslog(alarm_type + msg.DISABLE_ALARM_TYPE + zoneString(zoneID) + msg.ELLIPSIS);
}

void Control::audible_alarm(int zoneID) {
	// Turn on audio alarm

	// Create log information		
	syslog(msg.ACTIVATE_AUDIBLE_ALARM + zoneString(zoneID) + msg.ELLIPSIS);
}
	
void Control::disable_audio_alarm(int zoneID) {
	//Disabled audio alarm in zone passed

	// Create log information		
	syslog(msg.DEACTIVATE_AUDIBLE_ALARM + zoneString(zoneID) + msg.ELLIPSIS);
}
	
void Control::dir_indicator(int zoneID){
	// Turn on directional indicators

	// Create log information		
	syslog(msg.ACTIVATE_DIRECTIONAL_INDICATORS + zoneString(zoneID) + msg.ELLIPSIS);
}
	
void Control::deact_directional(int zoneID){
	//Disabled directional indicators in zone passed

	// Create log information		
	syslog(msg.DEACTIVATE_DIRECTIONAL_INDICATORS + zoneString(zoneID) + msg.ELLIPSIS);
}
	
void Control::sprink_on(int zoneID) {
	//Turn sprinklers on in zone passed
	string strquery = "UPDATE zone SET sprinklered = 1 WHERE id = " + zoneString(zoneID) + ";";
	char *query = strdup(strquery.c_str());
	db->query(query);

	// Create log information		
	syslog(msg.SPRINKLER_ON + zoneString(zoneID) + msg.ELLIPSIS);
}
	
void Control::sprink_off(int zoneID) {
	//Turns off sprinklers to zone passed
	string strquery = "UPDATE zone SET sprinklered = 0 WHERE id = " + zoneString(zoneID) + ";";
	char *query = strdup(strquery.c_str());
	db->query(query);

	// Create log information		
	syslog(msg.SPRINKLER_OFF + zoneString(zoneID) + msg.ELLIPSIS);
}
	
void Control::power_on(int zoneID) {
	//Turns power back on in zone passed
	string strquery = "UPDATE zone SET powered = 1 WHERE id = " + zoneString(zoneID) + ";";
	char *query = strdup(strquery.c_str());
	db->query(query);

	// Create log information		
	syslog(msg.POWER_ON + zoneString(zoneID) + msg.ELLIPSIS);
}
	
void Control::power_off(int zoneID) {
	//Turn power off in zone passed
	string strquery = "UPDATE zone SET powered = 0 WHERE id = " + zoneString(zoneID) + ";";
	char *query = strdup(strquery.c_str());
	db->query(query);

	// Create log information		
	syslog(msg.POWER_OFF + zoneString(zoneID) + msg.ELLIPSIS);
}
	
void Control::lock_doors(int zoneID) {
	// Lock all doors in zone passed
	string strquery = "UPDATE zone SET locked = 1 WHERE id = " + zoneString(zoneID) + ";";
	char *query = strdup(strquery.c_str());
	db->query(query);

	// Create log information		
	syslog(msg.DOORS_LOCKED + zoneString(zoneID) + msg.ELLIPSIS);
}
	
void Control::unlock_doors(int zoneID) {
	// Unlocks the doors in zone passed
	string strquery = "UPDATE zone SET locked = 0 WHERE id = " + zoneString(zoneID) + ";";
	char *query = strdup(strquery.c_str());
	db->query(query);

	// Create log information		
	syslog(msg.DOORS_UNLOCKED + zoneString(zoneID) + msg.ELLIPSIS);
}
	
// SYSTEM LOGGING
void Control::syslog(string toConsole) {
	std::cout << toConsole << std::endl;
}
	
void Control::log_alarm(int zoneID, string alarm_type) {
	// Write to database the zone and alarm type so the system can check if more
	// than one alarm is triggered at a time.
	string strquery = "INSERT INTO alarm (zoneID, type, createDt, resolveDt) VALUES (" + zoneString(zoneID) + ", '" + alarm_type + "', datetime('now'), 0);";
	char *query = strdup(strquery.c_str());
	db->query(query);

	// Create log information		
	syslog("Alarm added to " + zoneString(zoneID) + msg.ELLIPSIS);
}

string Control::zoneString(int zoneID) {
	// Converts the zoneID to a usable string for messaging
	stringstream ssLog;
	ssLog << zoneID;
	return ssLog.str();
}
