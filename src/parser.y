%code requires{
    #include "ast.hpp"



    using namespace ast;
	extern int yylineno;
	extern char* yytext;
    extern std::unordered_map<std::string,std::string> typedf_map;
    extern void add_typedef(std::string identifier,std::string type);
    extern Node* g_root;
    extern Context context;
    extern FILE* yyin;
    int yylex(void);
    void yyerror(const char*);
    int yylex_destroy(void);

    extern Context context;

}

%union{
    Node*           node;
    NodeList*       node_list;
    int             number_int;
    double          number_float;
    std::string*    string;
    StorageSpecifier storage_class_specifier;
    yytokentype     token;
}

%define parse.error detailed
%define parse.lac full


%token IDENTIFIER INT_CONSTANT FLOAT_CONSTANT STRING_LITERAL
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP
%token MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
%token TYPE_NAME TYPEDEF EXTERN STATIC AUTO REGISTER SIZEOF
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS
%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%type <node> external_declaration function_definition primary_expression postfix_expression argument_expression_list
%type <node> unary_expression cast_expression multiplicative_expression additive_expression shift_expression relational_expression
%type <node> equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression
%type <node> conditional_expression assignment_expression expression constant_expression
%type <node> statement compound_statement jump_statement expression_statement selection_statement iteration_statement
%type <node> init_declarator init_declarator_list declaration_list specifier_qualifier_list
%type <node> initializer initializer_list labeled_statement type_specifier
%type <node> declaration
%type <node> declarator direct_declarator parameter_list parameter_declaration abstract_declarator type_name
%type <node>  declaration_specifiers
%type <node_list> statement_list

%type <node_list> translation_unit


%type <string> unary_operator assignment_operator
%type <number_int> INT_CONSTANT
%type <number_float> FLOAT_CONSTANT
%type <string> STRING_LITERAL
%type <string> IDENTIFIER
%type <storage_class_specifier> storage_class_specifier

%start ROOT
%%

ROOT
    : translation_unit { g_root = $1; }

translation_unit
	: external_declaration { $$ = new NodeList(NodePtr($1)); }
	| translation_unit external_declaration {

        $1->PushBack(NodePtr($2));
        $$ = $1;

    }
	;

external_declaration
    : function_definition { $$ = $1; }
    | declaration         { $$ = $1; }
    ;

function_definition
    : declaration_specifiers declarator compound_statement {
        $$ = new FunctionDefinition(NodePtr($1), NodePtr($2), NodePtr($3));
    }

    ;


initializer
    : assignment_expression {
        $$ = $1;
    }
    | '{' initializer_list '}' {
        $$ = new InitializerList(NodePtr($2));
    }
    | '{' initializer_list ',' '}' {
        $$ = new InitializerList(NodePtr($2));
    }
    ;


initializer_list
    : initializer {
        // Create a new InitializerList with the first initializer
        $$ = new InitializerList(NodePtr($1));
    }
    | initializer_list ',' initializer {
        // Add the new initializer to the existing InitializerList
        auto initList = dynamic_cast<InitializerList*>($1);
        if (initList) {
            initList->PushBack(NodePtr($3));
            $$ = initList;
        } else {
            throw std::runtime_error("Expected $1 to be of type InitializerList");
        }
    }
    ;

storage_class_specifier
    : TYPEDEF { $$ = StorageSpecifier::TYPEDEF; }
    ;

init_declarator
    : declarator {
        // No initializer
        $$ = new InitDeclarator(NodePtr($1), nullptr);
    }
    | declarator '=' initializer {
        // With initializer
        $$ = new InitDeclarator(NodePtr($1), NodePtr($3));
    }
    ;

init_declarator_list
    : init_declarator {
        // Create a new InitDeclaratorList and add the first declarator
        auto* list = new InitDeclaratorList();
        list->AddDeclarator(NodePtr($1));
        $$ = list;
    }
    | init_declarator_list ',' init_declarator {
        auto* list = dynamic_cast<InitDeclaratorList*>($1);
        list->AddDeclarator(NodePtr($3));
        $$ = list;
    }
    ;

