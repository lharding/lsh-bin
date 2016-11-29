#include <stdio.h>

int main(int argc, char** argv) {
    int ch;

    while((ch = getchar()) != EOF) {
        if(ch & 0x80) putchar('#');
        putchar(ch & 0x7f);
    }
}
