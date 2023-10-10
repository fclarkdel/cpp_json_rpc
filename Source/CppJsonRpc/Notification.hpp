#ifndef CPPJSONRPC_NOTIFICATION_HPP
#define CPPJSONRPC_NOTIFICATION_HPP

#include <CppJsonRpc/SharedMemberTypes.hpp>

namespace CppJsonRpc
{
struct Notification
{
	Jsonrpc jsonrpc = "2.0";
	Method method;
	Params params;

	explicit Notification(
		Method method = Method(),
		Params params = Params());

	Notification(const Notification& copy) = default;

	Notification(Notification&& move) noexcept;

	Notification&
	operator=(const Notification& copy);

	Notification&
	operator=(Notification&& move) noexcept;

	bool
	operator==(const Notification& rhs) const;
};
}
#endif