#pragma once

#include "ast_node.hpp"
#include <memory>

namespace ast {

class ForLoop : public Node {
private:
    NodePtr initialization_;
    NodePtr condition_;
    NodePtr increment_;
    NodePtr body_;

public:
    ForLoop(NodePtr initialization, NodePtr condition, NodePtr increment, NodePtr body)
        : initialization_(std::move(initialization)),
          condition_(std::move(condition)),
          increment_(std::move(increment)),
          body_(std::move(body)) {}

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

} // namespace ast
