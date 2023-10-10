#include <CppJsonRpc/Response.hpp>

namespace CppJsonRpc
{
Response::Response(
	std::variant<std::string, Error> result_or_error,
	std::variant<std::monostate, int, double, std::string> id):
	jsonrpc("2.0"),
	result_or_error(std::move(result_or_error)),
	id(std::move(id))
{
}
Response::Response(Response&& move) noexcept:
	jsonrpc("2.0"),
	result_or_error(std::move(move.result_or_error)),
	id(std::move(move.id))
{
	move.id = std::monostate();
}
Response&
Response::operator=(const Response& copy)
{
	result_or_error = copy.result_or_error;
	id = copy.id;

	return *this;
}
Response&
Response::operator=(Response&& move) noexcept
{
	result_or_error = std::move(move.result_or_error);

	id = std::move(move.id);
	move.id = std::monostate();

	return *this;
}
bool
Response::operator==(const Response& rhs) const
{
	return jsonrpc == rhs.jsonrpc &&
		   result_or_error == rhs.result_or_error &&
		   id == rhs.id;
}
}