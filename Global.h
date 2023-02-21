#ifndef _GLOBAL_H
#define _GLOBAL_H

extern unsigned long time;
extern unsigned long _input_id;

inline unsigned long get_input_id()
{
    auto input_id = _input_id;
    _input_id += 1;
    return input_id;
}



#endif // _GLOBAL_H