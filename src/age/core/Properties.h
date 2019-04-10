#pragma once

#include <age/core/Export.h>
#include <age/core/String.h>
#include <memory>
#include <vector>

namespace age
{
	namespace core
	{
		///
		///	\class Property
		///
		///	\brief A base class used to handle setting values to properties from a string.
		///
		///	\date April 9, 2019
		///
		///	\author Aaron Shelley
		///
		class AGE_CORE_EXPORT Property
		{
		public:
			Property(std::string_view x);
			virtual ~Property();

			std::string getName() const;
			virtual void setValue(const std::string& x) = 0;
			virtual std::string getValue() const = 0;

		private:
			std::string name;
		};

		template <typename T>
		class TemplateProperty : public Property
		{
		public:
			TemplateProperty(T* r, std::string_view x) : Property{x}, reference{r}
			{
			}

			void setValue(const std::string& x) override
			{
				*this->reference = StringTo<T>(x);
			}

			std::string getValue() const
			{
				return ToString(*this->reference);
			}

		private:
			T* reference{};
		};

		///
		///	\class Properties
		///
		///	\brief This class manages registered properties.
		///
		///	\date April 9, 2019
		///
		///	\author Aaron Shelley
		///
		class AGE_CORE_EXPORT Properties
		{
		public:
			Properties();
			Properties(const Properties& x);
			Properties(Properties&& x);
			virtual ~Properties();

			Properties& operator=(const Properties& x);
			Properties& operator=(Properties&& x);

			template <typename T>
			void addProperty(T* p, std::string_view name)
			{
				this->properties.emplace_back(std::make_unique<TemplateProperty<T>>(p, name));
			}

			Property* getProperty(std::string_view x);
			const std::vector<std::unique_ptr<Property>>& getProperties() const;

		private:
			std::vector<std::unique_ptr<Property>> properties;
		};
	}
}
