#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SIZE 100

char Stack[SIZE];
int Top = -1;

void push(char ch);
void pop();
void infix_to_postfix(const char* Expr);

int main() {
    const char* infixExpr = "x^y/(s*3)+2"; // Your expression here
    
    printf("Infix Expression: %s\n", infixExpr);
    printf("Postfix Expression: ");
    infix_to_postfix(infixExpr);
    printf("\n");
    return 0;
}

void push(char ch) {
    if (Top + 1 >= SIZE) {
        printf("\nStack overflow!");
        exit(1);
    }
    Stack[++Top] = ch;
}

void pop() {
    if (Top < 0) {
        printf("\nStack underflow!");
        exit(1);
    }
    if (Stack[Top] != '(') {
        printf("%c", Stack[Top]);
    }
    Top--;
}

void infix_to_postfix(const char* Expr) {
    int i = 0;
    while (Expr[i] != '\0') {
        if (isalpha(Expr[i]) || isdigit(Expr[i])) {
            printf("%c", Expr[i]);
        }
        else if (Expr[i] == '(') {
            push(Expr[i]);
        }
        else if (Expr[i] == ')') {
            while (Top >= 0 && Stack[Top] != '(') {
                pop();
            }
            if (Top >= 0 && Stack[Top] == '(') {
                Top--; // Remove '(' from stack
            }
        }
        else if (Expr[i] == '+' || Expr[i] == '-') {
            while (Top >= 0 && Stack[Top] != '(' &&
                  (Stack[Top] == '+' || Stack[Top] == '-' ||
                   Stack[Top] == '*' || Stack[Top] == '/' ||
                   Stack[Top] == '^')) {
                pop();
            }
            push(Expr[i]);
        }
        else if (Expr[i] == '*' || Expr[i] == '/') {
            while (Top >= 0 && Stack[Top] != '(' &&
                  (Stack[Top] == '*' || Stack[Top] == '/' ||
                   Stack[Top] == '^')) {
                pop();
            }
            push(Expr[i]);
        }
        else if (Expr[i] == '^') {
            while (Top >= 0 && Stack[Top] != '(' &&
                   Stack[Top] == '^') {
                pop();
            }
            push(Expr[i]);
        }
        i++;
    }
    // Pop remaining operators
    while (Top >= 0) {
        pop();
    }

}

Output:
Infix Expression: x^y/(s*3)+2
Postfix Expression: xy^s3*/2+
