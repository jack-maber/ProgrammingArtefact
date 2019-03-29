#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <Xinput.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "ConsoleApplication1.h"
#include "cxxtimer.hpp"

#pragma comment(lib, "XInput.lib") // Includes XInput Library

using namespace std;

class Controller {
public:
	XINPUT_STATE _controllerState; // Holds Controller State
	int _controllerNum; // Controller Designation Number
	Controller(int num);
	~Controller();

	XINPUT_STATE getState(); // Gets state of inputs
	bool isConnected(); // Bool for the controller being connected

};

Controller::Controller(int num) // Contains -1 as no controllers are connected
{
	_controllerNum = num - 1;
}

Controller::~Controller() // Blank Controller class to assign to.
{

}

XINPUT_STATE Controller::getState() // Gets state of inputs
{
	XInputGetState(_controllerNum, &_controllerState);
	return _controllerState;
}

bool Controller::isConnected() //Checks if the controller is connected
{
	DWORD Result = XInputGetState(_controllerNum, &_controllerState);

	return Result == ERROR_SUCCESS;
}

float InputGap = 0;
bool timer = true;

int main(int argc, char* argv[]) {
	Controller* controller = new Controller(1); // Assigns new controller
	std::string filename, name = "";
	cxxtimer::Timer timer;


	cout << "Please enter your name: ";
	cin >> name;
	cout << "Your name is: " << name << endl;

	filename = name + ".txt";

	ofstream outFile(filename, ios::out); // Creates output file for button inputs

	//ADD TO INT AND THEN JUST PRINTS THEM AT THE END OF THE OPERATION.


	while (true) { // Main Loop
		if (controller->isConnected()) {


			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) { // Checks button presses
				cout << "Left\n"; // Prints to command prompt
				outFile << "Left\n"; // Writes to text file
				timer = false;
				Sleep(170);
			}

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) {
				cout << "Up\n";
				outFile << "Up\n";
				Sleep(170);
			}

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
				cout << "Right\n";
				outFile << "Right\n";
				Sleep(170);
			}

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
				cout << "Down\n";
				outFile << "Down\n";
				Sleep(170);
			}

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
			{
				cout << "A\n";
				outFile << "A\n";
				Sleep(170);
			}

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_X)
			{
				cout << "X\n";
				outFile << "X\n";
				Sleep(170);
			}

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
			{
				cout << "Y\n";
				outFile << "Y\n";
				Sleep(170);
			}

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_B)
			{
				cout << "B\n";
				outFile << "B\n";
				Sleep(170);
			}

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
			{
				cout << "Left Bumper\n";
				outFile << "Left Bumper\n";
				Sleep(170);
			}

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
			{
				cout << "Right Bumper\n";
				outFile << "Right Bumper\n";
				Sleep(170);
			}


			//if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_BACK) // Exits app if back button pressed
			//{
			//	break;
			//}

		}


		else {
			cout << "Controller not found\nPress any key to exit\n";
			if (cin.get()) break; // Quits application
		}
	}
	return 0;
	void close(); // Closes output file
}
