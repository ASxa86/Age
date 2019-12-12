#pragma once

#include <age/core/Object.h>
#include <chrono>

namespace age
{
	namespace core
	{
		class AGE_CORE_EXPORT Processor : public Object
		{
		public:
			Processor();
			virtual ~Processor();

			void fixed(std::chrono::microseconds x);
			void variable(std::chrono::microseconds x);
			void render(std::chrono::microseconds x);

		protected:
			void addFixedFunction(const std::function<void(std::chrono::microseconds)>& x);
			void addVariableFunction(const std::function<void(std::chrono::microseconds)>& x);
			void addRenderFunction(const std::function<void(std::chrono::microseconds)>& x);

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
