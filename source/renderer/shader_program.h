#pragma once

#include <glad/glad.h>
#include <string>

namespace Renderer {
	
	class Shader_program {
	public:
		Shader_program(const std::string& vertex_shader, const std::string& fragment_shader);
		~Shader_program();
		bool is_compiled() const { return m_is_compiled; }
		void use() const;

		Shader_program() = delete; 
		Shader_program(Shader_program&) = delete; 
		Shader_program& operator = (const Shader_program&) = delete; 
		Shader_program& operator=(Shader_program&& shader_program) noexcept;
		Shader_program(Shader_program&& shader_program) noexcept;  

	private:
		bool create_shader(const std::string& source, const GLenum shader_type, GLuint& shader_id);
		bool m_is_compiled = false;
		GLuint m_ID = 0;
	};

};
