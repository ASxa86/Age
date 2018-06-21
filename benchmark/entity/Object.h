#pragma once

#include <memory>
#include <vector>

namespace age
{
	namespace benchmark
	{
		class Object
		{
		public:
			Object()
			{
			}

			virtual ~Object()
			{
			}

			void addChild(std::unique_ptr<Object> x)
			{
				this->children.push_back(std::move(x));
			}

			Object* getChild() const;

			template <typename T>
			T* getChild() const
			{
				for(auto& child : children)
				{
					auto type = dynamic_cast<T*>(child.get());

					if(type != nullptr)
					{
						return type;
					}
				}

				return nullptr;
			}

			const std::vector<std::unique_ptr<Object>>& getChildren() const
			{
				return this->children;
			}

		private:
			std::vector<std::unique_ptr<Object>> children;
		};
	}
}
