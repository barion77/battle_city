#include "resources_manager.h"
#include "../renderer/shader_program.h"

#include <sstream>
#include <fstream>
#include <iostream>

ResourceManager::ResourceManager(const std::string& executable_path) {
	size_t found = executable_path.find_last_of("/\\");
  	m_path = executable_path.substr(0, found); 
};

std::string ResourceManager::get_file_string(const std::string& relative_file_path) const
{
	std::ifstream f;
	f.open(m_path + "/" + relative_file_path.c_str(), std::ios::in | std::ios::binary);
	if (!f.is_open())
	{
		std::cout << "failed to open fail: " << relative_file_path << std::endl;
		return std::string{};
	}

	std::stringstream buffer;
	buffer << f.rdbuf();
	return buffer.str();
}

std::shared_ptr<Renderer::Shader_program> ResourceManager::load_shader(const std::string& shader_name, const std::string& vertex_path, const std::string& fragment_path)
{
	std::string vertex_string = get_file_string(vertex_path);
	if (vertex_string.empty())
	{
		std::cerr << "failed to get vertex shader!" << std::endl;
		return nullptr;
	}

	std::string fragment_string = get_file_string(fragment_path);
	if (fragment_string.empty())
	{
		std::cerr << "failed to get fragment shader!" << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::Shader_program>& new_shader = m_shader_programs.emplace(shader_name, std::make_shared<Renderer::Shader_program>(vertex_string, fragment_string)).first->second;
	
	if (new_shader->is_compiled())
	{
		return new_shader;
	}
	std::cerr << "Can't load shader program:\n" 
		<< "Vertex: " << vertex_path << "\n"
		<< "Fragment: " << fragment_path << std::endl;

	return nullptr;
}

std::shared_ptr<Renderer::Shader_program> ResourceManager::get_shader(const std::string& shader_name)
{
	shader_program_map::const_iterator it = m_shader_programs.find(shader_name);
	if (it != m_shader_programs.end())
	{
		return it->second;
	}

	std::cerr << "Can't find the shader program: " << shader_name << std::endl;
	return nullptr;
}