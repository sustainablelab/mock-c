#include <glib.h>
#include <stdbool.h>
#include <stdio.h>

int main()
{
    GString *msg = g_string_new("Congratulations! GLib is installed.");
    puts(msg->str);
    g_string_free(msg, true);
    return 0;
}
