#pragma once

#include "ast_node.hpp"

namespace ast {

class Multiplication : public Node
{
    private:
        NodePtr l_op_;
        NodePtr r_op_;

    public:
        Multiplication(NodePtr l_op, NodePtr r_op):
        l_op_(std::move(l_op)), r_op_(std::move(r_op)) {}
        void EmitRISC(std::ostream& stream, Context& context) const override;
        void Print(std::ostream& stream) const override;

        int evaluate() const {
            return l_op_->evaluate() * r_op_-> evaluate();
        }
};




class Division : public Node
{
    private:
        NodePtr l_op_;
        NodePtr r_op_;

    public:
        Division(NodePtr l_op, NodePtr r_op):
        l_op_(std::move(l_op)), r_op_(std::move(r_op)) {}
        void EmitRISC(std::ostream& stream, Context& context) const override;
        void Print(std::ostream& stream) const override;

        int evaluate() const {
            return l_op_->evaluate() / r_op_-> evaluate();
        }

};

class Modulus : public Node
{
    private:
        NodePtr l_op_;
        NodePtr r_op_;

    public:
        Modulus(NodePtr l_op, NodePtr r_op):
        l_op_(std::move(l_op)), r_op_(std::move(r_op)) {}
        void EmitRISC(std::ostream& stream, Context& context) const override;
        void Print(std::ostream& stream) const override;
        int evaluate() const {
            return l_op_->evaluate() % r_op_-> evaluate();
        }
};

class Addition : public Node
{
    private:
        NodePtr l_op_;
        NodePtr r_op_;

    public:
        Addition(NodePtr l_op, NodePtr r_op):
        l_op_(std::move(l_op)), r_op_(std::move(r_op)) {}
        void EmitRISC(std::ostream& stream, Context& context) const override;
        void Print(std::ostream& stream) const override;
        int evaluate() const {
            return l_op_->evaluate() + r_op_-> evaluate();
        }
};

class Subtraction : public Node
{
    private:
        NodePtr l_op_;
        NodePtr r_op_;

    public:
        Subtraction(NodePtr l_op, NodePtr r_op):
        l_op_(std::move(l_op)), r_op_(std::move(r_op)) {}
        void EmitRISC(std::ostream& stream, Context& context) const override;
        void Print(std::ostream& stream) const override;
        int evaluate() const {
            return l_op_->evaluate() - r_op_-> evaluate();
        }
};

class LeftShift : public Node
{
    private:
        NodePtr l_op_;
        NodePtr r_op_;

    public:
        LeftShift(NodePtr l_op, NodePtr r_op):
        l_op_(std::move(l_op)), r_op_(std::move(r_op)) {}
        void EmitRISC(std::ostream& stream, Context& context) const override;
        void Print(std::ostream& stream) const override;
        int evaluate() const {
            return l_op_->evaluate() << r_op_-> evaluate();
        }
};

class RightShift : public Node
{
    private:
        NodePtr l_op_;
        NodePtr r_op_;

    public:
        RightShift(NodePtr l_op, NodePtr r_op):
        l_op_(std::move(l_op)), r_op_(std::move(r_op)) {}
        void EmitRISC(std::ostream& stream, Context& context) const override;
        void Print(std::ostream& stream) const override;
        int evaluate() const {
            return l_op_->evaluate() >> r_op_-> evaluate();
        }
};

class LessThan : public Node
{
    private:
        NodePtr l_op_;
        NodePtr r_op_;

    public:
        LessThan(NodePtr l_op, NodePtr r_op):
        l_op_(std::move(l_op)), r_op_(std::move(r_op)) {}
        void EmitRISC(std::ostream& stream, Context& context) const override;
        void Print(std::ostream& stream) const override;
        int evaluate() const {
            return l_op_->evaluate() < r_op_-> evaluate();
        }
};

class GreaterThan : public Node
{
    private:
        NodePtr l_op_;
        NodePtr r_op_;

    public:
        GreaterThan(NodePtr l_op, NodePtr r_op):
        l_op_(std::move(l_op)), r_op_(std::move(r_op)) {}
        void EmitRISC(std::ostream& stream, Context& context) const override;
        void Print(std::ostream& stream) const override;
        int evaluate() const {
            return l_op_->evaluate() > r_op_-> evaluate();
        }
};

class LessEqual : public Node
{
    private:
        NodePtr l_op_;
        NodePtr r_op_;

