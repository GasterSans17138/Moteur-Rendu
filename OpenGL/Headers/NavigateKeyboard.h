#pragma once
#include "Input.hpp"

class GUIitem
{
public:

	GUIitem* left;
	GUIitem* right;
	GUIitem* up;
	GUIitem* down;

	static GUIitem* selected;

	void Navigate(int key);
private:
	//static GLFWwindow* window;
};