#include "Texture.hpp"

#include <STB_Image/stb_image.h>
#include <iostream>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

using namespace Resources;
using namespace std;

GLuint Texture::sampler;


Texture::~Texture() {}

Texture::Texture()
	: texKey(0)
{
	type = Resource::ResourceType::R_TEXTURE;
}

void Texture::Unload()
{
	//cout << "Deleting texture" << endl;
	glDeleteTextures(1, &texKey);
}

void Texture::Load(const string& filepath)
{
	int  nrChannels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);

	glGenTextures(1, &texKey);
	glBindTexture(GL_TEXTURE_2D, texKey);

	if(nrChannels == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	if(nrChannels == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}


void Texture::DisplayGUI(int index)
{
	ImGui::Image((ImTextureID)texKey, ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0));
}

void Texture::InitSampler()
{
	// create a sampler and parameterize it
		// ------------------------------------
	sampler = 0;
	glGenSamplers(1, &sampler);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.f);

	GLint max = 0;
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max);
}

GLuint Texture::GetTexKey()
{
	return texKey;
}

int Texture::GetWidth()
{
	return width;
}

int Texture::GetHeight()
{
	return height;
}