#pragma once
#include "Scene.hpp"
#include "Input.hpp"
#include "ResourceManager.hpp"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <GLFW/glfw3.h>


class MainMenu
{
public:
	Core::DataStructure::Scene scene;
	static GLFWwindow* window;

	bool isPressedPlay = false;
	bool isPressedOptions = false;
	bool isWaitingToSelect = false;
	bool isNewKeyForward = false;
	bool isNewKeyLeft = false;
	bool isNewKeyRight = false;
	bool isNewKeyBackward = false;
	bool isNewKeyJump = false;
	bool firstTime = true;

	

	void Update();
	void DisplayGUI(GLFWwindow* _window);
	void DisplayGUIOptions();
	void ReturnMainMenu(GLFWwindow* _window);
	void TextCentered(std::string text);
};