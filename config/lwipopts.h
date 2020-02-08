/**
  ******************************************************************************
  * @file    lwipopts.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    31-October-2011
  * @brief   lwIP Options Configuration.
  *          This file is based on Utilities\lwip_v1.3.2\src\include\lwip\opt.h 
  *          and contains the lwIP configuration for the STM32F4x7 demonstration.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

#include "app_config.h" // For USE_DHCP

/**
 * SYS_LIGHTWEIGHT_PROT==1: if you want inter-task protection for certain
 * critical regions during buffer allocation, deallocation and memory
 * allocation and deallocation.
 */
#define SYS_LIGHTWEIGHT_PROT    1

#define ETHARP_TRUST_IP_MAC     0
#define IP_REASSEMBLY           0
#define IP_FRAG                 0
#define ARP_QUEUEING            0

/**
 * NO_SYS==1: Provides VERY minimal functionality. Otherwise,
 * use lwIP facilities.
 */

#define NO_SYS                  0

/* ---------- Memory options ---------- */
/* MEM_ALIGNMENT: should be set to the alignment of the CPU for which
   lwIP is compiled. 4 byte alignment -> define MEM_ALIGNMENT to 4, 2
   byte alignment -> define MEM_ALIGNMENT to 2. */
#define MEM_ALIGNMENT           4

/* MEM_SIZE: the size of the heap memory. If the application will send
a lot of data that needs to be copied, this should be set high. */
#define MEM_SIZE                (16*1024)

#define MEM_OVERFLOW_CHECK      0

/* MEMP_NUM_PBUF: the number of memp struct pbufs. If the application
   sends a lot of data out of ROM (or other static memory), this
   should be set high. */
//#define MEMP_NUM_PBUF           100
///#define MEMP_NUM_PBUF           40
#define MEMP_NUM_PBUF           50
/* MEMP_NUM_UDP_PCB: the number of UDP protocol control blocks. One
   per active UDP "connection". */
#define MEMP_NUM_UDP_PCB        6
/* MEMP_NUM_TCP_PCB: the number of simulatenously active TCP
   connections. */
#define MEMP_NUM_TCP_PCB        12
//#define MEMP_NUM_TCP_PCB        5
/* MEMP_NUM_TCP_PCB_LISTEN: the number of listening TCP
   connections. */
#define MEMP_NUM_TCP_PCB_LISTEN 5
//#define MEMP_NUM_TCP_PCB_LISTEN 15
/* MEMP_NUM_TCP_SEG: the number of simultaneously queued TCP
   segments. */
#define MEMP_NUM_TCP_SEG        16
//#define MEMP_NUM_TCP_SEG        100	 
/* MEMP_NUM_SYS_TIMEOUT: the number of simulateously active
   timeouts. */
#define MEMP_NUM_SYS_TIMEOUT    10
//#define MEMP_NUM_SYS_TIMEOUT    100

/**
 * MEMP_NUM_NETCONN: the number of struct netconns.
 * (only needed if you use the sequential API, like api_lib.c)
 */
#define MEMP_NUM_NETCONN                10

/* ---------- Pbuf options ---------- */
/* PBUF_POOL_SIZE: the number of buffers in the pbuf pool. */
//#define PBUF_POOL_SIZE          15
#define PBUF_POOL_SIZE          25
//#define PBUF_POOL_SIZE          18

/* PBUF_POOL_BUFSIZE: the size of each pbuf in the pbuf pool. */
//#define PBUF_POOL_BUFSIZE       1500
//#define PBUF_POOL_BUFSIZE       3024
#define PBUF_POOL_BUFSIZE         1540


/**
 * MEMP_NUM_NETBUF: the number of struct netbufs.
 * (only needed if you use the sequential API, like api_lib.c)
 */

#define MEMP_NUM_NETBUF                 7


#define TCP_LISTEN_BACKLOG              1


/* ---------- TCP options ---------- */
#define LWIP_TCP                1
#define TCP_TTL                 255

/* Controls if TCP should queue segments that arrive out of
   order. Define to 0 if your device is low on memory. */
#define TCP_QUEUE_OOSEQ         0

/* TCP Maximum segment size. */
#define TCP_MSS                 (1500 - 40)	  /* TCP_MSS = (Ethernet MTU - IP header size - TCP header size) */

/* TCP sender buffer space (bytes). */
#define TCP_SND_BUF             (4*TCP_MSS)
//#define TCP_SND_BUF             (18*TCP_MSS)

/*  TCP_SND_QUEUELEN: TCP sender buffer space (pbufs). This must be at least
  as much as (2 * TCP_SND_BUF/TCP_MSS) for things to work. */
//20 
#define TCP_SND_QUEUELEN        (4* TCP_SND_BUF/TCP_MSS)
//#define TCP_SND_QUEUELEN        (4* TCP_SND_BUF/TCP_MSS)

/* TCP receive window. */
#define TCP_WND                 (4*TCP_MSS)


/* ---------- ICMP options ---------- */
#define LWIP_ICMP                       1
#define ICMP_TTL			128

/* ---------- DHCP options ---------- */
/* Define LWIP_DHCP to 1 if you want DHCP configuration of
   interfaces. DHCP is not implemented in lwIP 0.5.1, however, so
   turning this on does currently not work. */
#define LWIP_DHCP                 USE_DHCP
#define LWIP_DHCP_MAX_DNS_SERVERS 1

// ---------- SNMP options ----------
#define LWIP_SNMP                       1
#define LWIP_SNMP_V3                    1
#define SNMP_USE_RAW                    1

/* ---------- UDP options ---------- */
#define LWIP_UDP                1
#define UDP_TTL                 255

