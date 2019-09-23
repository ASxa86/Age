#pragma once

#include <memory>
#include <map>
#include <typeindex>
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
				this->children2[typeid(*x)] = x.get();
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

			template <typename T>
			T* getChild2()
			{
				return static_cast<T*>(this->children2[typeid(T)]);
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

			virtual void update([[maybe_unused]] double x)
			{
				for(auto& child : children)
				{
					child->update(x);
				}
			}

			std::vector<std::unique_ptr<Object>> children;
			std::map<std::type_index, Object*> children2;
		};
	}
}
