#pragma once

#ifndef AST_NODE_HPP
#define AST_NODE_HPP

#include <iostream>
#include <memory>
#include <vector>


// Forward declarations
namespace ast {
    class Context;
    class Identifier;
    class IntConstant;
    class TypeSpecifier;
}


namespace ast {

class Node
{
public:
    virtual ~Node() = default;

    // Virtual methods to be overridden by derived classes
    virtual void EmitRISC(std::ostream& stream, Context& context) const = 0;
    virtual void Print(std::ostream& stream) const = 0;
    virtual std::string GetType() const;    virtual int evaluate() const;

    virtual void ProcessDeclaration(Context&) {}
};

using NodePtr = std::unique_ptr<Node>;

class NodeList : public Node
{
private:
    std::vector<NodePtr> nodes_;

public:
    NodeList(NodePtr first_node); // Declaration only
    void PushBack(NodePtr item); // Declaration only
    virtual void EmitRISC(std::ostream& stream, Context& context) const override; // Declaration only
    virtual void Print(std::ostream& stream) const override; // Declaration only
    const std::vector<NodePtr>& GetNodes() const; // Declaration only
};

class BlockStatement : public Node {
    NodePtr declarations_;
    NodePtr statements_;
public:
    // Declaration only
    BlockStatement(NodePtr declarations, NodePtr statements);

    // Declaration only
    void EmitRISC(std::ostream& stream, Context& context) const override;

    // Add missing Print declaration
    void Print(std::ostream& stream) const override;
};


class VariableReference : public Node
{
private:
    std::string identifier_;
    std::string type_;

public:
    VariableReference(const std::string& identifier, const std::string& type); // Declaration only
    virtual void EmitRISC(std::ostream& stream, Context& context) const override; // Declaration only
    virtual void Print(std::ostream& stream) const override; // Declaration only
    const std::string& GetIdentifier() const; // Declaration only
};


class InitializerList : public Node {
    private:
        std::vector<NodePtr> initializers_;

    public:
        InitializerList(NodePtr initializer) {
            initializers_.push_back(std::move(initializer));
        }

        void PushBack(NodePtr initializer) {
            initializers_.push_back(std::move(initializer));
        }

        virtual void EmitRISC(std::ostream& stream, Context& context) const override {
            for (const auto& initializer : initializers_) {
                initializer->EmitRISC(stream, context);
            }
        }

        virtual void Print(std::ostream& stream) const override {
            for (const auto& initializer : initializers_) {
                initializer->Print(stream);
            }
        }

        const std::vector<NodePtr>& GetInitializers() const { return initializers_; }
    };


} // namespace ast

#endif
