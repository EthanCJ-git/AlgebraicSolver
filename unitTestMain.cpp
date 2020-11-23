#include <gtest/gtest.h>
#include "expression.h"


TEST(oneExpression, plus)
{
	std::string testString("5+5");
	std::string answer("+{5, 5}");
	expression* null{};
	expression testEx(testString, null);
	EXPECT_EQ(testEx.toString(), answer);
}

TEST(oneExpression, minus)
{
	std::string testString("5-5");
	std::string answer("-{5, 5}");
	expression* null{};
	expression testEx(testString, null);
	EXPECT_EQ(testEx.toString(), answer);
}

TEST(oneExpression, multiply)
{
	std::string testString("5*5");
	std::string answer("*{5, 5}");
	expression* null{};
	expression testEx(testString, null);
	EXPECT_EQ(testEx.toString(), answer);
}

TEST(oneExpression, divide)
{
	std::string testString("5/5");
	std::string answer("/{5, 5}");
	expression* null{};
	expression testEx(testString, null);
	EXPECT_EQ(testEx.toString(), answer);
}

TEST(oneExpression, exponent)
{
	std::string testString("5^5");
	std::string answer("^{5, 5}");
	expression* null{};
	expression testEx(testString, null);
	EXPECT_EQ(testEx.toString(), answer);
}

TEST(compose, first)
{
	std::string testString("(4*(5+5))/4");
	std::string answer("/{*{4, +{5, 5}}, 4}");
	expression* null{};
	expression testEx(testString, null);
	EXPECT_EQ(testEx.toString(), answer);
}

int main(int argc, char **argv)
{
	
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}
