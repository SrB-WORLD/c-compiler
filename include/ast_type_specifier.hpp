#pragma once
#include "ast_node.hpp"
#include <string>


namespace ast {

    class TypeSpecifier:public Node {

    private:
        std::string type_name_;

    public:

        TypeSpecifier(std::string type_name):
        type_name_(type_name) {}
        void EmitRISC(std::ostream& stream , Context& context) const {
            stream << " ";
            (void)context;
        }
        void Print(std::ostream& stream) const {
            stream << " ";
        }

        std::string GetType() const {
            return type_name_;
        }
    };

} // namespace ast

