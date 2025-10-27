#include "ast_unary_expression.hpp"



namespace ast {

    void Unary::EmitRISC(std::ostream& stream, Context&) const
    {
        if (unary_operator_=="-"){
                stream << "  neg a5, a5\n";
        }
        else if (unary_operator_ == "~"){
            stream << "  not a5, a5\n";
        }
        else if (unary_operator_ == "!"){
            stream << "  seqz a5, a5\n";
        }
        else if (unary_operator_ == "+"){
            stream << "  mv a5, a5\n";
        } else {
            throw std::runtime_error("Unsupported unary operator");
        }
    }

    void Unary::Print(std::ostream& stream) const
    {
        stream << "Unary Expression: ";
        cast_expression_->Print(stream);
    }
} // namespace ast
