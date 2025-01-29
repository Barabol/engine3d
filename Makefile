COMPILER = g++
DEBUGGER = gdb

OUTPUT_FILE = test.out
COMPILATION_DIR = ./

FILES := ./src/*/*.cpp ./src/*/*.hpp ./main.cpp ./src/shape/stb_image.h
DEPENDENCIES := -lGL -lGLU -lglut

build:
	$(COMPILER) $(FILES) $(DEPENDENCIES) -o $(OUTPUT_FILE)

run:
	mangohud $(COMPILATION_DIR)$(OUTPUT_FILE)

debug:
	$(COMPILER) $(FILES) $(DEPENDENCIES) -o $(OUTPUT_FILE) -p 
	$(DEBUGGER) $(COMPILATION_DIR)$(OUTPUT_FILE)

