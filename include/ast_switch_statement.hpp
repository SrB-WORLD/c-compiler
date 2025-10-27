#pragma once
#include "ast_node.hpp"



namespace ast{


class SwitchStatement : public Node {


    private:

        NodePtr expression_;
        NodePtr case_list_;

    public:
        SwitchStatement(NodePtr expression, NodePtr case_list)
            : expression_(std::move(expression)), case_list_(std::move((case_list))) {}

        void EmitRISC(std::ostream &stream, Context &context) const override;
        void Print(std::ostream &stream) const override;

    };


}
