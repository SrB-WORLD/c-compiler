#pragma once
#include "ast_node.hpp"
#include <vector>
#include <memory>

namespace ast {

class Context;

class InitDeclaratorList : public Node {
private:
    std::vector<NodePtr> declaratorsList_;

public:
    void AddDeclarator(NodePtr declarator) {
        declaratorsList_.push_back(std::move(declarator));
    }

    void Print(std::ostream& stream) const override;
    void EmitRISC(std::ostream& stream, Context& context) const override;

    const std::vector<NodePtr>& GetDeclarators() const {
        return declaratorsList_;
    }
};

} // namespace ast
