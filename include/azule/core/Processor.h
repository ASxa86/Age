#pragma once

#include <azule/core/Object.h>
#include <azule/utilities/Pimpl.h>
#include <chrono>

namespace azule
{
	namespace core
	{
		class AZULE_CORE_EXPORT Processor : public Object
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
