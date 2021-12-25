#pragma once

#include "maths/maths.h"
#include "utils/fileUtils.h"
#include <GL/glew.h>
#include <string>
#include <vector>
#include <iostream>

namespace sparky { namespace graphics {

	class Shader
	{
		// TODO: Revert this section to private
	private:
		unsigned int m_ShaderID;
		const char* m_VertPath;
		const char* m_FragPath;
		std::string m_VertSource, m_FragSource;
		bool m_FromFile;
	public:
		Shader(const char* vertPath, const char* fragPath);
		Shader(const std::string& vertSource, const std::string& fragSource);
		~Shader();

		void setUniform1f(const GLchar* name, float value);
		void setUniform1i(const GLchar* name, int value);
		void setUniform2f(const GLchar* name, const maths::vec2& vector);
		void setUniform3f(const GLchar* name, const maths::vec3& vector);
		void setUniform4f(const GLchar* name, const maths::vec4& vector);
		void setUniformMat4(const GLchar* name, const maths::mat4& matrix);

		void enable() const;
		void disable() const;
	private:
		unsigned int load();
		GLint getUniformLocation(const GLchar* name);
	};

} }