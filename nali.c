#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "lib17mon/ipip.h"
#include "config.h"
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
    printf("%s",result);
    printf("\n");
    destroy();
    return 0;
}

