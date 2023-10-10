#include <gtest/gtest.h>

#include <CppJsonRpc/Response.hpp>

using namespace CppJsonRpc;

TEST(Response, constructor)
{
	Response response;

	EXPECT_EQ(response.jsonrpc, "2.0");
	EXPECT_EQ(std::get<std::string>(response.result_or_error), "");
	EXPECT_EQ(std::get<std::monostate>(response.id), std::monostate());
}
TEST(Response, constructor_with_result)
{
	Response response("result");

	EXPECT_EQ(response.jsonrpc, "2.0");
	EXPECT_EQ(std::get<std::string>(response.result_or_error), "result");
	EXPECT_EQ(std::get<std::monostate>(response.id), std::monostate());
}
TEST(Response, constructor_with_error)
{
	Response response(Error(0));

	EXPECT_EQ(response.jsonrpc, "2.0");
	EXPECT_EQ(std::get<Error>(response.result_or_error).code, Error(0).code);
	EXPECT_EQ(std::get<std::monostate>(response.id), std::monostate());
}
TEST(Response, constructor_with_result_and_id)
{
	Response response("result", 0);

	EXPECT_EQ(response.jsonrpc, "2.0");
	EXPECT_EQ(std::get<std::string>(response.result_or_error), "result");
	EXPECT_EQ(std::get<int>(response.id), 0);
}
TEST(Response, constructor_with_error_and_id)
{
	Response response(Error(0), 0);

	EXPECT_EQ(response.jsonrpc, "2.0");
	EXPECT_EQ(std::get<Error>(response.result_or_error).code, Error(0).code);
	EXPECT_EQ(std::get<int>(response.id), 0);
}
TEST(Response, equality_comparison)
{
	Response response0("result", 0);
	Response response1("result", 0);
	Response response2;

	EXPECT_EQ(response0, response1);
	EXPECT_NE(response0, response2);
	EXPECT_NE(response1, response2);
}
TEST(Response, copy_constructor)
{
	Response original("result", 0);
	Response copy(original);

	EXPECT_EQ(original, copy);
}
TEST(Response, move_constructor)
{
	Response original("result", 0);
	Response copy(original);
	Response move(std::move(copy));

	EXPECT_EQ(copy, Response());
	EXPECT_EQ(original, move);
}
TEST(Response, copy_assignment)
{
	Response original("result", 0);
	Response copy;
	copy = original;

	EXPECT_EQ(original, copy);
}
TEST(Response, move_assignmnet)
{
	Response original("result", 0);
	Response copy = original;
	Response move;
	move = std::move(copy);

	EXPECT_EQ(copy, Response());
	EXPECT_EQ(original, move);
}