#include "ast_Break.hpp"
#include "ast_context.hpp"
namespace ast {

void BreakStatement::EmitRISC(std::ostream& stream, Context& context) const {
    std::string break_label = context.GetCurrentBreakLabel();

    stream << "  j " << break_label << "  # Break out of loop" << std::endl;
}

void BreakStatement::Print(std::ostream& stream) const {
    stream << "BreakStatement";
}


}
