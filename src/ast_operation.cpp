#include "ast_operation.hpp"
#include <stdexcept>
#include <string>
#include "ast_context.hpp"
#include "ast_function_call.hpp"

namespace ast {

    void Multiplication::EmitRISC(std::ostream& stream, Context& context) const
    {
        l_op_->EmitRISC(stream, context);
        std::string l_calling_reg = context.allocate_temp_register();
        stream << "  mv "+ l_calling_reg + ", a5\n";
        r_op_->EmitRISC(stream, context);
        std::string r_calling_reg = context.allocate_temp_register();
        stream << "  mv " + r_calling_reg +", a5\n";
        stream << "  mul a5, "+l_calling_reg+", "+r_calling_reg+"\n";
        context.deallocate_temp_register(l_calling_reg);
        context.deallocate_temp_register(r_calling_reg);
    }

    void Multiplication::Print(std::ostream& stream) const
    {
        l_op_->Print(stream);
        stream << " * ";
        r_op_->Print(stream);
    }


    void Division::EmitRISC(std::ostream& stream, Context& context) const
    {
        l_op_->EmitRISC(stream, context);
        std::string l_calling_reg = context.allocate_temp_register();
        stream << "  mv "+ l_calling_reg + ", a5\n";
        r_op_->EmitRISC(stream, context);
        std::string r_calling_reg = context.allocate_temp_register();
        stream << "  mv " + r_calling_reg +", a5\n";
        stream << "  div a5, "+l_calling_reg+", "+r_calling_reg+"\n";
        context.deallocate_temp_register(l_calling_reg);
        context.deallocate_temp_register(r_calling_reg);
    }

    void Division::Print(std::ostream& stream) const
    {
        l_op_->Print(stream);
        stream << " / ";
        r_op_->Print(stream);
    }

    void Modulus::EmitRISC(std::ostream& stream, Context& context) const
    {
        l_op_->EmitRISC(stream, context);
        std::string l_calling_reg = context.allocate_temp_register();
        stream << "  mv "+ l_calling_reg + ", a5\n";
        r_op_->EmitRISC(stream, context);
        std::string r_calling_reg = context.allocate_temp_register();
        stream << "  mv " + r_calling_reg +", a5\n";
        stream << "  rem a5, "+l_calling_reg+", "+r_calling_reg+"\n";
        context.deallocate_temp_register(l_calling_reg);
        context.deallocate_temp_register(r_calling_reg);
    }

    void Modulus::Print(std::ostream& stream) const
    {
        l_op_->Print(stream);
        stream << " % ";
        r_op_->Print(stream);
    }

    void Addition::EmitRISC(std::ostream& stream, Context& context) const
    {
        const FunctionCall* check_l = dynamic_cast<FunctionCall*>(l_op_.get());
        if (check_l){
            context.save_temp_registers(stream);
        }
        l_op_->EmitRISC(stream, context);
        if (check_l){
            context.return_temp_registers(stream);
        }
        const FunctionCall* check_r = dynamic_cast<FunctionCall*>(r_op_.get());
        std::string l_calling_reg;
        if (check_r){
            context.save_temp_registers(stream);
            l_calling_reg = context.allocate_saved_register();
        } else {l_calling_reg = context.allocate_temp_register();}
        stream << "  mv "<< l_calling_reg << ", a5\n";
        r_op_->EmitRISC(stream, context);
        if (check_r){
            context.return_temp_registers(stream);
        }
        std::string r_calling_reg = context.allocate_temp_register();
        stream << "  mv " << r_calling_reg <<", a5\n";
        stream << "  add a5, "<<l_calling_reg<<", "<<r_calling_reg<<"\n";

        if (check_r){context.deallocate_saved_register(l_calling_reg);}
        else {context.deallocate_temp_register(l_calling_reg);}
        context.deallocate_temp_register(r_calling_reg);

    }

    void Addition::Print(std::ostream& stream) const
    {
        l_op_->Print(stream);
        stream << " + ";
        r_op_->Print(stream);
    }

