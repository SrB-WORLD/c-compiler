#include "ast_identifier.hpp"
#include "ast_context.hpp"
namespace ast {

void Identifier::EmitRISC(std::ostream& stream, Context& context) const
{
    int offset = context.get_variable_offset(identifier_); // Get the variable's stack offset
    stream << "  lw a5, -" << offset << "(s0)  # Load variable '" << identifier_ << "'" << std::endl;
}

void Identifier::Print(std::ostream& stream) const
{
    stream << "Identifier: " << identifier_;
}

} // namespace ast
