## -*- Makefile del progetto -*-

all: build
	g++ *.o -o main  `pkg-config --cflags --libs allegro-5 allegro_font-5 allegro_image-5 allegro_ttf-5` --std=c++11 -lallegro_dialog
	#-I/usr/include/allegro5 -L/usr/lib -lallegro `pkg-config --cflags --libs allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0`

## Target: build
build:
	g++ *.cpp -c

## Target: clean
clean:
	rm main
	rm *.o
