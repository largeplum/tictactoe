#include <dbus/dbus-glib.h>

int main(int argc, char **argv)
{
    DBusGConnection *connection;
    GError *error;
    DBusGProxy *proxy;
    char **name_list;
    char **name_list_ptr;
    char *name;

    g_type_init();

    if (argc < 3)
    {
	g_printerr("Usage: %s ADDR KEYNUM\n", argv[0]);
	exit(1);
    }

    error = NULL;
    connection = dbus_g_bus_get(DBUS_BUS_SESSION, &error);
    if(connection == NULL)
    {
	g_printerr("Fialed to open connection to bus: %s\n", error->message);
	g_error_free(error);
	exit(1);
    }

    /* Create a proxy object for the tictactoe */

    proxy = dbus_g_proxy_new_for_name(connection,
				      argv[1],
				      "/com/lp/tictactoe",
				      "com.lp.tictactoe");

    /* Call ListNames method, wait for reply */
    error = NULL;
    if(!dbus_g_proxy_call(proxy, "keypad", &error, 
			  G_TYPE_UINT, atoi(argv[2]), G_TYPE_INVALID,
			  G_TYPE_INVALID))
    {
	/* Just do demonstrate remote exceptions versus regular GError */
	if(error->domain == DBUS_GERROR && 
	   error->code == DBUS_GERROR_REMOTE_EXCEPTION)
	{
	    g_printerr("Caught remote method exception %s: %s",
		       dbus_g_error_get_name(error),
		       error->message);
	}
	else
	{
	    g_printerr("Error: %s\n", error->message);
	}
	g_error_free(error);
	exit(1);
    }

    g_object_unref(proxy);

    return 0;
}
