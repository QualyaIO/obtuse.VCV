#include "plugin.hpp"
#include "engine_synthFM.h"

struct SynthFM : Module {

   enum ParamIds {
      MOD_A,
      MOD_D,
      MOD_S,
      MOD_R,
      MOD_RATIO,
      MOD_MORPH,
      MOD_LEVEL,

      CAR_A,
      CAR_D,
      CAR_S,
      CAR_R,
      CAR_RATIO,
      CAR_MORPH,

      NUM_PARAMS
   };
   enum InputIds {
      VOCT,
      GATE,
      VEL,

      NUM_INPUTS
   };
   enum OutputIds {
      OUT,

      NUM_OUTPUTS
   };
   enum LightIds { NUM_LIGHTS };

   synthFM_Processor_process_type processor;

   SynthFM();
   void process(const ProcessArgs &args) override;
};

SynthFM::SynthFM() {
   config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

   // will config all parameters, setting as default the same as with botania DSP default (at least at the time of writing)
   // TODO: ensure safety check in DSP
   
   // retrieve upper level for ADSR
   // note: 3-steps to get multiple returns from vult (need type, call function, get values)
   synthFM_ADSR_getMaxValues_type adsr;
   synthFM_ADSR_getMaxValues(adsr);
   float maxA = fix_to_float(synthFM_ADSR_getMaxValues_ret_0(adsr)); 
   float maxD = fix_to_float(synthFM_ADSR_getMaxValues_ret_1(adsr)); 
   float maxS = fix_to_float(synthFM_ADSR_getMaxValues_ret_2(adsr)); 
   float maxR = fix_to_float(synthFM_ADSR_getMaxValues_ret_3(adsr)); 
   // also max number of wavetable to know up to what we can morph
   float maxMorph = synthFM_Wavetable_getNbWavetables();
   // quite arbitrary, actually. Nyquist will limit in practice (?)
   float maxRatio = 30.0;

   // modulator adsr
   configParam(SynthFM::MOD_A, 0.0, maxA, 0.0, "Modulator attack", " seconds");
   configParam(SynthFM::MOD_D, 0.0, maxD, 0.0, "Modulator decay", " seconds");
   configParam(SynthFM::MOD_S, 0.0, maxS, 0.5, "Modulator sustain", "");
   configParam(SynthFM::MOD_R, 0.0, maxR, 0.0, "Modulator release", " seconds");
   // modulator ratio and morph, plus level
   configParam(SynthFM::MOD_RATIO, 0.0, maxRatio, 2.0, "Modulator ratio", "");
   configParam(SynthFM::MOD_MORPH, 0.0, maxMorph, 0.0, "Modulator morph", "");
   configParam(SynthFM::MOD_LEVEL, 0.0, 1.0, 0.1, "Modulator level", " %", 0.0f, 100.0f);
   // carrier adsr
   configParam(SynthFM::CAR_A, 0.0, maxA, 0.0, "Carrier attack", " seconds");
   configParam(SynthFM::CAR_D, 0.0, maxD, 0.0, "Carrier decay", " seconds");
   configParam(SynthFM::CAR_S, 0.0, maxS, 0.5, "Carrier sustain", "");
   configParam(SynthFM::CAR_R, 0.0, maxR, 0.0, "Carrier release", " seconds");
   // carrier ratio and morph
   configParam(SynthFM::CAR_RATIO, 0.0, maxRatio, 1.0, "Carrier ratio", "");
   configParam(SynthFM::CAR_MORPH, 0.0, maxMorph, 0.0, "Carrier morph", "");

   synthFM_Processor_process_init(processor);
}

