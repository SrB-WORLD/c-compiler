#include "ast_expression.hpp"

#include <stdexcept>


namespace ast {

    void Postfix::EmitRISC(std::ostream& stream, Context& context) const
    {
        postfix_expression_->EmitRISC(stream,context);
        std::string store_var = context.allocate_temp_register();
        stream << "  mv " << store_var<<", a5\n";
        if (change_operator_=="++"){
            stream << "  addi "<<store_var<<", "<<store_var<<", 1\n";
        } else if (change_operator_=="--"){
            stream << "  addi "<<store_var<<", "<<store_var<<", -1\n";
        } else {
            throw std::runtime_error("Unsupported postfix operator");
        }
        auto identifier = dynamic_cast<Identifier*>(postfix_expression_.get());
        if (identifier){
            int offset = context.get_variable_offset(identifier->GetName()); // Get the variable's stack offset
            stream << "  sw "<<store_var<<", -"<<offset<<"(s0)\n";

        }
    }

    void Postfix::Print(std::ostream& stream) const
    {
        stream << "Postfix Expression: ";
        postfix_expression_->Print(stream);
        stream << change_operator_;
    }

    void Prefix::EmitRISC(std::ostream& stream, Context& context) const
    {
        prefix_expression_->EmitRISC(stream,context);
        std::string store_var = context.allocate_temp_register();
        if (change_operator_=="++"){
                stream << "  addi "<<store_var<<", a5, 1\n";
        } else if (change_operator_=="--"){
            stream << "  addi "<<store_var<<", a5, -1\n";
        }else {
            throw std::runtime_error("Unsupported postfix operator");

        }

        auto identifier = dynamic_cast<Identifier*>(prefix_expression_.get());
        if (identifier){
            int offset = context.get_variable_offset(identifier->GetName()); // Get the variable's stack offset
            stream << "  sw "<<store_var<<", -"<<offset<<"(s0)\n";
            stream << "  mv a5, " << store_var<<"\n";
        }

    }

    void Prefix::Print(std::ostream& stream) const
    {
        stream << "Prefix Expression: ";
        prefix_expression_->Print(stream);
        stream << change_operator_;
    }

    void Ternary::EmitRISC(std::ostream& stream, Context& context) const
    {
        std::string false_label = context.MakeLabel("false_expression");
        std::string end_ternary_label = context.MakeLabel("end_ternary");
        condition_->EmitRISC(stream,context);
        stream << "  beqz a5, "<< false_label<<"\n";
        true_expression_->EmitRISC(stream,context);
        stream << "  j "<< end_ternary_label<<"\n";
        stream << false_label<<":"<<"\n";
        false_expression_->EmitRISC(stream,context);
        stream << end_ternary_label<<":"<<"\n";

    }

    void Ternary::Print(std::ostream& stream) const
    {
        stream << "Ternary Expression: ";
        condition_->Print(stream);
        stream << "?";
        true_expression_->Print(stream);
        stream << ":";
        false_expression_->Print(stream);
    }



} // namespace ast
