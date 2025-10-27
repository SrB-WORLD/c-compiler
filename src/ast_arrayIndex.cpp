#include "ast_array_declarator.hpp"
#include "ast_context.hpp"
#include "ast_arrayIndex.hpp"


namespace ast {

    void ArrayIndex::EmitRISC(std::ostream& stream, Context& context) const{

        std::string array_name = GetName();

        int idx = evaluate();

        int offset = context.array_offset(array_name);

        int each_idx_offset = offset - ((idx + 1) * 4) ;


        stream << "lw a5, -" << each_idx_offset << "(s0) # get array index " <<  "\n";
    }

    void ArrayIndex::Print(std::ostream& stream) const
    {
        identifier_->Print(stream);
        stream << "[";
        index_->Print(stream);
        stream << "]";
    }
    } // namespace ast
