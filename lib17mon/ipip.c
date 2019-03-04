#include "ipip.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned char byte;
typedef unsigned int uint;
#define B2IL(b) (((b)[0] & 0xFF) | (((b)[1] << 8) & 0xFF00) | (((b)[2] << 16) & 0xFF0000) | (((b)[3] << 24) & 0xFF000000))
#define B2IU(b) (((b)[3] & 0xFF) | (((b)[2] << 8) & 0xFF00) | (((b)[1] << 16) & 0xFF0000) | (((b)[0] << 24) & 0xFF000000))

struct {
    byte *data;
    byte *index;
    uint *flag;
    uint offset;
} ipip;

int destroy() {
    if (!ipip.offset) {
        return 0;
    }
    free(ipip.flag);
    free(ipip.index);
    free(ipip.data);
    ipip.offset = 0;
    return 0;
}

int init(const char* ipdb) {
    if (ipip.offset) {
        return 0;
    }
    FILE *file = fopen(ipdb, "rb");
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    ipip.data = (byte *) malloc(size * sizeof(byte));
    fread(ipip.data, sizeof(byte), (size_t) size, file);

    fclose(file);

    uint indexLength = B2IU(ipip.data);

    ipip.index = (byte *) malloc(indexLength * sizeof(byte));
    memcpy(ipip.index, ipip.data + 4, indexLength);

    ipip.offset = indexLength;

    ipip.flag = (uint *) malloc(65536 * sizeof(uint));
    memcpy(ipip.flag, ipip.index, 65536 * sizeof(uint));

    return 0;
}

int find(const char *ip, char *result) {
    uint ips[4];
    int num = sscanf(ip, "%d.%d.%d.%d", &ips[0], &ips[1], &ips[2], &ips[3]);
    if (num == 4) {
        uint ip_prefix_value = ips[0] * 256 + ips[1];
        uint ip2long_value = B2IU(ips);
        uint start = ipip.flag[ip_prefix_value];
        uint max_comp_len = ipip.offset - 262144 - 4;
        uint index_offset = 0;
        uint index_length = 0;
        for (start = start * 9 + 262144; start < max_comp_len; start += 9) {
            if (B2IU(ipip.index + start) >= ip2long_value) {
                index_offset = B2IL(ipip.index + start + 4) & 0x00FFFFFF;
                index_length = (ipip.index[start+7] << 8) + ipip.index[start+8];
                break;
            }
        }
        memcpy(result, ipip.data + ipip.offset + index_offset - 262144, index_length);
        result[index_length] = '\0';
        int current_tabs = 0;
        int i;
        for (i = 0; i < index_length; i++) {
            if (result[i] == '\t') {
                if (current_tabs++ == 4) {
                    result[i] = 0;
                    break;
                }
                result[i] = ' ';
            }
        }
        if (result[strlen(result) - 1] == ' ') {
            result[strlen(result) - 1] = 0;
        }
    }
    return 0;
}
