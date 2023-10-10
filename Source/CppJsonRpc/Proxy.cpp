#include <CppJsonRpc/Proxy.hpp>

namespace CppJsonRpc
{
Proxy::Proxy(std::string url):
	url(std::move(url)),
	base_request(curl_easy_init())
{
}
Proxy::Proxy(std::string url, CURL* base_request):
	url(std::move(url)),
	base_request(curl_easy_duphandle(base_request))
{
}
Proxy::Proxy():
	base_request(curl_easy_init())
{
}
Proxy::Proxy(const Proxy& copy):
	url(copy.url),
	base_request(curl_easy_duphandle(copy.base_request))
{
}
Proxy::Proxy(Proxy&& move) noexcept:
	url(std::move(move.url)),
	base_request(move.base_request)
{
	move.base_request = curl_easy_init();
}
Proxy&
Proxy::operator=(const Proxy& copy)
{
	if(this == &copy)
		return *this;

	url = copy.url;
	base_request = curl_easy_duphandle(copy.base_request);

	return *this;
}
Proxy&
Proxy::operator=(Proxy&& move) noexcept
{
	if(this == &move)
		return *this;

	url = std::move(move.url);

	base_request = move.base_request;
	move.base_request = curl_easy_init();

	return *this;
}
bool
Proxy::operator==(const Proxy& rhs) const
{
	return url == rhs.url;
}
void
Proxy::send_notification(const Notification& notification)
{
	message_queue.push(notification);
}
std::future<Response>
Proxy::send_request(const Request& request)
{
	std::future<Response> future_response;

	message_queue.push(request);

	return future_response;
}
void
Proxy::process_queue()
{
	
}
}