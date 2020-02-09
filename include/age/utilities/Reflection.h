#pragma once

#include <age/utilities/export.h>
#include <age/utilities/String.h>
#include <map>
#include <string_view>
#include <typeindex>

namespace age
{
	namespace utilities
	{
		struct Test
		{
			void setV(int)
			{
			}
			int getV()
			{
				return 0;
			}
		};
		class ReflType;

		namespace impl
		{
			struct AnyRef
			{
				template <typename T>
				AnyRef(T& x);

				template <typename T>
				T* convert() const;

				const ReflType* type{nullptr};
				void* obj{nullptr};
			};
		}

		class AGE_UTILITIES_EXPORT ReflProp
		{
		public:
			ReflProp(const std::string& n);
			virtual ~ReflProp();

			virtual bool setValue(const impl::AnyRef& obj, const std::string& v) = 0;
			virtual std::string getValue(const impl::AnyRef& obj) const = 0;

			std::string Name;
		};

		template <typename T>
		class TemplateProperty;

		template <typename C, typename A>
		class TemplateProperty<A(C::*)> : public ReflProp
		{
		public:
			using accessor = A(C::*);

			TemplateProperty(const std::string& n, accessor p) : ReflProp{n}, property{p}
			{
			}

			bool setValue(const impl::AnyRef& x, const std::string& v) override
			{
				const auto obj = x.convert<C>();

				if(obj != nullptr)
				{
					obj->*property = StringTo<A>(v);
					return true;
				}

				return false;
			}

			std::string getValue(const impl::AnyRef& x) const override
			{
				std::string s;

				const auto obj = x.convert<C>();

				if(obj != nullptr)
				{
					s = ToString(obj->*property);
				}

				return s;
			}

		private:
			accessor property;
		};

		template <typename S, typename G>
		class TemplateMethod;

		template <typename Class, typename SetR, typename GetR, typename Arg>
		class TemplateMethod<SetR (Class::*)(Arg), GetR (Class::*)() const> : public ReflProp
		{
		public:
			using funcptr_set = SetR (Class::*)(Arg);
			using funcptr_get = GetR (Class::*)() const;

			TemplateMethod(const std::string& n, funcptr_set s, funcptr_get g) : ReflProp{n}, setter{s}, getter{g}
			{
			}

			bool setValue(const impl::AnyRef& x, const std::string& v) override
			{
				const auto obj = x.convert<Class>();

				if(obj != nullptr)
				{
					(obj->*setter)(StringTo<Arg>(v));
					return true;
				}

				return false;
			}

			std::string getValue(const impl::AnyRef& x) const override
			{
				std::string s;

				const auto obj = x.convert<Class>();

				if(obj != nullptr)
				{
					s = ToString((obj->*getter)());
				}

				return s;
			}

		private:
			funcptr_set setter;
			funcptr_get getter;
		};

		class AGE_UTILITIES_EXPORT ReflType
		{
		public:
			ReflType();
			ReflType(const std::string& n, const std::type_info& x);

			template <typename T>
			void addBase();

			template <typename T>
			void addProperty(const std::string& x, T t)
			{
				this->properties.push_back(std::make_shared<TemplateProperty<T>>(x, t));
			}

			template <typename Setter, typename Getter>
			void addMethod(const std::string& x, Setter setter, Getter getter)
			{
				auto temp = std::make_shared<TemplateMethod<Setter, Getter>>(x, setter, getter);
				this->properties.push_back(temp);
			}

			ReflProp* getProperty(std::string_view x) const;
			std::vector<ReflProp*> getProperties() const;

			bool operator==(const ReflType& rhs) const;

			std::string Name;

		private:
			std::vector<std::shared_ptr<ReflProp>> properties;
			std::map<std::type_index, ReflType>::const_iterator baseTypeIt;
			std::type_index index;
		};

		class AGE_UTILITIES_EXPORT Reflection
		{
		public:
			static void Clear();

			template <typename T>
			static ReflType& Add(const std::string& x)
			{
				ReflMap.insert({typeid(T), ReflType(x, typeid(T))});
				return ReflMap.at(typeid(T));
			}

			static const ReflType* const Get(std::string_view x);

			template <typename T>
			static const ReflType* const Get()
			{
				return &ReflMap.at(typeid(T));
			}

		private:
			friend ReflType;
			static std::map<std::type_index, ReflType> ReflMap;
		};

		template <typename T>
		class Register
		{
		public:
			template <typename Func>
			Register(Func f)
			{
				f();
			}
		};

		namespace impl
		{
			template <typename T>
			AnyRef::AnyRef(T& x) : type{Reflection::Get<T>()}, obj{&x}
			{
			}

			template <typename T>
			T* AnyRef::convert() const
			{
				if(*Reflection::Get<T>() == *this->type)
				{
					return static_cast<T*>(this->obj);
				}

				return nullptr;
			}
		}

		template <typename T>
		void ReflType::addBase()
		{
			Reflection::ReflMap[typeid(T)];
			this->baseTypeIt = Reflection::ReflMap.find(typeid(T));
		}
	}
}
