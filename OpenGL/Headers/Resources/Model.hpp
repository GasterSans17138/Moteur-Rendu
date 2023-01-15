#pragma once
#include <vector>
#include <iostream>

#include <Resources/IResource.hpp>

#include <Maths/Vec2.hpp>
#include <Maths/Vec3.hpp>

#define DEBUG
#include <Debug/Assertion.hpp>

using namespace Core::Maths;

namespace Resources
{
	struct Vertex
	{
		Vec3 Position;
		Vec3 Normal;
		Vec2 TextureUV;
	};

	class Model : public IResource
	{
	public:
		unsigned int VAO;

	private:
		unsigned int mVBO, mEBO;
		std::vector<uint32_t> mIndexBuffer;
		std::vector<Vertex> mVertexBuffer;

	public:
		Model(const char* path);
		~Model();
		void SetIndexBuffer(std::vector<uint32_t>& indexBuffer) { mIndexBuffer = indexBuffer; }
		void SetVertexBuffer(std::vector<Vertex>& vertexBuffer) { mVertexBuffer = vertexBuffer; }
		std::vector<uint32_t>& GetIndexBuffer() { return mIndexBuffer; };
		std::vector<Vertex>& GetVertexBuffer() { return mVertexBuffer; };
		void SetBuffers();

	private:
		void LoadData(const char* path) override;
	};
}