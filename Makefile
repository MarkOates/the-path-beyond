



# My Windows Setup:
# LIBS_ROOT=E:
# OPENGL_LIB=-lopengl32
# EXE_EXTENSION=.exe

# My OSX Setup:
LIBS_ROOT=/Users/markoates/Repos
OPENGL_LIB=-framework OpenGL
EXE_EXTENSION=




ALLEGRO_DIR=$(LIBS_ROOT)/allegro5
ALLEGRO_LIBS=-lallegro_color -lallegro_font -lallegro_ttf -lallegro_dialog -lallegro_audio -lallegro_acodec -lallegro_primitives -lallegro_image -lallegro_main -lallegro

ALLEGRO_FLARE_DIR=$(LIBS_ROOT)/allegro_flare
ALLEGRO_FLARE_LIB=allegro_flare-0.8.9wip
# ALLEGRO_FLARE_LIB=allegro_flare-0.8.7wip




all: bin/game$(EXE_EXTENSION)



SOURCES := $(shell find src -name '*.cpp')
OBJECTS := $(SOURCES:src/%.cpp=obj/%.o)
REQUIRED_DIRECTORIES := $(dir $(OBJECTS))



bin/game$(EXE_EXTENSION): $(OBJECTS) obj/game.o
	g++ $^ -o bin/game $(OPENGL_LIB) -l$(ALLEGRO_FLARE_LIB) $(ALLEGRO_LIBS) -L$(ALLEGRO_FLARE_DIR)/lib -L$(ALLEGRO_DIR)/build/lib



obj/%.o: src/%.cpp | required_obj_dirs
	g++ -c -std=gnu++11 $< -o $@ -I$(ALLEGRO_FLARE_DIR)/include -I$(ALLEGRO_DIR)/include -I./include



required_obj_dirs:
	@mkdir -p $(REQUIRED_DIRECTORIES)



obj/game.o: main.cpp include/style_assets.hpp include/logging.hpp start_screen.hpp script.hpp target_id.hpp navigation.hpp world_render.hpp game/project.hpp game/script_helper.hpp game/load_game_scripts.hpp $(wildcard game/scripts/*)
	g++ -o $@ -c -std=gnu++11 $< -I$(ALLEGRO_FLARE_DIR)/include -I$(ALLEGRO_DIR)/include -I./include



clean:
	-rm $(OBJECTS)
	-rm bin/game




