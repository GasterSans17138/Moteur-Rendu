#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>

#include <pybind11/include/pybind11/pybind11.h>
#include <pybind11/include/pybind11/embed.h>

#include <Resources/ScriptPy.hpp>

#define DEBUG
#include <Debug/Assertion.hpp>
#include <Debug/Log.hpp>

#include <Resources/ResourceManager.hpp>
#include <Resources/Model.hpp>
#include <Resources/Shader.hpp>
#include <Resources/Texture.hpp>

#include <LowRenderer/Mesh.hpp>
#include <LowRenderer/Camera.hpp>

#include <DataStructure/Graph.hpp>
#include <DataStructure/GameObject.hpp>

#include <Maths/Primitive.hpp>

#include "Player.hpp"
#include "Menu.hpp"

namespace Core
{
	struct AppInitializer
	{
		unsigned int width;
		unsigned int height;
		unsigned int major;
		unsigned int minor;
		const char* name;
		void (*framebuffer_size_callback)(GLFWwindow* windowm, int width, int height);
		void (*glDebugOutput)(GLenum source, GLenum type, GLuint id, GLenum severity,
							GLsizei length, const GLchar* message, const void* userParam);
	};

	class App
	{
	public:
		GLFWwindow* Window;

	private:
		float mDeltaTime = 0.0f;
		float mLastFrame = 0.0f;
		int mShaderProgram;
		LowRenderer::Camera mCam;
		double mMouseX = 0.0;
		double mMouseY = 0.0;
		int mHeight, mWidth;
		bool mInWindow = false;
		bool mFirstMouse = true;
		bool mGravity = true;
		bool mSlide = true;
		std::vector<LowRenderer::DirectionalLight> mDirectionalLights;
		std::vector<LowRenderer::PointLight> mPointLights;
		std::vector<LowRenderer::SpotLight> mSpotLights;
		DataStructure::Graph mGraph;
		Player mPlayer;
		Resources::ResourceManager* mRscManager;
		Menu mMenu;
		pybind11::scoped_interpreter interprteur{};

		void DisplaySliderFloatPosObject(std::vector<DataStructure::SceneNode> &Children, std::string index);

	public:
		App() {};
		~App();
		bool Init(AppInitializer& init);
		void InitResources();
		void Update();

	private:
		void processInput(GLFWwindow* Window);
	};
}