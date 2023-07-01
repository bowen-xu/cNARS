#ifndef _GLOBAL_H
#define _GLOBAL_H

namespace GLOBAL
{
    static unsigned long time = 0;
    static unsigned long _input_id = 0;

    inline unsigned long get_input_id()
    {
        auto input_id = _input_id;
        _input_id += 1;
        return input_id;
    }

} // namespace GLOBAL

#endif // _GLOBAL_H