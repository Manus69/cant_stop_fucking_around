#ifndef MACRO_H
#define MACRO_H

#define next_pow2_(n)   (1ul << (sizeof(unsigned long) * __CHAR_BIT__ - __builtin_clzl((n) | 1)))
#define deref_(type)    * (type *)
#define to0_(ptr, type) deref_(type) ptr = (type){}     
#define likely_(x)      __builtin_expect((x), 1)
#define unlikely_(x)    __builtin_expect((x), 0)
#define min_(x, y)       ({typeof(x) _x = x; typeof(y) _y = y; _x < _y ? _x : _y;})

#endif