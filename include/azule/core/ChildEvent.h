#pragma once

#include <azule/core/Event.h>

namespace azule
{
	namespace core
	{
		class Object;

		class AZULE_CORE_EXPORT ChildEvent : public Event
		{
		public:
			ChildEvent(Object* parent, Object* child);
			~ChildEvent() override;

			Object* getParent() const;
			Object* getChild() const;

		private:
			Object* parent;
			Object* child;
		};
	}
}
