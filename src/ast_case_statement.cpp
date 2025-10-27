#include "ast_case_statement.hpp"
#include "ast_context.hpp"

namespace ast {


void CaseStatement::EmitRISC(std::ostream &stream, Context &context) const {



    if (context.get_case_condition()){

        if (expression_ != nullptr){

            expression_->EmitRISC(stream,context);

        }

    } else {

        if (expression_ != nullptr){
            statement_->EmitRISC(stream,context);
        }
        else {
            std::string default_label = context.getdefault_label();
            stream << default_label << ":\n";
            statement_->EmitRISC(stream,context);
        }

    }




}

void CaseStatement::Print(std::ostream & stream) const {
    stream << "Emitting case : " << "\n";

    if (expression_ != nullptr){
        expression_->Print(stream);
    }


    statement_->Print(stream);

}

} // namespace ast
