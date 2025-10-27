#pragma once
#include "ast_node.hpp"


namespace ast {

class WhileLoop : public Node {
    NodePtr condition_;    // Loop condition (expression)
    NodePtr body_;         // Loop body (statement)

public:
    WhileLoop(NodePtr condition, NodePtr body)
        : condition_(std::move(condition)),
          body_(std::move(body)) {}

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

} // namespace ast
