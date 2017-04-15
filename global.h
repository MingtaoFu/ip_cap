#include <gtk/gtk.h>
#include <pcap.h>
#include <netinet/in.h>

GtkWidget *view;
GtkListStore *store;
GtkTreeIter iter;

struct ether_header {
    u_int8_t ether_dhost[6];
    /* 目的以太网地址 */
    u_int8_t ether_shost[6];
    /* 源以太网地址 */
    u_int16_t ether_type;
    /* 以太网类型 */
};
/* 下面是IP地址格式 */
typedef u_int32_t in_addr_t;

/*
-----------------------------------------------------------------------------------------------------------------------
下面是IP协议格式
-----------------------------------------------------------------------------------------------------------------------
 */
struct ip_header {
#ifdef WORDS_BIGENDIAN
    u_int8_t ip_version: 4,  /* IP协议版本 */
    ip_header_length: 4; /* IP协议首部长度 */
#else
    u_int8_t ip_header_length: 4, ip_version: 4;
#endif
    u_int8_t ip_tos;
    /* TOS服务质量 */
    u_int16_t ip_length;
    /* 总长度 */
    u_int16_t ip_id;
    /* 标识 */
    u_int16_t ip_off;
    /* 偏移 */
    u_int8_t ip_ttl;
    /* 生存时间 */
    u_int8_t ip_protocol;
    /* 协议类型 */
    u_int16_t ip_checksum;
    /* 校验和 */
    struct in_addr ip_source_address;
    /* 源IP地址 */
    struct in_addr ip_destination_address;
    /* 目的IP地址 */
};

void my_packet_handler(u_char*, const struct pcap_pkthdr*, const u_char*);
void add_data(GtkListStore*, char* source_ip, char* dest_ip, long len, ...);
GtkWidget * create_view_and_model (void);
