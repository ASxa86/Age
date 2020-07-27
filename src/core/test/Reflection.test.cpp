#include <azule/core/Reflection.h>
#include <gtest/gtest.h>
#include <functional>

using namespace age::core;

namespace
{
	class MyBase : public Object
	{
	public:
		void setD(double x)
		{
			this->d = x;
		}

		double getD() const
		{
			return this->d;
		}

		void add()
		{
			this->d += this->f;
		}

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

		void setX(int x)
		{
			this->x = x;
		}

		int getX() const
		{
			return this->x;
		}

		void setXRef(const int& x)
		{
			this->x = x;
		}

		const int& getXRef() const
		{
			return this->x;
		}

		std::filesystem::path path;
		int x{0};
		Enum e{Enum::One};
	};
}

TEST(AnyRef, Constructor)
{
	MyClass myClass;
	Reflection::Instance().add<MyClass>("MyClass");
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

TEST(TemplateMethod, SetValueRef)
{
	MyClass myClass;
	TemplateMethod<void (MyClass::*)(const int&), const int& (MyClass::*)() const> property("x", &MyClass::setXRef, &MyClass::getXRef);

	EXPECT_TRUE(property.setValue(myClass, "1"));
	EXPECT_EQ(1, myClass.x);

	EXPECT_TRUE(property.setValue(myClass, "-1"));
	EXPECT_EQ(-1, myClass.x);
}

TEST(TemplateProperty, GetValueRef)
{
	MyClass myClass;
	TemplateMethod<void (MyClass::*)(const int&), const int& (MyClass::*)() const> property("x", &MyClass::setXRef, &MyClass::getXRef);

	EXPECT_EQ("0", property.getValue(myClass));

	myClass.x = 1;

	EXPECT_EQ("1", property.getValue(myClass));

	myClass.x = -1;

	EXPECT_EQ("-1", property.getValue(myClass));
}

TEST(TemplateMethod, GetValue)
{
	MyClass myClass;
	TemplateMethod<void (MyClass::*)(int), int (MyClass::*)() const> property("x", &MyClass::setX, &MyClass::getX);

	EXPECT_EQ("0", property.getValue(myClass));

	myClass.x = 1;

	EXPECT_EQ("1", property.getValue(myClass));

	myClass.x = -1;

	EXPECT_EQ("-1", property.getValue(myClass));
}

TEST(ReflType, Copy)
{
	std::map<std::type_index, ReflType> ReflMap;
	MyClass myClass;
	ReflType type("MyClass", typeid(MyClass));
	type.Creator = std::make_shared<ReflCreator<MyClass>>();

	const auto copy = type;
	EXPECT_EQ(copy.Name, type.Name);
	EXPECT_EQ(copy.Creator, type.Creator);
	ReflMap.insert({typeid(MyClass), copy});

	auto& copied = ReflMap.at(typeid(MyClass));
}

TEST(Reflection, Register)
{
	Reflection::Instance().clear();

	auto& type = Reflection::Instance().add<MyClass>("MyClass");
	type.addBase<MyBase>();
	type.addProperty("x", &MyClass::x);
	type.addProperty("e", &MyClass::e);

	auto& typeBase = Reflection::Instance().add<MyBase>("MyBase");
	typeBase.addBase<Object>();

	{
		MyClass myClass;
		MyBase& myBase = myClass;

		auto type = Reflection::Instance().get<MyClass>();
		ASSERT_TRUE(type != nullptr);

		auto p = type->getProperty("x");
		ASSERT_TRUE(p != nullptr);

		p->setValue(myClass, "5");
		EXPECT_EQ(5, myClass.x);

		p = type->getProperty("e");
		ASSERT_TRUE(p != nullptr);

		p->setValue(myClass, "Two");
		EXPECT_EQ(MyClass::Enum::Two, myClass.e);

		type = Reflection::Instance().get(myBase);
		ASSERT_TRUE(type != nullptr);
		p = type->getProperty("e");
		p->setValue(myBase, "Three");
		EXPECT_EQ(MyClass::Enum::Three, myClass.e);
	}
}

TEST(Reflection, RegisterBaseClass)
{
	Reflection::Instance().clear();

	auto& type = Reflection::Instance().add<MyClass>("MyClass");
	type.addBase<MyBase>();
	type.addProperty("x", &MyClass::x);
	type.addProperty("e", &MyClass::e);

	auto properties = type.getProperties();
	EXPECT_EQ(properties.size(), 2);

	auto& typeBase = Reflection::Instance().add<MyBase>("MyBase");
	typeBase.addProperty("d", &MyBase::d);
	typeBase.addProperty("f", &MyBase::f);
	typeBase.addMethod("D", &MyBase::setD, &MyBase::getD);

	properties = type.getProperties();
	EXPECT_EQ(properties.size(), 5);

	MyClass myClass;
	myClass.d = 1;

	auto p = type.getProperty("D");
	p->setValue(myClass, "2");
	EXPECT_DOUBLE_EQ(myClass.d, 2);

	p = typeBase.getProperty("f");
	p->setValue(myClass, "1.0f");
	EXPECT_FLOAT_EQ(myClass.f, 1.0f);
}

TEST(Reflection, Create)
{
	Reflection::Instance().clear();

	auto& type = Reflection::Instance().add<MyClass>("MyClass");
	type.addBase<MyBase>();
	type.addProperty("x", &MyClass::x);
	type.addProperty("e", &MyClass::e);

	auto& typeBase = Reflection::Instance().add<MyBase>("MyBase");
	typeBase.addProperty("d", &MyBase::d);
	typeBase.addProperty("f", &MyBase::f);
	typeBase.addMethod("D", &MyBase::setD, &MyBase::getD);

	auto reflObj = Reflection::Instance().create("MyClass");
	ASSERT_TRUE(reflObj != nullptr);
	EXPECT_EQ(typeid(*reflObj), typeid(MyClass));

	reflObj = Reflection::Instance().create("MyBase");
	ASSERT_TRUE(reflObj != nullptr);
	EXPECT_EQ(typeid(*reflObj), typeid(MyBase));
}
