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

			void removeChild(Object* x)
			{
				this->children.erase(std::remove_if(std::begin(this->children), std::end(this->children), [x](auto& u) { return u.get() == x; }),
									 std::end(this->children));
			}

			std::vector<Object*> getChildren() const
			{
				std::vector<Object*> v;
				v.reserve(this->children.size());

				for(const auto& child : children)
				{
					v.push_back(child.get());
				}

				return v;
			}

		private:
			std::vector<std::unique_ptr<Object>> children;
		};
	}
}
