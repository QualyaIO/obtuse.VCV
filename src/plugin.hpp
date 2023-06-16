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

// ullo pink
static const NVGcolor SCHEME_PINK = nvgRGB(255, 10, 33);

template <typename TBase = GrayModuleLightWidget>
struct TPinkLight : TBase {
    TPinkLight() {
        this->addBaseColor(SCHEME_PINK);
    }
};
using PinkLight = TPinkLight<>;

struct LEDSliderPink : VCVLightSlider<PinkLight> {};
