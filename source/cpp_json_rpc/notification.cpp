#include <cpp_json_rpc/notification.hpp>

#include <utility>

namespace cpp_json_rpc
{
notification::notification(
	Method method,
	Params params):
	jsonrpc("2.0"),
	method(std::move(method)),
	params(std::move(params))
{
}
bool
notification::operator==(const notification& rhs) const
{
	return jsonrpc == rhs.jsonrpc &&
		   method == rhs.method &&
		   params == rhs.params;
}
notification::notification(notification&& move) noexcept:
	method(std::move(move.method)),
	params(std::move(move.params))
{
	move.params = std::nullopt;
}
notification&
notification::operator=(const notification& copy)
{
	method = copy.method;
	params = copy.params;

	return *this;
}
notification&
notification::operator=(notification&& move) noexcept
{
	method = std::move(move.method);

	params = std::move(move.params);
	move.params = std::nullopt;

	return *this;
}
std::string
notification::to_json() const
{
	// {"jsonrpc":"2.0",
	std::string json = "{\"jsonrpc\":\"";
	json += jsonrpc;
	json += "\",";

	// {"jsonrpc":"2.0","method":"<method>"
	json += "\"method\":\"";
	json += method;
	json += "\"";

	if(params)
	{
		// {"jsonrpc":"2.0","method":"<method>","params":<params>
		json += ",\"params\":";
		json += params.value();
	}
	// {"jsonrpc":"2.0","method":"<method>"...}
	json += "}";

	return json;
}
}