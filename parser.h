#pragma once
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <linux/limits.h>

#define TCP 0x06
#define UDP 0x11
#define IP_PACKET_WORD  4
#define TCP_PACKET_WORD 4

typedef struct _ip_hdr
{
    uint8_t ihl:4;
    uint8_t ver:4;
    uint8_t tos;
    uint16_t total_len;
    uint16_t fid;
    uint16_t frag_off;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t checksum;
    uint8_t src_addr[4];
    uint8_t dst_addr[4];
}ip_hdr, *pip_hdr;

typedef struct _tcp_hdr
{
    uint16_t src_port;
    uint16_t dst_port;
    uint32_t seq_num;
    uint32_t ack_num;
    uint8_t resrv:4;
    uint8_t HL:4;
    uint8_t flag;
    uint16_t win_size;
    uint16_t checksum;
    uint16_t Urg_pnt;
}tcp_hdr, *ptcp_hdr;

static inline int isTargetPort(tcp_hdr *header);
static inline int isHTTP(char* packet);
static inline int isTargetSite(uint8_t *data);
void init(int argc, char **argv);
int isTarget(void *data);