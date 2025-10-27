#pragma once
#include "ast_node.hpp"

namespace ast {
class FloatConstant : public Node {
    double value_;
public:
    FloatConstant(double value) : value_(value) {}
    void EmitRISC(std::ostream&, Context&) const override {}
    void Print(std::ostream&) const override {}
};
} // namespace ast