declaration
    : declaration_specifiers init_declarator_list ';' {
            auto* decl = new Declaration(NodePtr($1), NodePtr($2));
            decl->ProcessDeclaration(context);
            $$ = decl;
        }

    ;


declaration_list
: declaration {
    // Create a new NodeList with the first declaration
    $$ = new NodeList(NodePtr($1));
}
| declaration_list declaration {
    // Add the new declaration to the existing NodeList
    auto nodeList = dynamic_cast<NodeList*>($1);
    if (nodeList) {
        nodeList->PushBack(NodePtr($2));
        $$ = nodeList;
    } else {
        throw std::runtime_error("Expected $1 to be of type NodeList");
    }
}
;



declaration_specifiers
    :type_specifier { $$ = $1; }
    ;


declarator
    : direct_declarator { $$ = $1; }
    ;

direct_declarator
    : IDENTIFIER {
        $$ = new Identifier(std::move(*$1));
        delete $1;
    }
    | direct_declarator '(' ')' {
        $$ = new DirectDeclarator(NodePtr($1), nullptr);
    }
    | direct_declarator '(' parameter_list ')' {
        $$ = new DirectDeclarator(NodePtr($1), NodePtr($3));
    }

    | direct_declarator '[' constant_expression ']' {
        $$ = new ArrayDeclarator(NodePtr($1), NodePtr($3));
    }
    ;



parameter_list
    : parameter_declaration {
        // Create a new NodeList with the first (already processed) parameter
        $$ = new NodeList(NodePtr($1));
    }
    | parameter_list ',' parameter_declaration {
        // Add the next (already processed) parameter to the existing NodeList
        auto* list = dynamic_cast<NodeList*>($1);
        if (list) {
            list->PushBack(NodePtr($3));
            $$ = list;
        } else {
            throw std::runtime_error("Expected $1 to be of type NodeList");
        }
    }
    ;

type_name
	: specifier_qualifier_list {$$ = $1;}
	;

parameter_declaration
	: declaration_specifiers declarator {
        // Named parameter (e.g., int x)
        auto* param = new ParameterDeclaration(NodePtr($1), NodePtr($2));
        param->ProcessDeclaration(context);
        $$ = param;
    }
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier {$$ = $1;}
	;

type_specifier
    : INT { $$ = new TypeSpecifier("int"); }
    | FLOAT { $$ = new TypeSpecifier("float"); }
    | CHAR { $$ = new TypeSpecifier("char"); }
    | UNSIGNED { $$ = new TypeSpecifier("unsigned"); }
    | DOUBLE { $$ = new TypeSpecifier("double"); }
    | VOID
    ;


statement
	: expression_statement { $$ = $1; }
	| compound_statement {$$ = $1;}
	| jump_statement { $$ = $1; }
    | selection_statement { $$ = $1;}
    | iteration_statement { $$ = $1; }
    | labeled_statement { $$ = $1; }
	;

labeled_statement
	:
	| CASE constant_expression ':' statement { $$ = new CaseStatement(NodePtr($2) , NodePtr($4)); }

	| DEFAULT ':' statement {$$ = new CaseStatement(nullptr, NodePtr($3)); }

	;


selection_statement
	: IF '(' expression ')' statement { $$ = new IfStatement(NodePtr($3), NodePtr($5), nullptr); }
	| IF '(' expression ')' statement ELSE statement {
        $$ = new IfStatement(NodePtr($3), NodePtr($5), NodePtr($7));
      }
	| SWITCH '(' expression ')' statement {
        $$  = new SwitchStatement(NodePtr($3), NodePtr($5));

    }
	;

iteration_statement
	: WHILE '(' expression ')' statement { $$ = new WhileLoop(NodePtr($3), NodePtr($5)); }
	| DO statement WHILE '(' expression ')' ';'
	| FOR '(' expression_statement expression_statement ')' statement {
        $$ = new ForLoop(NodePtr($3), NodePtr($4), nullptr, NodePtr($6));
    }
	| FOR '(' expression_statement expression_statement expression ')' statement {
        $$ = new ForLoop(NodePtr($3), NodePtr($4), NodePtr($5), NodePtr($7));
    }
	;






