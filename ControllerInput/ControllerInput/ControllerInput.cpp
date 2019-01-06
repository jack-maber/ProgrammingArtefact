/*
The MIT License (MIT)
Copyright (c) 2015 Alexander Rizaev
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <Xinput.h>

#pragma comment(user, "Compiled on " __DATE__ " at " __TIME__)
#pragma comment(lib, "XInput.lib")

using namespace std;

class Controller {
private:
	XINPUT_STATE _controllerState;
	int _controllerNum;
public:
	Controller(int num);
	~Controller();
	XINPUT_STATE getState();
	bool isConnected();
	void vibrate(int left = 0, int right = 0);
};

Controller::Controller(int num) {
	_controllerNum = num - 1;
}

Controller::~Controller() {

}

XINPUT_STATE Controller::getState() {
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

	XInputGetState(_controllerNum, &_controllerState);

	return _controllerState;
}

bool Controller::isConnected() {
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

	DWORD Result = XInputGetState(_controllerNum, &_controllerState);

	return Result == ERROR_SUCCESS;
}

void Controller::vibrate(int left, int right) {
	XINPUT_VIBRATION v;

	ZeroMemory(&v, sizeof(XINPUT_VIBRATION));

	v.wLeftMotorSpeed = left;
	v.wRightMotorSpeed = right;

	XInputSetState(_controllerNum, &v);
}


int _tmain(int argc, _TCHAR* argv[]) {
	Controller* c = new Controller(1);

	int lpower = 10000;
	int rpower = 10000;

	while (true) {
		if (c->isConnected()) {
			cout << lpower << " " << rpower << endl;
			if (c->getState().Gamepad.wButtons & XINPUT_GAMEPAD_A) {
				c->vibrate(lpower, rpower);
			}
			if (c->getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
				if (lpower + 100 < 65536) {
					c->vibrate();
					lpower += 100;
					c->vibrate(lpower, rpower);
				}
			}
			if (c->getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) {
				if (lpower - 100 > 0) {
					c->vibrate();
					lpower -= 100;
					c->vibrate(lpower, rpower);
				}
			}
			if (c->getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
				if (rpower + 100 < 65536) {
					c->vibrate();
					rpower += 100;
					c->vibrate(lpower, rpower);
				}
			}
			if (c->getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
				if (rpower - 100 > 0) {
					c->vibrate();
					rpower -= 100;
					c->vibrate(lpower, rpower);
				}
			}
			if (c->getState().Gamepad.wButtons & XINPUT_GAMEPAD_Y) {
				c->vibrate(0);
				lpower = 100;
				rpower = 100;
				c->vibrate(lpower, rpower);
			}
			if (c->getState().Gamepad.wButtons & XINPUT_GAMEPAD_B) {
				c->vibrate();
			}
			if (c->getState().Gamepad.wButtons & XINPUT_GAMEPAD_BACK) {
				break;
			}
		}
		else {
			cout << "Controller not found\nPress any key to exit\n";
			if (cin.get()) break;
		}
	}

	return 0;
}

