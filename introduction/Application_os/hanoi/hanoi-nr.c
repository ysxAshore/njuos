#include <stdio.h>
#include <assert.h>

struct Frame {
    // Each frame has a program counter to keep track its next
    // to-be-executed statement.
    int pc;

    // The internal state of the frame. This state includes
    // both arguments and local variables (if any).
    //
    // Arguments:
		// 按照递归实现的汉诺塔，函数的参数有n from to via
		// 函数内部使用的局部变量包括c1,c2
    int n;
    char from, to, via;

    // Local variables:
    int c1, c2;
};

typedef struct Frame Frame;

int hanoi(int n, char from, char to, char via) {
    Frame stk[64]; //栈帧集合
    Frame *top = stk - 1; //top指向栈顶，没有元素时定义为栈起始-栈帧大小

    // Function call: push a new frame (PC=0) onto the stack
		// 调用函数，相当于新入栈一个栈帧，因为栈起始定义为stk-1
		// 所以这里需要先递增栈顶指针，再入栈frame
    #define call(...) ({ *(++top) = (Frame){.pc = 0, __VA_ARGS__}; })
    
    // Function return: pop the top-most frame
		// 从函数中返回相当于出栈　val中是返回值
    #define ret(val) ({ top--; retval = (val); })


    // The last function-return's value. It is not obvious
    // that we only need one retval.
    int retval = 0;

    // The initial call to the recursive function
    call(n, from, to, via);

    while (1) {
        // Fetch the top-most frame.
				// 获取栈顶指针
        Frame *f = top;
        if (top < stk) { //栈空
            // No top-most frame any more; we're done.
            break;
        }

        // Jumps may change this default next pc.
        int next_pc = f->pc + 1;

        // Single step execution.

        // Extract the parameters from the current frame. (It's
        // generally a bad idea to reuse variable names in
        // practice; but we did it here for readability.)
				// 从栈帧中获得参数
        int n = f->n, from = f->from, to = f->to, via = f->via;

				// 基本上是按照递归的汉诺塔函数内部实现
        switch (f->pc) {
            case 0:
                if (n == 1) {
                    printf("%c -> %c\n", from, to);
                    ret(1);
                }
                break;
            case 1: call(n - 1, from, via, to); break;
            case 2: f->c1 = retval; break;
            case 3: call(1, from, to, via); break;
            case 4: call(n - 1, via, to, from); break;
            case 5: f->c2 = retval; break;
            case 6: ret(f->c1 + f->c2 + 1); break;
            default: assert(0);
        }

        f->pc = next_pc; //写PC
    }

    return retval;
}
