#include <stdio.h>
#include <stdlib.h>

#include "kujira/scanner.h"
#include "kujira/token.h"

int main(int argc, char* argv[]) {
	char* filepath = NULL;

	if (argc != 2) {
		printf("Usage: %s FILE\n", argv[0]);
		return 1;
	} else {
		filepath = argv[1];
	}

	Scanner_t scanner = Scanner_Init();
	if (!Scanner_FileOpen(&scanner, filepath)) {
		printf("Failed to open file '%s'.\n", filepath);
	}

	Token_t token;
	do {
		token = Scanner_NextToken(&scanner);
		switch (token.type) {
			case T_EOF:
                printf("EOF\n");
                break;
			case T_ERROR:
                printf("ERROR ");
                break;
            case T_SEMICOLON:
                printf(";\n");
                break;
            case T_PRINT:
            case T_LET:
                printf("$");
			default:
                // Lexemes don't end with a null byte, kinda UB.
				printf("%s ", token.lexeme);
		}
	} while (token.type != T_EOF);
}