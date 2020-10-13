#pragma once

#include <azule/export.hxx>
#include <entt/entt.hpp>

namespace azule
{
	class Entity;

	class AZULE_EXPORT World
	{
	public:
		Entity create();

	private:
		friend class Entity;
		entt::registry registry;
	};
}