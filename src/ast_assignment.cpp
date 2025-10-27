#include "ast_assignment.hpp"
#include "ast_context.hpp"
#include "ast_identifier.hpp"
#include "ast_arrayIndex.hpp"


#include <stdexcept>


namespace ast {

    void Assignment::EmitRISC(std::ostream& stream, Context& context) const
    {
        // 1. Evaluate the right-hand side (result in a5)
        rhs_->EmitRISC(stream, context);

        // 2. Get variable name from left-hand side (assumes lhs is an Identifier)
        std::string var_name;
        std::string tmp_reg;
        int offset;
        if (auto identifier = dynamic_cast<Identifier*>(lhs_.get())){
            var_name = identifier->GetName();
            offset = context.get_variable_offset(var_name);

            if (assignment_operator_ == "="){
                stream << "  sw a5, -" << offset << "(s0)  # Store to " << var_name << std::endl;
            }

            else {
                tmp_reg = context.allocate_temp_register();

                if (assignment_operator_ == "+=") {
                    stream << "add a5, a5,"<< tmp_reg<< "\n";
                }


                stream << "  sw a5, -" << offset << "(s0)  # Store to " << var_name << std::endl;
            }

        }
        if (auto arrayval = dynamic_cast<ArrayIndex*>(lhs_.get())){
            var_name = arrayval->GetName();
            offset = context.get_variable_offset(var_name);
            int idx = arrayval->evaluate();
            int each_idx_offset = context.array_offset(var_name);
            offset = each_idx_offset - ((idx + 1) * 4) ;

        }
        // 3. Store result from a5 to stack relative to frame pointer

    }

    void Assignment::Print(std::ostream& stream) const
    {
        stream << "(";
        lhs_->Print(stream);
        stream << " = ";
        rhs_->Print(stream);
        stream << ")";
    }
    } // namespace ast
