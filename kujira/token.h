#ifndef TOKEN_H
#define TOKEN_H

// Type of token.
typedef enum _tokentype_t {
	// One char tokens:
	T_PLUS,       // "+"
	T_MINUS,      // "-"
	T_STAR,       // "*"
	T_SLASH,      // "/"
	T_LPAR,       // "("
	T_RPAR,       // ")"
	T_SEMICOLON,  // ";"
	T_EQUALS,     // "="
	T_PERCENT,    // "%"

	// Complex, generic tokens:
	T_NUMBER,
	T_IDENTIFIER,

	// Keywords:
	T_PRINT,
	T_LET,

	T_EOF,    // End of file.
	T_ERROR,  // Error token.
} TokenType_t;

// Defines token. Includes token type, line number, and heap allocated lexeme.
// TODO: replace with string struct (length + chars).
typedef struct _token_t {
	TokenType_t type;
	int line;
	char* lexeme;
} Token_t;

// Token_t Token_MakeToken(TokenType_t type, int line, char* lexeme);

#endif  // TOKEN_H