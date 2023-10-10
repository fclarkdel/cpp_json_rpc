#ifndef CPPJSONRPC_RESPONSE_HPP
#define CPPJSONRPC_RESPONSE_HPP

#include <string>
#include <variant>

#include <cpp_json_rpc/error.hpp>
#include <cpp_json_rpc/shared_member_types.hpp>

namespace cpp_json_rpc
{
struct response
{
	Jsonrpc jsonrpc;
	std::variant<std::string, error> result_or_error;
	Id id;

	explicit response(
		std::variant<std::string, error> result_or_error = std::string(),
		Id id = std::monostate());

	response(const response& copy) = default;

	response(response&& move) noexcept;

	response&
	operator=(const response& copy);

	response&
	operator=(response&& move) noexcept;

	bool
	operator==(const response& rhs) const;
};
}
#endif