#define LWIP_SO_RCVTIMEO        1 // Эта опция необходима для netconn_set_recvtimeout в модуле udp_netsetting.c
#define LWIP_SO_SNDTIMEO        1 //

/* ---------- Statistics options ---------- */
#define LWIP_STATS                      1
#define LWIP_STATS_DISPLAY              0
#define LWIP_PROVIDE_ERRNO              1

#define LWIP_NETIF_LINK_CALLBACK        0

#define LWIP_NUM_NETIF_CLIENT_DATA      1

/*
   --------------------------------------
   ---------- Checksum options ----------
   --------------------------------------
*/

/* 
The STM32F4x7 allows computing and verifying the IP, UDP, TCP and ICMP checksums by hardware:
 - To use this feature let the following define uncommented.
 - To disable it and process by CPU comment the  the checksum.
*/
//#define CHECKSUM_BY_HARDWARE


#ifdef CHECKSUM_BY_HARDWARE
  /* CHECKSUM_GEN_IP==0: Generate checksums by hardware for outgoing IP packets.*/
  #define CHECKSUM_GEN_IP                 0
  /* CHECKSUM_GEN_UDP==0: Generate checksums by hardware for outgoing UDP packets.*/
  #define CHECKSUM_GEN_UDP                0
  /* CHECKSUM_GEN_TCP==0: Generate checksums by hardware for outgoing TCP packets.*/
  #define CHECKSUM_GEN_TCP                0 
  /* CHECKSUM_CHECK_IP==0: Check checksums by hardware for incoming IP packets.*/
  #define CHECKSUM_CHECK_IP               0
  /* CHECKSUM_CHECK_UDP==0: Check checksums by hardware for incoming UDP packets.*/
  #define CHECKSUM_CHECK_UDP              0
  /* CHECKSUM_CHECK_TCP==0: Check checksums by hardware for incoming TCP packets.*/
  #define CHECKSUM_CHECK_TCP              0
  /* CHECKSUM_CHECK_ICMP==0: Check checksums by hardware for incoming ICMP packets.*/  
  #define CHECKSUM_GEN_ICMP               0
#else
  /* CHECKSUM_GEN_IP==1: Generate checksums in software for outgoing IP packets.*/
  #define CHECKSUM_GEN_IP                 1
  /* CHECKSUM_GEN_UDP==1: Generate checksums in software for outgoing UDP packets.*/
  #define CHECKSUM_GEN_UDP                1
  /* CHECKSUM_GEN_TCP==1: Generate checksums in software for outgoing TCP packets.*/
  #define CHECKSUM_GEN_TCP                1
  /* CHECKSUM_CHECK_IP==1: Check checksums in software for incoming IP packets.*/
  #define CHECKSUM_CHECK_IP               1
  /* CHECKSUM_CHECK_UDP==1: Check checksums in software for incoming UDP packets.*/
  #define CHECKSUM_CHECK_UDP              1
  /* CHECKSUM_CHECK_TCP==1: Check checksums in software for incoming TCP packets.*/
  #define CHECKSUM_CHECK_TCP              1
  /* CHECKSUM_CHECK_ICMP==1: Check checksums by hardware for incoming ICMP packets.*/  
  #define CHECKSUM_GEN_ICMP               1
#endif


/*
   ----------------------------------------------
   ---------- Sequential layer options ----------
   ----------------------------------------------
*/
/**
 * LWIP_NETCONN==1: Enable Netconn API (require to use api_lib.c)
 */
#define LWIP_NETCONN                    1

/*
   ------------------------------------
   ---------- Socket options ----------
   ------------------------------------
*/
/**
 * LWIP_SOCKET==1: Enable Socket API (require to use sockets.c)
 */
#define LWIP_SOCKET                     1
#define LWIP_DNS                        0
#define SO_REUSE                        1
   
/*
   -----------------------------------
   ---------- DEBUG options ----------
   -----------------------------------
*/

//#define LWIP_NOASSERT
#define LWIP_DEBUG

#define TCP_DEBUG                       LWIP_DBG_OFF
#define ETHARP_DEBUG                    LWIP_DBG_OFF
#define PBUF_DEBUG                      LWIP_DBG_OFF
#define IP_DEBUG                        LWIP_DBG_OFF
#define TCPIP_DEBUG                     LWIP_DBG_OFF
#define DHCP_DEBUG                      LWIP_DBG_OFF
#define UDP_DEBUG                       LWIP_DBG_OFF
#define SOCKETS_DEBUG                   LWIP_DBG_OFF
#define MEMP_DEBUG                      LWIP_DBG_OFF
#define PING_DEBUG                      LWIP_DBG_OFF
#define SNMP_DEBUG                      LWIP_DBG_OFF
#define SNMP_MIB_DEBUG                  LWIP_DBG_OFF
#define TIMERS_DEBUG                    LWIP_DBG_OFF
#define ICMP_DEBUG                      LWIP_DBG_OFF

#include <stdio.h>
#define LWIP_PLATFORM_DIAG(x)  do {printf x;} while(0)

/*
   ---------------------------------
   ---------- OS options ----------
   ---------------------------------
*/

#define TCPIP_THREAD_STACKSIZE          800
#define TCPIP_MBOX_SIZE                 50
#define DEFAULT_UDP_RECVMBOX_SIZE       20
#define DEFAULT_TCP_RECVMBOX_SIZE       70
#define DEFAULT_RAW_RECVMBOX_SIZE       10
#define DEFAULT_ACCEPTMBOX_SIZE         20
#define DEFAULT_THREAD_STACKSIZE        500
#define TCPIP_THREAD_PRIO               (configMAX_PRIORITIES - 2)

#define MEMP_NUM_TCPIP_MSG_INPKT        20



#endif /* __LWIPOPTS_H__ */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
