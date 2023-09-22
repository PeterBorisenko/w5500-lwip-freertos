/**
 * @file 	spiif.c
 * @brief 	LwIp+FreeRTOS binding for Wizchip W5500
 * @date 	8 feb 2020 г.
 * @author 	Peter Borisenko
 */

#include <stdbool.h>
#include <lwip/pbuf.h>
#include <netif/etharp.h>
#include <spiif.h>

#include "wizchip_conf.h"
#include "wizchip_port.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

static const char IFNAME0= 'e';
static const char IFNAME1= '0';

SemaphoreHandle_t s_xSemaphoreSpi = NULL;

static struct netif *spi_if_netif;

void spi_if_clr(void) {
  setSn_IR(0, 0x1F);
  setSIR(0);
}

/**
 * Checks PHYCFGR for the hardware link state, and calls lwIP's
 * netif_set_link_up() and netif_set_link_down() functions as needed.
 */
static void spi_if_check_link_state(void)
{
	static bool linkstate;

	// Bit 0 is link status (1 = up), 1 is speed (1 = 100), 2 is duplex (1 = full)
	volatile uint8_t phyReg = getPHYCFGR();
	linkstate = phyReg & (1 << 0);
	if (linkstate && !netif_is_link_up(spi_if_netif))
	{
		debug_print("ETH0 Hardware link up\r\n");
		netif_set_link_up(spi_if_netif);
	}
	else if (!linkstate && netif_is_link_up(spi_if_netif))
	{
		debug_print("ETH0 Hardware link down\r\n");
		netif_set_link_down(spi_if_netif);
	}
}

void spi_if_input(void * pvParameters) {
  err_t result;
  struct pbuf *p = NULL;
  uint8_t res= 0;
  uint16_t epktcnt;
  bool linkstate;

  for ( ;; ) {
    if (xSemaphoreTake(s_xSemaphoreSpi, pdMS_TO_TICKS(500)) != pdTRUE) {
      spi_if_clr();
      spi_if_check_link_state();
    }
    else {
 			if (!netif_is_link_up(spi_if_netif))
			{
				// Link must have come back up - need to check
				spi_if_check_link_state();
			}
GET_NEXT_FRAGMENT:
      spi_if_clr();
      res= wiz_read_receive_pbuf(&p);
      if (res == 0) {
        LWIP_DEBUGF(NETIF_DEBUG, ("incoming: %d packages, first read into %x\n", epktcnt, (unsigned int)(p)));
          if ( ERR_OK != spi_if_netif->input(p, spi_if_netif)) {
            pbuf_free(p);
            p=NULL;
          }
          else {
            LWIP_DEBUGF(NETIF_DEBUG, ("received with result %d\n", result));
            p=NULL;
            xSemaphoreTake(s_xSemaphoreSpi, 0);
            goto GET_NEXT_FRAGMENT;
          }
      }
      else {
        LWIP_DEBUGF(NETIF_DEBUG, ("didn't receive.\n"));
      }
    }
  }
}

static err_t spi_if_linkoutput(struct netif *netif, struct pbuf *p) {
  while (!(getSn_SR(0) & SOCK_MACRAW)); /* TODO: Implement wait timeout */
  wiz_transmit_pbuf(p);
  LWIP_DEBUGF(NETIF_DEBUG, ("sent %d bytes.\n", p->tot_len));
  /* TODO: Set up result value */
  return ERR_OK;
}

err_t spi_if_init(struct netif *netif) {
  int result;

  netif->hwaddr_len= ETHARP_HWADDR_LEN;
  netif->hwaddr[0]=  0x0C;
  netif->hwaddr[1]=  0x4B;
  netif->hwaddr[2]=  0x0A;
  netif->hwaddr[3]=  0x01;
  netif->hwaddr[4]=  0x0E;
  netif->hwaddr[5]=  0x02;
  netif->name[0]= IFNAME0;
  netif->name[1]= IFNAME1;
  netif->output= etharp_output;
  netif->linkoutput= spi_if_linkoutput;
  netif->mtu= 1500;
  netif->flags|= NETIF_FLAG_ETHARP | NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHERNET;
  spi_if_netif= netif;

  wiz_lowlevel_setup();
  
  wiz_hwReset();
  reg= getVERSIONR();
  if (reg != 0x04) {
      // Error
  }
  setMR(MR_RST);
  setSn_MR(0, Sn_MR_MACRAW | Sn_MR_MIP6B | Sn_MR_MMB);
  setSn_RXBUF_SIZE(0, 16);
  setSn_TXBUF_SIZE(0, 16);
  setINTLEVEL(1);
  setSIMR(1);
  setPHYCFGR(0x58);
  setPHYCFGR(0xD8);
  setSn_IMR(0, (Sn_IR_RECV));
  setSn_CR(0, Sn_CR_OPEN);

  if (s_xSemaphoreSpi == NULL) {
    s_xSemaphoreSpi= xSemaphoreCreateCounting(20,0);
    vQueueAddToRegistry(s_xSemaphoreSpi, "q_spi");
  }

  LWIP_DEBUGF(NETIF_DEBUG, ("Driver initialized.\n"));

  xTaskCreate(spi_if_input, "Spi_if", 256, NULL,
      configMAX_PRIORITIES - 1, &spiifTaskHandle);

  return ERR_OK;
}
