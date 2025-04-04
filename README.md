
Modules enabling the use of [Obtuse DSP](https://github.com/QualyaIO/obtuse.DSP) within VCV.

Note that we are using fixed float computations here to mimic as close as possible what happens on default DSP installations, e.g. on MCU such as RP2040.

# How-to

Define `RACK_DIR` and ponit to Rack SDK folder (to be downloaded separately, tested with 2.1.2 and 2.2.1). Then `make`. Required bash >= 4.

To install, place or link the folder in VCV plugins folder, e.g. on Linux `~/.Rack2/plugins`.

# Dev

Using git submodule to get source from obtuse DSP (itself using git LFS). Don't forget to clone recursive or init submodule afterwards.

Here we use more vult code to wrap obtuse for VCV, through `processor_*.vult`.

Check original template for more details about programming: https://github.com/vult-dsp/RackPlayground

There are prototype (and often buggy) versions of some modules (see `proto_*.vult`), to be used with [VCV Prototype](https://github.com/VCVRack/VCV-Prototype).

# TODO

- switch back to monophonic synth when polyphony cable is 1? (would need some change in the DSP)
- setting highest delay on effect, depending on the sample rate, will fail due to overflow with fixed float. Clamp beforehand.
- chord: select a fix shift
- chord: knob for root note
- sampler: better way to enforce loop size
- option to set or save seed where applicable?

# Changelog

## 2.6.0 (2025-02-17)

- [BREAKING] switch name to obtuse
- [BREAKING] bump DSP to v0.2.0, changing behavior for some drumkits and samples (plus reduce artifacts on delay and reverb upon delay change)
- FM: switch to alt version to reduce (by a lot) CPU while tuning wavetables
- Arp, Chord, Clock, Trigg: fix UI (names and discrete values where applicable)
- [BREAKING] Arp, Chord, Trigg: random seed for each instance of the modules

## 2.5.0 (2023-07-21)

- bump DSP
- FM (breaking change): faster ADSR
- FM, sampler: avoid stuck notes with retrigger
- FM: setting min ADSR values
- adding Saturator module

## 2.4.0 (2023-06-03)

- bump DSP, new FM features, fixes for clock
- FM: new band-limited waveforms
- FM (breaking change): change phase of most wavetables, improve transition

## 2.3.1 (2023-05-24)

- FM, sampler: hotfix for retrigger

## 2.3.0 (2023-05-23)

- bump DSP, some fixes, adding pitch bend and retrigger
- drummer: add pitch bend
- FM: add pitch bend and retrigger
- sampler: add pitch bend and retrigger

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
