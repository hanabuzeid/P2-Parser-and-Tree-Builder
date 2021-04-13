#include "parser.h"
#include "scanner.h"
#include <iostream>

std::ifstream in_file;
unsigned int lineNum = 1;
Token token;

std::string tokes[] = {"BEGIN_TK", "END_TK", "LOOP_TK", "WHILE_TK","VOID_TK", "EXIT_TK", "GETTER_TK", "OUTTER_TK", "MAIN_TK", "IF_TK","THEN_TK", "ASSIGN_TK", "DATA_TK", "PROC_TK", "EQUALS_TK", "EQUALS_OR_LESS_THAN_TK",
"EQUALS_OR_GREAT_THAN_TK", "EQUALS_EQUALS_TK", "COLON_TK", "COLON_EQUALS_TK", "PLUS_TK",
"MINUS_TK", "ASTERISK_TK", "SLASH_TK", "PERCENT_TK", "PERIOD_TK", "LEFT_PAREN_TK", "RIGHT_PAREN_TK",
"COMMA_TK", "LEFT_BRACE_TK", "RIGHT_BRACE_TK", "SEMI_COLON_TK", "LEFT_BRACKET_TK", "RIGHT_BRACKET_TK",
"ID_TK", "INT_TK", "EOF_TK", "ERROR_TK"};


Node *parser()
{

    Node *node;
    token = scanner(in_file, lineNum);

    
    node = program();
    if (token.token_ID == EOF_TK)
    {
        std::cout << "Parsing completed!" << std::endl;
        return node;
    }
    else
        error(EOF_TK, token);
}

Node *program()
{
    int depth = 0;

    Node *node = new Node("<program>", depth);

    node->child_1 = vars(depth);   
    if (token.token_ID == MAIN_TK) 
    {
        node->token_1 = token;         
        token = scanner(in_file, lineNum); 
        node->child_2 = block(depth);
    }
    else
        error(MAIN_TK, token);
    return node;
}

Node *block(unsigned int depth)
{
    depth++;
    Node *node = new Node("<block>", depth);

    if (token.token_ID == BEGIN_TK)
    {
        node->token_1 = token;
        token = scanner(in_file, lineNum);
        node->child_1 = vars(depth);
        node->child_2 = stats(depth);

        if (token.token_ID == END_TK)
        {
            node->token_2 = token;
            token = scanner(in_file, lineNum);

            return node;
        }
        else
            error(END_TK, token);
    }
    else
        error(BEGIN_TK, token);
}

Node *vars(unsigned int depth)
{
    depth++;
    
    Node *node = new Node("<vars>", depth);

    if (token.token_ID == DATA_TK)
    {
        node->token_1 = token;
        token = scanner(in_file, lineNum);
        if (token.token_ID == ID_TK)
        {
            node->token_2 = token;
            token = scanner(in_file, lineNum);

            if (token.token_ID == COLON_EQUALS_TK)
            {
                node->token_3 = token;
                token = scanner(in_file, lineNum);

                if (token.token_ID == INT_TK)
                {
                    node->token_4 = token;
                    token = scanner(in_file, lineNum);

                    if (token.token_ID == SEMI_COLON_TK)
                    {
                        node->token_5 = token;
                        token = scanner(in_file, lineNum);

                        node->child_1 = vars(depth);
                        return node;
                    }
                    else
                    {
                        error(SEMI_COLON_TK, token);
                    }
                }
                else
                    error(INT_TK, token);
            }
            else
                error(COLON_EQUALS_TK, token);
        }
        else
            error(ID_TK, token);
    }
    
    else
        return NULL;
}

Node *expr(unsigned int depth)
{

    depth++;
    Node *node = new Node("<expr>", depth);

    node->child_1 = n(depth);
    
    if (token.token_ID == MINUS_TK)
    {
        node->token_1 = token;
        token = scanner(in_file, lineNum);

        node->child_2 = expr(depth);
        return node;
    }
    else
        return node;
}

Node *n(unsigned int depth)
{

    depth++;
    Node *node = new Node("<N>", depth);
    node->child_1 = a(depth);
    
    if (token.token_ID == SLASH_TK)
    {
        node->token_1 = token;
        token = scanner(in_file, lineNum);
        node->child_2 = n(depth);
        return node;
    }
    else if (token.token_ID == ASTERISK_TK)
    {
        node->token_1 = token;
        token = scanner(in_file, lineNum);
        node->child_2 = n(depth);
        return node;
    }
    else
        return node;
}

