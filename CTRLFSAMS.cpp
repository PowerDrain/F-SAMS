#include "Control.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	// Create the Control and Initilize the building
	Control ctrl;
	//ctrl.initBldg();

	// Test a Fire Test Event in Zone 4
	cout << "// Test a Fire Test Event in Zone 4" << endl;
	ctrl.fire_test_event(4);
	cout << endl;

	// Turn Off alarms in Zone 4
	cout << "// Turn Off alarms in Zone 4" << endl;
	ctrl.turn_off(4, "fsams");
	cout << endl;

	// Print out the alarms
	ctrl.active_alarms();

	// Hit Enter to Continue...
	cout << endl << endl << "Hit Enter to Continue...";
	getchar();

	return 0;
}
 