#ifndef CPPJSONRPC_ERROR_HPP
#define CPPJSONRPC_ERROR_HPP

#include <optional>
#include <string>

namespace CppJsonRpc
{
struct Error
{
	int code;
	std::string message;
	std::optional<std::string> data;

	explicit Error(
		int code = 0,
		std::string message = std::string(),
		std::optional<std::string> data = std::nullopt);

	Error(const Error& copy) = default;

	Error(Error&& move) noexcept;

	Error&
	operator=(const Error& copy) = default;

	Error&
	operator=(Error&& move) noexcept;

	bool
	operator==(const Error& rhs) const;
};
}
#endif