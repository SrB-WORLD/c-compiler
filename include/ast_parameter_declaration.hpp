#pragma once

#include "ast_node.hpp"
#include "ast_identifier.hpp"
#include "ast_type_specifier.hpp"
namespace ast {

class ParameterDeclaration : public Node {
private:
    NodePtr type_;
    NodePtr declarator_;


public:
    ParameterDeclaration(NodePtr type, NodePtr declarator);

    void EmitRISC(std::ostream& stream, Context& context) const override;

    void Print(std::ostream& stream) const override;

    void ProcessDeclaration(Context& context) override;

    std::string GetName() const {
        auto identifier = dynamic_cast<const Identifier*>(declarator_.get());
        if (!identifier) {
            throw std::runtime_error("Expected identifier_ to be of type Identifier");
        }
        return identifier->GetName();
    }
};

} // namespace ast
