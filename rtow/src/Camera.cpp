#include "pch.h"
#include "Camera.h"

#include "utils.h"

Camera::Camera(const glm::vec3& position, float aspectRatio, float verticalFOV, float aperture)
	: m_Position(position),
	  m_AspectRatio(aspectRatio),
	  m_VerticalFOV(verticalFOV),
	  m_Aperture(aperture),
	  m_LookAt(glm::vec3(position.x, position.y, position.z + 1.0f)),
	  m_ViewUp(glm::vec3(0.0f, 1.0f, 0.0f))
{
	Update();
}

Ray Camera::CreateRay(float s, float t) const
{
	glm::vec3 rd = m_LensRadius * utils::randInUnitDisk();
	glm::vec3 offset = m_U * rd.x + m_V * rd.y;

	return Ray(m_Position + offset, m_BottomLeft + s * m_Horizontal + t * m_Vertical - m_Position - offset);
}

void Camera::Update()
{
	float theta = glm::radians(m_VerticalFOV);
	float h = glm::tan(theta / 2.0f);

	m_W = glm::normalize(m_Position - m_LookAt);
	m_U = glm::normalize(glm::cross(m_ViewUp, m_W));
	m_V = glm::cross(m_W, m_U);

	m_ViewportHeight = 2.0f * h;
	m_ViewportWidth = m_AspectRatio * m_ViewportHeight;

	m_Horizontal = m_FocusDistance * m_ViewportWidth * m_U;
	m_Vertical = m_FocusDistance * m_ViewportHeight * m_V;
	m_BottomLeft = m_Position - m_Horizontal / 2.0f - m_Vertical / 2.0f - m_FocusDistance * m_W;

	m_LensRadius = m_Aperture / 2.0f;
}
