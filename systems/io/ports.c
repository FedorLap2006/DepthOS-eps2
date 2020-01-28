#include "ports.h"

void port_sendb(port_id_t port, uint8_t v) {
	__asm__ volatile ("outb %1, %0" : : "dN"(port), "a"(v));
}
void port_sendw(port_id_t port, uint16_t v) {
	__asm__ volatile ("outw %1, %0" : : "dN"(port), "a"(v));
}
uint8_t port_readb(port_id_t port) {
	uint8_t r;
	__asm__ volatile ("inb %1, %0" : "=a" (r) : "dN" (port));
	return r;
}
uint16_t port_readw(port_id_t port) {
	uint16_t r;
	__asm__ volatile ("inw %1, %0" : "=a" (r) : "dN" (port));
	return r;
}