#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "ast_argument_list.hpp"
#include "ast_assignment.hpp"
#include "ast_direct_declarator.hpp"
#include "ast_function_definition.hpp"
#include "ast_identifier.hpp"
#include "ast_jump_statement.hpp"
#include "ast_node.hpp"
#include "ast_storage_specifier.hpp"
#include "ast_constant.hpp"
#include "ast_context.hpp"
#include "ast_init_declarator_list.hpp"
#include "ast_float_constant.hpp"
#include "ast_expression.hpp"
#include "ast_unary_expression.hpp"
#include "ast_operation.hpp"
#include "ast_string_literal.hpp"
#include "ast_assignment.hpp"
#include "ast_declaration.hpp"
#include "ast_if_statement.hpp"
#include "ast_WhileLoop.hpp"
#include "ast_function_call.hpp"
#include "ast_parameter_declaration.hpp"
#include "ast_init_declarator.hpp"
#include "ast_ForLoop.hpp"
#include "ast_continue.hpp"
#include "ast_Break.hpp"
#include "ast_typedef_declaration.hpp"
#include "ast_switch_statement.hpp"
#include "ast_sizeof.hpp"
#include "ast_case_statement.hpp"
#include "ast_type_specifier.hpp"
#include "ast_defaultstatement.hpp"

#include "ast_array_declarator.hpp"
#include "ast_arrayIndex.hpp"

ast::NodePtr ParseAST(std::string file_name);
