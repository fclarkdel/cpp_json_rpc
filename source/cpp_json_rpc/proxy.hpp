#ifndef CPPJSONRPC_PROXY_HPP
#define CPPJSONRPC_PROXY_HPP

#include <future>
#include <variant>
#include <vector>

#include <curl/curl.h>

#include <cpp_json_rpc/concurrent_queue.hpp>
#include <cpp_json_rpc/notification.hpp>
#include <cpp_json_rpc/request.hpp>
#include <cpp_json_rpc/response.hpp>

namespace cpp_json_rpc
{
struct proxy
{
	std::string url;
	CURL* base_request;

	explicit proxy(std::string url);

	proxy(std::string url, CURL* base_request);

	proxy();

	proxy(const proxy& copy);

	proxy(proxy&& move) noexcept;

	proxy&
	operator=(const proxy& copy);

	proxy&
	operator=(proxy&& move) noexcept;

	bool
	operator==(const proxy& rhs) const;

	void
	send_notification(const notification& notification);

	std::future<response>
	send_request(const request& request);

	std::variant<response, std::vector<response>>
	send_batch(const std::vector<std::variant<notification, request>>& batch);

private:
	concurrent_queue<
		std::variant<
			notification,
			request,
			std::vector<std::variant<
				notification,
				request>>>>
		message_queue;

	void
	process_queue();
};
}
#endif