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
      MOD_MODE,

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
   // pass all parameters to FM. force: engine will pass params even if not changed, use upon init
   void sendParams(bool force=false);
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
   configParam(SynthFM::MOD_RATIO, -maxRatio, maxRatio, 2.0, "Modulator ratio", "");
   configParam(SynthFM::MOD_MORPH, 0.0, maxMorph, 0.0, "Modulator morph", "");
   configParam(SynthFM::MOD_LEVEL, 0.0, 1.0, 0.1, "Modulator level", " %", 0.0f, 100.0f);
   // due to the position of the switch and label, here 1.0 phase -> "false" in DSP
   configSwitch(SynthFM::MOD_MODE, 0.0, 1.0, 1.0, "Modulator target", {"level", "phase"});

   // carrier adsr
   configParam(SynthFM::CAR_A, 0.0, maxA, 0.0, "Carrier attack", " seconds");
   configParam(SynthFM::CAR_D, 0.0, maxD, 0.0, "Carrier decay", " seconds");
   configParam(SynthFM::CAR_S, 0.0, maxS, 0.5, "Carrier sustain", "");
   configParam(SynthFM::CAR_R, 0.0, maxR, 0.0, "Carrier release", " seconds");
   // carrier ratio and morph
   configParam(SynthFM::CAR_RATIO, -maxRatio, maxRatio, 1.0, "Carrier ratio", "");
   configParam(SynthFM::CAR_MORPH, 0.0, maxMorph, 0.0, "Carrier morph", "");

   // init engine and apply default parameter
   synthFM_Processor_process_init(processor);
   sendParams(true);
}

void SynthFM::sendParams(bool force) {
   synthFM_Processor_setModulatorADSR(processor,
                                      float_to_fix(params[MOD_A].getValue()),
                                      float_to_fix(params[MOD_D].getValue()),
                                      float_to_fix(params[MOD_S].getValue()),
                                      float_to_fix(params[MOD_R].getValue()),
                                      force
                                      );
   synthFM_Processor_setModulatorRatio(processor, float_to_fix(params[MOD_RATIO].getValue()), force);
   synthFM_Processor_setModulatorWavetable(processor, float_to_fix(params[MOD_MORPH].getValue()), force);
   synthFM_Processor_setModulatorLevel(processor, float_to_fix(params[MOD_LEVEL].getValue()), force);
   synthFM_Processor_setModulatorMode(processor, float_to_fix(std::round(params[MOD_MODE].getValue())), force);

   synthFM_Processor_setCarrierADSR(processor,
                                      float_to_fix(params[CAR_A].getValue()),
                                      float_to_fix(params[CAR_D].getValue()),
                                      float_to_fix(params[CAR_S].getValue()),
                                      float_to_fix(params[CAR_R].getValue()),
                                      force
                                      );
   synthFM_Processor_setCarrierRatio(processor, float_to_fix(params[CAR_RATIO].getValue()), force);
   synthFM_Processor_setCarrierWavetable(processor, float_to_fix(params[CAR_MORPH].getValue()), force);
}

void SynthFM::process(const ProcessArgs &args) {
   // update parameters
   synthFM_Processor_setSamplerate(processor, float_to_fix(args.sampleRate/1000.0));
   sendParams();

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

   // from processor -1..1 to max audio voltage range
   outputs[OUT].setVoltage(fix_to_float(synthFM_Processor_process(processor) * 5.0f));
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
      // modulator ratio and morph knobs, plus level and mode
      float ratio_morph_x = 52.062;
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(ratio_morph_x, 128.5-112.286)), module, SynthFM::MOD_RATIO));
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(ratio_morph_x, 128.5-92.893)), module, SynthFM::MOD_MORPH));
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(25.188, 128.5-76.130)), module, SynthFM::MOD_LEVEL));
      addParam(createParamCentered<CKSS>(mm2px(Vec(39.851, 128.5-75.729)), module, SynthFM::MOD_MODE));

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
