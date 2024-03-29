#include "./Parser.h"
#include <iostream>

using namespace PARSER;

Parser::Parser()
{
    this->eof = '\n';
    this->stacksize = 0;
    this->buf = NULL;
    // const char *empty = "";
    // const char* start = "start";
    // auto len = sizeof(this->productions)/sizeof(this->productions[0]);
    // std::cout << len << std::endl;
    // int valid_cnt = 0;
    // for (int i = 0; i < len; i++)
    // {
    //     auto emit = this->productions[i].emit;
    //     if (emit != empty)
    //     {
    //         std::cout << i << ": " << emit << std::endl;
    //         valid_cnt++;
    //     }
    // }
    // std::cout << "valid count: " << valid_cnt << std::endl;
}

void *Parser::parse_string(std::string &input)
{
    char_fetcher.switch_string_mode();
    char_fetcher.fill(input);

    this->parse();

    char_fetcher.clear();
    /* Print AST */
    if (this->ast)
    {
        // this->ast_print( stderr, this->ast );
        Args *rets = this->transform(this->ast);
        this->ast = this->ast_free(this->ast);
        auto ret = (*rets)[0];
        delete rets;
        return ret;
    }
    return nullptr;
}

void *Parser::parse_input()
{
    char_fetcher.switch_stdin_mode();
    this->parse();
    /* Print AST */
    if (this->ast)
    {
        // this->ast_print( stderr, this->ast );
        Args *rets = this->transform(this->ast);
        this->ast = this->ast_free(this->ast);
        auto ret = (*rets)[0];
        delete rets;
        return ret;
    }
    return nullptr;
}

Args *Parser::transform(_ast *node)
{
    int i;
    char *name;
    void *ret = nullptr;

    if (!node)
        return nullptr;

    auto &rets = *(new Args);

    while (node)
    {
        ret = nullptr;
        name = (char *)(node->emit);

        if (node->token) // leaf-node
        {
            auto fptr = this->get_function(name);
            if (fptr != 0)
            {
                auto token = Args(1);
                token[0] = (void *)node->token;
                ret = ((METHOD)fptr)(this, token);
            }
        }
        else
        {
            auto ret_args = this->transform(node->child);
            auto fptr = this->get_function(name);
            if (fptr != 0)
            {
                ret = ((METHOD)fptr)(this, *ret_args);
            }
            if (ret_args != nullptr)
            {
                delete ret_args;
            }
        }
        rets.push_back(ret);

        node = node->next;
    }
    return &rets;
}

void Parser::regist(const char *name, METHOD function)
{
    _map[name] = (long)function;
}