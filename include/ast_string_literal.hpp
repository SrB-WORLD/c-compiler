#pragma once
#include "ast_node.hpp"
#include <string>

namespace ast {
class StringLiteral : public Node {
    std::string value_;
public:
    StringLiteral(std::string value) : value_(std::move(value)) {}
    void EmitRISC(std::ostream&, Context&) const override {}
    void Print(std::ostream&) const override {}
};
} // namespace ast
