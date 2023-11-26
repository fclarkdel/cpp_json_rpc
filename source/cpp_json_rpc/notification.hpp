#ifndef CPPJSONRPC_NOTIFICATION_HPP
#define CPPJSONRPC_NOTIFICATION_HPP

#include <cpp_json_rpc/shared_member_types.hpp>

namespace cpp_json_rpc
{
struct notification
{
	Jsonrpc jsonrpc = "2.0";
	Method method;
	Params params;

	explicit notification(
		Method method = Method(),
		Params params = Params());

	notification(const notification& copy) = default;

	notification(notification&& move) noexcept;

	notification&
	operator=(const notification& copy);

	notification&
	operator=(notification&& move) noexcept;

	bool
	operator==(const notification& rhs) const;

	std::string
	to_json() const;
};
}
#endif