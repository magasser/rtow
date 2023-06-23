#include "pch.h"

#include "utils.h"

namespace utils
{
	struct xorshift128_state
	{
		uint32_t x[4];
	};

	uint32_t xorshf128(struct xorshift128_state* state)
	{
		uint32_t t = state->x[3];

		uint32_t s = state->x[0];
		state->x[3] = state->x[2];
		state->x[2] = state->x[1];
		state->x[1] = s;

		t ^= t << 11;
		t ^= t >> 8;
		return state->x[0] = t ^ s ^ (s >> 19);
	}

	float randFloatFast()
	{
		static xorshift128_state state = {.x = {32409723, 230948, 2130123, 983403}};

		uint32_t n = xorshf128(&state);

		float* f = (float*)&n;

		return 1.0f / FLT_MAX * fabsf(*f);
	}

	float randFloat()
	{
		static std::mt19937 generator;
		static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

		return distribution(generator);
	}

	float randFloat(float min, float max)
	{
		static std::mt19937 generator;
		std::uniform_real_distribution<float> distribution(min, max);

		return distribution(generator);
	}

	glm::vec3 randVec3()
	{
		return glm::vec3(randFloat(), randFloat(), randFloat());
	}

	glm::vec3 randVec3(float min, float max)
	{
		return glm::vec3(randFloat(-1.0f, 1.0f), randFloat(-1.0f, 1.0f), randFloat(-1.0f, 1.0f));
	}

	// Unit sphere diffuse
	glm::vec3 randInUnitSphere()
	{
		while (true)
		{
			glm::vec3 point = randVec3(-1.0f, 1.0f);

			if (glm::length2(point) >= 1.0f)
				continue;

			return point;
		}
	}

	// Lambertian diffuse
	glm::vec3 randUnitVec()
	{
		return glm::normalize(randInUnitSphere());
	}

	// Hemisphere diffuse
	glm::vec3 randInHemisphere(const glm::vec3& normal)
	{
		glm::vec3 inUnitSphere = randInUnitSphere();

		return glm::dot(inUnitSphere, normal) > 0.0f ? inUnitSphere : -inUnitSphere;
	}

	glm::vec3 randInUnitDisk()
	{
		while (true)
		{
			glm::vec3 point(randFloat(-1.0f, 1.0f), randFloat(-1.0f, 1.0f), 0.0f);

			if (glm::length2(point) < 1.0f)
				return point;
		}
	}
}