compound_statement
    : '{' '}' {

        $$ = new BlockStatement(NodePtr(nullptr), NodePtr(nullptr));
    }
    | '{' statement_list '}' {
        $$ = $2;
    }
    | '{' declaration_list '}' {
        $$ = $2;
    }
    | '{' declaration_list statement_list '}' {

        $$ = new BlockStatement(NodePtr($2),NodePtr($3));
    }
    ;


statement_list
    : statement {

        $$ = new NodeList(NodePtr($1));
    }
    | statement_list statement {

        auto nodeList = dynamic_cast<NodeList*>($1);
        if (nodeList) {
            nodeList->PushBack(NodePtr($2));
            $$ = nodeList;
        } else {
            throw std::runtime_error("Expected $1 to be of type NodeList");
        }
    }
    ;


expression_statement
	: ';'
	| expression ';' { $$ = $1; }
	;


jump_statement
    : RETURN ';' { $$ = new ReturnStatement(nullptr); }
    | RETURN expression ';' { $$ = new ReturnStatement(NodePtr($2)); }
    | CONTINUE ';' { $$ = new ContinueStatement(); }
    | BREAK ';' { $$ = new BreakStatement(); }
    ;


primary_expression
    : IDENTIFIER {
        $$ = new Identifier(std::move(*$1));
        delete $1;
    }
    | INT_CONSTANT {
        $$ = new IntConstant($1);
    }
    | '(' expression ')' {
        $$ = $2;
    }
    | FLOAT_CONSTANT
    | STRING_LITERAL
    ;




postfix_expression
    : primary_expression { $$ = $1; }
    | postfix_expression '(' argument_expression_list ')'{
        $$ = new FunctionCall(NodePtr($1),NodePtr($3));
    }
    | postfix_expression '(' ')' {
        $$ = new FunctionCall(NodePtr($1), nullptr);
    }
	| postfix_expression INC_OP { $$ = new Postfix(NodePtr($1), "++");}
	| postfix_expression DEC_OP { $$ = new Postfix(NodePtr($1), "--");}
    | postfix_expression '[' expression ']'{
        $$ = new ArrayIndex(NodePtr($1), NodePtr($3));
    }
    ;

argument_expression_list
    : assignment_expression {
        auto* list = new ArgumentList();
        list->AddArgument(NodePtr($1));
        $$ = list;
    }
    | argument_expression_list ',' assignment_expression {
        auto* nodeList = dynamic_cast<ArgumentList*>($1);
        if (nodeList) {
            nodeList->AddArgument(NodePtr($3));
            $$ = nodeList;
        } else {
            throw std::runtime_error("Expected $1 to be of type ArgumentList");
        }
    }
    ;

unary_expression
    : postfix_expression { $$ = $1; }
    | INC_OP unary_expression { $$ = new Prefix(NodePtr($2),"++");}
	| DEC_OP unary_expression { $$ = new Prefix(NodePtr($2),"--");}
	| unary_operator cast_expression {
        $$ = new Unary(*$1, NodePtr($2));
        delete $1;
    }
    | SIZEOF unary_expression { $$ = new sizeOf(NodePtr($2));}
    | SIZEOF '(' type_name ')' { $$ = new sizeOf(NodePtr($3));}
    ;

cast_expression
	: unary_expression { $$ = $1; }
	| '(' type_specifier ')' cast_expression
	;

unary_operator
	: '&' { $$ = new std::string("&");}
	| '*' { $$ = new std::string("*");}
	| '+' { $$ = new std::string("+");}
	| '-' { $$ = new std::string("-");}
	| '~' { $$ = new std::string("~");}
	| '!' { $$ = new std::string("!");}
	;

multiplicative_expression
    : cast_expression { $$ = $1; }
    | multiplicative_expression '*' cast_expression {$$ = new Multiplication(NodePtr($1),NodePtr($3));}
	| multiplicative_expression '/' cast_expression {$$ = new Division(NodePtr($1),NodePtr($3));}
	| multiplicative_expression '%' cast_expression {$$ = new Modulus(NodePtr($1),NodePtr($3));}
    ;

