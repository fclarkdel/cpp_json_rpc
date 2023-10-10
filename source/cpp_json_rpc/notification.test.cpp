#include <gtest/gtest.h>

#include <cpp_json_rpc/notification.hpp>

using namespace cpp_json_rpc;

TEST(notification, constructor)
{
	notification notification;

	EXPECT_EQ(notification.jsonrpc, Jsonrpc("2.0"));
	EXPECT_EQ(notification.method, Method());
	EXPECT_EQ(notification.params, Params());
}
TEST(notification, constructor_with_method)
{
	notification notification("method");

	EXPECT_EQ(notification.jsonrpc, Jsonrpc("2.0"));
	EXPECT_EQ(notification.method, Method("method"));
	EXPECT_EQ(notification.params, Params(std::nullopt));
}
TEST(notification, constructor_with_method_and_params)
{
	notification notification("method", "params");

	EXPECT_EQ(notification.jsonrpc, Jsonrpc("2.0"));
	EXPECT_EQ(notification.method, Method("method"));
	EXPECT_EQ(notification.params, Params("params"));
}
TEST(notification, equality_comparison)
{
	notification notification0("method", "params");
	notification notification1("method", "params");
	notification notification2;

	EXPECT_EQ(notification0, notification1);
	EXPECT_NE(notification0, notification2);
	EXPECT_NE(notification1, notification2);
}
TEST(notification, copy_constructor)
{
	notification original("method", "params");
	notification copy(original);

	EXPECT_EQ(original, copy);
}
TEST(notification, move_constructor)
{
	notification original("method", "params");
	notification copy(original);
	notification move(std::move(copy));

	// Moving should leave object in a "default" state.
	EXPECT_EQ(copy, notification());
	EXPECT_EQ(original, move);
}
TEST(notification, copy_assignment)
{
	notification original("method", "params");
	notification copy;
	copy = original;

	EXPECT_EQ(original, copy);
}
TEST(notification, move_assignmnet)
{
	notification original("method", "params");
	notification copy = original;
	notification move;
	move = std::move(copy);

	// Moving should leave object in a "default" state.
	EXPECT_EQ(copy, notification());
	EXPECT_EQ(original, move);
}