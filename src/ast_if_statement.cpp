#include "ast_if_statement.hpp"
#include "ast_context.hpp"

namespace ast {

void IfStatement::EmitRISC(std::ostream& stream, Context& context) const {
    // Generate unique labels
    std::string else_label = context.MakeLabel("else");
    std::string end_label = context.MakeLabel("endif");

    // Evaluate condition
    condition_->EmitRISC(stream, context);

    // Branch instruction
    stream << "beqz a5, " << else_label << "  # Jump to else if false\n";

    // True branch
    true_branch_->EmitRISC(stream, context);
    stream << "j " << end_label << "          # Skip else block\n";

    // Else label
    stream << else_label << ":\n";
    if (false_branch_) {
        false_branch_->EmitRISC(stream, context);
    }

    // End label
    stream << end_label << ":\n";
}




void IfStatement::Print(std::ostream& stream) const {
    stream << "IfStatement:\n";
    stream << "|-Condition: "; condition_->Print(stream); stream << "\n";
    stream << "|-Then: "; true_branch_->Print(stream); stream << "\n";
    if (false_branch_) {
        stream << "`-Else: "; false_branch_->Print(stream);
    }
    stream << "\n";
}


} // namespace ast


