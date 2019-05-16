/******************************************************************************
  File Name     : ringbuffer.h
  Version       : Initial Draft
  Author        : belife
  Last Modified :
  Description   : ring buffer head file
  Function List :
  History       :
******************************************************************************/
#ifndef __RINGBUFFER_H__
#define __RINGBUFFER_H__


//#define RINGBUF_LOG LOGDEBUG

#ifndef RINGBUF_LOG
#define RINGBUF_LOG(x, ...)     do{ }while(0)
#endif

#define RINGBUF_DEFINE(_name,_type)\
typedef struct \
{\
    _type   *src;\
    uint32_t size;\
    uint32_t in;\
    uint32_t out;\
    uint32_t lenth;\
}RINGBUF_##_name##_t;\
\
RINGBUF_##_name##_t RINGBUF_##_name =\
{\
    .src = 0,\
    .size = 0,\
    .in  = 0,\
    .out = 0,\
    .lenth = 0,\
}

#define RINGBUF_TYPE_SIZE(_name)    (sizeof(RINGBUF_##_name.src[0]))
#define RINGBUF_EMPTY(_name)        (RINGBUF_##_name.lenth == 0)
#define RINGBUF_FULL(_name)         (RINGBUF_##_name.lenth == RINGBUF_##_name.size)
#define RINGBUF_LENTH(_name)        (RINGBUF_##_name.lenth)
#define RINGBUF_SIZE(_name)         (RINGBUF_##_name.size)


#define RINGBUF_INIT(_name,_src,_size)\
do {\
    RINGBUF_##_name.src = _src;\
    RINGBUF_##_name.size = _size;\
    RINGBUF_##_name.in  = 0;\
    RINGBUF_##_name.out = 0;\
    RINGBUF_##_name.lenth = 0;\
} while (/*CONSTCOND*/0)

#define RINGBUF_PUSH(_name,_item,_num)\
    do{\
        if((RINGBUF_##_name.src == 0)\
            || (RINGBUF_##_name.size == 0)\
            || (RINGBUF_##_name.in >= RINGBUF_##_name.size)\
            || (RINGBUF_##_name.out >= RINGBUF_##_name.size)\
            || ((RINGBUF_##_name.lenth + (_num)) > RINGBUF_##_name.size)\
            || ((_item) == 0)\
            || ((_num) <= 0))\
        {\
            RINGBUF_LOG("RINGBUF_" #_name "_push error!!, src = 0x%x, size = %d , lenth = %d, in = %d,out = %d, _item = 0x%x, _num = %d\r\n", RINGBUF_##_name.src, RINGBUF_##_name.size, RINGBUF_##_name.lenth, RINGBUF_##_name.in, RINGBUF_##_name.out, (_item), (_num));\
        }\
        else\
        {\
            if((_num) <= (RINGBUF_##_name.size - RINGBUF_##_name.in))\
            {\
                memcpy((void *)&RINGBUF_##_name.src[RINGBUF_##_name.in], (void *)(_item), (_num) * RINGBUF_TYPE_SIZE(_name));\
                RINGBUF_##_name.in = RINGBUF_##_name.in + (_num);\
                RINGBUF_##_name.in = RINGBUF_##_name.in % RINGBUF_##_name.size;\
            }\
            else\
            {\
                memcpy((void *)&RINGBUF_##_name.src[RINGBUF_##_name.in], (void *)(_item),((RINGBUF_##_name.size)-(RINGBUF_##_name.in))*RINGBUF_TYPE_SIZE(_name));\
                memcpy((void *)&RINGBUF_##_name.src[0], (void *)((_item)+ ((RINGBUF_##_name.size)-(RINGBUF_##_name.in))*RINGBUF_TYPE_SIZE(_name)),((_num) - ((RINGBUF_##_name.size)-(RINGBUF_##_name.in)))*RINGBUF_TYPE_SIZE(_name));\
                RINGBUF_##_name.in = ((_num) - ((RINGBUF_##_name.size)-(RINGBUF_##_name.in)));\
                RINGBUF_##_name.in = RINGBUF_##_name.in % RINGBUF_##_name.size;\
            }\
            RINGBUF_##_name.lenth = RINGBUF_##_name.lenth + (_num);\
        }\
    } while (/*CONSTCOND*/0)

#define RINGBUF_POP(_name,_item,_num)\
    do{\
        if((RINGBUF_##_name.src == 0)\
            || (RINGBUF_##_name.size == 0)\
            || (RINGBUF_##_name.in >= RINGBUF_##_name.size)\
            || (RINGBUF_##_name.out >= RINGBUF_##_name.size)\
            || (RINGBUF_##_name.lenth < (_num))\
            || ((_item) == 0)\
            || ((_num) <= 0))\
        {\
            RINGBUF_LOG("RINGBUF_" #_name "_pop error!!, src = 0x%x, size = %d , lenth = %d, in = %d,out = %d, _item = 0x%x, _num = %d\r\n", RINGBUF_##_name.src, RINGBUF_##_name.size, RINGBUF_##_name.lenth, RINGBUF_##_name.in, RINGBUF_##_name.out, (_item), (_num));\
        }\
        else\
        {\
            if((_num) <= (RINGBUF_##_name.size - RINGBUF_##_name.out))\
            {\
                memcpy((void *)(_item), (void *)&RINGBUF_##_name.src[RINGBUF_##_name.out],(_num) * RINGBUF_TYPE_SIZE(_name));\
                RINGBUF_##_name.out = RINGBUF_##_name.out + (_num);\
                RINGBUF_##_name.out = RINGBUF_##_name.out % RINGBUF_##_name.size;\
            }\
            else\
            {\
                memcpy((void *)(_item), (void *)&RINGBUF_##_name.src[RINGBUF_##_name.out], ((RINGBUF_##_name.size)-(RINGBUF_##_name.out))*RINGBUF_TYPE_SIZE(_name));\
                memcpy((void *)((_item) + ((RINGBUF_##_name.size)-(RINGBUF_##_name.out))*RINGBUF_TYPE_SIZE(_name)),(void *)&RINGBUF_##_name.src[0] , ((_num) - ((RINGBUF_##_name.size)-(RINGBUF_##_name.out)))*RINGBUF_TYPE_SIZE(_name));\
                RINGBUF_##_name.out = ((_num) - ((RINGBUF_##_name.size)-(RINGBUF_##_name.out)));\
                RINGBUF_##_name.out = RINGBUF_##_name.out % RINGBUF_##_name.size;\
            }\
            RINGBUF_##_name.lenth = RINGBUF_##_name.lenth - (_num);\
        }\
    } while (/*CONSTCOND*/0)


#endif /* __RINGBUFFER_H__ */
