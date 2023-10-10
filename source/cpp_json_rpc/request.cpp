#include <cpp_json_rpc/request.hpp>

namespace cpp_json_rpc
{
request::request(
	Method method,
	Params params,
	Id id):
	jsonrpc("2.0"),
	method(std::move(method)),
	params(std::move(params)),
	id(std::move(id))
{
}
request::request(request&& move) noexcept:
	jsonrpc("2.0"),
	method(std::move(move.method)),
	params(std::move(move.params)),
	id(std::move(move.id))
{
	move.params = std::nullopt;
	move.id = std::monostate();
}
request&
request::operator=(const request& rhs)
{
	method = rhs.method;
	params = rhs.params;
	id = rhs.id;

	return *this;
}
request&
request::operator=(request&& rhs) noexcept
{
	method = std::move(rhs.method);
	params = std::move(rhs.params);
	rhs.params = std::nullopt;

	id = std::move(rhs.id);
	rhs.id = std::monostate();

	return *this;
}
bool
request::operator==(const request& rhs) const
{
	return jsonrpc == rhs.jsonrpc &&
		   method == rhs.method &&
		   params == rhs.params &&
		   id == rhs.id;
}
}