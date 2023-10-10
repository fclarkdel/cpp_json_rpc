#include <CppJsonRpc/Notification.hpp>

#include <utility>

namespace CppJsonRpc
{
Notification::Notification(
	Method method,
	Params params):
	jsonrpc("2.0"),
	method(std::move(method)),
	params(std::move(params))
{
}
bool
Notification::operator==(const Notification& rhs) const
{
	return jsonrpc == rhs.jsonrpc &&
		   method == rhs.method &&
		   params == rhs.params;
}
Notification::Notification(Notification&& move) noexcept:
	method(std::move(move.method)),
	params(std::move(move.params))
{
	move.params = std::nullopt;
}
Notification&
Notification::operator=(const Notification& copy)
{
	method = copy.method;
	params = copy.params;

	return *this;
}
Notification&
Notification::operator=(Notification&& move) noexcept
{
	method = std::move(move.method);

	params = std::move(move.params);
	move.params = std::nullopt;

	return *this;
}
}