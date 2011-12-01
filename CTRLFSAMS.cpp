#include "Control.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	Control ctrl;
	ctrl.initBldg();

	ctrl.fire_test_event(4);

	getchar();

	return 0;
}
 