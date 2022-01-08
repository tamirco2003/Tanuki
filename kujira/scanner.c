#include "scanner.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"

#define BUFFER_SIZE 1024

Scanner_t Scanner_Init() {
	Scanner_t scanner;
	scanner.file = NULL;

	scanner.buffer = (char*)malloc(sizeof(char) * BUFFER_SIZE);
	scanner.length = 0;

	scanner.line = 1;

	scanner.keywordFlag = 1;

	return scanner;
}

int Scanner_FileOpen(Scanner_t* scanner, const char* filepath) {
	scanner->file = fopen(filepath, "r");
	if (scanner->file == NULL) {
		return 0;
	}

	scanner->current = fgetc(scanner->file);
	scanner->next = fgetc(scanner->file);

	return 1;
}

void Scanner_Advance(Scanner_t* scanner) {
	scanner->current = scanner->next;
	scanner->next = fgetc(scanner->file);
}

void Scanner_AppendAdvance(Scanner_t* scanner) {
	scanner->buffer[scanner->length++] = scanner->current;
	scanner->current = scanner->next;
	scanner->next = fgetc(scanner->file);
}

char* Scanner_GetLexeme(Scanner_t* scanner) {
	// Append current.
	scanner->buffer[scanner->length++] = scanner->current;

	// Advance scanner.
	scanner->current = scanner->next;
	scanner->next = fgetc(scanner->file);

	// Get lexeme.
	char* lexeme = (char*)malloc(sizeof(char) * scanner->length);
	memccpy(lexeme, scanner->buffer, scanner->length, scanner->length);
	scanner->length = 0;
	scanner->keywordFlag = 1;

	return lexeme;
}

Token_t Scanner_MakeToken(Scanner_t* scanner, TokenType_t type) {
	Token_t token;
	token.type = type;
	token.line = scanner->line;
	token.lexeme = Scanner_GetLexeme(scanner);
	
	return token;
}

Token_t Scanner_NextToken(Scanner_t* scanner) {
	// Skip whitespace (could improve?).
	char whitespace = 1;
	while (whitespace) {
		switch (scanner->current) {
			case '\n':
				scanner->line++;
			case ' ':
			case '\t':
			case '\r':
				Scanner_Advance(scanner);
				break;
			default:
				whitespace = 0;
		}
	}

	switch (scanner->current) {
		case '+':
			return Scanner_MakeToken(scanner, T_PLUS);
		case '-':
			return Scanner_MakeToken(scanner, T_MINUS);
		case '*':
			return Scanner_MakeToken(scanner, T_STAR);
		case '/':
			return Scanner_MakeToken(scanner, T_SLASH);
		case '(':
			return Scanner_MakeToken(scanner, T_LPAR);
		case ')':
			return Scanner_MakeToken(scanner, T_RPAR);
		case ';':
			return Scanner_MakeToken(scanner, T_SEMICOLON);
		case '=':
			return Scanner_MakeToken(scanner, T_EQUALS);
		case '%':
			return Scanner_MakeToken(scanner, T_PERCENT);

		case '0' ... '9':
			return Scanner_Number(scanner);

		case '_':
		case 'A' ... 'Z':
			scanner->keywordFlag = 0;
		case 'a' ... 'z':
			return Scanner_Keyword(scanner);

		case EOF:
			return Scanner_MakeToken(scanner, T_EOF);

		default:
			return Scanner_MakeToken(scanner, T_ERROR);
	}
}

Token_t Scanner_Number(Scanner_t* scanner) {
	while ('0' <= scanner->next && scanner->next <= '9') {
		Scanner_AppendAdvance(scanner);
	}
	
	return Scanner_MakeToken(scanner, T_NUMBER);
}

Token_t Scanner_Keyword(Scanner_t* scanner) {
	if (scanner->keywordFlag) {
		while ('a' <= scanner->next && scanner->next <= 'z') {
			Scanner_AppendAdvance(scanner);
		}
	}

	while (('A' <= scanner->next && scanner->next <= 'Z') ||
	       ('0' <= scanner->next && scanner->next <= '9') ||
	       ('a' <= scanner->next && scanner->next <= 'z') ||
	       scanner->next == '_') {
		scanner->keywordFlag = 0;
		Scanner_AppendAdvance(scanner);
	}

	if (scanner->keywordFlag) {
		if (strncmp(scanner->buffer, "print", scanner->length) == 0) {
			return Scanner_MakeToken(scanner, T_PRINT);
		}

		if (strncmp(scanner->buffer, "let", scanner->length) == 0) {
			return Scanner_MakeToken(scanner, T_LET);
		}
	}

	return Scanner_MakeToken(scanner, T_IDENTIFIER);
}