#include "ast_init_declarator_list.hpp"
#include <iostream>

namespace ast {

void InitDeclaratorList::Print(std::ostream& stream) const {
    stream << "InitDeclaratorList:" << std::endl;
    for (const auto& declarator : declaratorsList_) {
        declarator->Print(stream);
        stream << std::endl;
    }
}

void InitDeclaratorList::EmitRISC(std::ostream& stream, Context& context) const {
    for (const auto& declarator : declaratorsList_) {
        declarator->EmitRISC(stream, context);
    }
}


} // namespace ast
