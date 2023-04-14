
Based on Vult Playground for VCV Rack -- testing Botania DSP within VCV.

Note that we are using fixed float computations here to mimic as close as possible what happens on the RP2040.

# How-to

Define `RACK_DIR` and ponit to Rack SDK folder (to be downloaded separately, tested with 2.1.2 and 2.2.1). Then `make`.

To install, place or link the folder in VCV plugins folder, e.g. on Linux `~/.Rack2/plugins`.

# Dev

Using git submodule to get source from botania dsp (itself using git LFS). Don't forget to clone recursive or init submodule afterwards.

Here we use more vult code to wrap botania for VCV, through `processor_*.vult`.

Check original template for more details about programming https://github.com/vult-dsp/RackPlayground

There are prototype (and often buggy) versions of some modules (see `proto_*.vult`), to be used with [VCV Prototype](https://github.com/VCVRack/VCV-Prototype).

# TODO

- switch back to monophonic synth when polyphony cable is 1? (would need some change in botania DSP)
- setting highest delay on effect, depending on the sample rate, will fail due to overflow with fixed float. Clamp beforehand.
- chord: select a fix shift
- chord: knob for root note

# Changelog

## 2.1.0 (2023-04-12)

- bump DSP, improve init
- adding Trigg module
- adding Clock module
- adding Chord module
- adding Arp module
- adding Gate module

## 2.0.0 (2023-02-04)

- first release for all 3 OS
