
Based on Vult Playground for VCV Rack -- testing Botania DSP within VCV.

Note that we are using fixed float computations here to mimic as close as possible what happens on the RP2040.

# How-to

Define `RACK_DIR` and ponit to Rack SDK folder (to be downloaded separately). Then `make`.

To install, place or link the folder in VCV plugins folder, e.g. on Linux `~/.Rack2/plugins`.

# Dev

Using git submodule to get source from botania dsp (itself using git LFS). Don't forget to clone recursive or init submodule afterwards.

Here we use more vult code to wrap botania for VCV, through `processor_*.vult`.

Check original template for more details about programming https://github.com/vult-dsp/RackPlayground

# TODO

- unused v in ADSR
- take into account change in sampling rate
- switch back to monophonic synth when polyphony cable is 1? (would need some change in botania DSP)
