#include "./Parser.h"
#include <iostream>
#include <sstream>
#include "./generate.h"
#include <string>

#include <memory>
#include <stdexcept>
#include <fstream>
template<typename ... Args>
std::string string_format( const std::string& format, Args ... args )
{
    /*
    Reference: https://stackoverflow.com/a/26221725/20856310
    */
    int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
    if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
    auto size = static_cast<size_t>( size_s );
    std::unique_ptr<char[]> buf( new char[ size ] );
    std::snprintf( buf.get(), size, format.c_str(), args ... );
    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}

void GENERATE::generate()
{
    PARSER::Parser parser;
    const char *empty = "";
    
    std::stringstream ss;
    std::vector<const char*> emits;

    auto len = sizeof(parser.productions)/sizeof(parser.productions[0]);
    std::cout << len << std::endl;

    for (int i = 0; i < len; i++)
    {
        auto emit = parser.productions[i].emit;
        if (emit != empty)
            emits.push_back(emit);
    }
    len = sizeof(parser.symbols) / sizeof(parser.symbols[0]);
    for (int i = 0; i < len; i++)
    {
        auto emit = parser.symbols[i].emit;
        if (emit != empty)
            emits.push_back(emit);
    }

    std::cout << len << std::endl;

    std::cout << "valid count: " << emits.size() << std::endl;
    ss << "/*prototypes*/" << std::endl;
    for (auto it = emits.begin(); it != emits.end(); it++)
    {
        auto emit = *it;
        ss << "\textern void* " << emit << "(Args &args);" << std::endl;
    }
    ss << std::endl << std::endl;

    
    ss << "/*definitions*/" << std::endl;
    for (auto it = emits.begin(); it != emits.end(); it++)
    {
        auto emit = *it;
        ss << "void* NARSESEPARSER::"<< emit << "(Args& args)\n{\n\t" << "void* ret;\n\treturn ret;\n}" << std::endl;
    }
    ss << std::endl << std::endl;

    ss << "/*register*/" << std::endl;
    int max_len = 0;
    for (auto it = emits.begin(); it != emits.end(); it++)
    {
        auto emit = *it;
        auto len = strlen(emit);
        if (len > max_len)
            max_len = len;
    }
    auto format = string_format("\tregist(%%%ds, %%%ds );", max_len+3, max_len+1);
    for (auto it = emits.begin(); it != emits.end(); it++)
    {
        auto emit = *it;
        std::string name(emit);
        // if (name == "int" || name == "string")
        auto name2 = std::string("\"") + emit + std::string("\"");
        ss << string_format(format, name2.c_str(), name.c_str()) << std::endl;
    }
    ss << std::endl << std::endl;
    // auto content = ss.str();
    std::ofstream file("generate.out");
    file << ss.str();
    file.close();
}