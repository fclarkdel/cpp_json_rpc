#include <gtest/gtest.h>

#include <cpp_json_rpc/proxy.hpp>

using namespace cpp_json_rpc;

TEST(proxy, constructor)
{
	proxy proxy;

	EXPECT_EQ(proxy.url, "");
}
TEST(proxy, constructor_with_url)
{
	std::string url = "url";

	proxy proxy(url);

	EXPECT_EQ(proxy.url, url);
}
TEST(proxy, equality_comparison)
{
	std::string url = "url";

	proxy proxy0(url);
	proxy proxy1(url);
	proxy proxy2;

	EXPECT_EQ(proxy0, proxy1);
	EXPECT_NE(proxy0, proxy2);
	EXPECT_NE(proxy1, proxy2);
}
TEST(proxy, copy_constructor)
{
	std::string url = "url";

	proxy original(url);

	proxy copy(original);

	EXPECT_EQ(original, copy);
}
TEST(proxy, move_constructor)
{
	std::string url = "url";

	proxy original(url);

	proxy copy(original);

	proxy move(std::move(copy));

	// Moving should leave object in a "default" state.
	EXPECT_EQ(copy, proxy());
	EXPECT_EQ(original, move);
}
TEST(proxy, copy_assignment)
{
	std::string url = "url";

	proxy original(url);

	proxy copy;
	copy = original;

	EXPECT_EQ(original, copy);
}
TEST(proxy, move_assignmnet)
{
	std::string url = "url";

	proxy original(url);

	proxy copy = original;

	proxy move;
	move = std::move(copy);

	// Moving should leave object in a "default" state.
	EXPECT_EQ(copy, proxy());
	EXPECT_EQ(original, move);
}