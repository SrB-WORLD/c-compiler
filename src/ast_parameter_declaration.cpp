// ast_parameter_declaration.cpp
#include "ast_parameter_declaration.hpp"
#include "ast_context.hpp"
#include "ast_identifier.hpp"
#include "ast_type_specifier.hpp"
namespace ast {

ParameterDeclaration::ParameterDeclaration(NodePtr type, NodePtr declarator)
    : type_(std::move(type)), declarator_(std::move(declarator)) {
    // Extract the parameter name from the declarator
}

void ParameterDeclaration::EmitRISC(std::ostream& stream, Context& context) const {
    // Generate code to save the parameter from its register to the stack
    std::string reg_name = context.GetNextParamReg();  // Get the next parameter register index
    int offset_ = context.get_variable_offset(GetName());

    stream << "  sw " << reg_name << ", -" << offset_ << "(s0) # Save " << GetName() << "\n";
    context.deallocate_argument_register(reg_name);
}

void ParameterDeclaration::Print(std::ostream& stream) const {
    stream << "ParameterDeclaration: " << GetName() << " (Type: )";
}

void ParameterDeclaration::ProcessDeclaration(Context& context) {
    // Assign an offset to the parameter
    int size = context.get_TypeSize(type_->GetType());
    context.add_variable(GetName(), size,type_->GetType());  // 4 bytes for `int`
    std::cerr<<"("<<type_->GetType()<<")";
    // Generate code to save the parameter to the stack
}

} // namespace ast