Node *a(unsigned int depth)
{
    depth++;
    Node *node = new Node("<A>", depth);
    node->child_1 = m(depth);
    if (token.token_ID == PLUS_TK)
    {
        
        node->token_1 = token;
        token = scanner(in_file, lineNum);
        node->child_2 = a(depth);
    }
    return node;
}

Node *m(unsigned int depth)
{

    depth++;
    Node *node = new Node("<M>", depth);
    if (token.token_ID == ASTERISK_TK)
    {
    
        node->token_1 = token;
        token = scanner(in_file, lineNum);
        node->child_1 = m(depth);
        return node;
    }
    else
    {
        node->child_1 = r(depth);
        return node;
    }
}

Node *r(unsigned int depth)
{

    depth++;
    Node *node = new Node("<R>", depth);
    if (token.token_ID == LEFT_PAREN_TK)
    {
        node->token_1 = token;
        token = scanner(in_file, lineNum);

        node->child_1 = expr(depth);

        if (token.token_ID == RIGHT_PAREN_TK)
        {
            node->token_2 = token;

            token = scanner(in_file, lineNum);

            return node;
        }
        else
            error(RIGHT_PAREN_TK, token);
    }
    else if (token.token_ID == ID_TK)
    {
        node->token_1 = token;
        token = scanner(in_file, lineNum);

        return node;
    }
    else if (token.token_ID == INT_TK)
    {
        node->token_1 = token;
        token = scanner(in_file, lineNum);

        return node;
    }
    else
        error(LEFT_PAREN_TK, ID_TK, INT_TK, token);
}

Node *stats(unsigned int depth)
{

    depth++;
    Node *node = new Node("<stats>", depth);
    node->child_1 = stat(depth);
    node->child_2 = mstat(depth);
    return node;
}

Node *mstat(unsigned int depth)
{

    depth++;
    Node *node = new Node("<mstat>", depth);

    if (token.token_ID == GETTER_TK ||
        token.token_ID == OUTTER_TK || token.token_ID == BEGIN_TK ||
        token.token_ID == IF_TK || token.token_ID == LOOP_TK || token.token_ID == PROC_TK ||
        token.token_ID == ASSIGN_TK || token.token_ID == VOID_TK)
    {

        node->child_1 = stat(depth);
        node->child_2 = mstat(depth);
        return node;
    }
    else
        return node;
}

Node *stat(unsigned int depth)
{

    depth++;
    Node *node = new Node("<stat>", depth);

    if (token.token_ID == GETTER_TK)
    {
        node->child_1 = in(depth);
        if (token.token_ID == SEMI_COLON_TK)
        {
            node->token_1 = token;
            token = scanner(in_file, lineNum);

            return node;
        }
        else
            error(SEMI_COLON_TK, token);
    }
    else if (token.token_ID == OUTTER_TK)
    {

        node->child_1 = out(depth);
        if (token.token_ID == SEMI_COLON_TK)
        {
            node->token_1 = token;
            token = scanner(in_file, lineNum);

            return node;
        }
        else
            error(SEMI_COLON_TK, token);
    }
    else if (token.token_ID == BEGIN_TK)
    {
        node->child_1 = block(depth);
        return node;
    }
    else if (token.token_ID == IF_TK)
    {
        node->child_1 = iff(depth);
        if (token.token_ID == SEMI_COLON_TK)
        {
            node->token_1 = token;
            token = scanner(in_file, lineNum);

            return node;
        }
        else
            error(SEMI_COLON_TK, token);
    }
    else if (token.token_ID == LOOP_TK)
    {
        node->child_1 = loop(depth);
        if (token.token_ID == SEMI_COLON_TK)
        {
            node->token_1 = token;
            token = scanner(in_file, lineNum);

            return node;
        }
        else
            error(SEMI_COLON_TK, token);
    }
    else if (token.token_ID == ASSIGN_TK)
    {
        node->child_1 = assign(depth);
        if (token.token_ID == SEMI_COLON_TK)
        {
            node->token_1 = token;
            token = scanner(in_file, lineNum);

            return node;
        }
        else
            error(SEMI_COLON_TK, token);
    }
    else if (token.token_ID == PROC_TK)
    {
        node->child_1 = gotoo(depth);
        if (token.token_ID == SEMI_COLON_TK)
        {
            node->token_1 = token;
            token = scanner(in_file, lineNum);

            return node;
        }
        else
            error(SEMI_COLON_TK, token);
    }

    else
        error_stat(token);
}

