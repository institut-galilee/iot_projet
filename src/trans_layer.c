/*
 * IoT-Labs-2018
 * Copyright (C) 2018 Massinissa Hamidi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>

#include "lwip/api.h"
#include "lwip/netdb.h"
#include "lwip/err.h"
#include "lwip/ip_addr.h"

/* mbedtls includes */
#include "mbedtls/net.h"
#include "mbedtls/ssl.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/debug.h"
/* end of mbedtls includes */

#include "trans_layer.h"
#include "net_layer.h"
#include "tcpip_adapter.h"

// #include <lwip/inet.h>

struct netconn *cx = NULL;

int8_t
establish_conn(int port, char * hostname)
{
    printf("[[[ DEPART ESTABLISH_CONN ]]] \n");
    //struct _ip_addr local_ip;
    //struct _ip_addr remote_ip;
    //int8_t rc;
    ip_addr_t local_ip;
    ip_addr_t remote_ip;
    tcpip_adapter_ip_info_t ip_info;
///////////////////////////////////////////////////////////////////////////////////////////
    int rc2, rc3;
    tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_STA, &ip_info);

    cx = netconn_new ( NETCONN_TCP );

    if ( cx == NULL ) {
      printf("cx = null\n");
    }

    printf("[[[[[[ ip_info ]]]]]]:  %s\n", ip4addr_ntoa(&ip_info.ip));

    //local_ip = inet_addr(hostname); // Pas bon car ça ne renvoie pas de type u32_t demandé par lwip/ip_addr.h !!!!!!!!!
    local_ip.u_addr.ip4 = ip_info.ip;
    printf("[[[[[[ local_ip ]]]]]]:  %s\n", ip4addr_ntoa(&local_ip.u_addr.ip4));
    //local_ip.u_addr.ip4.addr = * hostname;

    netconn_bind ( cx, &local_ip, 0);

    //  remote_ip.addr = ENOSYS;  // or netconn_gethostbyname ()
    /* remote_ip.u_addr.ip4.addr = hostname;
    test2 = netconn_gethostbyname ("nom_du_serveur", &remote_ip ); */

    rc2 = netconn_gethostbyname(hostname,&remote_ip);

    rc3 = netconn_connect ( cx, &remote_ip, port );

    if ( rc2 != ERR_OK )
    {
          printf("[[[[[[ gethostbyname error ]]]]]]\n");
          netconn_delete ( cx );
    } else {
          printf("[[[[[[ remote_ip ]]]]]]:  %s\n", ip4addr_ntoa(&remote_ip.u_addr.ip4));
    }

    if (rc3 != ERR_OK ){
          printf("[[[[[[ netconn_connect error ]]]]]]\n");
    } else {
          printf("[[[[[[ netconn_connect SUCCESS ]]]]]]\n");
    }
//////////////////////////////////////////////////////////////////////////////////////

    return rc3;
}

int8_t
trans_send(const void *app_paquet)
{
    int8_t rc;

///////////////////// fait
    rc = netconn_write(cx,(char*)app_paquet, strlen((char*)app_paquet)+1, NETCONN_NOFLAG);
    // TODO switch whether tls is enabled or not and choose the right function
    // in order to send data over the created socket!

    //debug
    if (rc == ERR_OK){
      printf("-------------> netconn_write OK !\n");
      rc = 0;
    } else {
      printf("------------------------------> ERROR netconn_write\n");
      rc = -1;
    }

    return rc;
}

int8_t
transport_layer_start(enum trans_protocols trans_proto, int ssl_flag)
{
    int8_t rc;

    switch (trans_proto) {
        case TCP:
            printf("[[[ TRANSPORT_LAYER_START ]]] \n");
            rc = establish_conn(3000 ,"romain-T102HA");
            break;
        case UDP:
            rc = ENOSYS;
            break;
        default:
            rc = ENOSYS;
            break;
    }

    return rc;
}


int8_t
establish_secure_conn(const char *cert)
{
    int8_t rc;

    rc = ENOSYS;

    return rc;
}
