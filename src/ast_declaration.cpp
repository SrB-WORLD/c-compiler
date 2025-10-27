#include "ast_declaration.hpp"

namespace ast {


void Declaration::ProcessDeclaration(Context& context) const {
    // Process all variables in the declarator list
    auto* list = dynamic_cast<InitDeclaratorList*>(declarator_list_.get());
    for (const auto& declarator : list->GetDeclarators()) {
        auto* init_decl = dynamic_cast<InitDeclarator*>(declarator.get());
        init_decl->ProcessDeclaration(context, type_.get()->GetType()); // Pass type to declarators
    }
}

void Declaration::EmitRISC(std::ostream& stream, Context& context) const {
    if (declarator_list_) {
        declarator_list_->EmitRISC(stream, context);
    }
}

void Declaration::Print(std::ostream& stream) const {
    stream << "Declaration: ";
    if (declarator_list_) {
        declarator_list_->Print(stream);
    }
    stream << std::endl;
}

std::string Declaration::GetType() const {
    return type_->GetType();
}

} // namespace ast
