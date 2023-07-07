#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

#include "Narsese/include/Compound.h"
#include "Narsese/include/Interval.h"
#include "Narsese/include/Statement.h"
#include "Narsese/include/Task.h"
#include "Narsese/include/Tense.h"
#include "Narsese/include/Variable.h"

#include <iomanip>
#include <map>
#include <sstream>
#include <string>

namespace INTERPRETER
{
    using std::map;
    using std::string;
    using TASK::Task;
    using TERM::pTerm;
    using TERM::Term;
    using TERM::TermType;

    class Interpreter
    {
    public:
        map<size_t, string> dictionary;
        map<size_t, pTerm *> objects;
        map<string, size_t> dictionary_inv;
        map<size_t, int> count;

        inline void put(int key, string name, void *object)
        {
            dictionary[key] = name;
            objects[key] = (pTerm *)object;
            dictionary_inv[name] = key;
            count[key] = (check_count(key) == 0) ? 1 : (count[key] + 1);
        }

        inline string &get(int key) { return dictionary[key]; }
        inline pTerm *get_object(int key) { return objects[key]; }
        inline int get_by_name(string &name) { return dictionary_inv[name]; }
        inline bool check(int key) { return dictionary.count(key) == 1; }
        inline bool check_by_name(string &name) { return dictionary_inv.count(name) == 1; }
        inline int check_count(int key)
        {
            if (count.count(key) == 0)
            {
                return 0;
            }
            else
            {
                auto cnt = count[key];
                if (cnt == 0)
                {
                    count.erase(key);
                }
                return cnt;
            }
        }

        inline bool remove(int key)
        {
            if (check(key))
            {
                auto name = get(key);
                dictionary.erase(key);
                objects.erase(key);
                count.erase(key);
                if (check_by_name(name))
                {
                    dictionary_inv.erase(name);
                }
                return true;
            }
            else
            {
                return false;
            }
        }
        inline bool remove_by_name(string name)
        {
            if (check_by_name(name))
            {
                auto key = get_by_name(name);
                dictionary_inv.erase(name);
                if (check(key))
                {
                    dictionary.erase(key);
                    objects.erase(key);
                    count.erase(key);
                }

                return true;
            }
            else
            {
                return false;
            }
        }

        inline bool erase(int key)
        {
            if (check_count(key) > 0)
            {
                count[key]--;
                if (count[key] == 0)
                {
                    remove(key);
                }
                return true;
            }
            else
            {
                return false;
            }
        }

        string interpret(Term &term, bool colored = false);

        string interpret(Task &task, bool colored = false);

        // inline void colored(bool set = true)
        // {
        //     this->_is_colored = set;
        // }

        // private:
        //     bool _is_colored = true;
    };

    extern Interpreter interpreter;
}

#endif // _INTERPRETER_H_