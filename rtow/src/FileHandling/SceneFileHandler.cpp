#include "pch.h"

#include <json/json.h>

#include "SceneFileHandler.h"

SceneFile::Header ParseHeader(Json::Value headerData)
{
	return {
		.version = {
			.major = static_cast<uint16_t>(headerData["Version"].get("Major", 0).asInt()),
			.minor = static_cast<uint16_t>(headerData["Version"].get("Minor", 0).asInt()),
			.patch = static_cast<uint16_t>(headerData["Version"].get("Patch", 0).asInt()),
		}
	};
}

std::shared_ptr<SceneFile::Object> ParseObject(Json::Value object)
{
	ObjectType::ObjectType type = static_cast<ObjectType::ObjectType>(object.get("Type", 0).asInt());
	Json::Value positionData = object["Position"];

	glm::vec3 position(positionData.get("X", 0.0f).asFloat(),
	                   positionData.get("Y", 0.0f).asFloat(),
	                   positionData.get("Z", 0.0f).asFloat());

	switch (type)
	{
	case ObjectType::Sphere:
		return std::make_shared<SceneFile::Sphere>(
			position,
			object.get("Radius", 0.0f).asFloat());
	case ObjectType::Cuboid:
		return std::make_shared<SceneFile::Cuboid>(
			position,
			object.get("Width", 0.0f).asFloat(),
			object.get("Height", 0.0f).asFloat(),
			object.get("Length", 0.0f).asFloat());
	case ObjectType::Cylinder:
		return std::make_shared<SceneFile::Cylinder>(
			position,
			object.get("Height", 0.0f).asFloat(),
			object.get("Radius", 0.0f).asFloat());
	default:
		return nullptr;
	}
}

SceneFile::Body ParseBody(Json::Value bodyData)
{
	std::vector<std::shared_ptr<SceneFile::Object>> objects;

	Json::Value objectData = bodyData["Objects"];

	for (uint32_t i = 0; i < objectData.size(); ++i)
	{
		const std::shared_ptr<SceneFile::Object>& object = ParseObject(objectData[i]);

		if (object)
		{
			objects.push_back(ParseObject(objectData[i]));
		}
	}

	return {
		.objects = objects,
	};
}

SceneFile SceneFileHandler::Load(const std::filesystem::path& path)
{
	assert(std::filesystem::exists(path));

	Json::Reader reader;
	Json::Value data;
	std::ifstream sceneFile(path, std::ifstream::binary);

	bool success = reader.parse(sceneFile, data);

	assert(success);

	SceneFile::Header header = ParseHeader(data["Header"]);

	SceneFile::Body body = ParseBody(data["Body"]);


	return SceneFile(header.version, body.objects);
}

void SceneFileHandler::Save(const SceneFile& scene, const std::filesystem::path& path) {}
