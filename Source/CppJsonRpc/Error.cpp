#include <CppJsonRpc/Error.hpp>

namespace CppJsonRpc
{
Error::Error(
	int code,
	std::string message,
	std::optional<std::string> data):
	code(code),
	message(std::move(message)),
	data(std::move(data))
{
}
Error::Error(Error&& move) noexcept:
	code(move.code),
	message(std::move(move.message)),
	data(std::move(move.data))
{
	move.code = 0;
	move.data = std::nullopt;
}
Error&
Error::operator=(Error&& move) noexcept
{
	code = move.code;
	move.code = 0;

	message = std::move(move.message);

	data = std::move(move.data);
	move.data = std::nullopt;

	return *this;
}
bool
Error::operator==(const Error& rhs) const
{
	return code == rhs.code &&
		   message == rhs.message &&
		   data == rhs.data;
}
}