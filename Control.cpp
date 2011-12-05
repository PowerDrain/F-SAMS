#include "Control.h"

// DEFAULT CONSTRUCTOR
Control::Control() {
	// Initialize messaging
	msg = Messaging::Messaging();
	
	// Initialize database
	db = new Database("Database.sqlite");

	// Populates all floors of the building
	string strquery = "UPDATE floor SET occupied = '1';";
	char *query = strdup(strquery.c_str());
	db->query(query);
}

// DEFAULT DESTRUCTOR
Control::~Control() {
	db->close();
}

// Inialize the building layout
void Control::initBldg() {

	/* Table Creation [DATABASE ALREADY CONTAINS THIS INFORMATION -- DO NOT UNCOMMENT!] */
	db->query("CREATE TABLE floor (id INTEGER PRIMARY KEY, name TEXT, occupied TEXT, createDt INTEGER);");  
	db->query("CREATE TABLE zone  (id INTEGER PRIMARY KEY, floorID INTEGER, name TEXT, powered TEXT, locked TEXT, sprinklered TEXT, createDt INTEGER);");
	db->query("CREATE TABLE room  (id INTEGER PRIMARY KEY, zoneID INTEGER, name TEXT, xpos INTEGER, ypos INTEGER, height INTEGER, width INTEGER, createDt INTEGER);");
	db->query("CREATE TABLE alarm (id INTEGER PRIMARY KEY AUTOINCREMENT, zoneID INTEGER, type TEXT, createDt INTEGER, resolveDt INTEGER);");
	db->query("CREATE TABLE admin (id INTEGER PRIMARY KEY, username TEXT, password TEXT);");	

	/* DROP QUERIES
	db->query("DROP TABLE floor;");
	db->query("DROP TABLE zone;");
	db->query("DROP TABLE room;");
	db->query("DROP TABLE alarm;");
	db->query("DROP TABLE admin;");
	*/

	/* Initial table information [DATABASE ALREADY CONTAINS THIS INFORMATION -- DO NOT UNCOMMENT!] */
	db->query("INSERT INTO floor (id, name, occupied, createDt) VALUES (1, 'Floor 1', 0, datetime('now'));");
	db->query("INSERT INTO floor (id, name, occupied, createDt) VALUES (2, 'Floor 2', 0, datetime('now'));");
	db->query("INSERT INTO floor (id, name, occupied, createDt) VALUES (3, 'Floor 3', 0, datetime('now'));");
	
	db->query("INSERT INTO zone (id, floorID, name, powered, locked, sprinklered, createDt) VALUES (1, 1, 'Zone 1', '1', '0', '0', datetime('now'));");
	db->query("INSERT INTO zone (id, floorID, name, powered, locked, sprinklered, createDt) VALUES (2, 1, 'Zone 2', '1', '0', '0', datetime('now'));");
	db->query("INSERT INTO zone (id, floorID, name, powered, locked, sprinklered, createDt) VALUES (3, 1, 'Zone 3', '1', '0', '0', datetime('now'));");
	db->query("INSERT INTO zone (id, floorID, name, powered, locked, sprinklered, createDt) VALUES (4, 2, 'Zone 4', '1', '0', '0', datetime('now'));");
	db->query("INSERT INTO zone (id, floorID, name, powered, locked, sprinklered, createDt) VALUES (5, 2, 'Zone 5', '1', '0', '0', datetime('now'));");
	db->query("INSERT INTO zone (id, floorID, name, powered, locked, sprinklered, createDt) VALUES (6, 3, 'Zone 6', '1', '0', '0', datetime('now'));");
	db->query("INSERT INTO zone (id, floorID, name, powered, locked, sprinklered, createDt) VALUES (7, 3, 'Zone 7', '1', '0', '0', datetime('now'));");
	db->query("INSERT INTO zone (id, floorID, name, powered, locked, sprinklered, createDt) VALUES (8, 3, 'Zone 8', '1', '0', '0', datetime('now'));");
	
	db->query("INSERT INTO admin (id, username, password) VALUES (1, 'admin', 'fsams');");		
}
	
