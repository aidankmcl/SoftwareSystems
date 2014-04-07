metakafka: glibPrac.c
	gcc -o glibPrac glibPrac.c `pkg-config --libs --cflags glib-2.0`