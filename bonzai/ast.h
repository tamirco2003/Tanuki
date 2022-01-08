typedef struct _exprnode_t ExprNode_t;
typedef char* Identifier_t;

typedef struct _stmtnode_t {
	struct _stmtnode_t* next;
	enum _stmttype_t {
		S_EXPRESSION,
		S_DECLARATION,
		S_PRINT,
		S_END,
	} type;
} StmtNode_t;

typedef struct _decl_stmtnode_t {
	StmtNode_t base;
	Identifier_t identifier;
	ExprNode_t* expr;
} Decl_StmtNode_t;

typedef struct _expr_stmtnode_t {
	StmtNode_t base;
	ExprNode_t* expr;
} Expr_StmtNode_t;

struct _exprnode_t {
	enum _exprtype_t {
		E_BINARY,
		E_UNARY,
		E_GROUPING,
		E_LITERAL,
		E_ASSIGNMENT,
		E_VARIABLE,
	} type;
};

typedef struct _binary_exprnode_t {
	ExprNode_t base;

	enum _bin_exprtype_t {
		B_ADD,
		B_SUB,
		B_MUL,
		B_DIV,
		B_MOD,
	} type;

	ExprNode_t* left;
	ExprNode_t* right;
} Binary_ExprNode_t;

typedef struct _unary_exprnode_t {
	ExprNode_t base;

	enum _unary_exprtype_t { U_MINUS } type;

	ExprNode_t* operand;
} Unary_ExprNode_t;

typedef struct _group_exprnode_t {
	ExprNode_t base;
	ExprNode_t* expr;
} Group_ExprNode_t;

typedef struct _literal_exprnode_t {
	ExprNode_t base;

	enum _literal_exprtype_t {
		L_UNDEFINED,
		L_NUMBER,
	} type;
} Literal_ExprNode_t;

typedef struct _numberliteral_t {
	Literal_ExprNode_t base;

	int value;
} NumberLiteral_t;

typedef struct _assign_exprnode_t {
	ExprNode_t base;
	Identifier_t identifier;
	ExprNode_t* expression;
} Assign_ExprNode_t;

typedef struct _var_exprnode_t {
	ExprNode_t base;
	Identifier_t identifier;
} Var_ExprNode_t;