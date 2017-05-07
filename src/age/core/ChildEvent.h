#pragma once

#include <age/core/Event.h>

namespace age
{
	namespace core
	{
		class Object;

		class AGE_CORE_EXPORT ChildEvent : public Event
		{
		public:
			ChildEvent(Object* parent, Object* child);
			virtual ~ChildEvent();

			Object* getParent() const;
			Object* getChild() const;

		private:
			Object* parent;
			Object* child;
		};
	}
}
