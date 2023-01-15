#pragma once
#include <iostream>
#include <imgui.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Player.hpp"


enum GameState
{
	GS_PLAY,
	GS_OPTION,
	GS_MAIN_MENU
};

enum SelectButton
{
	B_FORWARD,
	B_BACKWARD,
	B_LEFT,
	B_RIGHT,
	B_JUMP
};

class Menu
{
public:
	void Render(GLFWwindow* Window, const int Width, const int Height);
	void RenderOption(Player& player, GLFWwindow* Window, const int Width, const int Height);
	int lastButtonPush(GLFWwindow* Window);
	int checkKey(int key, Player& player, int lastKey);
	GameState gameState = GS_MAIN_MENU;
	SelectButton selectButton = B_FORWARD;
private:
	char* textForward;
	int lastKey;
	bool changeInput = false;

};

