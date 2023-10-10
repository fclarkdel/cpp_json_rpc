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
TEST(proxy, constructor_with_url_and_base_request)
{
	std::string url = "url";

	CURL* base_request = curl_easy_init();
	curl_easy_setopt(base_request, CURLOPT_URL, url.c_str());

	proxy proxy(url, base_request);

	EXPECT_EQ(proxy.url, url);
}
TEST(proxy, equality_comparison)
{
	std::string url = "url";

	CURL* base_request = curl_easy_init();
	curl_easy_setopt(base_request, CURLOPT_URL, url.c_str());

	proxy proxy0(url, base_request);
	proxy proxy1(url, base_request);
	proxy proxy2;

	EXPECT_EQ(proxy0, proxy1);
	EXPECT_NE(proxy0, proxy2);
	EXPECT_NE(proxy1, proxy2);
}
TEST(proxy, copy_constructor)
{
	std::string url = "url";

	CURL* base_request = curl_easy_init();
	curl_easy_setopt(base_request, CURLOPT_URL, url.c_str());

	proxy original(url, base_request);
	proxy copy(original);

	EXPECT_EQ(original, copy);
}
TEST(proxy, move_constructor)
{
	std::string url = "url";

	CURL* base_request = curl_easy_init();
	curl_easy_setopt(base_request, CURLOPT_URL, url.c_str());

	proxy original(url, base_request);

	proxy copy(original);
	CURL* copy_base_request_before_move = copy.base_request;

	proxy move(std::move(copy));

	// Moving should leave object in a "default" state.
	EXPECT_EQ(copy, proxy());
	EXPECT_EQ(original, move);

	// Moved to object should steal base_request pointer from moved from object.
	EXPECT_EQ(copy_base_request_before_move, move.base_request);
	EXPECT_NE(move.base_request, copy.base_request);
}
TEST(proxy, copy_assignment)
{
	std::string url = "url";

	CURL* base_request = curl_easy_init();
	curl_easy_setopt(base_request, CURLOPT_URL, url.c_str());

	proxy original(url, base_request);
	proxy copy;
	copy = original;

	EXPECT_EQ(original, copy);
}
TEST(proxy, move_assignmnet)
{
	std::string url = "url";

	CURL* base_request = curl_easy_init();
	curl_easy_setopt(base_request, CURLOPT_URL, url.c_str());

	proxy original(url, base_request);

	proxy copy = original;
	CURL* copy_base_request_before_move = copy.base_request;

	proxy move;
	move = std::move(copy);

	// Moving should leave object in a "default" state.
	EXPECT_EQ(copy, proxy());
	EXPECT_EQ(original, move);

	// Moved to object should steal base_request pointer from moved from object.
	EXPECT_EQ(copy_base_request_before_move, move.base_request);
	EXPECT_NE(move.base_request, copy.base_request);
}