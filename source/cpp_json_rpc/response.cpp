#include <cpp_json_rpc/response.hpp>

namespace cpp_json_rpc
{
response::response(
	std::variant<std::string, error> result_or_error,
	std::variant<std::monostate, int, double, std::string> id):
	jsonrpc("2.0"),
	result_or_error(std::move(result_or_error)),
	id(std::move(id))
{
}
response::response(response&& move) noexcept:
	jsonrpc("2.0"),
	result_or_error(std::move(move.result_or_error)),
	id(std::move(move.id))
{
	move.id = std::monostate();
}
response&
response::operator=(const response& copy)
{
	result_or_error = copy.result_or_error;
	id = copy.id;

	return *this;
}
response&
response::operator=(response&& move) noexcept
{
	result_or_error = std::move(move.result_or_error);

	id = std::move(move.id);
	move.id = std::monostate();

	return *this;
}
bool
response::operator==(const response& rhs) const
{
	return jsonrpc == rhs.jsonrpc &&
		   result_or_error == rhs.result_or_error &&
		   id == rhs.id;
}
}