#include "Control.h"
#include "Messaging.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	Messaging msg;

	// Create the Control and Initilize the building
	Control ctrl;
	ctrl.initBldg();

	// Test a Fire Event in Zone 4
	cout << "// Test a Fire Event in Zone 4" << endl;
	ctrl.fire_event(4);
	cout << endl;

	// Test a Fire Test Event in Zone 3
	cout << "// Test a Fire Test Event in Zone 3" << endl;
	ctrl.fire_test_event(3);
	cout << endl;

	// Test a Security Event in Zone 1
	cout << "// Test a Security Event in Zone 1" << endl;
	ctrl.security_event(1);
	cout << endl;

	// Test a Security Test Event in Zone 2
	cout << "// Test a Security Test Event in Zone 2" << endl;
	ctrl.security_test_event(2);
	cout << endl;

	// Clear the Building
	cout << "// Clear the Building" << endl;
	ctrl.clear_bldg(1);
	cout << endl;

	// Check for Fire alarm in Zone 4
	cout << "// Check for Fire alarm in Zone 4 - expected:triggered" << endl;
	ctrl.fire_alarm_active(4);
	cout << endl;

	// Check for Fire alarm in Zone 6
	cout << "// Check for Fire alarm in Zone 6 - expected:not triggered" << endl;
	ctrl.fire_alarm_active(6);
	cout << endl;

	// Check for Security alarm in Zone 1
	cout << "// Check for Security alarm in Zone 1 - expected:triggered" << endl;
	ctrl.security_alarm_active(1);
	cout << endl;

	// Check for Security alarm in Zone 6
	cout << "// Check for Security alarm in Zone 6 - expected:not triggered" << endl;
	ctrl.security_alarm_active(6);
	cout << endl;

	// Turn Off Fire alarms in Zone 4
	cout << "// Turn Off Fire alarms in Zone 4" << endl;
	ctrl.turn_off(4, "fsams", msg.ALARM_TYPE_FIRE);
	cout << endl;

	// Turn Off any alarm in Zone 3
	cout << "// Turn Off any alarm in Zone 3" << endl;
	ctrl.turn_off(3, "fsams");
	cout << endl;

	// Turn Off all alarms
	cout << "// Turn Off all alarms" << endl;
	ctrl.turn_off("fsams");
	cout << endl;

	// Print out the alarms
	ctrl.active_alarms();

	// Print out the log
	ctrl.dump_log();

	// Hit Enter to Continue...
	cout << endl << endl << "Hit Enter to Continue...";
	getchar();

	return 0;
}
 