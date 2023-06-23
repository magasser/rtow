#pragma once

#include "SceneFile.h"

class SceneFileHandler
{
public:
	static SceneFile Load(const std::filesystem::path& path);
	static void Save(const SceneFile& scene, const std::filesystem::path& path);
};
