#include <stdio.h>
#include <stdlib.h>

#include <net/if.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <linux/if_packet.h>


int cria_raw_socket(char* nome_interface_rede);