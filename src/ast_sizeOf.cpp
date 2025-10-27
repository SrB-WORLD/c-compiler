#include "ast_sizeof.hpp"
#include "ast_context.hpp"
#include "ast_identifier.hpp"


namespace ast {

void sizeOf::EmitRISC(std::ostream& stream, Context& context) const
{
    int size = context.get_TypeSize(expression_->GetType());
    if (size != 0){
        stream << "  li a5, "<<size<<"\n";
    }else{
        auto id = dynamic_cast<Identifier*>(expression_.get());
        if(id){
            size = context.get_VariableSize(id->GetName());
            stream << "  li a5, "<<size<<"\n";
        }

    }
}

void sizeOf::Print(std::ostream& stream) const
{

    stream << "Size Of: " << expression_->GetType();
}



} // namespace ast