    void Subtraction::EmitRISC(std::ostream& stream, Context& context) const
    {
        l_op_->EmitRISC(stream, context);
        std::string l_calling_reg = context.allocate_temp_register();
        stream << "  mv "+ l_calling_reg + ", a5\n";
        r_op_->EmitRISC(stream, context);
        std::string r_calling_reg = context.allocate_temp_register();
        stream << "  mv " + r_calling_reg +", a5\n";
        stream << "  sub a5, "+l_calling_reg+", "+r_calling_reg+"\n";
        context.deallocate_temp_register(l_calling_reg);
        context.deallocate_temp_register(r_calling_reg);
    }

    void Subtraction::Print(std::ostream& stream) const
    {
        l_op_->Print(stream);
        stream << " - ";
        r_op_->Print(stream);
    }

    void LeftShift::EmitRISC(std::ostream& stream, Context& context) const
    {
        l_op_->EmitRISC(stream, context);
        std::string l_calling_reg = context.allocate_temp_register();
        stream << "  mv "+ l_calling_reg + ", a5\n";
        r_op_->EmitRISC(stream, context);
        std::string r_calling_reg = context.allocate_temp_register();
        stream << "  mv " + r_calling_reg +", a5\n";
        stream << "  sll a5, "+l_calling_reg+", "+r_calling_reg+"\n";
        context.deallocate_temp_register(l_calling_reg);
        context.deallocate_temp_register(r_calling_reg);
    }

    void LeftShift::Print(std::ostream& stream) const
    {
        l_op_->Print(stream);
        stream << " << ";
        r_op_->Print(stream);
    }

    void RightShift::EmitRISC(std::ostream& stream, Context& context) const
    {
        l_op_->EmitRISC(stream, context);
        std::string l_calling_reg = context.allocate_temp_register();
        stream << "  mv "+ l_calling_reg + ", a5\n";
        r_op_->EmitRISC(stream, context);
        std::string r_calling_reg = context.allocate_temp_register();
        stream << "  mv " + r_calling_reg +", a5\n";
        stream << "  srl a5, "+l_calling_reg+", "+r_calling_reg+"\n";
        context.deallocate_temp_register(l_calling_reg);
        context.deallocate_temp_register(r_calling_reg);
    }

    void RightShift::Print(std::ostream& stream) const
    {
        l_op_->Print(stream);
        stream << " >> ";
        r_op_->Print(stream);
    }

    void LessThan::EmitRISC(std::ostream& stream, Context& context) const
    {
        l_op_->EmitRISC(stream, context);
        std::string l_calling_reg = context.allocate_temp_register();
        stream << "  mv "+ l_calling_reg + ", a5\n";
        r_op_->EmitRISC(stream, context);
        std::string r_calling_reg = context.allocate_temp_register();
        stream << "  mv " + r_calling_reg +", a5\n";
        stream << "  slt a5, "+l_calling_reg+", "+r_calling_reg+"\n";
        context.deallocate_temp_register(l_calling_reg);
        context.deallocate_temp_register(r_calling_reg);

    }

    void LessThan::Print(std::ostream& stream) const
    {
        l_op_->Print(stream);
        stream << " < ";
        r_op_->Print(stream);
    }

    void GreaterThan::EmitRISC(std::ostream& stream, Context& context) const
    {
        l_op_->EmitRISC(stream, context);
        std::string l_calling_reg = context.allocate_temp_register();
        stream << "  mv "+ l_calling_reg + ", a5\n";
        r_op_->EmitRISC(stream, context);
        std::string r_calling_reg = context.allocate_temp_register();
        stream << "  mv " + r_calling_reg +", a5\n";
        stream << "  slt a5, "+r_calling_reg+", "+l_calling_reg+"\n";
        context.deallocate_temp_register(l_calling_reg);
        context.deallocate_temp_register(r_calling_reg);
    }

    void GreaterThan::Print(std::ostream& stream) const
    {
        l_op_->Print(stream);
        stream << " * ";
        r_op_->Print(stream);
    }

