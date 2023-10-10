#include <gtest/gtest.h>

#include <CppJsonRpc/Notification.hpp>

using namespace CppJsonRpc;

TEST(Notification, constructor)
{
	Notification notification;

	EXPECT_EQ(notification.jsonrpc, Jsonrpc("2.0"));
	EXPECT_EQ(notification.method, Method());
	EXPECT_EQ(notification.params, Params());
}
TEST(Notification, constructor_with_method)
{
	Notification notification("method");

	EXPECT_EQ(notification.jsonrpc, Jsonrpc("2.0"));
	EXPECT_EQ(notification.method, Method("method"));
	EXPECT_EQ(notification.params, Params(std::nullopt));
}
TEST(Notification, constructor_with_method_and_params)
{
	Notification notification("method", "params");

	EXPECT_EQ(notification.jsonrpc, Jsonrpc("2.0"));
	EXPECT_EQ(notification.method, Method("method"));
	EXPECT_EQ(notification.params, Params("params"));
}
TEST(Notification, equality_comparison)
{
	Notification notification0("method", "params");
	Notification notification1("method", "params");
	Notification notification2;

	EXPECT_EQ(notification0, notification1);
	EXPECT_NE(notification0, notification2);
	EXPECT_NE(notification1, notification2);
}
TEST(Notification, copy_constructor)
{
	Notification original("method", "params");
	Notification copy(original);

	EXPECT_EQ(original, copy);
}
TEST(Notification, move_constructor)
{
	Notification original("method", "params");
	Notification copy(original);
	Notification move(std::move(copy));

	// Moving should leave object in a "default" state.
	EXPECT_EQ(copy, Notification());
	EXPECT_EQ(original, move);
}
TEST(Notification, copy_assignment)
{
	Notification original("method", "params");
	Notification copy;
	copy = original;

	EXPECT_EQ(original, copy);
}
TEST(Notification, move_assignmnet)
{
	Notification original("method", "params");
	Notification copy = original;
	Notification move;
	move = std::move(copy);

	// Moving should leave object in a "default" state.
	EXPECT_EQ(copy, Notification());
	EXPECT_EQ(original, move);
}