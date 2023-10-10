#include <gtest/gtest.h>

#include <CppJsonRpc/Request.hpp>

using namespace CppJsonRpc;

TEST(Request, constructor)
{
	Request request;

	EXPECT_EQ(request.jsonrpc, Jsonrpc("2.0"));
	EXPECT_EQ(request.method, Method());
	EXPECT_EQ(request.params, Params());
	EXPECT_EQ(std::get<std::monostate>(request.id), std::monostate());
}
TEST(Request, constructor_with_method)
{
	Request request("method");

	EXPECT_EQ(request.jsonrpc, Jsonrpc("2.0"));
	EXPECT_EQ(request.method, Method("method"));
	EXPECT_EQ(request.params, Params());
	EXPECT_EQ(std::get<std::monostate>(request.id), std::monostate());
}
TEST(Request, constructor_with_method_params)
{
	Request request("method", "params");

	EXPECT_EQ(request.jsonrpc, Jsonrpc("2.0"));
	EXPECT_EQ(request.method, Method("method"));
	EXPECT_EQ(request.params, Params("params"));
	EXPECT_EQ(std::get<std::monostate>(request.id), std::monostate());
}
TEST(Request, constructor_with_method_params_id)
{
	Request request_int_id("method", "params", 0);

	EXPECT_EQ(request_int_id.jsonrpc, Jsonrpc("2.0"));
	EXPECT_EQ(request_int_id.method, Method("method"));
	EXPECT_EQ(request_int_id.params, Params("params"));
	EXPECT_EQ(std::get<int>(request_int_id.id), 0);

	Request request_double_id("method", "params", 0.0);

	EXPECT_EQ(request_double_id.jsonrpc, Jsonrpc("2.0"));
	EXPECT_EQ(request_double_id.method, Method("method"));
	EXPECT_EQ(request_double_id.params, Params("params"));
	EXPECT_EQ(std::get<double>(request_double_id.id), 0.0);

	Request request_string_id("method", "params", "0");

	EXPECT_EQ(request_string_id.jsonrpc, Jsonrpc("2.0"));
	EXPECT_EQ(request_string_id.method, Method("method"));
	EXPECT_EQ(request_string_id.params, Params("params"));
	EXPECT_EQ(std::get<std::string>(request_string_id.id), "0");
}
TEST(Request, equality_comparison)
{
	Request request0("method", "params", 0);
	Request request1("method", "params", 0);
	Request request2;

	EXPECT_EQ(request0, request1);
	EXPECT_NE(request0, request2);
	EXPECT_NE(request1, request2);
}
TEST(Request, copy_constructor)
{
	Request original("method", "params");
	Request copy(original);

	EXPECT_EQ(original, copy);
}
TEST(Request, move_constructor)
{
	Request original("method", "params");
	Request copy(original);
	Request move(std::move(copy));

	// Moving should leave object in a "default" state.
	EXPECT_EQ(copy, Request());
	EXPECT_EQ(original, move);
}
TEST(Request, copy_assignment)
{
	Request original("method", "params");
	Request copy;
	copy = original;

	EXPECT_EQ(original, copy);
}
TEST(Request, move_assignmnet)
{
	Request original("method", "params");
	Request copy = original;
	Request move;
	move = std::move(copy);

	// Moving should leave object in a "default" state.
	EXPECT_EQ(copy, Request());
	EXPECT_EQ(original, move);
}