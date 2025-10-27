#ifndef AST_DEFAULT_STATEMENT_HPP
#define AST_DEFAULT_STATEMENT_HPP
#pragma once


#include "ast_node.hpp"

namespace ast{

class DefaultStatement : public Node {
    private:
        NodePtr statement_;
    public:
        DefaultStatement(NodePtr statement)
            : statement_(std::move(statement)) {}

        void EmitRISC(std::ostream& stream, Context& context) const override;
        void Print(std::ostream& stream) const override;
};
}

#endif

