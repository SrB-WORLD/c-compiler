#pragma once
#include "ast_node.hpp"



namespace ast {

class IfStatement : public Node {
    NodePtr condition_;
    NodePtr true_branch_;
    NodePtr false_branch_;  // Can be nullptr when its just if


public:
    IfStatement(NodePtr condition, NodePtr true_branch, NodePtr false_branch)
        : condition_(std::move(condition)),
          true_branch_(std::move(true_branch)),
          false_branch_(std::move(false_branch)) {}

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;
};


}


