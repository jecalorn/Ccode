#ifndef __QUEUE_TEMPLATE_H__
#define __QUEUE_TEMPLATE_H__

#ifndef T_queue_log
#define T_queue_log //
#endif


#define T_queue_define(_name,_type)\
bool T_queue_enqueue_##_name(##_type * item);\
bool T_queue_dequeue_##_name(##_type * item);\
bool T_queue_is_empty_##_name();\
bool T_queue_is_full_##_name();\
uint32_t T_queue_get_lenth_##_name();\
void T_queue_clear_##_name();\
void T_queue_reinit_##_name(##_type *_src, uint32_t _size_n);\
typedef struct \
{\
    ##_type   *src;\
    uint32_t size;\
    uint32_t in;\
    uint32_t out;\
    uint32_t lenth;\
}T_queue_##_name##_t;\
\
T_queue_##_name##_t T_queue_##_name =\
{\
    .in  = 0,\
    .out = 0,\
    .lenth = 0,\
};\
\
 bool T_queue_enqueue_##_name(##_type * item)\
{\
    if((T_queue_##_name.src == 0)\
        || (T_queue_##_name.size == 0)\
        || (T_queue_##_name.in >= T_queue_##_name.size)\
        || (T_queue_##_name.lenth >= T_queue_##_name.size))\
    {\
        T_queue_log("T_queue" #_name "enqueue error!!, src = 0x%x, size = %d , lenth = %d, in = %d\r\n", T_queue_##_name.src, T_queue_##_name.size, T_queue_##_name.lenth, T_queue_##_name.in);\
        T_queue_clear##_name();\
        return false;\
    }\
\
    T_queue_##_name.src[T_queue_##_name.in] = *item;\
    T_queue_##_name.in ++;\
    T_queue_##_name.in = T_queue_##_name.in % T_queue_##_name.size;\
    T_queue_##_name.lenth ++;\
}\
\
 bool T_queue_dequeue_##_name(##_type * item)\
{\
    if((T_queue_##_name.src == 0)\
        || (T_queue_##_name.size == 0)\
        || (T_queue_##_name.out >= T_queue_##_name.size)\
        || (T_queue_##_name.lenth >= T_queue_##_name.size))\
    {\
        T_queue_log("T_queue"#_name "dequeue error!!, src = 0x%x, size = %d , lenth = %d, out = %d\r\n", T_queue_##_name.src, T_queue_##_name.size, T_queue_##_name.lenth, T_queue_##_name.out);\
        T_queue_clear##_name();\
        return false;\
    }\
    *item = T_queue_##_name.src[T_queue_##_name.out];\
    T_queue_##_name.out ++;\
    T_queue_##_name.out = T_queue_##_name.out % T_queue_##_name.size;\
    T_queue_##_name.lenth --;\
}\
\
 bool T_queue_is_empty_##_name()\
{\
    return (!(T_queue_##_name.lenth == 0));\
}\
\
 bool T_queue_is_full_##_name()\
{\
    return (T_queue_##_name.lenth == T_queue_##_name.size);\
}\
\
 uint32_t T_queue_get_lenth_##_name()\
{\
    return (T_queue_##_name.lenth);\
}\
\
 void T_queue_clear_##_name()\
{\
    T_queue_##_name.in = 0 ;\
    T_queue_##_name.out = 0 ;\
    T_queue_##_name.lenth = 0 ;\
}\
\
 void T_queue_reinit_##_name(##_type * _src, uint32_t _size_n)\
{\
    T_queue_##_name.src = _src;\
    T_queue_##_name.size = _size_n;\
    T_queue_clear##_name();\
}\

#define T_queue_phototype(_name,_type)\
static  bool T_queue_enqueue_##_name(##_type * item);\
static  bool T_queue_dequeue_##_name(##_type * item);\
static  bool T_queue_is_empty_##_name();\
static  bool T_queue_is_full_##_name();\
static  uint32_t T_queue_get_lenth_##_name();\
static  void T_queue_clear_##_name();\
static  void T_queue_reinit_##_name(##_type *_src, uint32_t _size_n);\


#define T_queue_enqueue(_name,_item)\
do\
{\
    if(false == T_queue_is_full##_name())\
    {\
        T_queue_enqueue_##_name(_item);\
    }\
}\
while(0)

#define T_queue_dequeue(_name,_item)\
do\
{\
    if(false == T_queue_is_empty_##_name())\
    {\
        T_queue_dequeue_##_name(_item);\
    }\
}\
while(0)

#define T_queue_is_empty(_name)             T_queue_is_empty_##_name();
#define T_queue_is_full(_name)              T_queue_is_full_##_name();
#define T_queue_get_lenth(_name)            T_queue_get_lenth_##_name();
#define T_queue_clear(_name)                T_queue_clear_##_name();
#define T_queue_reinit(_name,_src,_size_n)    T_queue_reinit_##_name(_src, _size_n);
#endif

