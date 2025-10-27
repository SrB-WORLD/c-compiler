#pragma once

#include "ast_node.hpp"
#include "ast_identifier.hpp"

namespace ast {

class DirectDeclarator : public Node
{
private:
    NodePtr identifier_;
    NodePtr parameters_;

public:


DirectDeclarator(NodePtr identifier, NodePtr parameters = nullptr)
: identifier_(std::move(identifier)), parameters_(std::move(parameters)) {}



    std::string GetName() const {
        auto identifier = dynamic_cast<const Identifier*>(identifier_.get());
        if (!identifier) {
            throw std::runtime_error("Expected identifier_ to be of type Identifier");
        }
        return identifier->GetName();
    }



    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

} // namespace ast
