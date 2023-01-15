#pragma once

//------------------- NOTES ------------------- 
//
//		This file is here to avoid 
//		useless dependencies in pybind
//
//--------------------------------------------- 

struct PlayerInputs
{
	bool moveForward = false;
	bool moveBackward = false;
	bool moveRight = false;
	bool moveLeft = false;
	bool moveJump = false;
};