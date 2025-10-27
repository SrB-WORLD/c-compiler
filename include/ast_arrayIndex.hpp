#pragma once

#include "ast_node.hpp"

#include "ast_identifier.hpp"

namespace ast {

class ArrayIndex : public Node {
private:

    NodePtr identifier_;
    NodePtr index_;

public:

    ArrayIndex(NodePtr identifier, NodePtr index)
        : identifier_(std::move(identifier)),
        index_(std::move(index)) {}


    void EmitRISC(std::ostream& stream, Context& context) const override;

    void Print(std::ostream& stream) const override;


    std::string GetName() const {
        auto identifier = dynamic_cast<const Identifier*>(identifier_.get());
        if (!identifier) {
            throw std::runtime_error("Expected identifier_ to be of type Identifier");
        }
        return identifier->GetName();

    }

    int evaluate() const {
        return index_->evaluate();
    }




};

}
