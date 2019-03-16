#pragma once

#include <age/core/Pimpl.h>
#include <age/qt/core/Export.h>

#include <age/qt/core/WidgetProperty.h>

class QWidget;

namespace age
{
	namespace core
	{
		namespace qt
		{
			///
			///	Factory helper class.
			///
			struct AGE_CORE_QT_EXPORT CreatorBase
			{
				virtual ~CreatorBase();
				virtual WidgetProperty* create(QWidget* parent = nullptr) const;
			};

			///
			///	Factory helper class.
			///
			template <typename T>
			struct Creator : public CreatorBase
			{
				WidgetProperty* create(QWidget* parent = nullptr) const override
				{
					static_assert(std::is_base_of<WidgetProperty, T>::value, "T must derive from Object");
					return new T(parent);
				}
			};

			///
			///	\class WidgetPropertyFactory
			///
			///	\brief This factory handles constructing WidgetProperty derived Widgets given an unknown type during run-time.
			///
			///	\date March 15, 2019
			///
			///	\author Aaron Shelley
			///
			class AGE_CORE_QT_EXPORT WidgetPropertyFactory
			{
			public:
				WidgetPropertyFactory(const WidgetPropertyFactory&) = delete;
				~WidgetPropertyFactory();

				WidgetPropertyFactory& operator=(const WidgetPropertyFactory&) = delete;
				static WidgetPropertyFactory& Instance();

				///
				///	\brief Create type given typeid string.
				///
				WidgetProperty* create(const rttr::type& x, QWidget* parent = nullptr) const;

				template <typename T>
				WidgetProperty* create(const rttr::type& x, QWidget* parent = nullptr) const
				{
					auto object = this->create(x, parent);
					return dynamic_cast<T*>(object);
				}

				void registerType(const rttr::type& x, std::unique_ptr<CreatorBase> creator);

				template <typename WidgetType, typename PropertyType>
				static void RegisterType()
				{
					WidgetPropertyFactory::Instance().registerType(rttr::type::get<PropertyType>(), std::make_unique<Creator<WidgetType>>());
				}

			private:
				WidgetPropertyFactory();

				struct Impl;
				Pimpl<Impl> pimpl;
			};

		}
	}
}
