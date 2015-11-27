#include <xcb/xcb.h>

xcb_connection_t *conn;

int main(int argc, char* argv[]) {
    int ret = 0;

    conn = xcb_connect(NULL, NULL);
    if(!conn || xcb_connection_has_error(conn))
            ret = 1;

    if(conn)
        xcb_disconnect(conn);

    return ret;
}
