#include "ast_node.hpp"
#include "ast_context.hpp"

namespace ast {


std::string Node::GetType() const
{
    return " " ;
}

int Node::evaluate() const{
    return 0;
}

// NodeList Implementation
NodeList::NodeList(NodePtr first_node) {
    nodes_.push_back(std::move(first_node));
}

void NodeList::PushBack(NodePtr item) {
    nodes_.push_back(std::move(item));
}

void NodeList::EmitRISC(std::ostream& stream, Context& context) const {
    for (const auto& node : nodes_) {
        node->EmitRISC(stream, context);
    }
}

void NodeList::Print(std::ostream& stream) const {
    for (const auto& node : nodes_) {
        node->Print(stream);
    }
}

const std::vector<NodePtr>& NodeList::GetNodes() const {
    return nodes_;
}


//Block Statement Implementation
BlockStatement::BlockStatement(NodePtr declarations, NodePtr statements)
    : declarations_(std::move(declarations)),
      statements_(std::move(statements)) {}

void BlockStatement::EmitRISC(std::ostream& stream, Context& context) const {


    if (declarations_) declarations_->EmitRISC(stream, context);
    if (statements_) statements_->EmitRISC(stream, context);


}

void BlockStatement::Print(std::ostream& stream) const {
    stream << "{\n";
    if (declarations_) declarations_->Print(stream);
    if (statements_) statements_->Print(stream);
    stream << "}\n";
}

// VariableReference Implementation
VariableReference::VariableReference(const std::string& identifier, const std::string& type)
    : identifier_(identifier), type_(type) {}

void VariableReference::EmitRISC(std::ostream& stream, Context& context) const {
    int offset = context.get_variable_offset(identifier_);
    stream << "lw a5, " << offset << "(sp)" << std::endl; // Load the variable's value into a5
}

void VariableReference::Print(std::ostream& stream) const {
    stream << "VariableReference: " << identifier_ << " (" << type_ << ")" << std::endl;
}

const std::string& VariableReference::GetIdentifier() const {
    return identifier_;
}



} // namespace ast
