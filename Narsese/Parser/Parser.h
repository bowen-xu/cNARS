#ifndef _PARSER_H_
#define _PARSER_H_

#include <iomanip>
#include <string>
// #include "Narsese/include/Term.h"
// #include "Narsese/include/Copula.h"
// #include "Narsese/include/Statement.h"
// #include "Narsese/include/Truth.h"
// #include "Narsese/include/Sentence.h"
// #include "Narsese/include/Task.h"
#include "./narsese.h"
#include "Narsese/include/Task.h"
#include <unordered_map>
#include <vector>
// #include "./Transformer.h"

namespace PARSER
{
    class Parser;
    typedef std::vector<void *> Args;
    typedef void *(*METHOD)(Parser *self, const std::vector<void *> &);

    class Parser : public _parser
    {
    public:
        /* function mappings from name to pointer */
        std::unordered_map<const char *, long> _map;

        /* variable mappings from name to index */
        std::unordered_map<std::string, long> names_ivar;
        std::unordered_map<std::string, long> names_dvar;
        std::unordered_map<std::string, long> names_qvar;

        Parser();
        ~Parser()
        {
            /*
            Note:
            To avoid memory leaks, the resouce should be free.
            This is a bug of UNICC parser, so we have to do it at here.
            */
            if (this->buf != NULL)
            {
                // std::cout << this->stacksize << std::endl;
                // if (this->buf != this->bufend)
                // {
                // std::cout<< "stacksize=" << this->stacksize << std::endl;
                free(this->buf);
                // std::cout<< "free" << std::endl;
                //     std::cout << "free 1" << std::endl;
                // }
                // else
                // {
                //     free(this->buf);
                //     std::cout << "free 2" << std::endl;
                // }
                this->buf = NULL;
                this->bufend = this->buf;
            }
        }

        Args *transform(_ast *node);

        void *parse_string(std::string &input);
        void *parse_input();
        void regist(const char *name, METHOD function);

        inline long get_function(const char *name)
        {
            auto it = _map.find(name);

            if (it != _map.end())
                return it->second;
            return 0;
        }
    };

}

#endif // _PARSER_H_