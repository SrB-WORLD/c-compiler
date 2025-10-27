#include "ast_continue.hpp"
#include "ast_context.hpp"

#include <iostream>

namespace ast {

void ContinueStatement::EmitRISC(std::ostream& stream, Context& context) const {
    // Get the current continue label from the context
    std::string continue_label = context.GetCurrentContinueLabel();

    // Emit a jump to the continue label
    stream << "  j " << continue_label << "  # Continue to next iteration" << std::endl;
}

void ContinueStatement::Print(std::ostream& stream) const {
    stream << "ContinueStatement";
}

} // namespace ast
