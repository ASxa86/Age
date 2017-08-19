#include <age/core/ChildEvent.h>
#include <age/core/Object.h>
#include <gtest/gtest.h>

using namespace age::core;

class ObjectOne : public Object
{
public:
	ObjectOne() : ChildAdded{0}, ChildRemoved{0}
	{
		//this->addChildAddedHandler([this](ChildEvent* x) {
		//	ASSERT_TRUE(x != nullptr);
		//	EXPECT_EQ(this->getChild(), x->getChild());
		//	ChildAdded++;
		//});

		//this->addChildRemovedHandler([this](ChildEvent* x) {
		//	ASSERT_TRUE(x != nullptr);
		//	EXPECT_TRUE(x->getChild() != nullptr);
		//	ChildRemoved++;
		//});
	}

	int ChildAdded;
	int ChildRemoved;
};

class ObjectTwo : public Object
{
public:
	ObjectTwo()
	{
		EXPECT_NO_THROW(this->addChild(std::make_shared<Object>()));
	}
};

TEST(Object, Constructor)
{
	EXPECT_NO_THROW(Object());
	EXPECT_NO_THROW(std::make_shared<Object>());
	EXPECT_TRUE(std::make_shared<Object>() != nullptr);
}

TEST(Object, setID)
{
	const auto object = std::make_shared<Object>();
	const auto id = std::string("id");
	object->setID(id);

	EXPECT_EQ(id, object->getID());
}

TEST(Object, getParent)
{
	const auto parent = std::make_shared<Object>();
	auto child = std::make_shared<Object>();

	EXPECT_TRUE(parent->addChild(child));
	EXPECT_EQ(parent.get(), child->getParent());
}

TEST(Object, getParent_Recursive)
{
	const auto parent = std::make_shared<ObjectTwo>();
	const auto child = std::make_shared<Object>();
	const auto subchild = std::make_shared<Object>();

	EXPECT_TRUE(parent->addChild(child));
	EXPECT_TRUE(child->addChild(subchild));
	EXPECT_EQ(parent.get(), subchild->getParent<ObjectTwo>(true));
}

TEST(Object, addChild)
{
	const auto parent = std::make_shared<Object>();
	auto child = std::make_shared<Object>();

	EXPECT_TRUE(parent->addChild(child));
	EXPECT_EQ(child, parent->getChild());
}

TEST(Object, removeChild)
{
	const auto parent = std::make_shared<Object>();
	auto child = std::make_shared<Object>();

	EXPECT_TRUE(parent->addChild(child));
	EXPECT_TRUE(parent->removeChild(child));
	EXPECT_TRUE(parent->getChildren().empty());
}

TEST(Object, getChild)
{
	const auto parent = std::make_shared<Object>();

	EXPECT_TRUE(parent->addChild(std::make_shared<ObjectOne>()));
	EXPECT_TRUE(parent->addChild(std::make_shared<ObjectTwo>()));
	EXPECT_TRUE(parent->getChild<ObjectOne>() != nullptr);
	EXPECT_TRUE(parent->getChild<ObjectTwo>() != nullptr);
}

TEST(Object, getChildren)
{
	const auto parent = std::make_shared<Object>();

	EXPECT_TRUE(parent->addChild(std::make_shared<ObjectOne>()));
	EXPECT_TRUE(parent->addChild(std::make_shared<ObjectTwo>()));

	EXPECT_EQ(size_t{2}, parent->getChildren().size());
	EXPECT_EQ(size_t{1}, parent->getChildren<ObjectOne>().size());
	EXPECT_EQ(size_t{1}, parent->getChildren<ObjectTwo>().size());
}

//TEST(Object, childAdded)
//{
//	const auto parent = std::make_shared<ObjectOne>();
//
//	EXPECT_TRUE(parent->addChild(std::make_shared<Object>()));
//	EXPECT_TRUE(parent->addChild(std::make_shared<Object>()));
//	EXPECT_EQ(parent->getChildren().size(), parent->ChildAdded);
//}
//
//TEST(Object, childRemoved)
//{
//	const auto parent = std::make_shared<ObjectOne>();
//	auto child = std::make_shared<Object>();
//	const auto child = child.get();
//
//	EXPECT_TRUE(parent->addChild(child));
//	EXPECT_TRUE(child->remove());
//	EXPECT_EQ(1, parent->ChildRemoved);
//}
