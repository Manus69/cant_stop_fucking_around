#ifndef DEF_H
#define DEF_H

#define NO_IDX (-1L)

typedef char    byte;
typedef long    idx;
typedef void    (* F)(void *);
typedef void    (* cF)(const void *);
typedef idx     (* Cmp)(const void *, const void *);
typedef void    (* Put)(void *, const void *);

#endif