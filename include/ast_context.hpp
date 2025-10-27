// ast_context.hpp
#pragma once

#include "ast_node.hpp"  // Include the type specifier
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "ast_type_specifier.hpp"




namespace ast {

class Context {

const std::string temp_reg_storage[7] = {"t0","t1","t2","t3","t4","t5","t6"};
const std::string argument_reg_storage[8] = {"a0","a1","a2","a3","a4","a6","a7","a5"};
const std::string saved_reg_storage[11] = {"s1","s2","s3","s4","s5","s6","s7","s8","s9","s10","s11"};



std::unordered_map<std::string, int> TypeSizeMap = {
    {"char", 1},
    {"int", 4},
    {"float", 4},
    {"double", 8},
    {"unsigned", 4}
};

private:


    std::unordered_map<std::string, int> arrays_;

    std::unordered_map<std::string, int> global_variables;
    std::unordered_map<std::string, std::string> variable_to_type;
    int label_counter_ = 0;
    int param_reg_index_ = 0;
    std::set<std::string> temp_registers;
    std::set<std::string> argument_registers;
    std::set<std::string> saved_registers;

    std::set<std::string> saved_handshake;
    std::set<std::string> temp_handshake;

    //label for functions
    std::vector<std::string> exit_label_stack_;
    std::unordered_set<std::string> declared_functions_;

    //to keep track of nested loops continue and break label
    std::vector<std::string> continue_stack_;
    std::vector<std::string> break_stack_;

    bool case_condition;
    std::string default_label;



    // to keep track of switch
    //SwitchStatement* current_switch_;


    using VariableInfo = std::pair<TypeSpecifier, int>;

    std::vector<std::unordered_map<std::string, VariableInfo>> scopes;
    std::vector<int> scope_offsets;
    int current_scope_offset = 0;
    int current_stack_offset = 0;

int allocate_stack_space(int size) {
    current_scope_offset += size;
    return current_scope_offset;
}




public:
    // Scoping
    void push_scope() {
        /*scopes.emplace_back();
        scope_offsets.push_back(current_scope_offset);*/
    }



    void pop_scope() {
        /*if (!scopes.empty()) {
            scopes.pop_back();
            current_scope_offset = scope_offsets.back();
            scope_offsets.pop_back();
        }*/
    }

    void case_true(){
        case_condition = true;
    }


    void case_false(){
        case_condition = false;
    }

    bool get_case_condition(){
        return case_condition;
    }

    /*
    Context() : current_switch_(nullptr) {}

    void SetCurrentSwitch(SwitchStatement* switch_stmt) {
        current_switch_ = switch_stmt;
    }

    SwitchStatement* GetCurrentSwitch() const {
        return current_switch_;
    }

    void ClearCurrentSwitch() {
        current_switch_ = nullptr;
    }
    */

    void PushContinueLabel(const std::string& label) {
        continue_stack_.push_back(label);
    }

    void PushBreakLabel(const std::string& label) {
        break_stack_.push_back(label);
    }




    void PopContinueLabel() {

        continue_stack_.pop_back();

    }

    void set_default_label(std::string defaultlabel){
        default_label = defaultlabel;

    }



    std::string getdefault_label(){
        return default_label;
    }

    void PopBreakLabel() {

        break_stack_.pop_back();

    }

    std::string GetCurrentContinueLabel() const {

        return continue_stack_.back();
    }

    std::string GetCurrentBreakLabel() const {

        return break_stack_.back();

    }

    std::string GetNextParamReg() {
        return argument_reg_storage[param_reg_index_++];
    }

    void DeclareFunction(const std::string& name) {
        declared_functions_.insert(name);
    }

    // Check if a function exists
    bool FunctionExists(const std::string& name) const {
        return declared_functions_.count(name) > 0;
    }

    void PushExitLabel(const std::string& label) {
        exit_label_stack_.push_back(label);
    }

    void PopExitLabel() {
        if (!exit_label_stack_.empty()) {
            exit_label_stack_.pop_back();
        }
    }

    std::string GetCurrentExitLabel() const {
        if (exit_label_stack_.empty()) {
            throw std::runtime_error("No active function context");
        }
        return exit_label_stack_.back();
    }

    /*
    void SetFunctionExitLabel(const std::string& label) {
        function_exit_label_ = label;
    }


    std::string GetFunctionExitLabel() const {
        return function_exit_label_;
    }*/

    std::string MakeLabel(const std::string& base) {
        return ".L" + std::to_string(label_counter_++) + "_" + base;
    }


    // Variable management
    /*void add_variable(const std::string& name, TypeSpecifier type) {
        int offset = allocate_stack_space(4);  // 4 bytes for int
        scopes.back()[name] = {type, offset};
    }*/

    void add_variable(const std::string& name, int size_bytes, std::string type) {
        current_stack_offset += size_bytes; // 4 bytes for `int`
        global_variables[name] = current_stack_offset;
        std::cerr<<name<<size_bytes<<current_stack_offset;
        variable_to_type[name] = type;// Track type and offset
    }

