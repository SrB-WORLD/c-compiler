#pragma once

#include "ast_node.hpp"

#include "ast_identifier.hpp"

namespace ast {

class ArrayDeclarator : public Node {
private:
    NodePtr declarator_;
    NodePtr size_expression_;

public:

    ArrayDeclarator(NodePtr declarator, NodePtr size)
        : declarator_(std::move(declarator)),
          size_expression_(std::move(size)) {}


    void EmitRISC(std::ostream& stream, Context& context) const override;

    void Print(std::ostream& stream) const override;


    std::string GetName() const {
        auto identifier = dynamic_cast<const Identifier*>(declarator_.get());
        if (!identifier) {
            throw std::runtime_error("Expected identifier_ to be of type Identifier");
        }
        return identifier->GetName();

    }

    int evaluate(){
        return size_expression_->evaluate();
    }




};

}
