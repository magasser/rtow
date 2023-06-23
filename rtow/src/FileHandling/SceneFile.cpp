#include "pch.h"
#include "SceneFile.h"

SceneFile::SceneFile(Version version, const std::vector<std::shared_ptr<Object>>& objects)
	: m_Version(version), m_Objects(objects) {}

SceneFile::Object::Object(ObjectType::ObjectType type, const glm::vec3& position)
	: type(type), position(position) {}

SceneFile::Sphere::Sphere(const glm::vec3& position, float radius)
	: Object(ObjectType::Sphere, position), radius(radius) {}

SceneFile::Cuboid::Cuboid(const glm::vec3& position, float width, float height, float length)
	: Object(ObjectType::Cuboid, position), width(width), height(height), length(length) {}

SceneFile::Cylinder::Cylinder(const glm::vec3& position, float height, float radius)
	: Object(ObjectType::Cylinder, position), height(height), radius(radius) {}
