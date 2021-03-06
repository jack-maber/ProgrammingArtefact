#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <Xinput.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <assert.h>
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


int main(int argc, char* argv[]) {
	Controller* controller = new Controller(1); // Assigns new controller
	std::string filename, name, times = ""; //Creatse file name templates for text files
	std::string usertimes = "times";
	cxxtimer::Timer timer;  //Instaniates timer for button presses


	cout << "Please enter your name: ";
	cin >> name;
	cout << "Your name is: " << name << endl;

	filename = name + ".txt";
	times = name + usertimes + ".txt"; //Combines name and times to create two seperate files

	ofstream outFile(filename, ios::out); // Creates output file for button inputs
	ofstream InputSpeed(times, ios::out); // Creates output file for input speed


	while (true) { // Main Loop
		if (controller->isConnected()) {
			timer.start(); //Starts Button Press Timer

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) { // Checks button presses
				cout << "Left\n"; // Prints to command prompt
				outFile << "Left\n"; // Writes to text file
				cout << "You took " << timer.count<std::chrono::milliseconds>() << " milliseconds.\n"; // Prints to command prompt
				InputSpeed << timer.count<std::chrono::milliseconds>() << " \n"; //Prints input speed to time file
				timer.reset(); //Resets timer to zero
				Sleep(175);
			}

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) {
				cout << "Up\n"; // Prints to command prompt
				outFile << "Up\n"; // Writes to text file
				cout << "You took " << timer.count<std::chrono::milliseconds>() << " milliseconds.\n"; // Prints to command prompt
				InputSpeed << timer.count<std::chrono::milliseconds>() << " \n";
				timer.reset();
				Sleep(175);
			}

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
				cout << "Right\n"; // Prints to command prompt
				outFile << "Right\n"; // Writes to text file
				cout << "You took " << timer.count<std::chrono::milliseconds>() << " milliseconds.\n"; // Prints to command prompt
				InputSpeed << timer.count<std::chrono::milliseconds>() << " \n";
				timer.reset();
				Sleep(175);
			}

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
				cout << "Down\n"; // Prints to command prompt
				outFile << "Down\n"; // Writes to text file
				cout << "You took " << timer.count<std::chrono::milliseconds>() << " milliseconds.\n"; // Prints to command prompt
				InputSpeed << timer.count<std::chrono::milliseconds>() << " \n";
				timer.reset();
				Sleep(175);
			}

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
			{
				cout << "Light Kick\n"; // Prints to command prompt
				outFile << "Light Kick\n"; // Writes to text file
				cout << "You took " << timer.count<std::chrono::milliseconds>() << " milliseconds.\n"; // Prints to command prompt
				InputSpeed << timer.count<std::chrono::milliseconds>() << " \n";
				timer.reset();
				Sleep(175);
			}

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_X)
			{
				cout << "Light Punch\n"; // Prints to command prompt
				outFile << "Light Punch\n"; // Writes to text file
				cout << "You took " << timer.count<std::chrono::milliseconds>() << " milliseconds.\n"; // Prints to command prompt
				InputSpeed << timer.count<std::chrono::milliseconds>() << " \n";
				timer.reset();
				Sleep(175);
			}

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
			{
				cout << "Medium Punch\n"; // Prints to command prompt
				outFile << "Medium Punch\n"; // Writes to text file
				cout << "You took " << timer.count<std::chrono::milliseconds>() << " milliseconds.\n"; // Prints to command prompt
				InputSpeed << timer.count<std::chrono::milliseconds>() << " \n";
				timer.reset();
				Sleep(175);
			}

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_B)
			{
				cout << "Medium Kick\n"; // Prints to command prompt
				outFile << "Medium Kick\n"; // Writes to text file
				cout << "You took " << timer.count<std::chrono::milliseconds>() << " milliseconds.\n"; // Prints to command prompt
				InputSpeed << timer.count<std::chrono::milliseconds>() << " \n";
				timer.reset();
				Sleep(175);
			}

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
			{
				cout << "Heavy Kick\n"; // Prints to command prompt
				outFile << "Heavy Kick\n"; // Writes to text file
				cout << "You took " << timer.count<std::chrono::milliseconds>() << " milliseconds.\n"; // Prints to command prompt
				InputSpeed << timer.count<std::chrono::milliseconds>() << " \n";
				timer.reset();
				Sleep(175);
			}

			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
			{
				cout << "Heavy Punch\n"; // Prints to command prompt
				outFile << "Heavy Punch\n"; // Writes to text file
				cout << "You took " << timer.count<std::chrono::milliseconds>() << " milliseconds.\n"; // Prints to command prompt
				InputSpeed << timer.count<std::chrono::milliseconds>() << " \n";
				timer.reset();
				Sleep(175);
			}


			if (controller->getState().Gamepad.wButtons & XINPUT_GAMEPAD_BACK) // Exits app if back button pressed
			{
				cout << "Game Start\n"; // Prints to command prompt
				outFile << "Game Start\n"; // Writes to text file
				InputSpeed << "Game Start" << " \n";
				Sleep(200);
			}

		}


		else {
			cout << "Controller not found\nPress any key to exit\n";
			if (cin.get()) break; // Quits application
		}
	}
	return 0;
	void close(); // Closes output files
}
