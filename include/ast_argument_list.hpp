#pragma once
#include "ast_node.hpp"
#include <vector>
#include <memory>

namespace ast {

class Context;

class ArgumentList : public Node {

private:
    std::vector<NodePtr> arguments_;
public:


    void AddArgument(NodePtr argument) {
        arguments_.push_back(std::move(argument));
    }

    void Print(std::ostream& stream) const override;
    void EmitRISC(std::ostream& stream, Context& context) const override;

    const std::vector<NodePtr>& GetArguments() const {
        return arguments_;
    }
};

} // namespace ast
