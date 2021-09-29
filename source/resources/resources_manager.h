#pragma once 

#include <string>
#include <memory>
#include <map>

namespace Renderer {
	class Shader_program;
}

class ResourceManager {
public:
	ResourceManager(const std::string& executable_path);
	~ResourceManager() = default;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete; 

	std::shared_ptr<Renderer::Shader_program> load_shader(const std::string& shader_name, const std::string& vertex_path, const std::string& fragment_path);
	std::shared_ptr<Renderer::Shader_program> get_shader(const std::string& shader_name);


private:
	std::string get_file_string(const std::string& relative_file_path) const;
	typedef std::map<const std::string, std::shared_ptr<Renderer::Shader_program>> shader_program_map;
	shader_program_map m_shader_programs;
	std::string m_path;
};