/**
 * @file 	spiif.h
 * @brief 	Header for LwIp+FreeRTOS binding for Wizchip W5500
 * @date 	8 feb 2020 г.
 * @author 	Peter Borisenko
 */

#ifndef __SPIIF_H
#define __SPIIF_H

#include <lwip/netif.h>
#include <lwip/err.h>

/** netif init function; have this called by passing it to netif_add, along
 * with a pointer to an uninitialized enc_device_t state. The MAC address has
 * to be configured beforehand in the netif, and configured on the card. */
err_t spi_if_init(struct netif *netif);

void spi_if_isr(void);

#endif /* __SPIIF_H */