Node *in(unsigned int depth)
{

    depth++;
    Node *node = new Node("<in>", depth);
    if (token.token_ID == GETTER_TK)
    {
        token = scanner(in_file, lineNum);

        if (token.token_ID == ID_TK)
        {
            node->token_1 = token;
            token = scanner(in_file, lineNum);
            return node;
        }
        else
            error(ID_TK, token);
    }
    else
        error(GETTER_TK, token);
}

Node *out(unsigned int depth)
{

    depth++;
    Node *node = new Node("<out>", depth);
    if (token.token_ID == OUTTER_TK)
    {

        token = scanner(in_file, lineNum);

        node->child_1 = expr(depth);
        return node;
    }
    else
        error(OUTTER_TK, token);
}

Node *iff(unsigned int depth)
{

    depth++;
    Node *node = new Node("<if>", depth);
    if (token.token_ID == IF_TK)
    {
        node->token_1 = token;
        token = scanner(in_file, lineNum);
        if (token.token_ID == LEFT_BRACKET_TK)
        {
            node->token_2 = token;
            token = scanner(in_file, lineNum);

            node->child_1 = expr(depth);
            node->child_2 = is_ro(depth);
            node->child_3 = expr(depth);
            if (token.token_ID == RIGHT_BRACKET_TK)
            {
                node->token_3 = token;
                if (token.token_ID == THEN_TK)
                {
                    node->token_4 = token;
                    token = scanner(in_file, lineNum);

                    node->child_4 = stat(depth);
                    return node;
                }
                else
                    error(THEN_TK, token);
            }
            else
                error(RIGHT_BRACKET_TK, token);
        }
        else
            error(LEFT_BRACKET_TK, token);
    }
    else
        error(LOOP_TK, token);
}

Node *loop(unsigned int depth)
{

    depth++;
    Node *node = new Node("<loop>", depth);
    if (token.token_ID == LOOP_TK)
    {
        node->token_1 = token;
        token = scanner(in_file, lineNum);

        if (token.token_ID == LEFT_BRACKET_TK)
        {
            node->token_2 = token;
            token = scanner(in_file, lineNum);

            node->child_1 = expr(depth);
            node->child_2 = is_ro(depth);
            node->child_3 = expr(depth);
            if (token.token_ID == RIGHT_BRACKET_TK)
            {
                node->token_3 = token;
                token = scanner(in_file, lineNum);
                node->child_4 = stat(depth);
                return node;
            }
            else
                error(RIGHT_BRACKET_TK, token);
        }
        else
            error(LEFT_BRACKET_TK, token);
    }
    else
        error(LOOP_TK, token);
}

Node *assign(unsigned int depth)
{

    depth++;
    Node *node = new Node("<assign>", depth);
    
    if (token.token_ID == ASSIGN_TK)
    {
        token = scanner(in_file, lineNum);

        if (token.token_ID == ID_TK)
        {
            node->token_1 = token;
            token = scanner(in_file, lineNum);

            if (token.token_ID == COLON_EQUALS_TK)
            {
                token = scanner(in_file, lineNum);

                node->child_1 = expr(depth);
                return node;
            }
            else
                error(COLON_EQUALS_TK, token);
        }
        else
            error(ID_TK, token);
    }
    else
        error(ASSIGN_TK, token);
}

