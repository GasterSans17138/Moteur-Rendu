#pragma once
#include "Math.hpp"
#include "Model.hpp"
#include "Camera.hpp"
#include "Material.hpp"
#include "ShaderProgram.hpp"
#include "Scene.hpp"
#include "Texture.hpp"
#include <string>


namespace LowRenderer
{
	

	class Mesh : public Core::DataStructure::MonoBehaviour
	{
	public :
		Mesh(Resources::Model* _model, int _shdaerProgram);
		Mesh(Resources::Model* _model, int _shdaerProgram, Resources::Material* _mat);

		
		void Start() override;
		void Update() override;
		void Render();
		void DisplayGUI() override;
		void Destroy() override;
	private :
		Resources::Material* material;

		Resources::Model* model;
		int shaderProgram;
		Core::myMath::mat4x4 modelMatrix;
	};
}
