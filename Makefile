
# Note: at the moment only take one file for each vult target, waiting for group target and make >= 4.3

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

VULT_EFFECTS_SRC = vult/processor_reverb.vult vult/processor_svf.vult vult/processor_saturator.vult
#VULT_EFFECTS_ENGINE_OUT = $(wildcard src/engine_effects.*)
VULT_EFFECTS_ENGINE_OUT = src/engine_effects.h
$(VULT_EFFECTS_ENGINE_OUT): $(VULT_EFFECTS_SRC)
	$(VULT_CMD) -ccode $(VULT_EFFECTS_SRC) -i botania/vult -i botania/vult/buffer_medium -o src/engine_effects -real fixed

# variants with extra buffer
VULT_EFFECTS_EXTRA_SRC =  vult/processor_combFF.vult vult/processor_combFB.vult vult/processor_allpass.vult 
#VULT_EFFECTS_EXTRA_ENGINE_OUT = $(wildcard src/engine_effects_extra.*)
VULT_EFFECTS_EXTRA_ENGINE_OUT = src/engine_effects_extra.h
$(VULT_EFFECTS_EXTRA_ENGINE_OUT): $(VULT_EFFECTS_EXTRA_SRC)
	$(VULT_CMD) -ccode $(VULT_EFFECTS_EXTRA_SRC) -i botania/vult -i botania/vult/buffer_extra_large -o src/engine_effects_extra -output-prefix extra_ -real fixed

# here as well using some sort of template between synths
VULT_SYNTH_FM_SRC = vult/synth_FM/processor.vult 
#VULT_SYNTH_FM_ENGINE_OUT = $(wildcard src/engine_synthFM.*)
VULT_SYNTH_FM_ENGINE_OUT = src/engine_synthFM.h
$(VULT_SYNTH_FM_ENGINE_OUT): $(VULT_SYNTH_FM_SRC)
	$(VULT_CMD) -ccode $(VULT_SYNTH_FM_SRC) -i botania/vult -i botania/vult/synth_FMalt -i botania/vult/buffer_medium -o src/engine_synthFM -output-prefix synthFM_ -real fixed

VULT_SYNTH_SAMPLER_SRC = vult/synth_sampler/processor.vult 
#VULT_SYNTH_SAMPLER_ENGINE_OUT = $(wildcard src/engine_synthSampler*)
VULT_SYNTH_SAMPLER_ENGINE_OUT = src/engine_synthSampler.h
$(VULT_SYNTH_SAMPLER_ENGINE_OUT): $(VULT_SYNTH_SAMPLER_SRC)
	./make_vult_sampler.sh $(VULT_CMD) $(VULT_SYNTH_SAMPLER_SRC)

VULT_SYNTH_DRUMMER_SRC = vult/synth_drummer/processor.vult 
#VULT_SYNTH_DRUMMER_ENGINE_OUT = $(wildcard src/engine_synthDrummer*)
VULT_SYNTH_DRUMMER_ENGINE_OUT = src/engine_synthDrummer.h
$(VULT_SYNTH_DRUMMER_ENGINE_OUT): $(VULT_SYNTH_DRUMMER_SRC)
	./make_vult_drummer.sh $(VULT_CMD) $(VULT_SYNTH_DRUMMER_SRC)

VULT_UTILS_SRC = vult/processor_trigg.vult vult/processor_clock.vult vult/processor_chord.vult vult/processor_arp.vult vult/processor_gate.vult 
#VULT_UTILS_ENGINE_OUT = $(wildcard src/engine_utils.*)
VULT_UTILS_ENGINE_OUT = src/engine_utils.h
$(VULT_UTILS_ENGINE_OUT): $(VULT_UTILS_SRC)
	$(VULT_CMD) -ccode $(VULT_UTILS_SRC) -i botania/vult -o src/engine_utils -real fixed 


vult: $(VULT_EFFECTS_ENGINE_OUT) $(VULT_EFFECTS_EXTRA_ENGINE_OUT) $(VULT_SYNTH_FM_ENGINE_OUT) $(VULT_SYNTH_DRUMMER_ENGINE_OUT) $(VULT_SYNTH_SAMPLER_ENGINE_OUT) $(VULT_UTILS_ENGINE_OUT)

# Include the Rack plugin Makefile framework
include $(RACK_DIR)/plugin.mk

