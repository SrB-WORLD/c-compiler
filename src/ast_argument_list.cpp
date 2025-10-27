#include "ast_argument_list.hpp"
#include "ast_context.hpp"

#include <iostream>

namespace ast {


    void ArgumentList::Print(std::ostream& stream) const {
        stream << "ArgumentList:" << std::endl;
        for (const auto& argument : arguments_) {
            stream << "Arg: ";
            argument->Print(stream);
            stream << "\n";
        }
    }

    void ArgumentList::EmitRISC(std::ostream& stream, Context& context) const {
        for (const auto& argument : arguments_) {
            argument->EmitRISC(stream, context);
            std::string store_reg = context.allocate_argument_register();
            stream << "  mv " << store_reg <<", a5\n";
        }
    }


} // namespace ast
