
#include "hen/render/shader/ShaderProgram.h"

#include "hen/core/Core.h"
#include "hen/io/XMLFile.h"
#include "hen/render/opengl/OpenGL.h"
#include "hen/render/shader/Shader.h"
#include "hen/render/uniform/UniformBlockManager.h"

#include <Log.h>

unsigned int hen::shader::ShaderProgram::m_boundHandle = 0;

hen::shader::ShaderProgram::ShaderProgram() {}
hen::shader::ShaderProgram::~ShaderProgram()
{
	onUnload();
}

void hen::shader::ShaderProgram::onLoad(const io::File& file)
{
	m_path = file.getPath();
	io::XMLFile xmlFile{ file };
	auto& doc = xmlFile.open();

	for (auto shader = doc.first_child(); shader; shader = shader.next_sibling())
	{
		std::string type = shader.attribute("type").as_string();
		std::string file = shader.child("file").child_value();
		if (type == "vertex")
			attach(ShaderType::VERTEX, file);
		else if (type == "geometry")
			attach(ShaderType::GEOMETRY, file);
		if (type == "fragment")
			attach(ShaderType::FRAGMENT, file);
	}
	build();
}
void hen::shader::ShaderProgram::onUnload()
{
	if (m_handle != 0)
		glDeleteProgram(m_handle);
	m_handle = 0;
	m_isBuilt = false;
}

bool hen::shader::ShaderProgram::attach(ShaderType type, const io::File& file)
{
	if (m_isBuilt)
		return false;

	Shader shader{ type, file };
	if (shader.getHandle() == 0)
		return false;

	if (m_handle == 0)
		m_handle = glCreateProgram();
	glAttachShader(m_handle, shader.getHandle());
	return true;
}
bool hen::shader::ShaderProgram::build()
{
	if (m_isBuilt || m_handle == 0)
		return false;
	m_isBuilt = true;

	glLinkProgram(m_handle);

	GLint result;
	glGetProgramiv(m_handle, GL_LINK_STATUS, &result);
	GLint length;
	glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &length);
	std::string message{ "", static_cast<unsigned int>(length) };
	glGetProgramInfoLog(m_handle, length, nullptr, &message[0]);

	if (!result)
	{
		LOG(plog::warning) << "Failed to compile shader program " << m_path;
		LOG(plog::warning) << message;
		return false;
	}
	else
		LOG(plog::info) << "Successfully linked shader program " << m_path << "!";

	for (const auto& binding : Core::getUniformBlockManager().getBindings())
	{
		GLuint index = glGetUniformBlockIndex(m_handle, binding.first.c_str());
		if (index == GL_INVALID_INDEX)
			LOG(plog::warning) << "Failed to bind " << binding.first << " in shader " << m_path;
		else
			glUniformBlockBinding(m_handle, index, binding.second);
	}
	return true;
}

void hen::shader::ShaderProgram::bind() const
{
	if (m_boundHandle == m_handle)
		return;
	m_boundHandle = m_handle;
	glUseProgram(m_handle);
}