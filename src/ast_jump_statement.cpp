#include "ast_jump_statement.hpp"
#include "ast_context.hpp"

namespace ast {

void ReturnStatement::EmitRISC(std::ostream& stream, Context& context) const {
    if (expression_ != nullptr) {
        expression_->EmitRISC(stream, context);  // Result will be in a5
        stream << "  mv a0, a5\n";              // Move result to return register a0
    } else {
        stream << "  li a0, 0\n";               // Default return value (0) if no expression
    }

    stream << "j " << context.GetCurrentExitLabel() << " # Exit function\n";

}

void ReturnStatement::Print(std::ostream& stream) const
{
    stream << "return";
    if (expression_ != nullptr)
    {
        stream << " ";
        expression_->Print(stream);
    }
    stream << ";" << std::endl;
}

}
