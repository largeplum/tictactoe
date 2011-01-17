CC = gcc -g

ttt_test : ttt_test.o tictactoe.o
	$(CC) -o $@ $^ `pkg-config --libs gtk+-2.0` `pkg-config --libs dbus-glib-1`

tictactoe.o : tictactoe.c tictactoe.h
	$(CC) -c tictactoe.c `pkg-config --cflags gtk+-2.0` `pkg-config --cflags dbus-glib-1`

ttt_test.o : ttt_test.c
	$(CC) -c ttt_test.c `pkg-config --cflags gtk+-2.0 dbus-glib-1`

tictactoe-client : tictactoe-client.o
	$(CC) -o $@ $^ `pkg-config --libs dbus-glib-1`

tictactoe-client.o : tictactoe-client.c
	$(CC) -c $^ `pkg-config --cflags dbus-glib-1`

clean :
	rm ttt_test tictactoe-client *.o
