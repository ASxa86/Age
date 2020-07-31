#include <azule/core/ChildEvent.h>
#include <azule/core/Object.h>
#include <gtest/gtest.h>

using namespace azule;

class ObjectOne : public Object
{
public:
	ObjectOne() : ChildAdded{0}, ChildRemoved{0}
	{
		// this->addChildAddedHandler([this](ChildEvent* x) {
		//	ASSERT_TRUE(x != nullptr);
		//	EXPECT_EQ(this->getChild(), x->getChild());
		//	ChildAdded++;
		//});

		// this->addChildRemovedHandler([this](ChildEvent* x) {
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
		EXPECT_NO_THROW(this->addChild(std::make_unique<Object>()));
	}
};

TEST(Object, Constructor)
{
	EXPECT_NO_THROW(Object());
	EXPECT_NO_THROW(auto m = std::make_unique<Object>());
	EXPECT_TRUE(std::make_unique<Object>() != nullptr);
}

TEST(Object, setID)
{
	const auto object = std::make_unique<Object>();
	const auto id = std::string("id");
	object->setID(id);

	EXPECT_EQ(id, object->getID());
}

TEST(Object, getParent)
{
	const auto parent = std::make_unique<Object>();
	auto child = std::make_unique<Object>();
	auto cPtr = child.get();

	EXPECT_TRUE(parent->addChild(std::move(child)));
	EXPECT_EQ(parent.get(), cPtr->getParent());
}

TEST(Object, getParent_Recursive)
{
	const auto parent = std::make_unique<ObjectTwo>();
	auto child = std::make_unique<Object>();
	auto subchild = std::make_unique<Object>();

	const auto cPtr = child.get();
	const auto scPtr = subchild.get();

	EXPECT_TRUE(parent->addChild(std::move(child)));
	EXPECT_TRUE(cPtr->addChild(std::move(subchild)));
	EXPECT_EQ(parent.get(), scPtr->getParent<ObjectTwo>(Object::FindOption::Recursive));
}

TEST(Object, addChild)
{
	const auto parent = std::make_unique<Object>();
	auto child = std::make_unique<Object>();
	auto cPtr = child.get();

	EXPECT_TRUE(parent->addChild(std::move(child)));
	EXPECT_EQ(cPtr, parent->getChild());
}

TEST(Object, removeChild)
{
	const auto parent = std::make_unique<Object>();
	auto child = std::make_unique<Object>();
	auto cPtr = child.get();

	EXPECT_TRUE(parent->addChild(std::move(child)));
	EXPECT_TRUE(cPtr->remove() != nullptr);
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

// TEST(Object, childAdded)
//{
//	const auto parent = std::make_unique<ObjectOne>();
//
//	EXPECT_TRUE(parent->addChild(std::make_unique<Object>()));
//	EXPECT_TRUE(parent->addChild(std::make_unique<Object>()));
//	EXPECT_EQ(parent->getChildren().size(), parent->ChildAdded);
//}
//
// TEST(Object, childRemoved)
//{
//	const auto parent = std::make_unique<ObjectOne>();
//	auto child = std::make_unique<Object>();
//	const auto child = child.get();
//
//	EXPECT_TRUE(parent->addChild(child));
//	EXPECT_TRUE(child->remove());
//	EXPECT_EQ(1, parent->ChildRemoved);
//}