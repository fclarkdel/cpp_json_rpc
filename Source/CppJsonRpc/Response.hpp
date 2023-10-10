#ifndef CPPJSONRPC_RESPONSE_HPP
#define CPPJSONRPC_RESPONSE_HPP

#include <string>
#include <variant>

#include <CppJsonRpc/Error.hpp>
#include <CppJsonRpc/SharedMemberTypes.hpp>

namespace CppJsonRpc
{
struct Response
{
	Jsonrpc jsonrpc;
	std::variant<std::string, Error> result_or_error;
	Id id;

	explicit Response(
		std::variant<std::string, Error> result_or_error = std::string(),
		Id id = std::monostate());

	Response(const Response& copy) = default;

	Response(Response&& move) noexcept;

	Response&
	operator=(const Response& copy);

	Response&
	operator=(Response&& move) noexcept;

	bool
	operator==(const Response& rhs) const;
};
}
#endif