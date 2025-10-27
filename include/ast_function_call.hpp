#pragma once
#include "ast_node.hpp"

namespace ast {
class FunctionCall : public Node {
    NodePtr callee_;   // Identifier (e.g., "printf")
    NodePtr args_;     // nullptr for no args

public:
    FunctionCall(NodePtr callee, NodePtr args)
        : callee_(std::move(callee)), args_(std::move(args)) {}

    void EmitRISC(std::ostream& os, Context& context) const override;
    void Print(std::ostream& os) const override;
};
}
