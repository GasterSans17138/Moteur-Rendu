#pragma once
#include "Scene.hpp"

class CameraBehaviour : public Core::DataStructure::MonoBehaviour
{
	void Start() override;
	void Update() override;
	void Destroy() override;
	void DisplayGUI() override;
};
