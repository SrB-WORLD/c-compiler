#include "ast_direct_declarator.hpp"

namespace ast {



void DirectDeclarator::EmitRISC(std::ostream& stream, Context& context) const {
    // Don't emit anything - function labels are handled by FunctionDefinition
    if (parameters_) {
        parameters_->EmitRISC(stream, context);  // Emit code for the parameter list
    }
}

void DirectDeclarator::Print(std::ostream& stream) const {
    identifier_->Print(stream);
    if (parameters_) {
        stream << "(";
        parameters_->Print(stream);
        stream << ")";
    }
}

} // namespace ast
