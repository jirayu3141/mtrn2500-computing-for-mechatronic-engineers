#include "XBoxController.h"
#include <iostream>
#include <cmath>
using namespace std;
XINPUT_STATE State;

//Map to XInput Wrapper
GamePad::XBoxController::XBoxController(XInputWrapper * xinput, DWORD id)
{
	this->xinput = xinput;
	this->id = id;
}

//methods which report information relating to the specific controller
DWORD GamePad::XBoxController::GetControllerId()
{
	return id; //retrun the manually created id of the controller
}

//checks if the controller is connected
bool GamePad::XBoxController::IsConnected()
{
	//if it is connected, return true
	if (xinput->XInputGetState(id,&State) == ERROR_SUCCESS) { 
		return true;
	}
	else // otherwise return false
	{
		return false;
	}


}

//Check if button A is pressed
bool GamePad::XBoxController::PressedA()
{
	xinput->XInputGetState(id, &State); //get the state of the controller
		return (State.Gamepad.wButtons & XINPUT_GAMEPAD_A); //check if the button A is pressed in the state
}

//Check if button B is pressed
bool GamePad::XBoxController::PressedB()
{
	xinput->XInputGetState(id, &State);

	return (State.Gamepad.wButtons & XINPUT_GAMEPAD_B);
}

//Check if button X is pressed
bool GamePad::XBoxController::PressedX()
{
	xinput->XInputGetState(id, &State);
	return (State.Gamepad.wButtons & XINPUT_GAMEPAD_X);
}

//Check if button Y is pressed
bool GamePad::XBoxController::PressedY()
{
	xinput->XInputGetState(id, &State);
	return (State.Gamepad.wButtons & XINPUT_GAMEPAD_Y);
}