Node *is_ro(unsigned int depth)
{

    depth++;
    Node *node = new Node("<ro>", depth);

    if (token.token_ID == EQUALS_OR_LESS_THAN_TK)
    {
        node->token_1 = token;
        token = scanner(in_file, lineNum);
        return node;
    }

    else if (token.token_ID == EQUALS_OR_GREAT_THAN_TK)
    {
        node->token_1 = token;
        token = scanner(in_file, lineNum);

        return node;
    }
    else if (token.token_ID == EQUALS_EQUALS_TK)
    {
        node->token_1 = token;
        token = scanner(in_file, lineNum);

        return node;
    }
    else if (token.token_ID == PERCENT_TK)
    {
        node->token_1 = token;
        token = scanner(in_file, lineNum);

        return node;
    }
    else if (token.token_ID == LEFT_BRACKET_TK)
    {
        node->token_1 = token;
        token = scanner(in_file, lineNum);

        if (token.token_ID == EQUALS_EQUALS_TK)
        {
            node->token_2 = token;
            token = scanner(in_file, lineNum);

            if (token.token_ID == RIGHT_BRACKET_TK)
            {
                
                node->token_3 = token;
                token = scanner(in_file, lineNum);

                node->token_4 = token;
                token = scanner(in_file, lineNum);

                node->token_5 = token;
                token = scanner(in_file, lineNum);

                node->token_6 = token;
                return node;
            }
            else
                error(RIGHT_BRACKET_TK, token);
        }
        else
            error(EQUALS_EQUALS_TK, token);
    }

    else
        error_stat(token);
}
Node *label(unsigned int depth)
{

    depth++;
    Node *node = new Node("<label>", depth);
    if (token.token_ID == VOID_TK)
    {
        token = scanner(in_file, lineNum);

        if (token.token_ID == ID_TK)
        {
            node->token_1 = token;
            token = scanner(in_file, lineNum);

            return node;
        }
        else
            error(ID_TK, token);
    }
    else
        error(VOID_TK, token);
}

Node *gotoo(unsigned int depth)
{

    depth++;
    Node *node = new Node("<goto>", depth);
    if (token.token_ID == PROC_TK)
    {
        token = scanner(in_file, lineNum);

        if (token.token_ID == ID_TK)
        {
            node->token_1 = token;
            token = scanner(in_file, lineNum);

            return node;
        }
        else
            error(ID_TK, token);
    }
    else
        error(PROC_TK, token);
}

void error(token_id need, Token got)
{
    std::cout << "--- ERROR ---" << std::endl;
    std::cout << "Needed token: " << tokes[need] << std::endl;
    std::cout << "Got token: " << tokes[got.token_ID];
    std::cout << " LINE NUMBER: " << got.lineNum << std::endl;
    exit(EXIT_FAILURE);
}

void error(token_id need_1, token_id need_2, Token got)
{
    std::cout << "--- ERROR ---" << std::endl;
    std::cout << "Needed token_id: " << tokes[need_1] << " or " << tokes[need_2] << std::endl;
    std::cout << "Got token: " << tokes[got.token_ID];
    std::cout << " LINE NUMBER: " << got.lineNum << std::endl;
    exit(EXIT_FAILURE);
}

void error(token_id need_1, token_id need_2, token_id need_3, Token got)
{
    std::cout << "--- ERROR ---" << std::endl;
    std::cout << "Needed token_id: " << tokes[need_1] << ", " << tokes[need_2];
    std::cout << ", or " << tokes[need_3] << std::endl;
    std::cout << "Got token: " << tokes[got.token_ID];
    std::cout << " LINE NUMBER: " << got.lineNum << std::endl;
    exit(EXIT_FAILURE);
}

void error_stat(Token recieved)
{
    std::cout << "Token did not follow rule: " << tokes[recieved.token_ID];
    std::cout << " LINE NUMBER: " << recieved.lineNum << std::endl;
    exit(EXIT_FAILURE);
}

void printTree(Node *node)
{
    if (node == nullptr)
    {
        std::cout << "EMPTY" << std::endl;
        return;
    }
    else
    {
        std::string indents((node->depth * 2), ' ');
        std::cout << indents;
        std::cout << node->name << "  ";
        std::cout << node->token_1.token_string << " " << node->token_2.token_string
                  << " " << node->token_3.token_string << " " << node->token_4.token_string << " "
                  << node->token_5.token_string << " " << node->token_6.token_string << std::endl;

        if (node->child_1 != nullptr)
            printTree(node->child_1);
        if (node->child_2 != nullptr)
            printTree(node->child_2);
        if (node->child_3 != nullptr)
            printTree(node->child_3);
        if (node->child_4 != nullptr)
            printTree(node->child_4);
    }
    return;
}