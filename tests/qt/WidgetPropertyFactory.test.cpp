#include <gtest/gtest.h>

#include  <azule/qt/WidgetPropertyFactory.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

using namespace azule::core::qt;

namespace
{
	struct Property
	{
	};

	class Widget : public WidgetProperty
	{
	public:
		Widget(QWidget* parent) : WidgetProperty(parent)
		{
		}

		void setValue(const std::string&) override
		{
		}

		std::string getValue() const override
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

	const auto widget = WidgetPropertyFactory::Instance().create(typeid(Property));
	ASSERT_TRUE(widget != nullptr);
	EXPECT_EQ(typeid(*widget), typeid(Widget));
}
