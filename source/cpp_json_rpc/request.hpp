#ifndef CPPJSONRPC_REQUEST_HPP
#define CPPJSONRPC_REQUEST_HPP

#include <cpp_json_rpc/shared_member_types.hpp>

namespace cpp_json_rpc
{
struct request
{
	Jsonrpc jsonrpc;
	Method method;
	Params params;
	Id id;

	explicit request(
		Method method = Method(),
		Params params = Params(),
		Id id = std::monostate());

	request(const request& copy) = default;

	request(request&& move) noexcept;

	request&
	operator=(const request& rhs);

	request&
	operator=(request&& rhs) noexcept;

	bool
	operator==(const request& rhs) const;
};
}
#endif