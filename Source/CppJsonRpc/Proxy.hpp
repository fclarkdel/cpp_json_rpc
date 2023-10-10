#ifndef CPPJSONRPC_PROXY_HPP
#define CPPJSONRPC_PROXY_HPP

#include <future>
#include <variant>
#include <vector>

#include <curl/curl.h>

#include <CppJsonRpc/ConcurrentQueue.hpp>
#include <CppJsonRpc/Notification.hpp>
#include <CppJsonRpc/Request.hpp>
#include <CppJsonRpc/Response.hpp>

namespace CppJsonRpc
{
struct Proxy
{
	std::string url;
	CURL* base_request;

	explicit Proxy(std::string url);

	Proxy(std::string url, CURL* base_request);

	Proxy();

	Proxy(const Proxy& copy);

	Proxy(Proxy&& move) noexcept;

	Proxy&
	operator=(const Proxy& copy);

	Proxy&
	operator=(Proxy&& move) noexcept;

	bool
	operator==(const Proxy& rhs) const;

	void
	send_notification(const Notification& notification);

	std::future<Response>
	send_request(const Request& request);

	std::variant<Response, std::vector<Response>>
	send_batch(const std::vector<std::variant<Notification, Request>>& batch);

private:
	ConcurrentQueue<
		std::variant<
			Notification,
			Request,
			std::vector<std::variant<
				Notification,
				Request>>>>
		message_queue;

	void
	process_queue();
};
}
#endif