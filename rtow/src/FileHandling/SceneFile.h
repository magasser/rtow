#pragma once

#include <vector>
#include <memory>
#include <glm/vec3.hpp>

namespace ObjectType
{
	enum ObjectType
	{
		Unknown = 0,
		Sphere = 1,
		Cuboid = 2,
		Cylinder = 3
	};
}

class SceneFile
{
public:
	struct Version
	{
		uint16_t major;
		uint16_t minor;
		uint16_t patch;
	};

	struct Object
	{
		Object(ObjectType::ObjectType type, const glm::vec3& position);

		ObjectType::ObjectType type;
		glm::vec3 position;
	};

	struct Sphere : public Object
	{
		Sphere(const glm::vec3& position, float radius);

		float radius;
	};

	struct Cuboid : public Object
	{
		Cuboid(const glm::vec3& position, float width, float height, float length);

		float width;
		float height;
		float length;
	};

	struct Cylinder : public Object
	{
		Cylinder(const glm::vec3& position, float height, float radius);

		float height;
		float radius;
	};

	struct Header
	{
		Version version;
	};

	struct Body
	{
		std::vector<std::shared_ptr<Object>> objects;
	};

public:
	SceneFile(Version version, const std::vector<std::shared_ptr<Object>>& objects);
	~SceneFile() = default;

	inline Version GetVersion() const { return m_Version; }
	inline std::vector<std::shared_ptr<Object>> GetObjects() const { return m_Objects; }

private:
	Version m_Version;
	std::vector<std::shared_ptr<Object>> m_Objects;
};
