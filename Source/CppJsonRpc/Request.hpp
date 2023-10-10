#ifndef CPPJSONRPC_REQUEST_HPP
#define CPPJSONRPC_REQUEST_HPP

#include <CppJsonRpc/SharedMemberTypes.hpp>

namespace CppJsonRpc
{
struct Request
{
	Jsonrpc jsonrpc;
	Method method;
	Params params;
	Id id;

	explicit Request(
		Method method = Method(),
		Params params = Params(),
		Id id = std::monostate());

	Request(const Request& copy) = default;

	Request(Request&& move) noexcept;

	Request&
	operator=(const Request& rhs);

	Request&
	operator=(Request&& rhs) noexcept;

	bool
	operator==(const Request& rhs) const;
};
}
#endif