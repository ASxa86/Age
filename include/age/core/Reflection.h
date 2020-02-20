#pragma once

#include <age/core/Object.h>
#include <age/utilities/SharedLibrary.h>
#include <age/utilities/String.h>
#include <map>
#include <set>
#include <string_view>
#include <typeindex>

namespace age
{
	namespace core
	{
		class ReflType;

		namespace impl
		{
			///
			///	\class AnyRef
			///
			///	\brief An "any" implementation that supports references in order to generically pass object to setValue and getValue for ReflProp.
			///
			///	\author Aaron Shelley
			///
			///	\date February 17, 2020
			///
			struct AnyRef
			{
				///
				///	\brief Constructor that accepts a reference to a given object.
				///
				///	This constructor is defined further down in order to prevent circular dependencies with class Reflection.
				///
				template <typename T>
				AnyRef(T& x);

				///
				///	\brief Attempt to convert the internal reference to a pointer of the given type.
				///
				///	\return T* The pointer to the given type. Nullptr if the conversion cannot be done.
				///
				template <typename T>
				T* convert() const;

				///
				///	\brief The reflection type of the given reference object.
				///
				const ReflType* type{nullptr};

				///
				///	\brief Generic pointer to the reference object.
				///
				void* obj{nullptr};
			};
		}

		///
		///	\class ReflProp
		///
		///	\brief The general property for reflection objects that consists of a name and reference to a member function or pointer.
		///
		///	\author Aaron Shelley
		///
		///	\date February 17, 2020
		///
		class AGE_CORE_EXPORT ReflProp
		{
		public:
			ReflProp(const std::string& n);
			virtual ~ReflProp();

			///
			///	\brief Attempt to set the given string value to the property of the given reference object.
			///
			///	\return bool Returns true if the property was successfully applied.
			///
			virtual bool setValue(const impl::AnyRef& obj, const std::string& v) = 0;

			///
			///	\brief Attempt to get the value of the property of the given reference object.
			///
			///	\return std::string Returns a string value of the property for the given reference object.
			///
			virtual std::string getValue(const impl::AnyRef& obj) const = 0;

			virtual const std::type_info& getTypeInfo() const = 0;

			///
			///	\brief The property name identifier.
			///
			const std::string Name;
		};

		///
		///	\brief Partial template declaration for defining a template class to handle function syntax.
		///
		template <typename T>
		class TemplateProperty;

		///
		///	\class TemplateProperty
		///
		///	\brief This class manages ReflProp for public class member variables.
		///
		///	\author Aaron Shelley
		///
		///	\date February 17, 2020
		///
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
					obj->*property = age::utilities::StringTo<A>(v);
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
					s = age::utilities::ToString(obj->*property);
				}

