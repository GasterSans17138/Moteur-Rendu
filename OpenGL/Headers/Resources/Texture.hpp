#pragma once
#include <Resources/IResource.hpp>

namespace Resources
{
	extern unsigned int ID;
	class Texture : public IResource
	{
	public:
		unsigned int texID;

	private:
		unsigned int mTexture;
		unsigned int mSampler;

	public:
		Texture(const char* path);
		~Texture();

	private:
		void LoadData(const char* path) override;

	};
}
