#pragma once

#include <azule/core/qt/WidgetProperty.h>
#include <azule/core/qt/export.h>
#include <azule/utilities/Pimpl.h>
#include <typeindex>

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
			struct AZULE_CORE_QT_EXPORT CreatorBase
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
			class AZULE_CORE_QT_EXPORT WidgetPropertyFactory
			{
			public:
				WidgetPropertyFactory(const WidgetPropertyFactory&) = delete;
				~WidgetPropertyFactory();

				WidgetPropertyFactory& operator=(const WidgetPropertyFactory&) = delete;
				static WidgetPropertyFactory& Instance();

				///
				///	\brief Create type given typeid string.
				///
				WidgetProperty* create(const std::type_index& x, QWidget* parent = nullptr) const;

				template <typename T>
				WidgetProperty* create(const std::type_index& x, QWidget* parent = nullptr) const
				{
					auto object = this->create(x, parent);
					return dynamic_cast<T*>(object);
				}

				void registerType(const std::type_index& x, std::unique_ptr<CreatorBase> creator);

				template <typename WidgetType, typename PropertyType>
				static void RegisterType()
				{
					WidgetPropertyFactory::Instance().registerType(typeid(PropertyType), std::make_unique<Creator<WidgetType>>());
				}

			private:
				WidgetPropertyFactory();

				struct Impl;
				Pimpl<Impl> pimpl;
			};
		}
	}
}
