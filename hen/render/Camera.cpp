
#include "hen/render/Camera.h"

#include "hen/core/Core.h"
#include "hen/ui/Display.h"
#include "hen/render/uniform/UniformBlockManager.h"
#include "hen/util/MathLib.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void hen::render::Camera::process()
{
	m_oldPos = m_pos;
	m_oldRot = m_rot;
	m_oldUp = m_up;
	m_oldFov = m_fov;
}
void hen::render::Camera::upload(float dt) const
{
	const auto pos = math::lerp(m_oldPos, m_pos, dt);
	const auto rot = math::lerp(m_oldRot, m_rot, dt);
	const auto up = math::lerp(m_oldUp, m_up, dt);
	const float fov = math::lerp(m_oldFov, m_fov, dt);

	const glm::vec2 size{ Core::getDisplay().getWidth(), Core::getDisplay().getHeight() };
	const auto proj = glm::perspective(fov, size.x / size.y, m_znear, m_zfar);
	const auto view = glm::lookAt(pos, pos + math::toCartesian(rot), up);
	const auto projView = proj * view;
	m_projviewInv = glm::inverse(projView);

	const auto& cameraBlock = Core::getUniformBlockManager().get("Camera");
	cameraBlock.setField("proj", proj);
	cameraBlock.setField("projInv", glm::inverse(proj));
	cameraBlock.setField("view", view);
	cameraBlock.setField("viewInv", glm::inverse(view));
	cameraBlock.setField("projview", projView);
	cameraBlock.setField("projviewInv", m_projviewInv);
}


void hen::render::Camera::setPosition(const glm::vec3& pos, bool snap)
{
	m_oldPos = snap ? pos : m_oldPos;
	m_pos = pos;
}
void hen::render::Camera::setRotation(const glm::vec2& rot, bool snap)
{
	m_oldRot = snap ? rot : m_oldRot;
	m_rot = rot;
}
void hen::render::Camera::setRotation(float yaw, float pitch, bool snap)
{
	setRotation(glm::vec2{ yaw, pitch }, snap);
}
void hen::render::Camera::lookTowards(const glm::vec3& target, bool snap)
{
	setRotation(math::toSpherical(target - m_pos), snap);
}

void hen::render::Camera::setUpVector(const glm::vec3& up, bool snap)
{
	m_oldUp = snap ? up : m_oldUp;
	m_up = up;
}
void hen::render::Camera::setFOV(float fov, bool snap)
{
	m_oldFov = snap ? fov : m_oldFov;
	m_fov = fov;
}
void hen::render::Camera::setViewDistance(float znear, float zfar)
{
	m_znear = znear;
	m_zfar = zfar;
}

glm::vec3 hen::render::Camera::getVector(const glm::vec2& mouseVector) const
{
	const glm::vec2 size{ Core::getDisplay().getWidth(), Core::getDisplay().getHeight() };
	const auto& cameraBlock = Core::getUniformBlockManager().get("Camera");

	// Magic. DO NOT TOUCH!
	const auto v = 2.0f * mouseVector / size - 1.0f;
	const auto far = m_projviewInv * glm::vec4{ v.x, -v.y, 1.0f, 1.0f };
	return glm::normalize(glm::vec3{ far });
}

