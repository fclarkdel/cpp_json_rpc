#include <gtest/gtest.h>

#include <cpp_json_rpc/request.hpp>

using namespace cpp_json_rpc;

TEST(request, constructor)
{
	request request;

	EXPECT_EQ(request.jsonrpc, Jsonrpc("2.0"));
	EXPECT_EQ(request.method, Method());
	EXPECT_EQ(request.params, Params());
	EXPECT_EQ(std::get<std::monostate>(request.id), std::monostate());
}
TEST(request, constructor_with_method)
{
	request request("method");

	EXPECT_EQ(request.jsonrpc, Jsonrpc("2.0"));
	EXPECT_EQ(request.method, Method("method"));
	EXPECT_EQ(request.params, Params());
	EXPECT_EQ(std::get<std::monostate>(request.id), std::monostate());
}
TEST(request, constructor_with_method_params)
{
	request request("method", "params");

	EXPECT_EQ(request.jsonrpc, Jsonrpc("2.0"));
	EXPECT_EQ(request.method, Method("method"));
	EXPECT_EQ(request.params, Params("params"));
	EXPECT_EQ(std::get<std::monostate>(request.id), std::monostate());
}
TEST(request, constructor_with_method_params_id)
{
	request request_int_id("method", "params", 0);

	EXPECT_EQ(request_int_id.jsonrpc, Jsonrpc("2.0"));
	EXPECT_EQ(request_int_id.method, Method("method"));
	EXPECT_EQ(request_int_id.params, Params("params"));
	EXPECT_EQ(std::get<int>(request_int_id.id), 0);

	request request_double_id("method", "params", 0.0);

	EXPECT_EQ(request_double_id.jsonrpc, Jsonrpc("2.0"));
	EXPECT_EQ(request_double_id.method, Method("method"));
	EXPECT_EQ(request_double_id.params, Params("params"));
	EXPECT_EQ(std::get<double>(request_double_id.id), 0.0);

	request request_string_id("method", "params", "0");

	EXPECT_EQ(request_string_id.jsonrpc, Jsonrpc("2.0"));
	EXPECT_EQ(request_string_id.method, Method("method"));
	EXPECT_EQ(request_string_id.params, Params("params"));
	EXPECT_EQ(std::get<std::string>(request_string_id.id), "0");
}
TEST(request, equality_comparison)
{
	request request0("method", "params", 0);
	request request1("method", "params", 0);
	request request2;

	EXPECT_EQ(request0, request1);
	EXPECT_NE(request0, request2);
	EXPECT_NE(request1, request2);
}
TEST(request, copy_constructor)
{
	request original("method", "params");
	request copy(original);

	EXPECT_EQ(original, copy);
}
TEST(request, move_constructor)
{
	request original("method", "params");
	request copy(original);
	request move(std::move(copy));

	// Moving should leave object in a "default" state.
	EXPECT_EQ(copy, request());
	EXPECT_EQ(original, move);
}
TEST(request, copy_assignment)
{
	request original("method", "params");
	request copy;
	copy = original;

	EXPECT_EQ(original, copy);
}
TEST(request, move_assignmnet)
{
	request original("method", "params");
	request copy = original;
	request move;
	move = std::move(copy);

	// Moving should leave object in a "default" state.
	EXPECT_EQ(copy, request());
	EXPECT_EQ(original, move);
}
TEST(request, to_json)
{
	request req("method");

	// {"jsonrpc":"2.0","method":"method","id":null}
	std::string expected = "{\"jsonrpc\":\"2.0\",\"method\":\"method\",\"id\":null}";

	EXPECT_EQ(expected, req.to_json());

	req = request("method", "[0, 1, 2]");

	// {"jsonrpc":"2.0","method":"method","id":null}
	expected = "{\"jsonrpc\":\"2.0\",\"method\":\"method\",\"params\":[0, 1, 2],\"id\":null}";

	EXPECT_EQ(expected, req.to_json());

	req = request("method", "[0, 1, 2]", 0);

	// {"jsonrpc":"2.0","method":"method","id":0}
	expected = "{\"jsonrpc\":\"2.0\",\"method\":\"method\",\"params\":[0, 1, 2],\"id\":0}";

	EXPECT_EQ(expected, req.to_json());

	req = request("method", "[0, 1, 2]", 0.52346);

	// {"jsonrpc":"2.0","method":"method","id":0.52346}
	expected = "{\"jsonrpc\":\"2.0\",\"method\":\"method\",\"params\":[0, 1, 2],\"id\":0.52346}";

	EXPECT_EQ(expected, req.to_json());

	req = request("method", "[0, 1, 2]", "0");

	// {"jsonrpc":"2.0","method":"method","id":"0"}
	expected = "{\"jsonrpc\":\"2.0\",\"method\":\"method\",\"params\":[0, 1, 2],\"id\":\"0\"}";

	EXPECT_EQ(expected, req.to_json());
}