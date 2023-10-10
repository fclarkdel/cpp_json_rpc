#ifndef CPPJSONRPC_CONCURRENTQUEUE_HPP
#define CPPJSONRPC_CONCURRENTQUEUE_HPP

#include <mutex>
#include <optional>
#include <queue>

namespace CppJsonRpc
{
template<typename Type>
struct ConcurrentQueue
{
	void
	push(Type value)
	{
		std::scoped_lock scoped_lock(_lock);

		_queue.push(std::move(value));
	}
	std::optional<Type>
	pop()
	{
		std::scoped_lock scoped_lock(_lock);

		if(_queue.empty())
			return std::nullopt;

		Type value = _queue.front();
		_queue.pop();
		return value;
	}
	std::size_t
	size()
	{
		std::scoped_lock scoped_lock(_lock);

		return _queue.size();
	}

private:
	std::mutex _lock;
	std::queue<Type> _queue;
};
}
#endif