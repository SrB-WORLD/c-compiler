#include "ast_WhileLoop.hpp"
#include "ast_context.hpp"


namespace ast {

void WhileLoop::EmitRISC(std::ostream& stream, Context& context) const {

    // Generate unique labels for the be
    std::string start_label = context.MakeLabel("loop_start");
    std::string exit_label = context.MakeLabel("loop_exit");

    std::string continue_label = context.MakeLabel("Continue_label");
    context.PushContinueLabel(continue_label);

    std::string break_label = context.MakeLabel("Break_label");
    context.PushBreakLabel(break_label);


    stream << continue_label <<":\n";
    // Loop start (condition check)
    stream << start_label << ":\n";

    // Emit code to evaluate condition (result in a0)
    condition_->EmitRISC(stream, context);

    // Branch to exit if condition is false (a0 == 0)
    stream << "    beqz a5, " << exit_label << "\n";

    // Emit loop body (no label for body)
    body_->EmitRISC(stream, context);

    // Jump back to condition check
    stream << "    j " << start_label << "\n";

    // Exit label
    stream << break_label<< ":\n";
    stream << exit_label << ":\n";
    context.PopContinueLabel();
    context.PopBreakLabel();

}

void WhileLoop::Print(std::ostream& stream) const {
    stream << "WhileLoop [\n";
    stream << "  Condition: ";
    condition_->Print(stream);
    stream << ",\n  Body: ";
    body_->Print(stream);
    stream << "\n]\n";
}

} // namespace ast
