#include "parser.h"

int p_argc;
char **p_argv;

// Check if TCP dest port is 80
static inline int isTargetPort(tcp_hdr *header)
{
    return ntohs(header->dst_port) == 80 ? 1 : 0;
}

// Check if TCP payload is HTTP
static inline int isHTTP(char* packet)
{
    if( memcmp(packet,"GET",3) == 0 )
        return 1;
    else if( memcmp(packet,"HEAD",4) == 0 )
        return 1;
    else if( memcmp(packet,"POST",4) == 0 )
        return 1;
    else if( memcmp(packet,"PUT",3) == 0 )
        return 1;
    else if( memcmp(packet,"DELETE",6) == 0 )
        return 1;
    else if( memcmp(packet,"CONNECT",7) == 0 )
        return 1;
    else if( memcmp(packet,"OPTIONS",7) == 0 )
        return 1;
    else if( memcmp(packet,"TRACE",5) == 0 )
        return 1;
    else if( memcmp(packet,"PATCH",5) == 0 )
        return 1;
    else
        return 0;
}

// Check if HTTP request for target
static inline int isTargetSite(uint8_t *data)
{   
    int i;
    char *ptr = strtok(data, "\r\n");   // string => GET / HTTP/1.1 ~~ \r\n
    ptr = strtok(NULL, "\r\n");         // string => Host : ~~~ \r\n

    if(ptr == NULL) return 0;

    // Find all arguments
    for(i = 1 ; i < p_argc; i++)
    {
        // Search after "Host :" string
        if(strstr(ptr+6 ,p_argv[i]))
        {
            printf("%c[31mHTTP Request to %s detected!%c[0m\n",27 ,p_argv[i] ,27);
            return 1;
        }
    }
    return 0;
}

// Copy argc & argv
void init(int argc, char **argv)
{
    p_argc = argc;
    p_argv = argv;
}

// Target Check Wrapper Function
int isTarget(void *data)
{
    ip_hdr *ip_headr = (ip_hdr*)data;
    data += ip_headr->ihl * IP_PACKET_WORD;

    if( ip_headr->protocol == TCP)
    {
        tcp_hdr *tcp_header; tcp_header = (tcp_hdr*)data;
        data += tcp_header->HL * TCP_PACKET_WORD;

        if( isTargetPort(tcp_header) && isHTTP(data) && isTargetSite(data))
            return 1;
    }
    else return 0;

}