#include <iostream>

#include "errors.h"

#ifndef _STACK_H_
#define _STACK_H_

#define STACK_MAX 1000

int top = -1;
int stack[STACK_MAX];

int gl_isEmpty() {
    if (top == -1) {
        return 1;
    }
    else {
        return 0;
    }
}

int gl_canAdd() {
    if (top > 0)
        return 1;
    else
        return 0;
}

int gl_isFull() {
    if (top == STACK_MAX-1) {
        return 1;
    }
    else {
        return 0;
    }
}

int gl_push(const int& val) {
    if (gl_isFull()) {
        GL_RUNTIME_ERROR_MSG("Cannot push, stack is full!");
        return GL_RUNTIME_ERROR;
    }
    stack[++top] = val;
    return 0;
}

int gl_pop() {
    if (gl_isEmpty()) {
        GL_RUNTIME_ERROR_MSG("Cannot pop, stack is empty!");
        return GL_RUNTIME_ERROR;
    }
    top--;
    return GL_RUNTIME_SUCCESS;
}

int gl_peek() {
    if (gl_isEmpty()) {
        return GL_RUNTIME_ERROR;
    }
    return stack[top];
}

#endif

#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

void gl_print() {
    if (!gl_isEmpty())
        printf("%i\n", gl_peek());
    else
        GL_RUNTIME_ERROR_MSG("Cannot print, stack is empty!");
}

void gl_printc() {
    if (!gl_isEmpty())
        printf("%c", char(gl_peek()));
    else
        GL_RUNTIME_ERROR_MSG("Cannot print, stack is empty!");
}

void gl_input() {
    int n;
    std::cin >> n;
    gl_push(n);
}

void gl_inputc() {
    char n;
    std::cin >> n;
    gl_push(int(n));
}

int gl_add() {
    if (gl_canAdd()) {
        gl_push(stack[top] + stack[top-1]);
        return GL_RUNTIME_SUCCESS;
    } else {
        GL_RUNTIME_ERROR_MSG("Cannot add, not enuogh items on stack!");
        return GL_RUNTIME_ERROR;
    }
}

int gl_sub() {
    if (gl_canAdd()) {
        gl_push(stack[top] - stack[top-1]);
        return GL_RUNTIME_SUCCESS;
    } else {
        GL_RUNTIME_ERROR_MSG("Cannot subtract, not enuogh items on stack!");
        return GL_RUNTIME_ERROR;
    }
}

int gl_mul() {
    if (gl_canAdd()) {
        gl_push(stack[top] * stack[top-1]);
        return GL_RUNTIME_SUCCESS;
    } else {
        GL_RUNTIME_ERROR_MSG("Cannot multiply, not enuogh items on stack!");
        return GL_RUNTIME_ERROR;
    }
}

int gl_inc() {
    if (!gl_isEmpty()) {
        gl_push(stack[top] + 1);
        return GL_RUNTIME_SUCCESS;
    } else {
        GL_RUNTIME_ERROR_MSG("Cannot increment, stack is empty!");
        return GL_RUNTIME_ERROR;
    }
}

int gl_dec() {
    if (!gl_isEmpty()) {
        gl_push(stack[top] - 1);
        return GL_RUNTIME_SUCCESS;
    } else {
        GL_RUNTIME_ERROR_MSG("Cannot decrement, stack is empty!");
        return GL_RUNTIME_ERROR;
    }
}

void  gl_dup() {
    if (!gl_isEmpty()) {
        gl_push(gl_peek());
    } else {
        GL_RUNTIME_ERROR_MSG("Cannot duplicate, stack is empty!");
    }
}

#endif