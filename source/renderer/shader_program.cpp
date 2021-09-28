#include "shader_program.h"

#include <iostream>

namespace Renderer {
	Shader_program::Shader_program(const std::string& vertex_shader, const std::string& fragment_shader)
	{
		GLuint vertex_shader_id;
		if (!create_shader(vertex_shader, GL_VERTEX_SHADER, vertex_shader_id))
		{
			std::cerr << "VERTEX SHADER compile-time error" << std::endl;
			return;
		}

		GLuint fragment_shader_id;
		if (!create_shader(fragment_shader, GL_FRAGMENT_SHADER, fragment_shader_id))
		{
			std::cerr << "FRAGMENT SHADER compile-time error" << std::endl;
			glDeleteShader(vertex_shader_id);
			return;
		}

		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertex_shader_id);
		glAttachShader(m_ID, fragment_shader_id);
		glLinkProgram(m_ID); 

		GLint succes;
		glGetProgramiv(m_ID, GL_LINK_STATUS, &succes);
		if (!succes)
		{
			GLchar info_log[1024];
			glGetShaderInfoLog(m_ID, 1024, nullptr, info_log);
			std::cerr << "ERROR::SHADER: Link-time error\n" << info_log << std::endl;
		}
		else
		{
			m_is_compiled = true; 
		}

		glDeleteShader(vertex_shader_id);
		glDeleteShader(fragment_shader_id);
	}

	bool Shader_program::create_shader(const std::string& source, const GLenum shader_type, GLuint& shader_id)
	{
		shader_id = glCreateShader(shader_type);
		const char* code = source.c_str();
		glShaderSource(shader_id, 1, &code, nullptr);
		glCompileShader(shader_id);

		GLint succes;
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &succes);
		if (!succes)
		{
			GLchar info_log[1024];
			glGetShaderInfoLog(shader_id, 1024, nullptr, info_log);
			std::cerr << "ERROR::SHADER: Compile-time error\n" << info_log << std::endl;
			return false;
		}
		return true;
	}

	Shader_program::~Shader_program()
	{
		glDeleteProgram(m_ID);
	}

	void Shader_program::use() const
	{
		glUseProgram(m_ID);
	}

	Shader_program& Shader_program::operator=(Shader_program && shader_program) noexcept
	{
		glDeleteProgram(m_ID);
		m_ID = shader_program.m_ID;
		m_is_compiled = shader_program.m_is_compiled;

		shader_program.m_ID = 0;
		shader_program.m_is_compiled = false;
		return *this;
	}

	Shader_program::Shader_program(Shader_program&& shader_program) noexcept 
	{
		m_ID = shader_program.m_ID;
		m_is_compiled = shader_program.m_is_compiled;

		shader_program.m_ID = 0;
		shader_program.m_is_compiled = false;
	}
};