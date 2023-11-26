#include <gtest/gtest.h>

#include <cpp_json_rpc/session.hpp>

using namespace cpp_json_rpc;

TEST(session, constructor)
{
	session proxy;

	EXPECT_EQ(proxy.get_url(), "");
}
TEST(session, constructor_with_url)
{
	std::string url = "url";

	session proxy(url);

	EXPECT_EQ(proxy.get_url(), url);
}
TEST(session, equality_comparison)
{
	std::string url = "url";

	session proxy0(url);
	session proxy1(url);
	session proxy2;

	EXPECT_EQ(proxy0, proxy1);
	EXPECT_NE(proxy0, proxy2);
	EXPECT_NE(proxy1, proxy2);
}
TEST(session, copy_constructor)
{
	std::string url = "url";

	session original(url);

	session copy(original);

	EXPECT_EQ(original, copy);
}
TEST(session, move_constructor)
{
	std::string url = "url";

	session original(url);

	session copy(original);

	session move(std::move(copy));

	// Moving should leave object in a "default" state.
	EXPECT_EQ(copy, session());
	EXPECT_EQ(original, move);
}
TEST(session, copy_assignment)
{
	std::string url = "url";

	session original(url);

	session copy;
	copy = original;

	EXPECT_EQ(original, copy);
}
TEST(session, move_assignmnet)
{
	std::string url = "url";

	session original(url);

	session copy = original;

	session move;
	move = std::move(copy);

	// Moving should leave object in a "default" state.
	EXPECT_EQ(copy, session());
	EXPECT_EQ(original, move);
}
TEST(session, send_notification)
{
	session session("https://eth.llamarpc.com");

	notification notification("eth_blockNumber", "[]");

	session.send_notification(notification);
}
TEST(session, send_request)
{
	session session("https://eth.llamarpc.com");

	request request_id_null("eth_blockNumber", "[]");
	request request_id_int("eth_blockNumber", "[]", 0);
	request request_id_double("eth_blockNumber", "[]", 22.0 / 7.0);
	request request_id_string("eth_blockNumber", "[]", "string");

	session.send_request(request_id_null);
	session.send_request(request_id_int);
	session.send_request(request_id_double);
	session.send_request(request_id_string);
}
TEST(session, send_batch)
{
	session session("https://eth.llamarpc.com");

	session::batch batch;

	for(int i = 0; i < 1; ++i)
		batch.emplace_back(request("eth_blockNumber", "[]", i));

	session.send_batch(batch);
}