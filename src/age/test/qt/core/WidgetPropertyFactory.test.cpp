#include <gtest/gtest.h>

#include <age/qt/core/WidgetPropertyFactory.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

using namespace age::core::qt;

namespace
{
	struct Property
	{
	};

	class Widget : public QWidget, public WidgetProperty
	{
	public:
		Widget(QWidget* parent) : QWidget(parent), WidgetProperty()
		{
		}

		void setValue(const rttr::argument&) override
		{
		}

		rttr::argument getValue() const override
		{
			return {};
		}
	};
}

TEST(WidgetPropertyFactory, Instance)
{
	EXPECT_NO_THROW(WidgetPropertyFactory::Instance());
}

TEST(WidgetPropertyFactory, Create)
{
	EXPECT_NO_THROW((WidgetPropertyFactory::RegisterType<Widget, Property>()));

	const auto widget = WidgetPropertyFactory::Instance().create(rttr::type::get<Property>());
	ASSERT_TRUE(widget != nullptr);
	EXPECT_EQ(typeid(*widget), typeid(Widget));
}
