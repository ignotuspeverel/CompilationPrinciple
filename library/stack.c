#include "stack.h"

Stack_err_t Stack_init(Stack *s){
    s->base=(ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
    if(!s->base) return ERROR;
    s->top = s->base;
    s->stackSize = STACK_INIT_SIZE;
    return OK;
}

Stack_err_t Stack_push(Stack *s, ElemType e){
    if((s->top - s->base)/sizeof(ElemType) >= s->stackSize){
        s->base = (ElemType *)realloc(s->base, (s->stackSize + STACK_INCREMENT) * sizeof(ElemType));
        if(!s->base) return ERROR;
        s->top = s->base + s->stackSize * sizeof(ElemType);
        s->stackSize = s->stackSize + STACK_INCREMENT;
    }
    *(s->top) = e;
    s->top += sizeof(ElemType);
    return OK;
}

Stack_err_t Stack_pop(Stack *s, ElemType *e){
    if(s->top == s->base) return ERROR;
    *e = *(s->top - sizeof(ElemType));
    s->top-=sizeof(ElemType);
    return OK;
}

int Stack_length(Stack *s){
    return(s->top - s->base)/sizeof(ElemType);
}