    public:
        LessEqual(NodePtr l_op, NodePtr r_op):
        l_op_(std::move(l_op)), r_op_(std::move(r_op)) {}
        void EmitRISC(std::ostream& stream, Context& context) const override;
        void Print(std::ostream& stream) const override;
        int evaluate() const {
            return l_op_->evaluate() <= r_op_-> evaluate();
        }
};

class GreaterEqual : public Node
{
    private:
        NodePtr l_op_;
        NodePtr r_op_;

    public:
        GreaterEqual(NodePtr l_op, NodePtr r_op):
        l_op_(std::move(l_op)), r_op_(std::move(r_op)) {}
        void EmitRISC(std::ostream& stream, Context& context) const override;
        void Print(std::ostream& stream) const override;
        int evaluate() const {
            return l_op_->evaluate() >= r_op_-> evaluate();
        }
};


class Equal : public Node
{
    private:
        NodePtr l_op_;
        NodePtr r_op_;

    public:
        Equal(NodePtr l_op, NodePtr r_op):
        l_op_(std::move(l_op)), r_op_(std::move(r_op)) {}
        void EmitRISC(std::ostream& stream, Context& context) const override;
        void Print(std::ostream& stream) const override;
        int evaluate() const {
            return l_op_->evaluate() == r_op_-> evaluate();
        }
};

class NotEqual : public Node
{
    private:
        NodePtr l_op_;
        NodePtr r_op_;

    public:
        NotEqual(NodePtr l_op, NodePtr r_op):
        l_op_(std::move(l_op)), r_op_(std::move(r_op)) {}
        void EmitRISC(std::ostream& stream, Context& context) const override;
        void Print(std::ostream& stream) const override;
        int evaluate() const {
            return l_op_->evaluate() !=  r_op_-> evaluate();
        }
};

class BitwiseAnd : public Node
{
    private:
        NodePtr l_op_;
        NodePtr r_op_;

    public:
        BitwiseAnd(NodePtr l_op, NodePtr r_op):
        l_op_(std::move(l_op)), r_op_(std::move(r_op)) {}
        void EmitRISC(std::ostream& stream, Context& context) const override;
        void Print(std::ostream& stream) const override;
        int evaluate() const {
            return l_op_->evaluate() & r_op_-> evaluate();
        }
};

class BitwiseXor : public Node
{
    private:
        NodePtr l_op_;
        NodePtr r_op_;

    public:
        BitwiseXor(NodePtr l_op, NodePtr r_op):
        l_op_(std::move(l_op)), r_op_(std::move(r_op)) {}
        void EmitRISC(std::ostream& stream, Context& context) const override;
        void Print(std::ostream& stream) const override;
        int evaluate() const {
            return l_op_->evaluate() ^ r_op_-> evaluate();
        }
};

class BitwiseOr : public Node
{
    private:
        NodePtr l_op_;
        NodePtr r_op_;

    public:
        BitwiseOr(NodePtr l_op, NodePtr r_op):
        l_op_(std::move(l_op)), r_op_(std::move(r_op)) {}
        void EmitRISC(std::ostream& stream, Context& context) const override;
        void Print(std::ostream& stream) const override;
        int evaluate() const {
            return l_op_->evaluate() | r_op_-> evaluate();
        }
};

class LogicalAnd : public Node
{
    private:
        NodePtr l_op_;
        NodePtr r_op_;

    public:
        LogicalAnd(NodePtr l_op, NodePtr r_op):
        l_op_(std::move(l_op)), r_op_(std::move(r_op)) {}
        void EmitRISC(std::ostream& stream, Context& context) const override;
        void Print(std::ostream& stream) const override;
        int evaluate() const {
            return l_op_->evaluate() && r_op_-> evaluate();
        }
};

class LogicalOr : public Node
{
    private:
        NodePtr l_op_;
        NodePtr r_op_;

    public:
        LogicalOr(NodePtr l_op, NodePtr r_op):
        l_op_(std::move(l_op)), r_op_(std::move(r_op)) {}
        void EmitRISC(std::ostream& stream, Context& context) const override;
        void Print(std::ostream& stream) const override;
        int evaluate() const {
            return l_op_->evaluate() || r_op_-> evaluate();
        }
};
} // namespace ast
