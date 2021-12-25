#include "graphics/shader.h"

namespace sparky { namespace graphics {

	Shader::Shader(const char* vertPath, const char* fragPath)
		: m_VertPath(vertPath), m_FragPath(fragPath)
	{
		m_VertSource = std::string();
		m_FragSource = std::string();
		m_FromFile = true;
		m_ShaderID = load();
	}

	Shader::Shader(const std::string& vertSource, const std::string& fragSource)
		: m_VertSource(vertSource), m_FragSource(fragSource)
	{
		m_VertPath = "";
		m_FragPath = "";
		m_FromFile = false;
		m_ShaderID = load();
	}

	unsigned int Shader::load()
	{
		GLuint program = glCreateProgram();

		GLuint vert = glCreateShader(GL_VERTEX_SHADER);
		GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);

		if (m_FromFile)
		{
			m_VertSource = readFileAsText(m_VertPath);
			m_FragSource = readFileAsText(m_FragPath);
		}

		const char* vertC = m_VertSource.c_str();
		const char* fragC = m_FragSource.c_str();

		glShaderSource(vert, 1, &vertC, NULL);
		glCompileShader(vert);

		GLint result;
		glGetShaderiv(vert, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(vert, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(vert, length, &length, &error[0]);
			std::cout << "[ERROR] Failed to compile Vertex shader!" << std::endl << &error[0] << std::endl;
			glDeleteShader(vert);
			return 0;
		}

		glShaderSource(frag, 1, &fragC, NULL);
		glCompileShader(frag);
		glGetShaderiv(frag, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(frag, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(frag, length, &length, &error[0]);
			std::cout << "[ERROR] Failed to compile Fragment shader!" << std::endl << &error[0] << std::endl;
			glDeleteShader(frag);
			return 0;
		}

		glAttachShader(program, vert);
		glAttachShader(program, frag);

		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vert);
		glDeleteShader(frag);

		return program;
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ShaderID);
	}

	void Shader::enable() const
	{
		glUseProgram(m_ShaderID);
	}

	void Shader::disable() const
	{
		glUseProgram(0);
	}

	GLint Shader::getUniformLocation(const GLchar* name)
	{
		return glGetUniformLocation(m_ShaderID, name);
	}

	void Shader::setUniform1f(const GLchar* name, float value)
	{
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniform1i(const GLchar* name, int value)
	{
		glUniform1i(getUniformLocation(name), value);
	}

	void Shader::setUniform2f(const GLchar* name, const maths::vec2& vector)
	{
		glUniform2f(getUniformLocation(name), vector.x, vector.y);
	}

	void Shader::setUniform3f(const GLchar* name, const maths::vec3& vector)
	{
		glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
	}

	void Shader::setUniform4f(const GLchar* name, const maths::vec4& vector)
	{
		glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.h);
	}

	void Shader::setUniformMat4(const GLchar* name, const maths::mat4& matrix)
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
	}


} }