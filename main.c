#include <stdio.h>
#include <pcap.h>
#include <stdlib.h>
#include "global.h"

static void* cap_main(void *a) {
    char dev[] = "wlp4s0";
    pcap_t *handle;
    char error_buffer[PCAP_ERRBUF_SIZE];
    struct bpf_program filter;
    char filter_exp[] = "ip";
    bpf_u_int32 subnet_mask, ip;

    if (pcap_lookupnet(dev, &ip, &subnet_mask, error_buffer) == -1) {
        printf("Could not get information for device: %s\n", dev);
        ip = 0;
        subnet_mask = 0;
    }
    handle = pcap_open_live(dev, BUFSIZ, 1, 1000, error_buffer);
    if (handle == NULL) {
        printf("Could not open %s - %s\n", dev, error_buffer);
    }
    if (pcap_compile(handle, &filter, filter_exp, 0, ip) == -1) {
        printf("Bad filter - %s\n", pcap_geterr(handle));
    }
    if (pcap_setfilter(handle, &filter) == -1) {
        printf("Error setting filter - %s\n", pcap_geterr(handle));
    }

    pcap_loop(handle, 0, my_packet_handler, NULL);

    pcap_close(handle);
}

void activate (GtkApplication* app, gpointer user_data) {
//    setInterface(app, user_data);
    pthread_t thread1;
    pthread_create(&thread1, NULL, cap_main, (void *) "da");

    GtkWidget *window;
    window = gtk_application_window_new (app);
    g_signal_connect (window, "delete_event", gtk_main_quit, NULL); /* dirty */
    view = create_view_and_model ();

    gtk_container_add (GTK_CONTAINER (window), view);

    gtk_widget_show_all (window);

}

int main(int argc, char **argv) {
    GtkApplication *app;
    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    g_application_run (G_APPLICATION (app), argc, argv);
    gtk_main ();
    return 0;
}
