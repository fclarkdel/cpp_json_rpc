#include <gtest/gtest.h>

#include <cpp_json_rpc/response.hpp>

using namespace cpp_json_rpc;

TEST(response, constructor)
{
	response response;

	EXPECT_EQ(response.jsonrpc, "2.0");
	EXPECT_EQ(std::get<std::string>(response.result_or_error), "");
	EXPECT_EQ(std::get<std::monostate>(response.id), std::monostate());
}
TEST(response, constructor_with_result)
{
	response response("result");

	EXPECT_EQ(response.jsonrpc, "2.0");
	EXPECT_EQ(std::get<std::string>(response.result_or_error), "result");
	EXPECT_EQ(std::get<std::monostate>(response.id), std::monostate());
}
TEST(response, constructor_with_error)
{
	response response(error(0));

	EXPECT_EQ(response.jsonrpc, "2.0");
	EXPECT_EQ(std::get<error>(response.result_or_error).code, error(0).code);
	EXPECT_EQ(std::get<std::monostate>(response.id), std::monostate());
}
TEST(response, constructor_with_result_and_id)
{
	response response("result", 0);

	EXPECT_EQ(response.jsonrpc, "2.0");
	EXPECT_EQ(std::get<std::string>(response.result_or_error), "result");
	EXPECT_EQ(std::get<int>(response.id), 0);
}
TEST(response, constructor_with_error_and_id)
{
	response response(error(0), 0);

	EXPECT_EQ(response.jsonrpc, "2.0");
	EXPECT_EQ(std::get<error>(response.result_or_error).code, error(0).code);
	EXPECT_EQ(std::get<int>(response.id), 0);
}
TEST(response, equality_comparison)
{
	response response0("result", 0);
	response response1("result", 0);
	response response2;

	EXPECT_EQ(response0, response1);
	EXPECT_NE(response0, response2);
	EXPECT_NE(response1, response2);
}
TEST(response, copy_constructor)
{
	response original("result", 0);
	response copy(original);

	EXPECT_EQ(original, copy);
}
TEST(response, move_constructor)
{
	response original("result", 0);
	response copy(original);
	response move(std::move(copy));

	EXPECT_EQ(copy, response());
	EXPECT_EQ(original, move);
}
TEST(response, copy_assignment)
{
	response original("result", 0);
	response copy;
	copy = original;

	EXPECT_EQ(original, copy);
}
TEST(response, move_assignmnet)
{
	response original("result", 0);
	response copy = original;
	response move;
	move = std::move(copy);

	EXPECT_EQ(copy, response());
	EXPECT_EQ(original, move);
}