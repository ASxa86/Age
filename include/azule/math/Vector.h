#pragma once

#include <array>
#include <azule/export.hxx>
#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

namespace glm
{
	AZULE_EXPORT void to_json(nlohmann::json& j, const glm::vec2& x);
	AZULE_EXPORT void from_json(const nlohmann::json& j, glm::vec2& x);
}
