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

err_t spi_if_init(struct netif *netif);

#endif /* __SPIIF_H */
