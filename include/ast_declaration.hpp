#pragma once
#include "ast_node.hpp"
#include "ast_type_specifier.hpp"
#include "ast_init_declarator_list.hpp"
#include "ast_init_declarator.hpp"

namespace ast {

class Declaration : public Node {
    NodePtr type_;
    NodePtr declarator_list_;  // Holds InitDeclaratorList

public:

Declaration(NodePtr type, NodePtr declarator_list)
: type_(std::move(type)),
  declarator_list_(std::move(declarator_list)) {}

    void ProcessDeclaration(Context& context) const;
    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;
    std::string GetType() const;
};

} // namespace ast
