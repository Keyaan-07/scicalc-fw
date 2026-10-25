#include <stdio.h>
#include <stdbool.h>
// #include <string.h>
int checkComplete(char *exp){
    int c = 0;
    int bracketCount = 0;
    char prevChar = '0';
    bool charErr = 0;
    while(exp[c] != '\0'){
        char currChar = exp[c];
        if(exp[c]=='(') bracketCount++;
        if(exp[c] == ')') bracketCount--;
        if(bracketCount<0){
            return 0; // for the edge case where )x+2( is entered
        }
        // doesnt allow multiple symbols consecutively. 
        if(currChar == '+' || currChar == '/' || currChar == '*' || currChar == '^' || currChar == '-'){
            if(prevChar == '+' || prevChar == '-' || prevChar == '*' || prevChar == '/'){
                charErr = 1;
            }
            if(exp[c+1]=='\0') charErr = 1;
        }
        prevChar = currChar;
        c++;
    }
    // returns if  bracket count is not in order or multiple symbols are used consecutively. 
    if(bracketCount == 0&&charErr==0) return 1;
    else return 0;
}


// checker loop: 
// int main(){
//     char exp[20];
//     scanf("%[^\n]", &exp);
//     int x = checkComplete(exp);
//     printf("%d", x);
//     return 0;
// }
