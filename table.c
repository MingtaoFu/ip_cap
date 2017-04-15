#include <string.h>
#include "global.h"

enum {
    COL_SOURCE = 0,
    COL_DEST,
    COL_DATA,
    NUM_COLS
};

void add_data(GtkListStore* store, char* source_ip, char* dest_ip, long len, ...) {
    gchar *col0, *col1;
    glong col2;

    va_list ap;
    gboolean b = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(store), &iter);
    int has = 0;
    while(b) {
        gtk_tree_model_get(GTK_TREE_MODEL(store), &iter, 0, &col0 , -1);
        gtk_tree_model_get(GTK_TREE_MODEL(store), &iter, 1, &col1 , -1);
        if((!strcmp(source_ip, col0)) && (!strcmp(dest_ip, col1))) {
            gtk_tree_model_get(GTK_TREE_MODEL(store), &iter, 2, &col2 , -1);
            gtk_list_store_set(store, &iter,
                               0,source_ip,
                               1,  dest_ip,
                               2, len + col2
                                  -1);
            has = 1;
            break;
        }
        b = gtk_tree_model_iter_next(GTK_TREE_MODEL(store), &iter);
    }
    if (has == 0) {
        //printf("\n\n\n\n----------------------------\n\n\n\n");
        gtk_list_store_append (store, &iter);
        gtk_list_store_set (store, &iter,
                            0,source_ip,
                            1,  dest_ip,
                            2, len,
                            -1);
        //gtk_tree_view_set_model (GTK_TREE_VIEW (view), GTK_TREE_MODEL(store));

    }
}

static GtkTreeModel *
create_and_fill_model (void) {


    store = gtk_list_store_new (NUM_COLS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_UINT);


    /* Append a row and fill in some data */
//    gtk_list_store_append (store, &iter);
//    gtk_list_store_set (store, &iter,
//                        COL_SOURCE, "Heinz El-Mann",
//                        COL_DEST, "dsa",
//                        COL_DATA, "dsa",
//                        -1);
//
//
//    /* append another row and fill in some data */
//    gtk_list_store_append (store, &iter);
//    gtk_list_store_set (store, &iter,
//                        COL_SOURCE, "Jane Doe",
//                        COL_DEST, "asa",
//                        COL_DATA, "dsa",
//                        -1);
//
//    /* ... and a third row */
//    gtk_list_store_append (store, &iter);
//    gtk_list_store_set (store, &iter,
//                        COL_SOURCE, "Joe Bungop",
//                        COL_DEST, "dsa",
//                        COL_DATA, "dsa",
//                        -1);


    return GTK_TREE_MODEL (store);
}
GtkWidget* create_view_and_model (void) {
    GtkCellRenderer     *renderer;
    GtkTreeModel        *model;
    GtkWidget           *view;

    view = gtk_tree_view_new ();

    /* --- Column #1 --- */
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                                 -1,
                                                 "source ip",
                                                 renderer,
                                                 "text", COL_SOURCE,
                                                 NULL);

    /* --- Column #2 --- */
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                                 -1,
                                                 "dest ip",
                                                 renderer,
                                                 "text", COL_DEST,
                                                 NULL);

    /* --- Column #3 --- */
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                                 -1,
                                                 "data",
                                                 renderer,
                                                 "text", COL_DATA,
                                                 NULL);


    model = create_and_fill_model ();

    gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);

    /* The tree view has acquired its own reference to the
     *  model, so we can drop ours. That way the model will
     *  be freed automatically when the tree view is destroyed */
    //g_object_unref (model);
    return view;
}
