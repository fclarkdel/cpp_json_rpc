#include <gtest/gtest.h>

#include <CppJsonRpc/Error.hpp>

using namespace CppJsonRpc;

TEST(Error, constructor)
{
	Error error;

	EXPECT_EQ(error.code, 0);
	EXPECT_EQ(error.message, "");
	EXPECT_EQ(error.data, std::nullopt);
}
TEST(Error, constructor_with_code)
{
	Error error(1);

	EXPECT_EQ(error.code, 1);
	EXPECT_EQ(error.message, "");
	EXPECT_EQ(error.data, std::nullopt);
}
TEST(Error, constructor_with_code_and_message)
{
	Error error(1, "message");

	EXPECT_EQ(error.code, 1);
	EXPECT_EQ(error.message, "message");
	EXPECT_EQ(error.data, std::nullopt);
}
TEST(Error, constructor_with_code_and_message_and_data)
{
	Error error(1, "message", "data");

	EXPECT_EQ(error.code, 1);
	EXPECT_EQ(error.message, "message");
	EXPECT_EQ(error.data, "data");
}
TEST(Error, equality_comparison)
{
	Error error0(1, "message", "data");
	Error error1(1, "message", "data");
	Error error2;

	EXPECT_EQ(error0, error1);
	EXPECT_NE(error0, error2);
	EXPECT_NE(error1, error2);
}
TEST(Error, copy_constructor)
{
	Error original(1, "message", "data");
	Error copy(original);

	EXPECT_EQ(original, copy);
}
TEST(Error, move_constructor)
{
	Error original(1, "message", "data");
	Error copy(original);
	Error move(std::move(copy));

	// Moving should leave object in a "default" state.
	EXPECT_EQ(copy, Error());
	EXPECT_EQ(original, move);
}
TEST(Error, copy_assignment)
{
	Error original(1, "message", "data");
	Error copy;
	copy = original;

	EXPECT_EQ(original, copy);
}
TEST(Error, move_assignmnet)
{
	Error original(1, "message", "data");
	Error copy = original;
	Error move;
	move = std::move(copy);

	// Moving should leave object in a "default" state.
	EXPECT_EQ(copy, Error());
	EXPECT_EQ(original, move);
}