additive_expression
    : multiplicative_expression { $$ = $1; }
	| additive_expression '+' multiplicative_expression {$$ = new Addition(NodePtr($1),NodePtr($3));}
	| additive_expression '-' multiplicative_expression {$$ = new Subtraction(NodePtr($1),NodePtr($3));}
    ;

shift_expression
    : additive_expression { $$ = $1; }
	| shift_expression LEFT_OP additive_expression {$$ = new LeftShift(NodePtr($1),NodePtr($3));}
	| shift_expression RIGHT_OP additive_expression {$$ = new RightShift(NodePtr($1),NodePtr($3));}
    ;

relational_expression
    : shift_expression { $$ = $1; }
	| relational_expression '<' shift_expression {$$ = new LessThan(NodePtr($1),NodePtr($3));}
	| relational_expression '>' shift_expression {$$ = new GreaterThan(NodePtr($1),NodePtr($3));}
	| relational_expression LE_OP shift_expression {$$ = new LessEqual(NodePtr($1),NodePtr($3));}
	| relational_expression GE_OP shift_expression {$$ = new GreaterEqual(NodePtr($1),NodePtr($3));}
    ;

equality_expression
    : relational_expression { $$ = $1; }
	| equality_expression EQ_OP relational_expression {$$ = new Equal(NodePtr($1),NodePtr($3));}
	| equality_expression NE_OP relational_expression {$$ = new NotEqual(NodePtr($1),NodePtr($3));}
    ;

and_expression
    : equality_expression { $$ = $1; }
	| and_expression '&' equality_expression {$$ = new BitwiseAnd(NodePtr($1),NodePtr($3));}

    ;

exclusive_or_expression
	: and_expression { $$ = $1; }
	| exclusive_or_expression '^' and_expression {$$ = new BitwiseXor(NodePtr($1),NodePtr($3));}
	;

inclusive_or_expression
	: exclusive_or_expression { $$ = $1; }
	| inclusive_or_expression '|' exclusive_or_expression {$$ = new BitwiseOr(NodePtr($1),NodePtr($3));}
	;

logical_and_expression
	: inclusive_or_expression { $$ = $1; }
	| logical_and_expression AND_OP inclusive_or_expression {$$ = new LogicalAnd(NodePtr($1),NodePtr($3));}
	;

logical_or_expression
	: logical_and_expression { $$ = $1; }
	| logical_or_expression OR_OP logical_and_expression {$$ = new LogicalOr(NodePtr($1),NodePtr($3));}
	;

conditional_expression
	: logical_or_expression { $$ = $1; }
	| logical_or_expression '?' expression ':' conditional_expression {$$ = new Ternary(NodePtr($1),NodePtr($3),NodePtr($5));}

	;

assignment_expression
    : conditional_expression
        { $$ = $1; }
    | unary_expression assignment_operator assignment_expression {

        $$ = new ast::Assignment(NodePtr($1), *$2, NodePtr($3));
        delete $2;
    }
    ;

assignment_operator
	: '=' {$$ = new std::string("=");}
	| MUL_ASSIGN
	| DIV_ASSIGN
	| MOD_ASSIGN
	| ADD_ASSIGN {$$ = new std::string("+="); }
	| SUB_ASSIGN
	| LEFT_ASSIGN
	| RIGHT_ASSIGN
	| AND_ASSIGN
	| XOR_ASSIGN
	| OR_ASSIGN
	;


expression
    : assignment_expression
        { $$ = $1; }
    ;


constant_expression
	: conditional_expression { $$ = $1;}
	;




%%

void yyerror (const char *s)
{
  std::cerr << "Error: " << s << " at line " << yylineno;
  std::cerr << " near '" << yytext << "'" << std::endl;
  std::exit(1);
}

Node* g_root;

NodePtr ParseAST(std::string file_name)
{
    yyin = fopen(file_name.c_str(), "r");
    if (yyin == NULL) {
        std::cerr << "Couldn't open input file: " << file_name << std::endl;
        exit(1);
    }
    g_root = nullptr;
    yyparse();
    fclose(yyin);
    yylex_destroy();
    return NodePtr(g_root);
}
