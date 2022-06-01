#pragma once
#ifndef ES_CORE_RENDERER_SHADER_H
#define ES_CORE_RENDERER_SHADER_H

#include "GlExtensions.h"
#include "math/Transform4x4f.h"

#include <string>
#include <vector>

namespace Renderer
{
	class Shader
	{
	public:
		Shader()
		{
			id = -1;
			compileStatus = false;
		}

		static Shader createShader(GLenum type, const std::string& source);
		void deleteShader();

		GLuint id;
		bool compileStatus;

	private:
		// Compile a shader
		// id should be a valid shader id created by glCreateShader with GL_VERTEX_SHADER or GL_FRAGMENT_SHADER type
		bool compile(GLuint id, const char* source);
	};

	class ShaderProgram
	{
	public:
		ShaderProgram();

		bool loadFromFile(const std::string& path);

		// Links vertex and fragment shaders together to make a GLSL program
		bool createShaderProgram(Shader &vertexShader, Shader &fragmentShader);

		void select();
		void unSelect();

		void setMatrix(Transform4x4f& mvpMatrix);
		void setSaturation(GLfloat saturation);
		void setTextureSize(const Vector2f& size);
		void setOutputSize(const Vector2f& size);

		bool supportsTextureSize() { return mTextureSize != -1; }

		void deleteProgram();

	private:
		GLuint mId;
		bool linkStatus;
		GLint mPositionAttribute;
		GLint mColorAttribute;
		GLint mTexCoordAttribute;
		GLint mvpUniform;

		GLint mSaturation;		
		GLint mTextureSize;
		GLint mOutputSize;

		std::vector<Shader> mAttachedShaders;

	private:
		void findAttribsAndUniforms();
	};

} // Renderer::

#endif // ES_CORE_RENDERER_SHADER_H
