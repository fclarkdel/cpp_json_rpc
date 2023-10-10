#ifndef CPPJSONRPC_SHAREDMEMBERS_HPP
#define CPPJSONRPC_SHAREDMEMBERS_HPP

#include <optional>
#include <string>
#include <variant>

namespace cpp_json_rpc
{
using Id = std::variant<std::monostate, int, double, std::string>;
using Jsonrpc = std::string;
using Method = std::string;
using Params = std::optional<std::string>;
}
#endif