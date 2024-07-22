#include <stdio.h>

void PrintSymbol(int counter, char symbol){
    for (int i = 0; i < counter; ++i){
        printf("%c", symbol);
    }
}

void Ungetch(char a, char b, char c){
    ungetc(a, stdin);
    ungetc(b, stdin);
    ungetc(c, stdin);
}

void Decode(){
    unsigned char d;
    char a, b, c;
    int counter = 0;

   while (1){

        scanf("%c%c%c", &a, &b, &c);

        if (c == '\n'){
            Ungetch(c, b, a);
            scanf("%hhx", &d);
            printf("%c\n", d);
            break;
        }
        else if (c != ' '){
            PrintSymbol(counter, '\b');
            PrintSymbol(counter, ' ');
            PrintSymbol(counter, '\b');
            printf("n/a\n");
            break;
        }
        else {
            Ungetch(c, b, a);
            scanf("%hhx ", &d);
            printf("%c ", d);
            counter += 3;
        }
   }
}

int main(){

    Decode();

    return 0;
}