void SynthFM::process(const ProcessArgs &args) {
   // update parameters
   synthFM_Processor_setSamplerate(processor, float_to_fix(args.sampleRate/1000.0));

   // retrieve current max number of channels for gate and v/oct
   int channels =
      std::max(
               std::max(inputs[GATE].getChannels(), inputs[VOCT].getChannels()),
               inputs[VEL].getChannels());
   synthFM_Processor_nbCables(processor, channels);
   // pass each note to the synth
   for (int c = 0; c < channels; c++) {
      // Reads all the input values and normalizes the values
      float voct = inputs[VOCT].getPolyVoltage(c) / 10.0f;
      float gate = inputs[GATE].getPolyVoltage(c) / 10.0f;
      float vel = inputs[VEL].getPolyVoltage(c) / 10.0f;
      synthFM_Processor_setNote(processor, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
   }

   // Reads all the parameters and sets them.
   // The parameters could be set at a lower rate if needed
   /* {
      float knob1 = params[KNOB1].getValue();
      float knob2 = params[KNOB2].getValue();
      float knob3 = params[KNOB3].getValue();
      float knob4 = params[KNOB4].getValue();
      float mod1 = params[MOD1].getValue();
      float mod2 = params[MOD2].getValue();
      float mod3 = params[MOD3].getValue();
      float mod4 = params[MOD4].getValue();

      synthFM_Processor_setParam1(processor, knob1, mod1, mod_in1);
      synthFM_Processor_setParam2(processor, knob2, mod2, mod_in2);
      synthFM_Processor_setParam3(processor, knob3, mod3, mod_in3);
      synthFM_Processor_setParam4(processor, knob4, mod4, mod_in4);
   }
   */

   // from processor -1..1 to max voltage range
   outputs[OUT].setVoltage(fix_to_float(synthFM_Processor_process(processor) * 10.0f));
}
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

struct SynthFMWidget : ModuleWidget {
   SynthFMWidget(SynthFM *module) {
      setModule(module);

      setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SynthFM.svg")));

      // modulator ADSR sliders
      // here and after: use heihgt of canvas since my inskscape has Y origin flow lower left
      float mod_adsr_y = 128.5-99.2;
      addParam(createParamCentered<LEDSliderPink>(mm2px(Vec(10.934, mod_adsr_y)), module, SynthFM::MOD_A));
      addParam(createParamCentered<LEDSliderPink>(mm2px(Vec(19.972, mod_adsr_y)), module, SynthFM::MOD_D));
      addParam(createParamCentered<LEDSliderPink>(mm2px(Vec(29.009, mod_adsr_y)), module, SynthFM::MOD_S));
      addParam(createParamCentered<LEDSliderPink>(mm2px(Vec(38.046, mod_adsr_y)), module, SynthFM::MOD_R));
      // modulator ratio and morph knobs, plus level
      float ratio_morph_x = 52.062;
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(ratio_morph_x, 128.5-112.286)), module, SynthFM::MOD_RATIO));
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(ratio_morph_x, 128.5-92.893)), module, SynthFM::MOD_MORPH));
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(30.480, 128.5-75.790)), module, SynthFM::MOD_LEVEL));

      // carrier ADSR sliders
      float car_adsr_y = 128.5-43.637;
      addParam(createParamCentered<LEDSliderPink>(mm2px(Vec(10.934, car_adsr_y)), module, SynthFM::CAR_A));
      addParam(createParamCentered<LEDSliderPink>(mm2px(Vec(19.972, car_adsr_y)), module, SynthFM::CAR_D));
      addParam(createParamCentered<LEDSliderPink>(mm2px(Vec(29.009, car_adsr_y)), module, SynthFM::CAR_S));
      addParam(createParamCentered<LEDSliderPink>(mm2px(Vec(38.046, car_adsr_y)), module, SynthFM::CAR_R));
      // carrier ratio and morph knobs
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(ratio_morph_x, 128.5-56.723)), module, SynthFM::CAR_RATIO));
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(ratio_morph_x, 128.5-37.330)), module, SynthFM::CAR_MORPH));

      // input: v/oct, gate, velocity
      float port_y = 128.5 - 14.625;
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.147, port_y)), module, SynthFM::VOCT));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(23.369, port_y)), module, SynthFM::GATE));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(37.638, port_y)), module, SynthFM::VEL));

      addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(51.86, port_y)), module, SynthFM::OUT));
   }
};

Model *synthFM = createModel<SynthFM, SynthFMWidget>("BotaniaSynthFM");
