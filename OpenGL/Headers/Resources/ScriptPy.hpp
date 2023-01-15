#pragma once
#include <string>
#include <iostream>

#include <Resources/IResource.hpp>

#include <LowRenderer/Camera.hpp>

#include <pybind11/include/pybind11/pybind11.h>
#include <pybind11/include/pybind11/embed.h>

#include <DataStructure/GameObject.hpp>
#include <PlayerCommon.hpp>


namespace Resources
{
	class Script : public Resources::IResource
	{
	public:
		Script(const char* path);
		Script();
		~Script();

		void LoadData(const char* path)override;

		void Update(const float deltaTime, const LowRenderer::Camera& cam);

		static const char *ParseModuleName(const char* path);

		DataStructure::GameObject* Object;
		PlayerInputs PlayerInput;

		void takePlayer(DataStructure::GameObject* Obj, PlayerInputs PlInput)
		{
			Object = Obj;
			PlayerInput = PlInput;
		}

	private:
		pybind11::module scriptModule;
		pybind11::object scriptObj;
	};
}



