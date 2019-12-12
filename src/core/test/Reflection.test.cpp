#include <age/core/Reflection.h>
#include <gtest/gtest.h>
#include <functional>

using namespace age::core;

namespace
{
	class MyClass
	{
	public:
		int x{0};
	};
}

TEST(ReflObj, Constructor)
{
	MyClass myClass;
	impl::AnyRef obj(myClass);
	obj.convert<MyClass>()->x = 1;
}

TEST(TemplateProperty, Constructor)
{
	TemplateProperty<int(MyClass::*)> property("x", &MyClass::x);
}

TEST(TemplateProperty, SetValue)
{
	MyClass myClass;
	TemplateProperty<int(MyClass::*)> property("x", &MyClass::x);

	property.setValue(myClass, "1");
	EXPECT_EQ(1, myClass.x);

	property.setValue(myClass, "-1");
	EXPECT_EQ(-1, myClass.x);
}

TEST(TemplateProperty, GetValue)
{
	MyClass myClass;
	TemplateProperty<int(MyClass::*)> property("x", &MyClass::x);

	EXPECT_EQ("0", property.getValue(myClass));

	myClass.x = 1;

	EXPECT_EQ("1", property.getValue(myClass));

	myClass.x = -1;

	EXPECT_EQ("-1", property.getValue(myClass));
}

TEST(ReflType, GetProperty)
{
	MyClass myClass;
	ReflType type("MyClass", typeid(MyClass));
}

TEST(Reflection, Register)
{
	auto& type = Reflection::Add<MyClass>("MyClass");
	type.addProperty("x", &MyClass::x);

	{
		MyClass myClass;

		auto type = Reflection::Get<MyClass>();
		auto p = type->getProperty("x");
		p->setValue(myClass, "5");
		EXPECT_EQ(5, myClass.x);
	}
}
