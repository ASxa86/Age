#include <gtest/gtest.h>

#include <QtWidgets/QApplication>

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	// Construction of qt widgets require that a QApplication object exists.
	QApplication app(argc, argv);

	return RUN_ALL_TESTS();
}
