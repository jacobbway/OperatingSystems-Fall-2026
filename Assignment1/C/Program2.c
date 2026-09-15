#include <stdio.h>
#include <string.h>

int main()
{
    char userInputString[1000] = "";
    char userToken[100] = "";

    printf("Enter a string\n");
    fgets(userInputString, sizeof(userInputString), stdin);

    userInputString[strcspn(userInputString, "\n")] = '\0';
    
    printf("Enter a token\n");
    fgets(userToken, sizeof(userToken), stdin);

    userToken[strcspn(userToken, "\n")] = '\0';
    
    if(strstr(userInputString, userToken) != NULL)
    {
        printf("FOUND\n");
    }
    else
    {
        printf("NOT FOUND\n");
    }
}