    void LessEqual::EmitRISC(std::ostream& stream, Context& context) const
    {
        l_op_->EmitRISC(stream, context);
        std::string l_calling_reg = context.allocate_temp_register();
        stream << "  mv "+ l_calling_reg + ", a5\n";
        r_op_->EmitRISC(stream, context);
        std::string r_calling_reg = context.allocate_temp_register();
        stream << "  mv " + r_calling_reg +", a5\n";
        stream << "  slt "+l_calling_reg+", "+r_calling_reg+", "+l_calling_reg+"\n";
        stream << "  xori a5, "+l_calling_reg+", 1\n";
        context.deallocate_temp_register(l_calling_reg);
        context.deallocate_temp_register(r_calling_reg);
    }

    void LessEqual::Print(std::ostream& stream) const
    {
        l_op_->Print(stream);
        stream << " <= ";
        r_op_->Print(stream);
    }

    void GreaterEqual::EmitRISC(std::ostream& stream, Context& context) const
    {
        l_op_->EmitRISC(stream, context);
        std::string l_calling_reg = context.allocate_temp_register();
        stream << "  mv "+ l_calling_reg + ", a5\n";
        r_op_->EmitRISC(stream, context);
        std::string r_calling_reg = context.allocate_temp_register();
        stream << "  mv " + r_calling_reg +", a5\n";
        stream << "  slt "+l_calling_reg+", "+l_calling_reg+", "+r_calling_reg+"\n";
        stream << "  xori a5, "+l_calling_reg+", 1\n";
        context.deallocate_temp_register(l_calling_reg);
        context.deallocate_temp_register(r_calling_reg);
    }

    void GreaterEqual::Print(std::ostream& stream) const
    {
        l_op_->Print(stream);
        stream << " >= ";
        r_op_->Print(stream);
    }

    void Equal::EmitRISC(std::ostream& stream, Context& context) const
    {
        l_op_->EmitRISC(stream, context);
        std::string l_calling_reg = context.allocate_temp_register();
        stream << "  mv "+ l_calling_reg + ", a5\n";
        r_op_->EmitRISC(stream, context);
        std::string r_calling_reg = context.allocate_temp_register();
        stream << "  mv " + r_calling_reg +", a5\n";
        stream << "  xor "+l_calling_reg+", "+l_calling_reg+", "+r_calling_reg+"\n";
        stream << "  seqz a5, "+l_calling_reg+"\n";
        context.deallocate_temp_register(l_calling_reg);
        context.deallocate_temp_register(r_calling_reg);
    }

    void Equal::Print(std::ostream& stream) const
    {
        l_op_->Print(stream);
        stream << " == ";
        r_op_->Print(stream);
    }

    void NotEqual::EmitRISC(std::ostream& stream, Context& context) const
    {
        l_op_->EmitRISC(stream, context);
        std::string l_calling_reg = context.allocate_temp_register();
        stream << "  mv "+ l_calling_reg + ", a5\n";
        r_op_->EmitRISC(stream, context);
        std::string r_calling_reg = context.allocate_temp_register();
        stream << "  mv " + r_calling_reg +", a5\n";
        stream << "  xor "+l_calling_reg+", "+l_calling_reg+", "+r_calling_reg+"\n";
        stream << "  snez a5, "+l_calling_reg+"\n";
        context.deallocate_temp_register(l_calling_reg);
        context.deallocate_temp_register(r_calling_reg);
    }

    void NotEqual::Print(std::ostream& stream) const
    {
        l_op_->Print(stream);
        stream << " != ";
        r_op_->Print(stream);
    }

    void BitwiseAnd::EmitRISC(std::ostream& stream, Context& context) const
    {
        l_op_->EmitRISC(stream, context);
        std::string l_calling_reg = context.allocate_temp_register();
        stream << "  mv "+ l_calling_reg + ", a5\n";
        r_op_->EmitRISC(stream, context);
        std::string r_calling_reg = context.allocate_temp_register();
        stream << "  mv " + r_calling_reg +", a5\n";
        stream << "  and a5, "+l_calling_reg+", "+r_calling_reg+"\n";
        context.deallocate_temp_register(l_calling_reg);
        context.deallocate_temp_register(r_calling_reg);
    }

