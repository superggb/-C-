#include<stdio.h>

int search(char id){
    switch(id){
    case '+':
        return 27;
    case '-':
        return 28;
    case '*':
        return 29;
    case '/':
        return 30;
    case ':':
        return 31;
    case '<':
        return 33;
    case '=':
        return 38;
    case ';':
        return 41;
    case '(':
        return 42;
    case ')':
        return 43;
    case '#':
        return 0;
        break;
        }
        return -1;
}
