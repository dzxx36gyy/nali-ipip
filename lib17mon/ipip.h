#ifndef _IPIP_H_
#define _IPIP_H_

int init(const char* ipdb);
int destroy();
int find(const char *ip, char *result);

#endif //_IPIP_H_
