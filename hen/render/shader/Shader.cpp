
#include "hen/render/shader/Shader.h"

#include "hen/render/opengl/OpenGL.h"

#include <Log.h>

#include <fstream>
#include <sstream>

hen::shader::Shader::Shader(ShaderType type, const io::File& file)
{
	GLenum glShaderType;
	switch (type)
	{
	case ShaderType::VERTEX:
		glShaderType = GL_VERTEX_SHADER;
		break;

	case ShaderType::FRAGMENT:
		glShaderType = GL_FRAGMENT_SHADER;
		break;

	case ShaderType::GEOMETRY:
		glShaderType = GL_GEOMETRY_SHADER;
		break;
	}

	m_handle = glCreateShader(glShaderType);
	if (m_handle == 0)
		LOG_WARNING << "Failed to create handle for shader " << file.getPath() << "!";
	else
	{
		if (compile(parse(file)))
			LOG_INFO << "Compiled shader " << file.getPath() << " successfully!";
		else
		{
			LOG_WARNING << "Failed to compile shader " << file.getPath() << "!";
			glDeleteShader(m_handle);
			m_handle = 0;
		}
	}
}
hen::shader::Shader::~Shader()
{
	if (m_handle != 0)
		glDeleteShader(m_handle);
}

std::string hen::shader::Shader::parse(const io::File& file) const
{
	std::ifstream stream{ file.getPath() };
	if (!stream.is_open())
	{
		LOG_WARNING << "Could not find file " << file.getPath();
		return "";
	}

	std::stringstream buffer;
	for (std::string line; std::getline(stream, line); )
	{
		if (line.find("#include ") != std::string::npos)
		{
			auto first = line.find_first_of("\"");
			auto last = line.find_last_of("\"");
			if (first != std::string::npos && last != std::string::npos)
				buffer << parse(line.substr(first + 1, last - first - 1));
		}
		else
			buffer << line << std::endl;
	}
	return buffer.str();
}
bool hen::shader::Shader::compile(const std::string& code) const
{
	if (m_handle == 0 || code.empty())
		return false;

	const char* data = code.c_str();
	glShaderSource(m_handle, 1, &data, nullptr);
	glCompileShader(m_handle);

	GLint result;
	glGetShaderiv(m_handle, GL_COMPILE_STATUS, &result);
	GLint length;
	glGetShaderiv(m_handle, GL_INFO_LOG_LENGTH, &length);
	std::string message{ "", static_cast<unsigned int>(length) };
	glGetShaderInfoLog(m_handle, length, nullptr, &message[0]);

	if (!result)
		LOG_WARNING << message;
	return result;
}
