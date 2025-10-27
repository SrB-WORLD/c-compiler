#include "ast_array_declarator.hpp"
#include "ast_context.hpp"


namespace ast {

    void ArrayDeclarator::EmitRISC(std::ostream& stream, Context& context) const{
        (void)stream;
        (void)context;
    }

    void ArrayDeclarator::Print(std::ostream& stream) const
    {
        declarator_->Print(stream);
        stream << "[";
        size_expression_->Print(stream);
        stream << "]";
    }
    } // namespace ast
