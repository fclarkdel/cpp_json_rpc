#include <CppJsonRpc/Request.hpp>

namespace CppJsonRpc
{
Request::Request(
	Method method,
	Params params,
	Id id):
	jsonrpc("2.0"),
	method(std::move(method)),
	params(std::move(params)),
	id(std::move(id))
{
}
Request::Request(Request&& move) noexcept:
	jsonrpc("2.0"),
	method(std::move(move.method)),
	params(std::move(move.params)),
	id(std::move(move.id))
{
	move.params = std::nullopt;
	move.id = std::monostate();
}
Request&
Request::operator=(const Request& rhs)
{
	method = rhs.method;
	params = rhs.params;
	id = rhs.id;

	return *this;
}
Request&
Request::operator=(Request&& rhs) noexcept
{
	method = std::move(rhs.method);
	params = std::move(rhs.params);
	rhs.params = std::nullopt;

	id = std::move(rhs.id);
	rhs.id = std::monostate();

	return *this;
}
bool
Request::operator==(const Request& rhs) const
{
	return jsonrpc == rhs.jsonrpc &&
		   method == rhs.method &&
		   params == rhs.params &&
		   id == rhs.id;
}
}