// PUBLIC CONTROL METHODS
void Control::fire_event(int zoneID) {

	// If there are no other Fire Alarms -- this is the only one
	if (only_alarm(msg.ALARM_TYPE_FIRE)) {

		// Log the alarm
		log_alarm(zoneID, msg.ALARM_TYPE_FIRE);

		// Activate audible alarm
		audible_alarm(zoneID);

		// Activate Directional Indicators
		dir_indicator(zoneID);

		// Warning about automatic calling		
		syslog(msg.CALL_FIRE_DEPARTMENT_WARNING + msg.ELLIPSIS);

		// Check if the building is occupied
		if (floor_occupied(zoneID)) {
			// Have to wait for people to exit
		} else {
			// Power off the zone
			power_off(zoneID);

			// Turn on sprinklers in zone
			sprink_on(zoneID);
		}

	} else {

		// If alaram is in same zone
		if (repeat_alarm(msg.ALARM_TYPE_FIRE, zoneID)) {

			// Check if the building is occupied
			if (floor_occupied(zoneID)) {
				// Have to wait for people to exit
			} else {
				// Power off the zone
				power_off(zoneID);

				// Turn on sprinklers in zone
				sprink_on(zoneID);
			}

		} else {

			// Log the alarm
			log_alarm(zoneID, msg.ALARM_TYPE_FIRE);

			// Activate audible alarm
			audible_alarm(zoneID);

			// Activate Directional Indicators
			dir_indicator(zoneID);

			// Call Fire Department		
			call_FD();

			// Check if the building is occupied
			if (floor_occupied(zoneID)) {
				// Have to wait for people to exit
			} else {
				// Power off the zone
				power_off(zoneID);

				// Turn on sprinklers in zone
				sprink_on(zoneID);
			}
		}
	}
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
	
void Control::security_event(int zoneID) {

	// If there are no other Security Alarms -- this is the only one
	if (only_alarm(msg.ALARM_TYPE_SECURITY)) {

		// Log the alarm
		log_alarm(zoneID, msg.ALARM_TYPE_SECURITY);

		// Activate audible alarm
		audible_alarm(zoneID);

		// Lock doors
		lock_doors(zoneID);

		// Warning about automatic calling		
		syslog(msg.CALL_POLICE_WARNING + msg.ELLIPSIS);

	} else {

		// Log the alarm
		log_alarm(zoneID, msg.ALARM_TYPE_FIRE);

		// Activate audible alarm
		audible_alarm(zoneID);

		// Lock doors
		lock_doors(zoneID);

		// Call Fire Department		
		call_cops();
	}
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

void Control::clear_bldg() {
	//Clears all floors of the building
	string strquery = "UPDATE floor SET occupied = '0';";
	char *query = strdup(strquery.c_str());
	db->query(query);

	// Create log information		
	syslog(msg.CLEAR_BUILDING + msg.ELLIPSIS);
}

void Control::active_alarms() {
	// Display the active alarms
	cout << "Alarms: " << endl;
	vector<vector<string> > result = db->query("SELECT * FROM alarm;");
	for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
	{
		vector<string> row = *it;
		cout << "ID: " << row.at(0) << ", Zone ID: " << row.at(1) << ", Type: " << row.at(2) << ", Created: " << row.at(3) << ", Resolved: " << row.at(4) <<endl;
	}
	cout << endl;
}
	
// PRIVATE METHODS	
bool Control::only_alarm(string alarm_type) {
	// Check database for existing alarm of this type
	string activeAlarm;
	string strquery = "SELECT count(*) FROM alarm WHERE (type = " + alarm_type + ") AND (resolveDt != 0);";
	char *query = strdup(strquery.c_str());
	vector<vector<string> > result = db->query(query);
	for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
	{
		vector<string> row = *it;
		activeAlarm = row.at(0);
	}
	// Return if alarm exists in different zone
	return (activeAlarm == "0");
}
	
bool Control::repeat_alarm(string alarm_type, int zoneID) {
	// Check database for existing alarm of this type in same zone
	string activeAlarm;
	string strquery = "SELECT count(*) FROM alarm WHERE (type = " + alarm_type + ") AND (zoneID = " + zoneString(zoneID) + ") AND (resolveDt != 0);";
	char *query = strdup(strquery.c_str());
	vector<vector<string> > result = db->query(query);
	for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
	{
		vector<string> row = *it;
		activeAlarm = row.at(0);
	}
	// Return if alarm exists in different zone
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
	
bool Control::floor_occupied(int zoneID){
	//Check database for people on floor
	string occupied;
	string strquery = "SELECT occupied FROM floor, zone WHERE (floor.id = zone.floorID) AND (zone.id = " + zoneString(zoneID) + ");";
	char *query = strdup(strquery.c_str());
	vector<vector<string> > result = db->query(query);
	for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
	{
		vector<string> row = *it;
		occupied = row.at(0);
	}
	//If the password is correct then return true
	return (occupied == "1");
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

void Control::disable_alarm(int zoneID) {
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
