#pragma once

#include "ast_node.hpp"

namespace ast {

class Unary : public Node
{
private:
    std::string unary_operator_;
    NodePtr cast_expression_;

public:
    Unary(std::string unary_operator, NodePtr cast_expression) :
    unary_operator_(unary_operator),cast_expression_(std::move(cast_expression)) {}
    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

} // namespace ast
