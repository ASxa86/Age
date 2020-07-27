#include <age/utilities/SharedLibrary.h>
#include <gtest/gtest.h>

using namespace age::utilities;

constexpr std::string_view LibraryName{"D:/age/build/bin/Debug/age-utilitiesd.dll"};

TEST(SharedLibrary, ConstructorLoad)
{
	SharedLibrary library(LibraryName);
	EXPECT_TRUE(library.loaded());
	EXPECT_EQ(library.location(), LibraryName);
}

TEST(SharedLibrary, Load)
{
	SharedLibrary library;
	EXPECT_TRUE(library.load(LibraryName));
	EXPECT_TRUE(library.loaded());
}

TEST(SharedLibrary, Unload)
{
	SharedLibrary library;
	EXPECT_TRUE(library.load(LibraryName));
	EXPECT_TRUE(library.loaded());
	library.unload();
	EXPECT_FALSE(library.loaded());
}

TEST(SharedLibrary, LoadCopyConstructor)
{
	SharedLibrary library(LibraryName);
	EXPECT_TRUE(library.loaded());

	SharedLibrary copy(library);
	EXPECT_TRUE(copy.loaded());
}

TEST(SharedLibrary, LoadCopyAssignment)
{
	SharedLibrary library(LibraryName);
	EXPECT_TRUE(library.loaded());

	SharedLibrary copy;
	EXPECT_FALSE(copy.loaded());

	copy = library;
	EXPECT_TRUE(copy.loaded());
}

TEST(SharedLibrary, LoadMoveConstructor)
{
	SharedLibrary library(LibraryName);
	EXPECT_TRUE(library.loaded());

	SharedLibrary copy(std::move(library));
	EXPECT_TRUE(copy.loaded());
}

TEST(SharedLibrary, LoadMoveAssignment)
{
	SharedLibrary library(LibraryName);
	EXPECT_TRUE(library.loaded());

	SharedLibrary copy;
	EXPECT_FALSE(copy.loaded());

	copy = std::move(library);
	EXPECT_TRUE(copy.loaded());
}
