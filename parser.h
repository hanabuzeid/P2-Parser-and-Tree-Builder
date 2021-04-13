#ifndef PARSER_H
#define PARSER_H
#include "token.h"
#include "node.h"

extern std::ifstream in_file;

Node *parser();
Node *program();
Node *block(unsigned int);
Node *vars(unsigned int);
Node *expr(unsigned int);
Node *n(unsigned int);
Node *a(unsigned int);
Node *m(unsigned int);
Node *r(unsigned int);
Node *stats(unsigned int);
Node *mstat(unsigned int);
Node *stat(unsigned int);
Node *in(unsigned int);
Node *out(unsigned int);
Node *iff(unsigned int);
Node *loop(unsigned int);
Node *assign(unsigned int);
Node *is_ro(unsigned int);
Node *gotoo(unsigned int);
Node *label(unsigned int);

void error(token_id, Token);
void error(token_id, token_id, Token);
void error(token_id, token_id, token_id, Token);
void error_stat(Token);

void printTree(Node *node);

#endif