#include <azule/math/GLM.h>

void glm::to_json(nlohmann::json& j, const glm::vec2& x)
{
	j["x"] = x.x;
	j["y"] = x.y;
}

void glm::from_json(const nlohmann::json& j, glm::vec2& x)
{
	j["x"].get_to(x.x);
	j["y"].get_to(x.y);
}
