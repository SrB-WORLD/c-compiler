#include "ast_function_definition.hpp"
#include "ast_type_specifier.hpp"



namespace ast {

void FunctionDefinition::EmitRISC(std::ostream& stream, Context& context) const {
    // Safely cast declarator_ to DirectDeclarator*


    auto declarator = dynamic_cast<const DirectDeclarator*>(declarator_.get());
    std::string func_name = declarator->GetName();

    context.DeclareFunction(func_name);

    // Set exit label
    std::string exit_label = context.MakeLabel("func_exit");
    context.PushExitLabel(exit_label);

    // Function prologue
    stream << "  .text\n";
    stream << "  .globl " << declarator->GetName() << "\n";
    stream << declarator->GetName() << ":\n";
    stream << "  addi sp, sp, -1024\n";  // Allocate 32 bytes of stack space for local vars and saved regs
    stream << "  sw ra, 28(sp)\n";     // Save return address
    stream << "  sw s0, 24(sp)\n";     // Save old frame pointer
    stream << "  sw s1, 20(sp)\n";   //Force code
    stream << "  addi s0, sp, 20\n";   // Set up new frame pointer
    declarator_->EmitRISC(stream,context);



    // Emit code for the function body
    compound_statement_->EmitRISC(stream, context);

    // Function epilogue
    stream << exit_label << ":\n";
    stream << "  lw ra, 28(sp)\n";     // Restore return address
    stream << "  lw s0, 24(sp)\n";     // Restore frame pointer
    stream << "  lw s1, 20(sp)\n";   //Force Code
    stream << "  addi sp, sp, 1024\n";   // Deallocate stack frame
    stream << "  ret\n";               // Return to caller

    context.PopExitLabel();

}

void FunctionDefinition::Print(std::ostream& stream) const {
    stream << "FunctionDefinition: ";
    declarator_->Print(stream);                // Print function name
    stream << "() {\n";
    compound_statement_->Print(stream);        // Print function body
    stream << "}\n";
}

} // namespace ast


