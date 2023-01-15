#pragma once
#include "Shader.hpp"
#include <string>
#include "Math.hpp"
#include "Resource.h"

namespace Resources
{
	class ShaderProgram : public Resource
	{
	public :
		ShaderProgram(int vertexShader, int fragmentShader);
		void Unload();
		~ShaderProgram();
		int GetProgram();

	private :
		int program;
	};
}