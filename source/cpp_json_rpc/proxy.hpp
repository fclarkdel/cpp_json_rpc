#ifndef CPPJSONRPC_PROXY_HPP
#define CPPJSONRPC_PROXY_HPP

#include <future>
#include <variant>
#include <vector>

#include <fluent_curl/session.hpp>

#include <cpp_json_rpc/concurrent_queue.hpp>
#include <cpp_json_rpc/notification.hpp>
#include <cpp_json_rpc/request.hpp>
#include <cpp_json_rpc/response.hpp>

namespace cpp_json_rpc
{
struct proxy
{
	std::string url;

	explicit proxy(std::string url = "");

	proxy(const proxy& copy);

	proxy(proxy&& move) noexcept;

	~proxy();

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
	fluent_curl::session _session;
	fluent_curl::handle _handle;

	curl_slist* _headers;

	static std::size_t
	write_cb(
		char* data,
		size_t member_size,
		size_t member_quantity,
		void* userdata);
};
}
#endif