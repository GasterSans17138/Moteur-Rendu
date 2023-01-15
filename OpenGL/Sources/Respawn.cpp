#include "Respawn.hpp"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

using namespace Core::myMath;
using namespace Physics;
using namespace Core::DataStructure;

void Respawnable::Start()
{
	rb = gameObject->GetComponent<RigidBody>();
	startPos = gameObject->transform.position;
}

void Respawnable::Update()
{
	if (gameObject->transform.position.y < -30)
	{
		gameObject->transform.position = startPos;
		if (rb)
			rb->velocity = Vec3();

	}

}

void Respawnable::Destroy()
{

}

void Respawnable::DisplayGUI()
{
	ImGui::CollapsingHeader("Respawnable");
}