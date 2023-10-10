#include <cpp_json_rpc/proxy.hpp>

namespace cpp_json_rpc
{
proxy::proxy(std::string url):
	url(std::move(url)),
	base_request(curl_easy_init())
{
}
proxy::proxy(std::string url, CURL* base_request):
	url(std::move(url)),
	base_request(curl_easy_duphandle(base_request))
{
}
proxy::proxy():
	base_request(curl_easy_init())
{
}
proxy::proxy(const proxy& copy):
	url(copy.url),
	base_request(curl_easy_duphandle(copy.base_request))
{
}
proxy::proxy(proxy&& move) noexcept:
	url(std::move(move.url)),
	base_request(move.base_request)
{
	move.base_request = curl_easy_init();
}
proxy&
proxy::operator=(const proxy& copy)
{
	if(this == &copy)
		return *this;

	url = copy.url;
	base_request = curl_easy_duphandle(copy.base_request);

	return *this;
}
proxy&
proxy::operator=(proxy&& move) noexcept
{
	if(this == &move)
		return *this;

	url = std::move(move.url);

	base_request = move.base_request;
	move.base_request = curl_easy_init();

	return *this;
}
bool
proxy::operator==(const proxy& rhs) const
{
	return url == rhs.url;
}
void
proxy::send_notification(const notification& notification)
{
	message_queue.push(notification);
}
std::future<response>
proxy::send_request(const request& request)
{
	std::future<response> future_response;

	message_queue.push(request);

	return future_response;
}
void
proxy::process_queue()
{
}
}