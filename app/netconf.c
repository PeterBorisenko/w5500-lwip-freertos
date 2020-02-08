/**
 * @file  netconf.c
 * @brief LwIp app-level init
 * @date  8 feb 2020 г.
 * @author  Peter Borisenko
 */

#include <string.h>
#include "spiif.h"
#include "lwip/netif.h"
#include "lwip/ip4_addr.h"
#include "lwip/tcpip.h"

struct netif eth0;

void lwipInit(void)
{
  struct ip4_addr ipaddr;
  struct ip4_addr netmask;
  struct ip4_addr gw;

  tcpip_init( NULL, NULL);

  ipaddr.addr= ipaddr_addr("192.168.1.2");
  netmask.addr= ipaddr_addr("255.255.255.0");
  gw.addr = ipaddr_addr("192.168.1.1");

  netif_add(
      &eth0,
      &ipaddr,
      &netmask,
      &gw,
      NULL,
      &spi_if_init,
      &tcpip_input);

  netif_set_up(&eth0);
}
