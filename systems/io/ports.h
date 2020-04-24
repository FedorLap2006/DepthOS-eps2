#ifndef _PORTS_H_
#define _PORTS_H_

#include <depthos/types.h>

// id of port
typedef short int port_id_t;

// sends to 'port' v (8 bit value)
void port_sendb(port_id_t port, uint8_t v);
// sends to 'port' v (16 bit value)
void port_sendw(port_id_t port, uint16_t v);
// reads from 'port' value (8 bit value)
uint8_t port_readb(port_id_t port);
// reads from 'port' value (16 bit value)
uint16_t port_readw(port_id_t port);

#endif
