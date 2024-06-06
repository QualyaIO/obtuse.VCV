#pragma once
#include <rack.hpp>

using namespace rack;

// Declare the Plugin, defined in plugin.cpp
extern Plugin *pluginInstance;

// Declare each Model, defined in each module source file
extern Model *effectReverb;
extern Model *effectSVF;
extern Model *effectCombFF;
extern Model *effectCombFB;
extern Model *effectAllpass;
extern Model *effectSaturator;
extern Model *synthFM;
extern Model *synthSampler;
extern Model *synthDrummer;
extern Model *utilTrigg;
extern Model *utilClock;
extern Model *utilChord;
extern Model *utilArp;
extern Model *utilGate;

// obtuse rblue
static const NVGcolor SCHEME_OBLUE = nvgRGB(0, 217, 217);
static const NVGcolor SCHEME_ORED = nvgRGB(244, 0, 78);

template <typename TBase = GrayModuleLightWidget>
struct TOblueLight : TBase {
    TOblueLight() {
        this->addBaseColor(SCHEME_OBLUE);
    }
};
using OblueLight = TOblueLight<>;

template <typename TBase = GrayModuleLightWidget>
struct TOredLight : TBase {
    TOredLight() {
        this->addBaseColor(SCHEME_ORED);
    }
};
using OredLight = TRedLight<>;


struct LEDSliderOblue : VCVLightSlider<OblueLight> {};
struct LEDSliderOred : VCVLightSlider<OredLight> {};
