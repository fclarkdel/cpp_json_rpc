#include <gtest/gtest.h>

#include <CppJsonRpc/ConcurrentQueue.hpp>

using namespace CppJsonRpc;

TEST(ConcurrentQueue, constructor)
{
	ConcurrentQueue<int> concurrent_queue;

	EXPECT_EQ(concurrent_queue.size(), 0);
	EXPECT_EQ(concurrent_queue.pop(), std::nullopt);
}
TEST(ConcurrentQueue, should_push_and_pop_and_size)
{
	ConcurrentQueue<int> concurrent_queue;

	EXPECT_EQ(concurrent_queue.size(), 0);
	EXPECT_EQ(concurrent_queue.pop(), std::nullopt);

	concurrent_queue.push(0);

	EXPECT_EQ(concurrent_queue.size(), 1);
	EXPECT_EQ(concurrent_queue.pop(), 0);

	EXPECT_EQ(concurrent_queue.size(), 0);
	EXPECT_EQ(concurrent_queue.pop(), std::nullopt);
}