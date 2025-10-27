#pragma once
#include "ast_node.hpp"

namespace ast {

class Assignment : public Node
{
private:
    NodePtr lhs_;
    std::string assignment_operator_;
    NodePtr rhs_;

public:

    Assignment(NodePtr lhs, std::string assignment_operator, NodePtr rhs):
    lhs_(std::move(lhs)), assignment_operator_(std::move(assignment_operator)), rhs_(std::move(rhs)) {}

    void EmitRISC(std::ostream&, Context&) const override;
    void Print(std::ostream&) const override;

};

}
