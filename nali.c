#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "lib17mon/ipip.h"
#include "config.h"

void split(char **arr, char *str, const char *del) {
    char *s = strtok(str, del);
    while(s != NULL) {
        *arr++ = s;
        s = strtok(NULL, del);
    }
}

void removeDuplicate(char *str[], int len) {
    int i, j = 0;
    int k = len - 1;
    for(i = len - 1; i > 0; i--)
    {
        --k;
        if(strncmp(str[i], "*",1))
        {
            if (strcmp(str[i],str[k]) == 0) {
                str[i] = "*";
            }
        }
    }
}

int main(int argc, char *argv[])
{
    init(IPIPDB_PATH);
    char *ip;
    if (argc != 2) {
        ip=(char *)malloc(128);//有可能前面有大段非数字字符，所以申请128
        ip=fgets(ip,128,stdin);
    } else {
        ip=argv[1];
    }
    char result[128];
    find(ip, result);
    destroy();
    strcat(result,"\n");
    puts(result);

    return 0;
}

