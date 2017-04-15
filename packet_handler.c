#include <arpa/inet.h>
#include "global.h"
#include <string.h>

void ip_protocol_packet_callback(
        u_char *argument,
        const struct pcap_pkthdr *packet_header,
        const u_char *packet_content
) {
    struct ip_header *ip_protocol;
    /* IP协议变量 */
    u_int header_length;
    /* 长度 */
    u_int offset;
    /* 偏移 */
    u_char tos;
    /* 服务质量 */
    u_int16_t checksum;
    /* 校验和 */
    ip_protocol = (struct ip_header*)(packet_content + 14);
    /* 获得IP协议数据内容，去掉以太网头 */
    checksum = ntohs(ip_protocol->ip_checksum);
    /* 获得校验和 */
    header_length = ip_protocol->ip_header_length *4;
    /* 获得长度 */
    tos = ip_protocol->ip_tos;
    /* 获得TOS */
    offset = ntohs(ip_protocol->ip_off);
    /* 获得偏移量 */
    //printf("----------- IP Protocol  (Network Layer)  -----------\n");
    //printf("IP Version:%d\n", ip_protocol->ip_version);
    //printf("Header length:%d\n", header_length);
    //printf("TOS:%d\n", tos);
    printf("Total length:%d\n", ntohs(ip_protocol->ip_length));



    char source[20], dest[20];
    strcpy(source, inet_ntoa(ip_protocol->ip_source_address));
    strcpy(dest, inet_ntoa(ip_protocol->ip_destination_address));

    add_data(store, source, dest, ntohs(ip_protocol->ip_length));

    ////////////////

    /* 获得总长度 */
    //printf("Identification:%d\n", ntohs(ip_protocol->ip_id));
    /* 获得标识 */
    //printf("Offset:%d\n", (offset &0x1fff) *8);
    //printf("TTL:%d\n", ip_protocol->ip_ttl);
    /* 获得TTL */
    //printf("Protocol:%d\n", ip_protocol->ip_protocol);
    /* 获得协议类型 */
    switch (ip_protocol->ip_protocol) /* 判断协议类型的值 */
    {
        case 6:
     //       printf("The Transport Layer Protocol is TCP\n");
            break;
            /* 如果协议类型为6，表示上层协议为TCP协议 */
        case 17:
     //       printf("The Transport Layer Protocol is UDP\n");
            break;
            /* 如果协议类型为17，表示上层协议为UDP协议 */
        case 1:
      //      printf("The Transport Layer Protocol is ICMP\n");
            break;
            /* 如果协议类型为1，表示传上层协议为ICMP协议 */
        default:
            break;
    }
    //printf("Header checksum:%d\n", checksum);
    printf("Source address:%s\n", inet_ntoa(ip_protocol->ip_source_address));
    /* 获得源IP地址 */
    printf("Destination address:%s\n", inet_ntoa(ip_protocol->ip_destination_address));
    /* 获得目的IP地址 */
}
void my_packet_handler(
        u_char *argument,
        const struct pcap_pkthdr *packet_header,
        const u_char *packet_content
) {

    u_short ethernet_type;
    /* 以太网类型 */
    struct ether_header *ethernet_protocol;
    /* 以太网协议变量 */
    u_char *mac_string;
    static int packet_number = 1;
    //printf("**************************************************\n");
    //printf("The %d IP  packet is captured.\n", packet_number);
    //printf("-------------   Ehternet Protocol (Link Layer)      ------------\n");
    ethernet_protocol = (struct ether_header*)packet_content;
    /* 获得以太网协议数据内容 */
    //printf("Ethernet type is :\n");
    ethernet_type = ntohs(ethernet_protocol->ether_type);
    /* 获得以太网类型 */
    //printf("%04x\n", ethernet_type);
    switch (ethernet_type) /* 判断以太网类型的值 */
    {
        case 0x0800:
      //      printf("The network layer is IP protocol\n");
            break;
            /* 如果为0x0800，表示上层协议为IP协议 */
        case 0x0806:
        //    printf("The network layer is ARP protocol\n");
            break;
            /* 如果为0x0806，表示上层协议为ARP协议 */
        case 0x8035:
         //   printf("The network layer is RARP potocol\n");
            break;
            /* 如果为0x8035，表示上层协议为RARP协议 */
        default:
            break;
    }
    //printf("Mac Source Address is : \n");
    mac_string = ethernet_protocol->ether_shost;
    //printf("%02x:%02x:%02x:%02x:%02x:%02x\n", *mac_string, *(mac_string + 1), *(mac_string + 2), *(mac_string + 3), *(mac_string + 4), *(mac_string + 5));
    /* 获得源以太网地址 */
    //printf("Mac Destination Address is : \n");
    mac_string = ethernet_protocol->ether_dhost;
    //printf("%02x:%02x:%02x:%02x:%02x:%02x\n", *mac_string, *(mac_string + 1), *(mac_string + 2), *(mac_string + 3), *(mac_string + 4), *(mac_string + 5));
    /* 获得目的以太网地址 */
    switch (ethernet_type)
    {
        case 0x0800:
            ip_protocol_packet_callback(argument, packet_header, packet_content);
            break;
            /*
             * 如果上层协议是IP协议，就调用分析IP协议的函数对IP协议进行分析。注意，此时传递的参数，跟回调函数的参数是一样的，表示代表同一个数据包
             */
        default:
            break;
    }
    //printf("**************************************************\n");
    packet_number++;
    return;
}
