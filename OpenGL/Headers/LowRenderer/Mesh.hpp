#pragma once
#include <LowRenderer/Camera.hpp>
#include <LowRenderer/Light.hpp>

#include <Resources/Model.hpp>
#include <Resources/Texture.hpp>

#include <Maths/Vec2.hpp>
#include <Maths/Vec3.hpp>
#include <Maths/Vec4.hpp>
#include <Maths/Mat4.hpp>

#include <vector>
#include <string>

using namespace Core::Maths;

namespace LowRenderer
{
	class Mesh
	{
	public:
		Mat4 ModelMatrix;
		Mat4 MVPmat;

	private:
		int mShaderProgram;
		Resources::Texture* mTexture;
		Resources::Model* mModel;

	public:
		Mesh(Resources::Model* model = nullptr, const int shaderProgram = -1, Resources::Texture* texture = nullptr);
		void Draw(LowRenderer::Camera& cam, const std::vector<LowRenderer::DirectionalLight>& dirLights, const std::vector<LowRenderer::PointLight>& pointLights, const std::vector<LowRenderer::SpotLight>& spotLights);

	private:
		void SetBool(const char* name, bool value);
		void SetInt(const char* name, int value);
		void SetFloat(const char* name, float value);
		void SetVec2(const char* name, const Vec2& value);
		void SetVec3(const char* name, const Vec3& value);
		void SetVec4(const char* name, const Vec4& value);
		void SetMat4(const char* name, const Mat4& mat);
	};
}