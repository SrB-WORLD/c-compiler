#pragma once

#include "ast_node.hpp"


namespace ast {

class sizeOf : public Node {

    private:
    NodePtr expression_;

    public:
    sizeOf(NodePtr expression):
    expression_(std::move(expression)) {}

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;


 };

} // namespace ast
