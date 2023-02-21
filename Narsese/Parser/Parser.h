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
#include <unordered_map>
#include <vector>
#include "./narsese.h"
// #include "./Transformer.h"

namespace PARSER
{
    typedef std::vector<void *> Args;
    typedef void *(*METHOD)(std::vector<void *> &);

    class Parser : public _parser
    {
    public:
        // TRANSFORMER::Transformer transformer;
        std::unordered_map<const char*, long> map;

        Parser();


        Args *transform(_ast *node);    

        void* parse_string(std::string &input);
        void* parse_input();
        void regist(const char *name, METHOD function);


        inline long get_function(const char* name)
        {
            auto it = map.find(name);

            if(it != map.end() )
                return it->second;
            return 0;
        }
    };

    
    
}

#endif // _PARSER_H_