    void add_array(const std::string& name, int element_count) {
        int array_offset = element_count * 4;
        current_stack_offset += array_offset;
        arrays_[name] = current_stack_offset ;
    }

    int array_offset(const std::string& name){
        auto temp = arrays_.find(name);
        if (temp == arrays_.end()){
            return 0;
        }

        return temp ->second;

    }


    /*TypeSpecifier get_variable_type(const std::string& name) const {
        for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
            if (it->count(name)) return it->at(name).first;
        }
        throw TypeSpecifier::UNKNOWN;
    }

    TypeSpecifier get_variable_type(const std::string& name) const {
        if (global_variables.find(name) != global_variables.end()) {
            return global_variables.at(name);
        }
        throw std::runtime_error("Undefined variable: " + name);
    }
    */

    int get_variable_offset(const std::string& name) const {
        return global_variables.at(name);
    }

    int get_TypeSize(std::string type_name){
        auto it = TypeSizeMap.find(type_name);
        if (it != TypeSizeMap.end()) {
            return it->second;
        } else {
            return 0;
        }
    }

    int get_VariableSize(std::string identifier){
        auto vt_it = variable_to_type.find(identifier);
        if (vt_it == variable_to_type.end()) {
            return 0;
        }
        std::string type = vt_it->second;
        return get_TypeSize(type);
    }


    // ------------------------
    // Allocate/Deallocate 't' Registers for Expression
    // ------------------------

    std::string allocate_temp_register() {
        int reg_storage_size = sizeof(temp_reg_storage)/sizeof(temp_reg_storage[0]);
        for (int i=0;i<reg_storage_size;i++){
            auto reg_pointer = temp_registers.find(temp_reg_storage[i]);
            if (reg_pointer == temp_registers.end()){
                std::string new_reg = temp_reg_storage[i];
                temp_registers.insert(new_reg);
                return new_reg;
            }
        }
        throw std::runtime_error("No more temporary registers");
        return "";

    }

    void deallocate_temp_register(std::string& finish_reg){
        temp_registers.erase(finish_reg);
    }

    // ------------------------
    // Allocate/Deallocate 'a' Registers for Argument
    // ------------------------

    std::string allocate_argument_register() {
        int reg_storage_size = sizeof(argument_reg_storage)/sizeof(argument_reg_storage[0]);
        for (int i=0;i<reg_storage_size;i++){
            auto reg_pointer = argument_registers.find(argument_reg_storage[i]);
            if (reg_pointer == argument_registers.end()){
                std::string new_reg = argument_reg_storage[i];
                argument_registers.insert(new_reg);
                return new_reg;
            }
        }
        throw std::runtime_error("No more arg registers");
        return "";

    }

    void deallocate_argument_register(std::string& finish_reg){
        argument_registers.erase(finish_reg);
    }

    void reset_argument_register(){
        argument_registers.clear();
    }

    // ------------------------
    // Allocate/Deallocate 's' Registers for Functions/Saved
    // ------------------------

    std::string allocate_saved_register() {
        int reg_storage_size = sizeof(saved_reg_storage)/sizeof(saved_reg_storage[0]);
        for (int i=0;i<reg_storage_size;i++){
            auto reg_pointer = saved_registers.find(saved_reg_storage[i]);
            if (reg_pointer == saved_registers.end()){
                std::string new_reg = saved_reg_storage[i];
                saved_registers.insert(new_reg);
                return new_reg;
            }
        }
        throw std::runtime_error("No more saved registers");
        return "";

    }

    void reset_saved_register(){
        saved_registers.clear();
    }

    void deallocate_saved_register(std::string& finish_reg){
        saved_registers.erase(finish_reg);
    }

    void save_temp_registers(std::ostream& stream){
        while(!temp_registers.empty()){
            std::string saved_switch = allocate_saved_register();
            saved_handshake.insert(saved_switch);
            std::string temp_switch = *temp_registers.begin();
            std::cerr << temp_switch;
            temp_handshake.insert(temp_switch);
            stream << "  mv "+ saved_switch + ", "+ temp_switch+"\n";
            temp_registers.erase(temp_registers.begin());
        }
    }

    void return_temp_registers(std::ostream& stream){
        if (!temp_handshake.empty()){
            std::string temp_trade = *temp_handshake.begin();
            std::string saved_trade = *saved_handshake.begin();
            stream << "  mv " + temp_trade + ", "+saved_trade+"\n";
            temp_handshake.erase(temp_handshake.begin());
            saved_handshake.erase(saved_handshake.begin());
            temp_registers.insert(temp_trade);
            saved_registers.erase(saved_trade);
        }

    }

    // ------------------------
    // Type Identifier
    // ------------------------

    // bool isFunctionCall(const auto& node_){
    //     const FunctionCall* check = dynamic_cast<FunctionCall*>(node_.get());
    //     return check?true:false;
    // }

};

} // namespace ast
