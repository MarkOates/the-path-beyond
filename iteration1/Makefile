



# My Windows Setup:
# LIBS_ROOT=E:
# OPENGL_LIB=-lopengl32
# EXE_EXTENSION=.exe

# My OSX Setup:
LIBS_ROOT=/Users/markoates/Repos
OPENGL_LIB=-framework OpenGL
EXE_EXTENSION=




ALLEGRO_DIR=$(LIBS_ROOT)/allegro5/build
ALLEGRO_LIBS=-lallegro_color -lallegro_font -lallegro_ttf -lallegro_dialog -lallegro_audio -lallegro_acodec -lallegro_primitives -lallegro_image -lallegro_main -lallegro

ALLEGRO_FLARE_DIR=$(LIBS_ROOT)/allegro_flare
ALLEGRO_FLARE_LIB=allegro_flare-0.8.7wip




all: bin/game$(EXE_EXTENSION)




bin/game$(EXE_EXTENSION): obj/game.o
		g++ obj/game.o -o bin/game -l$(ALLEGRO_FLARE_LIB) $(ALLEGRO_LIBS) -L$(ALLEGRO_FLARE_DIR)/lib -L$(ALLEGRO_DIR)/lib

obj/game.o: game.cpp inventory.hpp start_screen.hpp navigation.hpp
		g++ -o $@ -c -std=gnu++11 $< -I$(ALLEGRO_FLARE_DIR)/include -I$(ALLEGRO_DIR)/include



