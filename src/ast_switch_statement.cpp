#include "ast_switch_statement.hpp"
#include "ast_context.hpp"
#include "ast_case_statement.hpp"
namespace ast {


bool has_def = false;

void SwitchStatement::EmitRISC(std::ostream &stream, Context &context) const {

    auto* case_list = dynamic_cast<NodeList*>(case_list_.get());
    if (!case_list) return;

    std::vector<std::string> caseLabels;

    std::string break_label = context.MakeLabel("Break_label");
    context.PushBreakLabel(break_label);

    //if (!case_list) return;

    // Allocate register and get expression value
    std::string switch_reg = context.allocate_temp_register();
    if (expression_){
        expression_->EmitRISC(stream, context);  // Result in a5
    }

    stream << "mv " << switch_reg << ", a5\n";


    // Generate labels
    std::string end_label = context.MakeLabel("switch_end");

    std::string default_label = context.MakeLabel("switch_default");

    context.case_true();
    std::cerr<<"Issue here";

    // First pass: generate comparisons
    for (auto &case_statement : case_list->GetNodes()){
        auto case_check = dynamic_cast<CaseStatement*>(case_statement.get());
        std::cerr<<"next one";
        if (case_check){
            if (case_check->getExpression()){
                std::cerr<<"Inside";
                std::string case_label = context.MakeLabel("case_label");
                caseLabels.push_back(case_label);
                if (case_statement){
                    std::cerr<<"Inner";
                    case_statement->EmitRISC(stream, context);
                }

                stream << "  beq " << switch_reg << ", a5, " << case_label << "\n";
            }
        }





    }

    context.set_default_label(default_label);

    // Jump to default if no matches


    stream << "j " << default_label << "\n";




    // Second pass: emit case bodies
    context.case_false();

    for (auto &case_statement : case_list->GetNodes()){

        auto case_check = dynamic_cast<CaseStatement*>(case_statement.get());
        if (case_check->getExpression()){
            std::string case_label = caseLabels.front();
            caseLabels.erase(caseLabels.begin());
            stream << case_label<< ":\n";

            if (case_statement) {
                case_statement->EmitRISC(stream, context);
                stream << "j " << end_label << "\n";

            }
        }
        else{
            has_def = true;
            case_statement->EmitRISC(stream, context);
            stream << "j " << end_label << "\n";
        }
        std::cerr<<"Issue next";




    }



    if (!has_def){
        stream << default_label << ":\n";
    }




    // ... emit default body if exists ...

    // Cleanup
    stream << break_label<< ":"<< std::endl;
    stream << end_label << ":\n";
    context.deallocate_temp_register(switch_reg);
    context.PopBreakLabel();

    //context.ExitSwitch();
}

void SwitchStatement::Print(std::ostream & stream) const {
    stream << "Switch : " << "\n";
    if (expression_){
        expression_->Print(stream);
    }
    if (case_list_){
        case_list_->Print(stream);

    }

}

}
