#include "pch.h"

#include "FileHandling/PPMFileHandler.h"
#include "FileHandling/SceneFileHandler.h"
#include "Scene.h"
#include "Ray.h"
#include "Objects/Sphere.h"
#include "Timer.h"
#include "utils.h"

#include "Materials/Metal.h"
#include "Materials/Dielectric.h"
#include "Materials/Lambertian.h"

const int samples = 10;
const int maxDepth = 4;
const int width = 1200;

glm::vec3 RandomVec()
{
	return glm::vec3(utils::randFloat(), utils::randFloat(), utils::randFloat());
}

glm::vec3 RandomVec(float min, float max)
{
	return glm::vec3(utils::randFloat(min, max), utils::randFloat(min, max), utils::randFloat(min, max));
}

void CreateRandomScene(std::vector<std::shared_ptr<Hittable>>& objects)
{
	std::shared_ptr<Material> ground = std::make_shared<Lambertian>(glm::vec3(0.5f, 0.5f, 0.5f));

	objects.push_back(std::make_shared<Sphere>(glm::vec3(0.0f, -1000.0f, 0.0f), 1000.0f, ground));

	for (int32_t a = -11; a < 11; ++a)
	{
		for (int32_t b = -11; b < 11; b++)
		{
			float chooseMat = utils::randFloat();

			glm::vec3 center(a + 0.9f * utils::randFloat(), 0.2f, b + 0.9f * utils::randFloat());

			if (glm::length(center - glm::vec3(4.0f, 0.2f, 0.0f)) > 0.9f)
			{
				std::shared_ptr<Material> sphereMat;

				if (chooseMat < 0.8f)
				{
					glm::vec3 albedo = RandomVec() * RandomVec();
					sphereMat = std::make_shared<Lambertian>(albedo);
					objects.push_back(std::make_shared<Sphere>(center, 0.2f, sphereMat));
				}
				else if (chooseMat < 0.95)
				{
					glm::vec3 albedo = RandomVec(0.5f, 1.0f);
					float fuzz = utils::randFloat(0.0f, 0.5f);
					sphereMat = std::make_shared<Metal>(albedo, fuzz);
					objects.push_back(std::make_shared<Sphere>(center, 0.2f, sphereMat));
				}
				else
				{
					sphereMat = std::make_shared<Dielectric>(1.5f);
					objects.push_back(std::make_shared<Sphere>(center, 0.2f, sphereMat));
				}
			}
		}
	}

	auto material1 = std::make_shared<Dielectric>(1.5f);
	auto material2 = std::make_shared<Lambertian>(glm::vec3(0.4f, 0.2f, 0.1f));
	auto material3 = std::make_shared<Metal>(glm::vec3(0.7f, 0.6f, 0.5f), 0.0f);

	objects.push_back(std::make_shared<Sphere>(glm::vec3(0.0f, 1.0f, 0.0f), 1.0f, material1));
	objects.push_back(std::make_shared<Sphere>(glm::vec3(-4.0f, 1.0f, 0.0f), 1.0f, material2));
	objects.push_back(std::make_shared<Sphere>(glm::vec3(4.0f, 1.0f, 0.0f), 1.0f, material3));
}

Scene::Scene(const std::filesystem::path& sceneFile)
{
	SceneFile file = SceneFileHandler::Load(sceneFile);

	std::vector<std::shared_ptr<SceneFile::Object>> objects = file.GetObjects();

	CreateRandomScene(m_Objects);

	/*for (auto object : objects)
	{
		switch (object->type)
		{
		case ObjectType::Sphere:
			{
				SceneFile::Sphere* sphere = (SceneFile::Sphere*)object.get();
				m_Objects.push_back(std::make_shared<Sphere>(sphere->position, sphere->radius, ground));
				break;
			}
		default:
			break;
		}
	}*/

	glm::vec3 cameraPosition(13.0f, 2.0f, 3.0f);
	glm::vec3 cameraLookAt(0.0f, 0.0f, 0.0f);
	float aspectRatio = 3.0f / 2.0f;
	m_Camera = std::make_shared<Camera>(cameraPosition, aspectRatio, 20.0f, 0.1f);
	m_Camera->LookAt(cameraLookAt);
}

inline glm::vec3 Scene::GetBackgroundColor(const glm::vec3& direction) const
{
	static glm::vec3 white(1.0f);
	static glm::vec3 lightBlue(0.5f, 0.7f, 1.0f);

	glm::vec3 normalized = glm::normalize(direction);

	float t = 0.5f * (normalized.y + 1.0f);

	return (1.0f - t) * white + t * lightBlue;
}

inline glm::vec3 Scene::GetHitColor(const Ray& ray, const HitRecord& hit, uint32_t depth) const
{
	static glm::vec3 black(0.0f);

	Ray scattered;
	glm::vec3 attenuation;

	return hit.material->Scatter(ray, hit, attenuation, scattered) ? attenuation * CastRay(scattered, depth) : black;
}

void Scene::RenderPart(Image* image, uint32_t fromY, uint32_t toY) const
{
	for (uint32_t y = fromY; y < toY; ++y)
	{
		for (uint32_t x = 0; x < image->GetWidth(); ++x)
		{
			glm::vec3 pixel(0.0f, 0.0f, 0.0f);
			for (uint32_t s = 0; s < samples; ++s)
			{
				float u = float(x + utils::randFloat()) / (image->GetWidth() - 1);
				float v = float(y + utils::randFloat()) / (image->GetHeight() - 1);

				Ray ray = m_Camera->CreateRay(u, v);

				pixel += CastRay(ray, maxDepth);
			}

			image->SetPixel(x, y, pixel, samples);
		}
	}
	
}

void Test(uint32_t o) {}

void Scene::Render() const
{
	int32_t cores = std::thread::hardware_concurrency();
	int32_t parts = std::max(1, cores - 2);
	uint32_t height = static_cast<uint32_t>(width / m_Camera->GetAspectRatio());
	Image* image = new Image(width, height);

	Timer timer;
	timer.Start();
	std::vector<std::future<void>> futures;
	uint32_t partSize = image->GetHeight() / parts;
	for (uint32_t i = 0; i < parts; ++i)
	{
		uint32_t fromY = i * partSize;
		uint32_t toY = std::min(fromY + partSize, image->GetHeight());

		futures.push_back(std::async(std::launch::async, [image, fromY, toY, this]() mutable { RenderPart(image, fromY, toY); }));
	}

	for (auto& f : futures)
	{
		f.wait();
	}

	timer.Stop();

	std::cout << "Render time: " << timer.GetSeconds() << "s" << std::endl;

	PPMFileHandler::Save(*image, "test.ppm");
}

glm::vec3 Scene::CastRay(const Ray& ray, uint32_t depth) const
{
	static glm::vec3 black(0.0f);

	if (depth <= 0)
		return black;

	HitRecord hit;
	HitRecord tempHit;
	float closestT = FLT_MAX;

	for (const std::shared_ptr<Hittable>& object : m_Objects)
	{
		if (object->Hit(ray, FLT_EPSILON, closestT, tempHit))
		{
			closestT = tempHit.t;
			hit = tempHit;
		}
	}

	return closestT != FLT_MAX
		       ? GetHitColor(ray, hit, depth - 1)
		       : GetBackgroundColor(ray.GetDirection());
}
