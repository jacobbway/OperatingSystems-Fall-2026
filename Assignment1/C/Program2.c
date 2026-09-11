#include <stdio.h>
#include <string.h>

int main()
{
    char userInputString[100] = "";
    char userToken[100] = "";

    printf("Enter a string\n");
    fgets(userInputString, sizeof(userInputString), stdin);
    
    printf("Enter a token\n");
    fgets(userToken, sizeof(userToken), stdin);
    
    if(strstr(userInputString, userToken) != NULL)
    {
        printf("FOUND\n");
    }
    else
    {
        printf("NOT FOUND\n");
    }
}