#ifndef CPPJSONRPC_PROXY_HPP
#define CPPJSONRPC_PROXY_HPP

#include <future>
#include <variant>
#include <vector>

#include <fluent_curl/session.hpp>

#include <cpp_json_rpc/notification.hpp>
#include <cpp_json_rpc/request.hpp>
#include <cpp_json_rpc/response.hpp>

namespace cpp_json_rpc
{
struct session
{
	using batch = std::vector<std::variant<notification, request>>;

	explicit session(std::string url = "");

	session(const session& copy);

	session(session&& move) noexcept;

	~session();

	session&
	operator=(const session& copy);

	session&
	operator=(session&& move) noexcept;

	bool
	operator==(const session& rhs) const;

	std::string_view
	get_url() const noexcept;

	void
	set_url(std::string url);

	void
	send_notification(const notification& notification);

	std::future<response>
	send_request(const request& request);

	std::variant<response, std::vector<response>>
	send_batch(const batch& batch);

private:
	std::string _url;

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