#include <gtest/gtest.h>

#include <CppJsonRpc/Proxy.hpp>

using namespace CppJsonRpc;

TEST(Proxy, constructor)
{
	Proxy proxy;

	EXPECT_EQ(proxy.url, "");
}
TEST(Proxy, constructor_with_url)
{
	std::string url = "url";

	Proxy proxy(url);

	EXPECT_EQ(proxy.url, url);
}
TEST(Proxy, constructor_with_url_and_base_request)
{
	std::string url = "url";

	CURL* base_request = curl_easy_init();
	curl_easy_setopt(base_request, CURLOPT_URL, url.c_str());

	Proxy proxy(url, base_request);

	EXPECT_EQ(proxy.url, url);
}
TEST(Proxy, equality_comparison)
{
	std::string url = "url";

	CURL* base_request = curl_easy_init();
	curl_easy_setopt(base_request, CURLOPT_URL, url.c_str());

	Proxy proxy0(url, base_request);
	Proxy proxy1(url, base_request);
	Proxy proxy2;

	EXPECT_EQ(proxy0, proxy1);
	EXPECT_NE(proxy0, proxy2);
	EXPECT_NE(proxy1, proxy2);
}
TEST(Proxy, copy_constructor)
{
	std::string url = "url";

	CURL* base_request = curl_easy_init();
	curl_easy_setopt(base_request, CURLOPT_URL, url.c_str());

	Proxy original(url, base_request);
	Proxy copy(original);

	EXPECT_EQ(original, copy);
}
TEST(Proxy, move_constructor)
{
	std::string url = "url";

	CURL* base_request = curl_easy_init();
	curl_easy_setopt(base_request, CURLOPT_URL, url.c_str());

	Proxy original(url, base_request);

	Proxy copy(original);
	CURL* copy_base_request_before_move = copy.base_request;

	Proxy move(std::move(copy));

	// Moving should leave object in a "default" state.
	EXPECT_EQ(copy, Proxy());
	EXPECT_EQ(original, move);

	// Moved to object should steal base_request pointer from moved from object.
	EXPECT_EQ(copy_base_request_before_move, move.base_request);
	EXPECT_NE(move.base_request, copy.base_request);
}
TEST(Proxy, copy_assignment)
{
	std::string url = "url";

	CURL* base_request = curl_easy_init();
	curl_easy_setopt(base_request, CURLOPT_URL, url.c_str());

	Proxy original(url, base_request);
	Proxy copy;
	copy = original;

	EXPECT_EQ(original, copy);
}
TEST(Proxy, move_assignmnet)
{
	std::string url = "url";

	CURL* base_request = curl_easy_init();
	curl_easy_setopt(base_request, CURLOPT_URL, url.c_str());

	Proxy original(url, base_request);

	Proxy copy = original;
	CURL* copy_base_request_before_move = copy.base_request;

	Proxy move;
	move = std::move(copy);

	// Moving should leave object in a "default" state.
	EXPECT_EQ(copy, Proxy());
	EXPECT_EQ(original, move);

	// Moved to object should steal base_request pointer from moved from object.
	EXPECT_EQ(copy_base_request_before_move, move.base_request);
	EXPECT_NE(move.base_request, copy.base_request);
}