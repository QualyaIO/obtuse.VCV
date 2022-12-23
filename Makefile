# If RACK_DIR is not defined when calling the Makefile, default to two directories above
RACK_DIR ?= ../..

# FLAGS will be passed to both the C and C++ compiler
FLAGS +=
CFLAGS +=
CXXFLAGS +=

# Careful about linking to shared libraries, since you can't assume much about the user's environment and library search path.
# Static libraries are fine, but they should be added to this plugin's build system.
LDFLAGS +=

# Add .cpp files to the build
SOURCES += $(wildcard src/*.cpp)

# Add files to the ZIP package when running `make dist`
# The compiled plugin and "plugin.json" are automatically added.
DISTRIBUTABLES += res
DISTRIBUTABLES += $(wildcard LICENSE*)

include $(RACK_DIR)/arch.mk
include vult.inc

VULT_EFFECTS_SRC = src/processor_effects.vult 
VULT_EFFECTS_ENGINE_OUT = $(wildcard src/engine_effects.*)
$(VULT_EFFECTS_ENGINE_OUT): $(VULT_EFFECTS_SRC)
	$(VULT_CMD) -ccode $(VULT_EFFECTS_SRC) -i botania/vult -o src/engine_effects -real fixed

# here as well using some sort of template between synths
VULT_SYNTH_FM_SRC = src/synth_FM/processor.vult 
VULT_SYNTH_FM_ENGINE_OUT = $(wildcard src/engine_synthFM.*)
$(VULT_SYNTH_FM_ENGINE_OUT): $(VULT_SYNTH_FM_SRC)
	$(VULT_CMD) -ccode $(VULT_SYNTH_FM_SRC) -i botania/vult -i botania/vult/synth_FM -o src/engine_synthFM -output-prefix synthFM_ -real fixed

VULT_SYNTH_DRUMMER_SRC = src/synth_drummer/processor.vult 
VULT_SYNTH_DRUMMER_ENGINE_OUT = $(wildcard src/engine_synthDrummer.*)
$(VULT_SYNTH_DRUMMER_ENGINE_OUT): $(VULT_SYNTH_DRUMMER_SRC)
	$(VULT_CMD) -ccode $(VULT_SYNTH_DRUMMER_SRC) -i botania/vult -i botania/vult/synth_drummer -o src/engine_synthDrummer -output-prefix synthDrummer_ -real fixed 


vult: $(VULT_EFFECTS_ENGINE_OUT) $(VULT_SYNTH_FM_ENGINE_OUT) $(VULT_SYNTH_DRUMMER_ENGINE_OUT)

# Include the Rack plugin Makefile framework
include $(RACK_DIR)/plugin.mk



