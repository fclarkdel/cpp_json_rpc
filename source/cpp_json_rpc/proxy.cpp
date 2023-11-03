#include <cpp_json_rpc/proxy.hpp>

namespace cpp_json_rpc
{
proxy::proxy(std::string url):
	url(std::move(url)),
	_headers(curl_slist_append(nullptr, "Content-Type: application/json"))
{
	_handle
		.option<CURLOPT_URL>(this->url.c_str())
		.option<CURLOPT_HTTPHEADER>(_headers);
}
proxy::proxy(const proxy& copy):
	url(copy.url),
	_headers(curl_slist_append(nullptr, "Content-Type: application/json")),
	_handle(copy._handle)
{
}
proxy::proxy(proxy&& move) noexcept:
	url(std::move(move.url)),
	_headers(move._headers),
	_handle(std::move(move._handle))
{
	// Necessary such that when the destructor of
	// the moved from proxy is called, it will not free
	// its _headers, which is now being used by this.
	move._headers = nullptr;
}
proxy::~proxy()
{
	curl_slist_free_all(_headers);
}
proxy&
proxy::operator=(const proxy& copy)
{
	if(this == &copy)
		return *this;

	url = copy.url;

	_headers = curl_slist_append(nullptr, "Content-Type: application/json");

	_handle = copy._handle;

	return *this;
}
proxy&
proxy::operator=(proxy&& move) noexcept
{
	if(this == &move)
		return *this;

	url = std::move(move.url);

	_headers = move._headers;

	_handle = std::move(move._handle);

	// Necessary such that when the destructor of
	// the moved from proxy is called, it will not free
	// its _headers which is now being used.
	move._headers = nullptr;

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
	fluent_curl::handle handle = _handle;


}
std::future<response>
proxy::send_request(const request& request)
{
	return {};
}
std::variant<response, std::vector<response>>
proxy::send_batch(const std::vector<std::variant<notification, request>>& batch)
{
	return {};
}
size_t
proxy::write_cb(
	char* data,
	size_t member_size,
	size_t member_quantity,
	void* userdata)
{
	size_t total_size = member_size * member_quantity;

	auto response = static_cast<std::string*>(userdata);

	response->append(data, total_size);

	return total_size;
}
}