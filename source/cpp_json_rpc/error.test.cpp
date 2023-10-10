#include <gtest/gtest.h>

#include <cpp_json_rpc/error.hpp>

using namespace cpp_json_rpc;

TEST(error, constructor)
{
	error error;

	EXPECT_EQ(error.code, 0);
	EXPECT_EQ(error.message, "");
	EXPECT_EQ(error.data, std::nullopt);
}
TEST(error, constructor_with_code)
{
	error error(1);

	EXPECT_EQ(error.code, 1);
	EXPECT_EQ(error.message, "");
	EXPECT_EQ(error.data, std::nullopt);
}
TEST(error, constructor_with_code_and_message)
{
	error error(1, "message");

	EXPECT_EQ(error.code, 1);
	EXPECT_EQ(error.message, "message");
	EXPECT_EQ(error.data, std::nullopt);
}
TEST(error, constructor_with_code_and_message_and_data)
{
	error error(1, "message", "data");

	EXPECT_EQ(error.code, 1);
	EXPECT_EQ(error.message, "message");
	EXPECT_EQ(error.data, "data");
}
TEST(error, equality_comparison)
{
	error error0(1, "message", "data");
	error error1(1, "message", "data");
	error error2;

	EXPECT_EQ(error0, error1);
	EXPECT_NE(error0, error2);
	EXPECT_NE(error1, error2);
}
TEST(error, copy_constructor)
{
	error original(1, "message", "data");
	error copy(original);

	EXPECT_EQ(original, copy);
}
TEST(error, move_constructor)
{
	error original(1, "message", "data");
	error copy(original);
	error move(std::move(copy));

	// Moving should leave object in a "default" state.
	EXPECT_EQ(copy, error());
	EXPECT_EQ(original, move);
}
TEST(error, copy_assignment)
{
	error original(1, "message", "data");
	error copy;
	copy = original;

	EXPECT_EQ(original, copy);
}
TEST(error, move_assignmnet)
{
	error original(1, "message", "data");
	error copy = original;
	error move;
	move = std::move(copy);

	// Moving should leave object in a "default" state.
	EXPECT_EQ(copy, error());
	EXPECT_EQ(original, move);
}