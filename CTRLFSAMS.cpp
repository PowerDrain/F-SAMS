#include "Control.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	Control ctrl;

	cout << ctrl.fire_event(1) << endl;

	getchar();

	return 0;
}