#include <cpp_json_rpc/error.hpp>

namespace cpp_json_rpc
{
error::error(
	int code,
	std::string message,
	std::optional<std::string> data):
	code(code),
	message(std::move(message)),
	data(std::move(data))
{
}
error::error(error&& move) noexcept:
	code(move.code),
	message(std::move(move.message)),
	data(std::move(move.data))
{
	move.code = 0;
	move.data = std::nullopt;
}
error&
error::operator=(error&& move) noexcept
{
	code = move.code;
	move.code = 0;

	message = std::move(move.message);

	data = std::move(move.data);
	move.data = std::nullopt;

	return *this;
}
bool
error::operator==(const error& rhs) const
{
	return code == rhs.code &&
		   message == rhs.message &&
		   data == rhs.data;
}
}