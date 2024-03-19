include config.mk

cflags := -Isrc/brogue -Isrc/platform -Isrc/variants -std=c99 \
	-Wall -Wpedantic -Werror=implicit -Wno-parentheses -Wno-unused-result \
	-Wformat -Werror=format-security -Wformat-overflow=0 -Wmissing-prototypes
libs := -lm
cppflags := -DDATADIR=$(DATADIR)

ifeq ($(SYSTEM),MIYOO)
sources := src/brogue/GlobalsBase.c src/brogue/Architect.c src/brogue/IO.c src/brogue/PowerTables.c src/brogue/Buttons.c src/brogue/Items.c src/brogue/Recordings.c src/brogue/Combat.c src/brogue/Light.c src/brogue/RogueMain.c src/brogue/Dijkstra.c src/brogue/MainMenu.c src/brogue/SeedCatalog.c src/brogue/Math.c src/brogue/Time.c src/brogue/Globals.c src/brogue/Monsters.c src/brogue/Utilities.c src/brogue/Grid.c src/brogue/Movement.c src/brogue/Wizard.c $(wildcard src/variants/*.c) $(addprefix src/platform/,main.c platformdependent.c null-platform.c)
else
sources := $(wildcard src/brogue/*.c) $(wildcard src/variants/*.c) $(addprefix src/platform/,main.c platformdependent.c null-platform.c)
endif
objects :=

ifeq ($(SYSTEM),WINDOWS)
objects += windows/icon.o
.exe := .exe
endif

ifeq ($(SYSTEM),OS2)
cflags += -march=pentium4 -mtune=pentium4 -Zmt -Wno-narrowing
cppflags += -D__ST_MT_ERRNO__
libs += -lcx -lc -Zomf -Zbin-files -Zargs-wild -Zargs-resp -Zhigh-mem -Zstack 8000
objects += os2/icon.res os2/brogue.lib
.exe := .exe
endif

ifeq ($(SYSTEM),MIYOO)
cflags += -fPIC -fpermissive -DMIYOO -I../sdl2_miyoo/include
#-Os -marm -mtune=cortex-a7 -march=armv7ve+simd -mfpu=neon-vfpv4 -mfloat-abi=hard -ffunction-sections -fdata-sections
CC = arm-linux-gnueabihf-g++
STRIP = arm-linux-gnueabihf-strip
libs += -L../sdl2_miyoo/libs -lSDL2 -lEGL -lGLESv2 -lbz2
endif

ifeq ($(RELEASE),YES)
extra_version :=
else
extra_version := $(shell bash tools/git-extra-version)
endif

ifeq ($(TERMINAL),YES)
sources += $(addprefix src/platform/,curses-platform.c term.c)
cppflags += -DBROGUE_CURSES
libs += -lncurses
ifeq ($(SYSTEM),OS2)
libs += -ltinfo
endif
endif

ifeq ($(GRAPHICS),YES)
sources += $(addprefix src/platform/,sdl2-platform.c tiles.c)
cppflags += -DBROGUE_SDL
ifeq ($(SYSTEM),MIYOO)
libs += -lSDL2_image
else
cflags += $(shell $(SDL_CONFIG) --cflags)
libs += $(shell $(SDL_CONFIG) --libs) -lSDL2_image
endif
endif

ifeq ($(WEBBROGUE),YES)
sources += $(addprefix src/platform/,web-platform.c)
cppflags += -DBROGUE_WEB
endif

ifeq ($(RAPIDBROGUE),YES)
cppflags += -DRAPID_BROGUE
endif

ifeq ($(MAC_APP),YES)
cppflags += -DSDL_PATHS
endif

ifeq ($(DEBUG),YES)
cflags += -g -Og
cppflags += -DENABLE_PLAYBACK_SWITCH
else
cflags += -O2
endif

# Add user-provided flags.
cflags += $(CFLAGS)
cppflags += $(CPPFLAGS)
libs += $(LDLIBS)

objects += $(sources:.c=.o)

include make/*.mk
.DEFAULT_GOAL := bin/brogue$(.exe)

clean:
	$(warning 'make clean' is no longer needed in many situations, so is not supported. Use 'make -B' to force rebuild something.)

escape = $(subst ','\'',$(1))
vars:
	mkdir -p vars
# Write the value to a temporary file and only overwrite if it's different.
vars/%: vars FORCE
	@echo '$(call escape,$($*))' > vars/$*.tmp
	@if cmp --quiet vars/$*.tmp vars/$*; then :; else cp vars/$*.tmp vars/$*; fi


FORCE:
