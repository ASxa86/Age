#include <age/core/Reflection.h>
#include <gtest/gtest.h>
#include <functional>

using namespace age::core;

namespace
{
	class MyBase
	{
	public:
		double d{};
		float f{};
		
	};

	class MyClass : public MyBase
	{
	public:
		enum class Enum : int
		{
			One,
			Two,
			Three
		};

		int x{0};
		Enum e{Enum::One};
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
	type.addProperty("e", &MyClass::e);

	{
		MyClass myClass;

		auto type = Reflection::Get<MyClass>();
		auto p = type->getProperty("x");
		p->setValue(myClass, "5");
		EXPECT_EQ(5, myClass.x);

		p = type->getProperty("e");
		p->setValue(myClass, "Two");
		EXPECT_EQ(MyClass::Enum::Two, myClass.e);
	}
}

TEST(Reflection, RegisterBaseClass)
{
	Reflection::Clear();

	auto& type = Reflection::Add<MyClass>("MyClass");
	type.addBase<MyBase>();
	type.addProperty("x", &MyClass::x);
	type.addProperty("e", &MyClass::e);

	auto properties = type.getProperties();
	EXPECT_EQ(properties.size(), 2);

	auto& typeBase = Reflection::Add<MyBase>("MyBase");
	typeBase.addProperty("d", &MyBase::d);
	typeBase.addProperty("f", &MyBase::f);

	properties = type.getProperties();
	EXPECT_EQ(properties.size(), 4);

	MyClass myClass;
	myClass.d = 1;

	auto p = type.getProperty("d");
	p->setValue(myClass, "2");
	EXPECT_EQ(myClass.d, 2);
}
