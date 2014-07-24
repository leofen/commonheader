#include "list.h"

/*
 *  Usage:
 *  in .h file:
 *      define a struct include an hlist_node element,
 *      HASH_EXTERN
 *  in .c file:
 *      define an hlist_head array,
 *      implement two (static for recommend) function: structname##_hash_func and structname##_hash_cmp,
 *      use HASH_IMPL
 */

#define HASH_EXTERN(stname, keytype, keyname, tablename) \
void tablename##_init(); \
struct stname* get_##stname(keytype keyname); \
void insert_##stname(struct stname* symb); 

#define HASH_IMPL(stname, hnodename, keytype, keyname, tablename, tablesize) \
void tablename##_init() { \
    int i; \
    for (i = 0 ; i < tablesize; i++) {\
        INIT_HLIST_HEAD(&tablename[i]); \
    } \
} \
struct stname* get_##stname(keytype keyname) { \
    int index = stname##_hash_func(keyname); \
    struct stname *item; \
    hlist_node *p; \
    hlist_for_each_entry(item, p, (hlist_head *)&tablename[index], hnodename){ \
        if(stname##_hash_cmp(item->keyname, keyname) == 0) {\
            return item; \
        } \
    } \
    return NULL;\
} \
void insert_##stname(struct stname* symb) { \
    int index = stname##_hash_func(symb->keyname); \
    INIT_HLIST_NODE(&symb->hnodename); \
    hlist_add_head(&symb->hnodename, &tablename[index]); \
}
