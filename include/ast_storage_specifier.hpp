#pragma once
#include <string>
#include <stdexcept>

namespace ast {

enum class StorageSpecifier {
    TYPEDEF,
    EXTERN,
    STATIC,
    AUTO,
    REGISTER
 };


// Conversion function for enum -> string
inline std::string type_to_string(StorageSpecifier type) {
    switch(type) {
        case StorageSpecifier::TYPEDEF: return "typedef";
        case StorageSpecifier::EXTERN: return "extern";
        case StorageSpecifier::STATIC: return "static";
        case StorageSpecifier::AUTO: return "auto";
        case StorageSpecifier::REGISTER: return "register";
        default: throw std::runtime_error("Unknown type");
    }
}
// Optional: Keep the stream operator for logging
template<typename LogStream>
LogStream& operator<<(LogStream& ls, const StorageSpecifier& type) {
    return ls << type_to_string(type);
}

} // namespace ast
