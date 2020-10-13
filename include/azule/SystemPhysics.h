#pragma once

#include <azule/export.hxx>

namespace azule
{
	class Engine;

	class AZULE_EXPORT SystemPhysics
	{
	public:
		void frame(const Engine& x);
	};
}