    void BitwiseAnd::Print(std::ostream& stream) const
    {
        l_op_->Print(stream);
        stream << " & ";
        r_op_->Print(stream);
    }

    void BitwiseXor::EmitRISC(std::ostream& stream, Context& context) const
    {

        l_op_->EmitRISC(stream, context);
        std::string l_calling_reg = context.allocate_temp_register();
        stream << "  mv "+ l_calling_reg + ", a5\n";
        r_op_->EmitRISC(stream, context);
        std::string r_calling_reg = context.allocate_temp_register();
        stream << "  mv " + r_calling_reg +", a5\n";
        stream << "  xor a5, "+l_calling_reg+", "+r_calling_reg+"\n";
        context.deallocate_temp_register(l_calling_reg);
        context.deallocate_temp_register(r_calling_reg);
    }

    void BitwiseXor::Print(std::ostream& stream) const
    {
        l_op_->Print(stream);
        stream << " ^ ";
        r_op_->Print(stream);
    }

    void BitwiseOr::EmitRISC(std::ostream& stream, Context& context) const
    {

        l_op_->EmitRISC(stream, context);
        std::string l_calling_reg = context.allocate_temp_register();
        stream << "  mv "+ l_calling_reg + ", a5\n";
        r_op_->EmitRISC(stream, context);
        std::string r_calling_reg = context.allocate_temp_register();
        stream << "  mv " + r_calling_reg +", a5\n";
        stream << "  or a5, "+l_calling_reg+", "+r_calling_reg+"\n";
        context.deallocate_temp_register(l_calling_reg);
        context.deallocate_temp_register(r_calling_reg);
    }

    void BitwiseOr::Print(std::ostream& stream) const
    {
        l_op_->Print(stream);
        stream << " | ";
        r_op_->Print(stream);
    }

    void LogicalAnd::EmitRISC(std::ostream& stream, Context& context) const
    {

        l_op_->EmitRISC(stream, context);
        std::string l_calling_reg = context.allocate_temp_register();
        stream << "  mv "+ l_calling_reg + ", a5\n";
        stream << "  snez "+l_calling_reg+", "+l_calling_reg+"\n";
        r_op_->EmitRISC(stream, context);
        std::string r_calling_reg = context.allocate_temp_register();
        stream << "  mv " + r_calling_reg +", a5\n";
        stream << "  snez "+r_calling_reg+", "+r_calling_reg+"\n";
        stream << "  and a5, "+l_calling_reg+", "+r_calling_reg+"\n";
        context.deallocate_temp_register(l_calling_reg);
        context.deallocate_temp_register(r_calling_reg);
    }

    void LogicalAnd::Print(std::ostream& stream) const
    {
        l_op_->Print(stream);
        stream << " && ";
        r_op_->Print(stream);
    }

    void LogicalOr::EmitRISC(std::ostream& stream, Context& context) const
    {

        l_op_->EmitRISC(stream, context);
        std::string l_calling_reg = context.allocate_temp_register();
        stream << "  mv "+ l_calling_reg + ", a5\n";
        stream << "  snez "+l_calling_reg+", "+l_calling_reg+"\n";
        r_op_->EmitRISC(stream, context);
        std::string r_calling_reg = context.allocate_temp_register();
        stream << "  mv " + r_calling_reg +", a5\n";
        stream << "  snez "+r_calling_reg+", "+r_calling_reg+"\n";
        stream << "  or a5, "+l_calling_reg+", "+r_calling_reg+"\n";
        context.deallocate_temp_register(l_calling_reg);
        context.deallocate_temp_register(r_calling_reg);
    }

    void LogicalOr::Print(std::ostream& stream) const
    {
        l_op_->Print(stream);
        stream << " || ";
        r_op_->Print(stream);
    }

} // namespace ast
