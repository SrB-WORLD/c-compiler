#pragma once


#include "ast_node.hpp"

namespace ast {
class CaseStatement : public Node {
    private:
        NodePtr expression_; // The case expression
        NodePtr statement_; // The statement for this case


    public:

        CaseStatement(NodePtr expression, NodePtr statement)
            : expression_(std::move(expression)), statement_(std::move(statement)) {

            }

        bool getExpression() const{
            if (expression_ == nullptr){
                return false;
            }

            return true;
        }

        void EmitRISC(std::ostream& stream, Context& context) const override;
        void Print(std::ostream& stream) const override;
    };
}
