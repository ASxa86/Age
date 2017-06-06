#pragma once

#include <age/core/System.h>

namespace age
{
	namespace core
	{
		///
		///	\class RenderProcessor
		///
		///	\brief This class can be overriden to implement rendering graphics.
		///
		///	This class was made so the Engine can find it and invoke frame().
		///	This was done so that the developer and build their own rendering library
		///	and wire it in to the Engine.
		///
		///	\date May 25, 2017
		///
		///	\author Aaron Shelley
		///
		class AGE_CORE_EXPORT RenderSystem : public System
		{
		public:
			RenderSystem();
			virtual ~RenderSystem() override;

			///
			///	\brief Override to handle polling for events.
			///
			///	Generally, graphics libraries use operating specific APIs to poll for events.
			///	In order to gather these events and send them throught the Engine generically
			///	override this function and use Age's event system.
			///
			virtual void pollEvents();
		};
	}
}
