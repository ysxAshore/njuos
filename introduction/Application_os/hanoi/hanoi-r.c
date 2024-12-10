#include <stdio.h>

int hanoi(int n, char from, char to, char via) {
    if (n == 1) {
        printf("%c -> %c\n", from, to);//只有一个盘子，把它从from移到to
        return 1;
    } else {
        int c1 = hanoi(n - 1, from, via, to);//先把n-1个盘子移到中间
        hanoi(1, from, to, via);//然后把１个盘子移到to
        int c2 = hanoi(n - 1, via, to, from);//最后再把n-1个在中间的盘子移到to
        return c1 + c2 + 1;
    }
}
