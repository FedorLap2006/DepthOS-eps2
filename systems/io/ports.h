#pragma once

#include <depthos/types.h>


typedef short int port_id_t;

void port_sendb(port_id_t port, uint8_t v);
void port_sendw(port_id_t port, uint16_t v);
uint8_t port_readb(port_id_t port);
uint16_t port_readw(port_id_t port);