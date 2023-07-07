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

        Args *transform(_ast *node);

        TASK::pTask parse_task(std::string &input);
        TASK::pTask parse_task(const char* input) 
        {
            auto str = std::string(input);
            return parse_task(str);
        }
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