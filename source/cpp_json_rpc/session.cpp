#include <cpp_json_rpc/session.hpp>

namespace cpp_json_rpc
{
session::session(std::string url):
	_headers(curl_slist_append(nullptr, "Content-Type: application/json"))
{
	set_url(std::move(url));

	_handle
		.option<CURLOPT_HTTPHEADER>(_headers);
}
session::session(const session& copy):
	_headers(curl_slist_append(nullptr, "Content-Type: application/json"))
{
	set_url(copy._url);

	_handle
		.option<CURLOPT_HTTPHEADER>(_headers);
}
session::session(session&& move) noexcept:
	_headers(curl_slist_append(nullptr, "Content-Type: application/json"))
{
	set_url(std::move(move._url));

	_handle
		.option<CURLOPT_HTTPHEADER>(_headers);
}
session::~session()
{
	curl_slist_free_all(_headers);
}
session&
session::operator=(const session& copy)
{
	if(this == &copy)
		return *this;

	set_url(copy._url);

	return *this;
}
session&
session::operator=(session&& move) noexcept
{
	if(this == &move)
		return *this;

	_url = std::move(move._url);

	return *this;
}
bool
session::operator==(const session& rhs) const
{
	return _url == rhs._url;
}
std::string_view
session::get_url() const noexcept
{
	return _url;
}
void
session::set_url(std::string url)
{
	_url = std::move(url);

	_handle.option<CURLOPT_URL>(_url.c_str());
}
void
session::send_notification(const notification& notification)
{
	fluent_curl::handle handle = _handle;

	std::string notification_json = notification.to_json();

	handle.option<CURLOPT_COPYPOSTFIELDS>(notification_json.c_str());

	_session.perform(handle);
}
std::future<response>
session::send_request(const request& request)
{
	fluent_curl::handle handle = _handle;

	std::string request_json = request.to_json();

	handle.option<CURLOPT_COPYPOSTFIELDS>(request_json.c_str());

	_session.perform(handle);

	return {};
}

std::variant<response, std::vector<response>>
session::send_batch(const batch& batch)
{
	fluent_curl::handle handle = _handle;

	std::string batch_json = "[";

	for(int i = 0; i < batch.size(); ++i)
	{
		std::visit([&](auto& element)
				   {
					   using element_t = std::decay_t<decltype(element)>;

					   if constexpr(std::is_same_v<element_t, notification>)
						   batch_json += ((notification)element).to_json();
					   else
						   batch_json += ((request)element).to_json();
				   },
				   batch[i]);

		if(i != batch.size() - 1)
			batch_json += ",";
	}
	batch_json += "]";

	handle.option<CURLOPT_COPYPOSTFIELDS>(batch_json.c_str());

	_session.perform(handle);

	return {};
}
size_t
session::write_cb(
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