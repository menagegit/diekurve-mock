#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>

#define PACKET_SIZE 512

typedef struct packet_allocator packet_allocator_t;
typedef struct packet
{
    int64_t len;
    uint8_t *data;
    uint8_t buffer[PACKET_SIZE];
}
packet_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

packet_t* allocate_packet();
void release_packet(packet_t*);

uint32_t max_packet_size();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PACKET_H */
