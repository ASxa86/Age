#pragma once

#include <age/core/Pimpl.h>
#include <age/qt/core/Export.h>

#ifdef WIN32
#pragma warning(push, 0)
#endif

#include <rttr/registration.h>

#ifdef WIN32
#pragma warning(pop)
#endif

class QWidget;

namespace age
{
	namespace core
	{
		namespace qt
		{
			class Object;

			struct AGE_CORE_QT_EXPORT CreatorBase
			{
				virtual ~CreatorBase();
				virtual QWidget* create(QWidget* parent = nullptr) const;
			};

			template <typename T>
			struct Creator : public CreatorBase
			{
				QWidget* create(QWidget* parent = nullptr) const override
				{
					static_assert(std::is_base_of<QWidget, T>::value, "T must derive from Object");
					return new T(parent);
				}
			};

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
				QWidget* create(const rttr::type& x, QWidget* parent = nullptr) const;

				template <typename T>
				QWidget* create(const rttr::type& x, QWidget* parent = nullptr) const
				{
					auto object = this->create(x, parent);
					return dynamic_cast<T*>(object);
				}

				void registerType(const rttr::type& x, std::unique_ptr<CreatorBase> creator);

				template <typename T>
				static void RegisterType(const rttr::type& x)
				{
					Factory::Instance().registerType(rttr::type::get<T>(), std::make_shared<Creator<T>>());
				}

			private:
				WidgetPropertyFactory();

				struct Impl;
				Pimpl<Impl> pimpl;
			};

		}
	}
}
