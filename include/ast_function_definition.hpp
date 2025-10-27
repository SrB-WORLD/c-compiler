#ifndef AST_FUNCTION_DEFINITION_HPP
#define AST_FUNCTION_DEFINITION_HPP

#include "ast_node.hpp"
#include "ast_context.hpp"
#include "ast_direct_declarator.hpp"

namespace ast {

class FunctionDefinition : public Node {
private:
    NodePtr declaration_specifiers_;  // Return type (e.g., "int")
    NodePtr declarator_;                          // Function name (e.g., "f")
    NodePtr compound_statement_;                  // Function body (e.g., compound statement)

public:
    FunctionDefinition(NodePtr declaration_specifiers, NodePtr declarator, NodePtr compound_statement)
        : declaration_specifiers_(std::move(declaration_specifiers)), declarator_(std::move(declarator)), compound_statement_(std::move(compound_statement)) {}

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

} // namespace ast

#endif
