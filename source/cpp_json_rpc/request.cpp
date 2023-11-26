#include <cpp_json_rpc/request.hpp>

namespace cpp_json_rpc
{
request::request(
	Method method,
	Params params,
	Id id):
	method(std::move(method)),
	params(std::move(params)),
	id(std::move(id))
{
}
request::request(request&& move) noexcept:
	jsonrpc("2.0"),
	method(std::move(move.method)),
	params(std::move(move.params)),
	id(std::move(move.id))
{
	move.params = std::nullopt;
	move.id = std::monostate();
}
request&
request::operator=(const request& rhs)
{
	method = rhs.method;
	params = rhs.params;
	id = rhs.id;

	return *this;
}
request&
request::operator=(request&& rhs) noexcept
{
	method = std::move(rhs.method);
	params = std::move(rhs.params);
	rhs.params = std::nullopt;

	id = std::move(rhs.id);
	rhs.id = std::monostate();

	return *this;
}
bool
request::operator==(const request& rhs) const
{
	return jsonrpc == rhs.jsonrpc &&
		   method == rhs.method &&
		   params == rhs.params &&
		   id == rhs.id;
}
std::string
request::to_json() const
{
	// {"jsonrpc":"2.0",
	std::string json = "{\"jsonrpc\":\"";
	json += jsonrpc;
	json += "\",";

	// {"jsonrpc":"2.0","method":"<method>"
	json += "\"method\":\"";
	json += method;
	json += "\"";

	if(params)
	{
		// {"jsonrpc":"2.0","method":"<method>","params":<params>
		json += ",\"params\":";
		json += params.value();
	}
	// {"jsonrpc":"2.0","method":"<method>"...,"id":<id>}
	json += ",\"id\":";

	std::visit([&](auto&& visit_id)
	{
		using id_t = std::decay_t<decltype(visit_id)>;

		if constexpr(std::is_same_v<id_t, std::monostate>)
			json += "null";
		if constexpr(std::is_same_v<id_t, int>)
			json += std::to_string(visit_id);
		if constexpr(std::is_same_v<id_t, double>)
		{
			std::string temp = std::to_string(visit_id);

			std::size_t i = temp.size() - 1;

			for(; temp[i] == '0' && temp[i - 1] != '.'; --i);

			temp.erase(i + 1, std::string::npos);

			json += temp;
		}
		if constexpr(std::is_same_v<id_t, std::string>)
		{
			json += "\"";
			json += visit_id;
			json += "\"";
		}
		json += "}";
	},
	id);

	return json;
}
}