				return s;
			}

			virtual const std::type_info& getTypeInfo() const override
			{
				return typeid(A);
			}

		private:
			accessor property;
		};

		///
		///	\brief Partial template declaration for defining a template class to handle function syntax.
		///
		template <typename S, typename G>
		class TemplateMethod;

		///
		///	\class TemplateMethod
		///
		///	\brief This class manages ReflProp for member functions.
		///
		///	\author Aaron Shelley
		///
		///	\date February 17, 2020
		///
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
					(obj->*setter)(age::utilities::StringTo<Arg>(v));
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
					s = age::utilities::ToString((obj->*getter)());
				}

				return s;
			}

			virtual const std::type_info& getTypeInfo() const override
			{
				return typeid(Arg);
			}

		private:
			funcptr_set setter;
			funcptr_get getter;
		};

		///
		///	\class ReflCreatorBase
		///
		///	\brief Base class for factory creation methods.
		///
		///	\author Aaron Shelley
		///
		///	\date February 17, 2020
		///
		class ReflCreatorBase
		{
		public:
			virtual ~ReflCreatorBase()
			{
			}

			virtual std::unique_ptr<Object> create() const = 0;
		};

		///
		///	\class ReflCreator
		///
		///	\brief Templated creator class for creating ReflObj derived types.
		///
		///	\author Aaron Shelley
		///
		///	\date February 17, 2020
		///
		template <typename T>
		class ReflCreator : public ReflCreatorBase
		{
			static_assert(std::is_base_of<Object, T>::value == true, "T must derive from Object.");

		public:
			virtual std::unique_ptr<Object> create() const
			{
				return std::make_unique<T>();
			}
		};

		///
		///	\class ReflType
		///
		///	\brief The reflection type representaion for reflected objects.
		///
		///	\author Aaron Shelley
		///
		///	\date February 17, 2020
		///
		class AGE_CORE_EXPORT ReflType
		{
		public:
			ReflType();
			ReflType(const std::string& n, const std::type_info& x);

			template <typename T>
			ReflType& addBase();
			ReflType& addAlias(const std::string& x);

			template <typename T>
			ReflType& addProperty(const std::string& x, T t)
			{
				this->properties.push_back(std::make_shared<TemplateProperty<T>>(x, t));
				return *this;
			}

			template <typename Setter, typename Getter>
			ReflType& addMethod(const std::string& x, Setter setter, Getter getter)
			{
				auto temp = std::make_shared<TemplateMethod<Setter, Getter>>(x, setter, getter);
				this->properties.push_back(temp);
				return *this;
			}

			ReflProp* getProperty(std::string_view x) const;
			std::vector<ReflProp*> getProperties() const;

			bool operator==(const ReflType& rhs) const;

			std::string Name;
			std::shared_ptr<ReflCreatorBase> Creator;

		private:
			friend class Reflection;
			std::vector<std::shared_ptr<ReflProp>> properties;
			std::map<std::type_index, ReflType>::const_iterator baseTypeIt;
			std::set<std::string> aliases;
			std::type_index index;
		};

		///
		///	\class Reflection
		///
		///	\brief Object storage for all reflection information.
		///
		///	\author Aaron Shelley
		///
		///	\date February 17, 2020
		///
		class AGE_CORE_EXPORT Reflection
		{
		public:
			Reflection(const Reflection&) = delete;
			Reflection& operator=(const Reflection&) = delete;

			Reflection(Reflection&&) = delete;
			Reflection& operator=(Reflection&&) = delete;

			static Reflection& Instance();

			void clear();

			std::unique_ptr<Object> create(std::string_view x);

			template <typename T>
			std::unique_ptr<T> create(std::string_view x)
			{
				auto p = this->create(x);
				auto temp = p.release();
				return std::unique_ptr<T>(dynamic_cast<T*>(temp));
			}

			template <typename T>
			ReflType& add(const std::string& x)
			{
				ReflType type(x, typeid(T));
				type.Creator = std::make_shared<ReflCreator<T>>();
				this->reflMap[typeid(T)] = type;
				return this->reflMap.at(typeid(T));
			}

			const ReflType* const get(std::string_view x) const;
			const ReflType* const get(const std::type_info& x) const;

			template <typename T>
			const ReflType* const get(const T& x) const
			{
				return this->get(typeid(x));
			}

			template <typename T>
			const ReflType* const get() const
			{
				return this->get(typeid(T));
			}

			std::vector<const ReflType*> const getTypes(const std::type_info& x) const;

		private:
			Reflection() = default;

			friend class ReflType;
			std::map<std::type_index, ReflType> reflMap;
			std::vector<age::utilities::SharedLibrary> libraries;
			bool initialized{false};
		};

		// Define declared classes and methods below to prevent circular dependencies.

		namespace impl
		{
			template <typename T>
			AnyRef::AnyRef(T& x) : type{Reflection::Instance().get<T>()}, obj{&x}
			{
			}

			template <typename T>
			T* AnyRef::convert() const
			{
				if(*Reflection::Instance().get<T>() == *this->type)
				{
					return static_cast<T*>(this->obj);
				}

				return nullptr;
			}
		}

		template <typename T>
		ReflType& ReflType::addBase()
		{
			// Construct an empty type for the given template T if one doesn't already exist.
			Reflection::Instance().reflMap[typeid(T)];

			// Save an iterator to this base type so that it can be referred to by ReflType incase the base type
			// reflection information is populated later on.
			this->baseTypeIt = Reflection::Instance().reflMap.find(typeid(T));
			return *this;
		}
	}
}
