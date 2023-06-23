#pragma once

#include "Ray.h"

class Camera
{
public:
	Camera(const glm::vec3& position, float aspectRatio, float verticalFOV, float aperture);
	~Camera() = default;

	inline const glm::vec3& GetPosition() const { return m_Position; }

	inline float GetAspectRatio() const { return m_AspectRatio; }

	inline float GetVerticalFOV() const { return m_VerticalFOV; }

	void SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		m_FocusDistance = glm::length(m_Position - m_LookAt);
		Update();
		
	}
	void LookAt(const glm::vec3& target)
	{
		m_LookAt = target;
		m_FocusDistance = glm::length(m_Position - m_LookAt);
		Update();
	}

	void SetViewUp(const glm::vec3& up)
	{
		m_ViewUp = up;
		Update();
	}

	void SetVerticalFOV(float verticalFOV)
	{
		m_VerticalFOV = verticalFOV;
		Update();
	}

	void SetAperture(float aperture)
	{
		m_Aperture = aperture;
		Update();
	}

	Ray CreateRay(float s, float t) const;

private:
	void Update();

private:
	float m_AspectRatio;
	float m_VerticalFOV;
	float m_Aperture;
	float m_FocusDistance;
	float m_ViewportHeight;
	float m_ViewportWidth;
	float m_LensRadius;

	glm::vec3 m_LookAt;
	glm::vec3 m_ViewUp;
	glm::vec3 m_Position;

	glm::vec3 m_U, m_V, m_W;
	glm::vec3 m_Horizontal;
	glm::vec3 m_Vertical;
	glm::vec3 m_BottomLeft;
};
