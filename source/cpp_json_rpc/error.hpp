#ifndef CPPJSONRPC_ERROR_HPP
#define CPPJSONRPC_ERROR_HPP

#include <optional>
#include <string>

namespace cpp_json_rpc
{
struct error
{
	int code;
	std::string message;
	std::optional<std::string> data;

	explicit error(
		int code = 0,
		std::string message = std::string(),
		std::optional<std::string> data = std::nullopt);

	error(const error& copy) = default;

	error(error&& move) noexcept;

	error&
	operator=(const error& copy) = default;

	error&
	operator=(error&& move) noexcept;

	bool
	operator==(const error& rhs) const;
};
}
#endif