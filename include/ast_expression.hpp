#pragma once

#include "ast_node.hpp"
#include "ast_context.hpp"
#include "ast_identifier.hpp"
#include <string>
namespace ast {

    class Postfix : public Node
    {
    private:
        NodePtr postfix_expression_;
        std::string change_operator_;

    public:
        Postfix(NodePtr postfix_expression, std::string change_operator) :
        postfix_expression_(std::move(postfix_expression)),change_operator_(change_operator) {}
        void EmitRISC(std::ostream& stream, Context& context) const override;
        void Print(std::ostream& stream) const override;
    };


    class Prefix : public Node
    {
    private:
        NodePtr prefix_expression_;
        std::string change_operator_;

    public:
        Prefix(NodePtr prefix_expression, std::string change_operator) :
        prefix_expression_(std::move(prefix_expression)),change_operator_(change_operator) {}
        void EmitRISC(std::ostream& stream, Context& context) const override;
        void Print(std::ostream& stream) const override;
    };

    class Ternary : public Node
    {
    private:
        NodePtr condition_;
        NodePtr true_expression_;
        NodePtr false_expression_;
    public:
        Ternary(NodePtr condition, NodePtr true_expression, NodePtr false_expression)
        : condition_(std::move(condition)),
          true_expression_(std::move(true_expression)),
          false_expression_(std::move(false_expression)) {}

        void EmitRISC(std::ostream& stream, Context& context) const override;
        void Print(std::ostream& stream) const override;
    };

} // namespace ast
