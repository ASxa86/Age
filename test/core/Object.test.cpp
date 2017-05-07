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
};

TEST(Object, Constructor)
{
	EXPECT_NO_THROW(Object());
	EXPECT_NO_THROW(std::make_unique<Object>());
	EXPECT_TRUE(std::make_unique<Object>() != nullptr);
}

TEST(Object, setID)
{
	const auto object = std::make_unique<Object>();
	const auto id = std::string("id");
	object->setID(id);

	EXPECT_EQ(id, object->getID());
}

TEST(Object, setParent)
{
	const auto parent = std::make_unique<Object>();
	auto child = std::make_unique<Object>();
	const auto raw = child.get();

	EXPECT_TRUE(parent->addChild(std::move(child)));
	EXPECT_EQ(parent.get(), raw->getParent());
}

TEST(Object, addChild)
{
	const auto parent = std::make_unique<Object>();
	auto child = std::make_unique<Object>();
	const auto raw = child.get();

	EXPECT_TRUE(parent->addChild(std::move(child)));
	EXPECT_EQ(raw, parent->getChild());
}

TEST(Object, removeChild)
{
	const auto parent = std::make_unique<Object>();
	auto child = std::make_unique<Object>();
	const auto raw = child.get();

	EXPECT_TRUE(parent->addChild(std::move(child)));
	EXPECT_TRUE(parent->removeChild(raw));
	EXPECT_TRUE(parent->getChildren().empty());
}

TEST(Object, getChild)
{
	const auto parent = std::make_unique<Object>();

	EXPECT_TRUE(parent->addChild(std::make_unique<ObjectOne>()));
	EXPECT_TRUE(parent->addChild(std::make_unique<ObjectTwo>()));
	EXPECT_TRUE(parent->getChild<ObjectOne>() != nullptr);
	EXPECT_TRUE(parent->getChild<ObjectTwo>() != nullptr);
}

TEST(Object, getChildren)
{
	const auto parent = std::make_unique<Object>();

	EXPECT_TRUE(parent->addChild(std::make_unique<ObjectOne>()));
	EXPECT_TRUE(parent->addChild(std::make_unique<ObjectTwo>()));

	EXPECT_EQ(size_t{2}, parent->getChildren().size());
	EXPECT_EQ(size_t{1}, parent->getChildren<ObjectOne>().size());
	EXPECT_EQ(size_t{1}, parent->getChildren<ObjectTwo>().size());
}

//TEST(Object, childAdded)
//{
//	const auto parent = std::make_unique<ObjectOne>();
//
//	EXPECT_TRUE(parent->addChild(std::make_unique<Object>()));
//	EXPECT_TRUE(parent->addChild(std::make_unique<Object>()));
//	EXPECT_EQ(parent->getChildren().size(), parent->ChildAdded);
//}
//
//TEST(Object, childRemoved)
//{
//	const auto parent = std::make_unique<ObjectOne>();
//	auto child = std::make_unique<Object>();
//	const auto raw = child.get();
//
//	EXPECT_TRUE(parent->addChild(std::move(child)));
//	EXPECT_TRUE(raw->remove());
//	EXPECT_EQ(1, parent->ChildRemoved);
//}
