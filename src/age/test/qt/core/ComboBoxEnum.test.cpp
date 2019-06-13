#include <age/qt/core/ComboBoxEnum.h>
#include <gtest/gtest.h>

namespace
{
	enum class TestEnum : int
	{
		One,
		Two,
		Three
	};
}

TEST(ComboBoxEnum, TestEnum)
{
	age::core::qt::ComboBoxEnum<TestEnum> cbEnum;
	EXPECT_EQ(cbEnum.count(), 3);
	EXPECT_EQ(cbEnum.getCurrentEnum(), TestEnum::One);
	EXPECT_EQ(cbEnum.currentText().toStdString(), "One");

	cbEnum.setCurrentEnum(TestEnum::Two);
	EXPECT_EQ(cbEnum.getCurrentEnum(), TestEnum::Two);
	EXPECT_EQ(cbEnum.currentText().toStdString(), "Two");

	cbEnum.setCurrentEnum(TestEnum::Three);
	EXPECT_EQ(cbEnum.getCurrentEnum(), TestEnum::Three);
	EXPECT_EQ(cbEnum.currentText().toStdString(), "Three");
}
