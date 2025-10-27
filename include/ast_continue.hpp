
#pragma once

#include "ast_node.hpp"

namespace ast {

class ContinueStatement : public Node {
public:

    ContinueStatement() = default;

    // Override the EmitRISC method to generate code for the continue statement
    void EmitRISC(std::ostream& stream, Context& context) const override;

    // Override the Print method to print the continue statement
    void Print(std::ostream& stream) const override;
};

} // namespace ast
