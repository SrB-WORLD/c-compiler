// ast_init_declarator.hpp
#pragma once
#include "ast_node.hpp"
#include "ast_type_specifier.hpp"

namespace ast {

class TypedefDeclaration : public Node {
private:
    StorageSpecifier specifier_;
    TypeSpecifier declaration_spec_;

public:

    TypedefDeclaration(StorageSpecifier specifier, TypeSpecifier declaration_spec)
        : specifier_(specifier),
          declaration_spec_(declaration_spec) {}


    void EmitRISC(std::ostream& stream, Context& context) const {
        (void)stream;
        (void)context;
    }
    void Print(std::ostream& stream) const {
        stream << "Typedef : ";
        stream << declaration_spec_.GetType();
    }


    StorageSpecifier GetSpecifier() const { return specifier_; }
    TypeSpecifier GetDeclarator() const { return declaration_spec_;}

};

} // namespace ast
