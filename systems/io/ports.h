#ifndef _PORTS_H_
#define _PORTS_H_

#include <depthos/types.h>

// id of port
typedef uint16_t port_id_t;

// sends 'v' (8 bits) to 'port'
void port_sendb(port_id_t port, uint8_t v);
// sends 'v' (16 bits) to 'port'
void port_sendw(port_id_t port, uint16_t v);
// reads value (8 bits) from 'port'
uint8_t port_readb(port_id_t port);
// reads value (16 bits) from 'port'
uint16_t port_readw(port_id_t port);

#endif
