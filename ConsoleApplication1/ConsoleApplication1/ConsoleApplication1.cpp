#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <Xinput.h>
#include <iostream>
#include <fstream>

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

	bool LStick_InDeadzone(); // Checks deadzone

	float LeftStick_X();  // Return X axis of left stick
	float LeftStick_Y();  // Return Y axis of left stick

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

// Deadzone check for Left Thumbstick
bool Controller::LStick_InDeadzone()
{
	// Obtain the X & Y axes of the stick
	short sX = _controllerState.Gamepad.sThumbLX;
	short sY = _controllerState.Gamepad.sThumbLY;

	// X axis is outside of deadzone
	if (sX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		sX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return false;

	// Y axis is outside of deadzone
	if (sY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		sY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return false;

	// One (or both axes) axis is inside of deadzone
	return true;
}

// Return X axis of left stick
float Controller::LeftStick_X()
{
	// Obtain X axis of left stick
	short sX = _controllerState.Gamepad.sThumbLX;

	// Return axis value, converted to a float, then divied to make sure it either equals 1 or 0, depending on the input
	return (static_cast<float>(sX) / 32768.0f);
}

// Return Y axis of left stick
float Controller::LeftStick_Y()
{
	// Obtain Y axis of left stick
	short sY = _controllerState.Gamepad.sThumbLY;

	// Return axis value, converted to a float, then divied to make sure it either equals 1 or 0, depending on the input
	return (static_cast<float>(sY) / 32768.0f);
}


int main(int argc, char* argv[]) {
	Controller* controller = new Controller(1); // Assigns new controller

	ofstream outFile("Controller1output.txt", ios::out); // Creates output file for button inputs

	while (true) { // Main Loop
		if (controller->isConnected()) {

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) { // Checks button presses
				cout << "Left\n"; // Prints to command prompt
				outFile << "Left\n"; // Writes to text file
			}

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) {
				cout << "Up\n";
				outFile << "Up\n";
			}

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
				cout << "Right\n";
				outFile << "Right\n";
			}

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
				cout << "Down\n";
				outFile << "Down\n";
			}

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
			{
				cout << "A\n";
				outFile << "A\n";
			}

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_X)
			{
				cout << "X\n";
				outFile << "X\n";
			}

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
			{
				cout << "Y\n";
				outFile << "Y\n";
			}

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_B)
			{
				cout << "B\n";
				outFile << "B\n";
			}

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
			{
				cout << "Left Bumper\n";
				outFile << "Left Bumper\n";
			}

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
			{
				cout << "Right Bumper\n";
				outFile << "Right Bumper\n";
			}


			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_BACK) // Exits app if back button pressed
			{
				break;
			}

		}

		else {
			cout << "Controller not found\nPress any key to exit\n";
			if (cin.get()) break; // Quits application
		}
	}
	return 0;
}
