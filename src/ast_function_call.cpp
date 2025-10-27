#include "ast_function_call.hpp"
#include "ast_context.hpp"
#include "ast_identifier.hpp"
namespace ast {
void FunctionCall::EmitRISC(std::ostream& stream, Context& context) const {
    // Get identifier name
    auto* id = dynamic_cast<Identifier*>(callee_.get());
    if (!id) {
        throw std::runtime_error("Function call callee must be an identifier");
    }
    std::string func_name = id->GetName();

    if (!context.FunctionExists(func_name)) {
        throw std::runtime_error("Undefined function: " + func_name);
    }

    if (args_){
        args_->EmitRISC(stream,context);
    }

    stream << "    jal " << func_name << "\n";
    stream << "  mv a5, a0\n";
    context.reset_argument_register();
}

void FunctionCall::Print(std::ostream& stream) const {
    stream << "FunctionCall: ";
    callee_->Print(stream);
    stream << "()";
    if (args_){
        args_->Print(stream);
    }
}
} // namespace ast
