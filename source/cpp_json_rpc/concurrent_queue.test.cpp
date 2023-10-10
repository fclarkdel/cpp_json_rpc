#include <gtest/gtest.h>

#include <cpp_json_rpc/concurrent_queue.hpp>

using namespace cpp_json_rpc;

TEST(concurrent_queue, constructor)
{
	concurrent_queue<int> concurrent_queue;

	EXPECT_EQ(concurrent_queue.size(), 0);
	EXPECT_EQ(concurrent_queue.pop(), std::nullopt);
}
TEST(concurrent_queue, should_push_and_pop_and_size)
{
	concurrent_queue<int> concurrent_queue;

	EXPECT_EQ(concurrent_queue.size(), 0);
	EXPECT_EQ(concurrent_queue.pop(), std::nullopt);

	concurrent_queue.push(0);

	EXPECT_EQ(concurrent_queue.size(), 1);
	EXPECT_EQ(concurrent_queue.pop(), 0);

	EXPECT_EQ(concurrent_queue.size(), 0);
	EXPECT_EQ(concurrent_queue.pop(), std::nullopt);
}