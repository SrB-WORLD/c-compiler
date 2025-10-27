// ast_init_declarator.hpp
#pragma once
#include "ast_node.hpp"
#include "ast_array_declarator.hpp"

namespace ast {

class InitDeclarator : public Node {
private:
    NodePtr declarator_;
    NodePtr initializer_;

public:

    InitDeclarator(NodePtr declarator, NodePtr initializer)
        : declarator_(std::move(declarator)),
          initializer_(std::move(initializer)) {}


    void ProcessDeclaration(Context& context, std::string type);

    //code gen
    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;


    Node* GetDeclarator() const { return declarator_.get(); }
    Node* GetInitializer() const { return initializer_.get(); }

};

} // namespace ast
