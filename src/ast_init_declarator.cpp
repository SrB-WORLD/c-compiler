// ast_init_declarator.cpp
#include "ast_init_declarator.hpp"
#include "ast_context.hpp"
#include "ast_identifier.hpp"
#include "ast_direct_declarator.hpp"


namespace ast {


void InitDeclarator::ProcessDeclaration(Context& context, std::string type) {
    // GetDeclarator() returns Node*, cast to Identifier*
    std::string name;
    std::string funct_name;

    if (const Identifier* id = dynamic_cast<Identifier*>(declarator_.get())){

        int size = context.get_TypeSize(type);
        name = id->GetName();
        context.add_variable(name, size, type);

    };

    if (DirectDeclarator* id_func = dynamic_cast<DirectDeclarator*>(declarator_.get())) {
        funct_name = id_func->GetName();
        context.DeclareFunction(funct_name);

    }

    if (ArrayDeclarator* array_id = dynamic_cast<ArrayDeclarator*>(declarator_.get())){
        context.add_array(array_id->GetName(), array_id->evaluate());
    }

}

void InitDeclarator::EmitRISC(std::ostream& stream, Context& context) const {

    if (!initializer_) return;

    // 1. Get variable info
    if (Identifier* id = dynamic_cast<Identifier*>(declarator_.get())){
        const std::string& name = id->GetName();
        const int offset = context.get_variable_offset(name);

        // 2. Generate initializer value
        initializer_->EmitRISC(stream, context);  // e.g., "li a5,10"

        // 3. Store to stack
        stream << "sw a5, -" << offset << "(s0) # Initialize " << name << "\n";

    }

    if (ArrayDeclarator* array_id = dynamic_cast<ArrayDeclarator*>(declarator_.get())){
        std::string name = array_id->GetName();

        int offset = context.get_variable_offset(name);
        int idx = 0;

        int each_idx_offset = ((idx + 1) * 4) + offset;
        array_id->EmitRISC(stream,context);
        auto* list = dynamic_cast<InitializerList*>(initializer_.get());
            for (const auto& initializer : list->GetInitializers()){
                initializer->EmitRISC(stream,context);
                stream << "sw a5, -" << each_idx_offset << "(s0) # Initialize " << name << "\n";
                idx++;


            }



    }


}

void InitDeclarator::Print(std::ostream& stream) const {
    stream << "InitDeclarator: ";
    if (declarator_) declarator_->Print(stream);
    if (initializer_) {
        stream << " = ";
        initializer_->Print(stream);
    }
}

} // namespace ast