//Check if button is pressed
bool GamePad::XBoxController::PressedLeftShoulder()
{
	xinput->XInputGetState(id, &State);
	return (State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
}

//Check if button X is pressed
bool GamePad::XBoxController::PressedRightShoulder()
{
	xinput->XInputGetState(id, &State);
	return (State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
}

//Check if button X is pressed
bool GamePad::XBoxController::PressedLeftDpad()
{
	xinput->XInputGetState(id, &State);
	return (State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
}

//Check if Right D Pad is pressed
bool GamePad::XBoxController::PressedRightDpad()
{
	xinput->XInputGetState(id, &State);
	return (State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
}

//Check if button Up D Pad is pressed
bool GamePad::XBoxController::PressedUpDpad()
{
	xinput->XInputGetState(id, &State);
	return (State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP);
}

//Check if button Down D Pad is pressed
bool GamePad::XBoxController::PressedDownDpad()
{
	xinput->XInputGetState(id, &State);
	return (State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
}

//Check if button start is pressed
bool GamePad::XBoxController::PressedStart()
{
	xinput->XInputGetState(id, &State);
	return (State.Gamepad.wButtons & XINPUT_GAMEPAD_START);
}

//Check if button back is pressed
bool GamePad::XBoxController::PressedBack()
{
	xinput->XInputGetState(id, &State);
	return (State.Gamepad.wButtons & XINPUT_GAMEPAD_BACK);
}

//Check if left thumb button is pressed
bool GamePad::XBoxController::PressedLeftThumb()
{
	xinput->XInputGetState(id, &State);
	return (State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB);
}

//Check if right thumb button is pressed
bool GamePad::XBoxController::PressedRightThumb()
{
	xinput->XInputGetState(id, &State);
	return (State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB);
}

//Determine how much left trigger is pressed and return the value between 0-255
BYTE GamePad::XBoxController::LeftTriggerLocation()
{
	xinput->XInputGetState(id,&State);
	return State.Gamepad.bLeftTrigger;
}

//Determine how much right trigger is pressed and return the value between 0-255
BYTE GamePad::XBoxController::RightTriggerLocation()
{
	xinput->XInputGetState(id, &State);
	return State.Gamepad.bRightTrigger;
}

//Determine the coordinate of the left thumbstick
GamePad::Coordinate GamePad::XBoxController::LeftThumbLocation()
{
	xinput->XInputGetState(id, &State);
	float LX = State.Gamepad.sThumbLX; //get the x-coor of the left thumbstick
	float LY = State.Gamepad.sThumbLY;//get the y-coor of the left thumbstick
	float magnitude = sqrt(LX*LX + LY * LY); //determine the distance travelled by the thumbsitck
	float normalizedMagnitude = 0;

	//check if the controller is outside a circular dead zone
	if (magnitude > deadZone)
	{
		//clip the magnitude at its expected maximum value
		if (magnitude > 32767) magnitude = 32767;

		//adjust magnitude relative to the end of the dead zone
		magnitude -= deadZone;

		//optionally normalize the magnitude with respect to its expected range
		//giving a magnitude value of 0.0 to 1.0
		normalizedMagnitude = magnitude / (32767 - deadZone);
	}
	else //if the controller is in the deadzone zero out the magnitude
	{
		magnitude = 0.0;
		normalizedMagnitude = 0.0;
	}
	//multiply the normalized multiplier to get the new scaling
	LX = LX * normalizedMagnitude;
	LY = LY * normalizedMagnitude;
	GamePad::Coordinate LeftCoor(LX,LY);
	return LeftCoor;
}

//Determine the coordinate of the right thumstick
GamePad::Coordinate GamePad::XBoxController::RightThumbLocation()
{
	xinput->XInputGetState(id, &State);
	float RX = State.Gamepad.sThumbRX; //get the x-coor of the right thumbstick
	float RY = State.Gamepad.sThumbRY; //get the y-coor of the right thumbstick
	float magnitude = sqrt(RX*RX + RY * RY); //determine the distance travelled by the thumbsitck
	float normalizedMagnitude = 0;

	//check if the controller is outside a circular dead zone
	if (magnitude > deadZone)
	{
		//clip the magnitude at its expected maximum value
		if (magnitude > 32767) magnitude = 32767;

		//adjust magnitude relative to the end of the dead zone
		magnitude -= deadZone;

		//optionally normalize the magnitude with respect to its expected range
		//giving a magnitude value of 0.0 to 1.0
		normalizedMagnitude = magnitude / (32767 - deadZone);
	}
	else //if the controller is in the deadzone zero out the magnitude
	{
		magnitude = 0.0;
		normalizedMagnitude = 0.0;
	}
	//multiply the normalized multiplier to get the new scaling
	RX = RX * normalizedMagnitude;
	RY = RY * normalizedMagnitude;
	GamePad::Coordinate RightCoor(RX,RY);
	return RightCoor;
}

//Sets vibration motor to vibrate at desired value between 0-65535
void GamePad::XBoxController::Vibrate(WORD left, WORD right)
{
	vibration.wLeftMotorSpeed = left;
	vibration.wRightMotorSpeed = right;

	XInputSetState(id, &vibration);
}

//Set the deadzone of the controller
void GamePad::XBoxController::SetDeadzone(unsigned int radius)
{
	deadZone = radius;
}

//Prints out the interface of the mains
void GamePad::XBoxController::printController()
{
	if (PressedA() == 1) {
		cout << "A";
	}
	cout << "  ";
	if (PressedB() == 1) {
		cout << "B";
	}
	cout << "  ";
	if (PressedX() == 1) {
		cout << "X";
	}
	cout << "  ";
	if (PressedY() == 1) {
		cout << "Y";
	}
	cout << "  ";
	if (PressedLeftShoulder() == 1) {
		cout << "LB";
	}
	cout << "  ";
	if (PressedRightShoulder() == 1) {
		cout << "RB";
	}
	cout << "  ";
	if (PressedLeftDpad() == 1) {
		cout << "<";
	}
	cout << "  ";
	if (PressedRightDpad() == 1) {
		cout << ">";
	}
	cout << "  ";
	if (PressedUpDpad() == 1) {
		cout << "^";
	}
	cout << "  ";
	if (PressedDownDpad() == 1) {
		cout << "˅";
	}
	cout << "  ";
	if (PressedStart() == 1) {
		cout << "Start";
	}
	cout << "  ";
	if (PressedBack() == 1) {
		cout << "Back";
	}
	cout << "  ";
	if (PressedLeftThumb() == 1) {
		cout << "L.Thumb";
	}
	cout << "  ";
	if (PressedRightThumb() == 1) {
		cout << "R.Thumb";
	}
	cout << "  ";
	cout << (int)LeftTriggerLocation() << "  ";
	cout << (int)RightTriggerLocation() << "  ";
	cout << LeftThumbLocation().GetX() << "  ";
	cout << LeftThumbLocation().GetY() << "  ";
	cout << RightThumbLocation().GetX() << "  ";
	cout << RightThumbLocation().GetY() << "  ";
	cout << endl;
}