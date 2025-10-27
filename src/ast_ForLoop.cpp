#include "ast_ForLoop.hpp"
#include "ast_context.hpp"

#include <iostream>

namespace ast {

void ForLoop::EmitRISC(std::ostream& stream, Context& context) const {

    if (initialization_) {
        initialization_->EmitRISC(stream, context);
    }


    std::string conditionLabel = context.MakeLabel("for_cond");
    std::string bodyLabel = context.MakeLabel("for_body");
    std::string endLabel = context.MakeLabel("for_end");

    std::string continue_label = context.MakeLabel("Continue_label");
    context.PushContinueLabel(continue_label);

    std::string break_label = context.MakeLabel("Break_label");
    context.PushBreakLabel(break_label);


    // Jump to condition check first (before entering the loop)
    stream << conditionLabel << ":" << "  #Start of the Loop"  << std::endl;

    if (condition_) {
        condition_->EmitRISC(stream, context);
        stream << "  beqz a5, " << endLabel << "  # Exit loop if condition is false" << std::endl;
    }


    if (body_) {
        body_->EmitRISC(stream, context);
    }

    // Emit increment (executed after body)
    stream << continue_label <<":";
    if (increment_) {
        increment_->EmitRISC(stream, context);
    }

    // Jump to start of Loop
    stream << "  j " <<conditionLabel << "  # Jump to loop body" << std::endl;

    // Exit label
    stream << break_label<< ":"<< std::endl;
    stream << endLabel << ":" << std::endl;
    context.PopContinueLabel();
    context.PopBreakLabel();
}

void ForLoop::Print(std::ostream& stream) const {
    stream << "for (";
    if (initialization_) initialization_->Print(stream);
    stream << "; ";
    if (condition_) condition_->Print(stream);
    stream << "; ";
    if (increment_) increment_->Print(stream);
    stream << ") { ";
    if (body_) body_->Print(stream);
    stream << " }";
}

} // namespace ast
