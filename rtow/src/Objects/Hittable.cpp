#include "pch.h"
#include "Hittable.h"

Hittable::Hittable(const std::shared_ptr<Material>& material)
	: m_Material(material) {}
