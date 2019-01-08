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


	bool LStick_InDeadzone(); // Thumbstick functions

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

XINPUT_STATE Controller::getState() // Returns state of inputs from controller
{
	XInputGetState(_controllerNum, &_controllerState);
	return _controllerState;
}

bool Controller::isConnected()
{
	DWORD Result = XInputGetState(_controllerNum, &_controllerState);

	return Result = ERROR_SUCCESS;
}

// Only needs inputs from left stick as the right stick is not used for fighting games
bool Controller::LStick_InDeadzone() // Deadzone check for Left Thumbstick
{
	// Obtain the X & Y axes of the stick
	short StickX = _controllerState.Gamepad.sThumbLX;
	short StickY = _controllerState.Gamepad.sThumbLY;

	// X axis is outside of deadzone
	if (StickX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || StickX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return false;

	// Y axis is outside of deadzone
	if (StickY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || StickY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return false;

	// The sticks are inside the deadzone
	return true;
}

// Return X axis of left stick
float Controller::LeftStick_X()
{
	// Obtain X axis of left stick
	short StickX = _controllerState.Gamepad.sThumbLX;

	// Return axis value, converted to a float, then made to equal out to 1 or 0 depending on input
	return (static_cast<float>(StickX) / 32768.0f);
}

// Return Y axis of left stick
float Controller::LeftStick_Y()
{
	// Obtain Y axis of left stick
	short StickY = _controllerState.Gamepad.sThumbLY;

	// Return axis value, converted to a float, then made to equal out to 1 or 0 depending on input
	return (static_cast<float>(StickY) / 32768.0f);
}

int main(int argc, char* argv[]) {
	Controller* controller = new Controller(1); // Assigns new controller
	
	ofstream outFile("Controller1output.txt", ios::out); // Creates output file for button inputs
	
	while (true) { // Main Loop
		if (controller->isConnected()) {
	
			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) { // Checks if D-Pad has been pressed 
				cout << "Left\n";
				outFile << "Left\n"; // Writes output to the text file
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
			
			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_A) // Checks if the face buttons have been pressed
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

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) // Checks if the shoulders have been pressed
			{
				cout << "Left Bumper\n";
				outFile << "Left Bumper\n";
			}

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
			{
				cout << "Right Bumper\n";
				outFile << "Right Bumper\n";
			}
			
			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_BACK) // Exits app if back button is pressed
			{
				break;
			}
				
		}
			
		else {
			cout << "XInput Device Not Found, Press any key to exit application\n";
			if (cin.get()) break;
		}
	}
	return 0;
}
