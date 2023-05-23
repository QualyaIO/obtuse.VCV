
Based on Vult Playground for VCV Rack -- testing Botania DSP within VCV.

Note that we are using fixed float computations here to mimic as close as possible what happens on the RP2040.

# How-to

Define `RACK_DIR` and ponit to Rack SDK folder (to be downloaded separately, tested with 2.1.2 and 2.2.1). Then `make`. Required bash >= 4.

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
- comb, allpass, reverb: fix arifacts upon launching scene that is playing
- sampler: better way to enforce loop size

# Changelog

## 2.3.0 (2023-05-23)

- bump DSP, some fixes, adding pitch bend and retrigger
- drummer: add pitch bend
- FM: add pitch bend and retrigger

## 2.2.2 (2023-05-10)

- clock: adding an output for ticks

## 2.2.1 (2023-04-27)

- bump DSP, fix chord shift and trigg, init correctly buffers to avoid artifacts upon launch

## 2.2.0 (2023-04-26)

- bump DSP, adding new samples and drum kits
- sampler: select sample, option to set loop manually
- drummer: select kit

## 2.1.0 (2023-04-12)

- bump DSP, improve init
- adding Trigg module
- adding Clock module
- adding Chord module
- adding Arp module
- adding Gate module

## 2.0.0 (2023-02-04)

- first release for all 3 OS
