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
      MOD_IN1,
      MOD_IN2,
      MOD_IN3,
      MOD_IN4,

      GATE,
      VOCT,
      VEL,
      IN4,

      NUM_INPUTS
   };
   enum OutputIds {
      OUT1,
      OUT2,
      OUT3,
      OUT4,

      NUM_OUTPUTS
   };
   enum LightIds { NUM_LIGHTS };

   synthFM_Processor_process_type processor;

   SynthFM();
   void process(const ProcessArgs &args) override;
};

SynthFM::SynthFM() {
   config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

   // modulator adsr
   configParam(SynthFM::MOD_A, 0.0, 1.0, 0.5, "Modulator attack", " %", 0.0f, 100.f);
   configParam(SynthFM::MOD_D, 0.0, 1.0, 0.5, "Modulator decay", " %", 0.0f, 100.f);
   configParam(SynthFM::MOD_S, 0.0, 1.0, 0.5, "Modulator sustain", " %", 0.0f, 100.f);
   configParam(SynthFM::MOD_R, 0.0, 1.0, 0.5, "Modulator release", " %", 0.0f, 100.f);
   // modulator ratio and morph, plus level
   configParam(SynthFM::MOD_RATIO, 0.0, 1.0, 0.5, "Modulator ratio", " %", 0.0f, 100.f);
   configParam(SynthFM::MOD_MORPH, 0.0, 1.0, 0.5, "Modulator morph", " %", 0.0f, 100.f);
   configParam(SynthFM::MOD_LEVEL, 0.0, 1.0, 0.5, "Modulator level", " %", 0.0f, 100.f);
   // carrier adsr
   configParam(SynthFM::CAR_A, 0.0, 1.0, 0.5, "Carrier attack", " %", 0.0f, 100.f);
   configParam(SynthFM::CAR_D, 0.0, 1.0, 0.5, "Carrier decay", " %", 0.0f, 100.f);
   configParam(SynthFM::CAR_S, 0.0, 1.0, 0.5, "Carrier sustain", " %", 0.0f, 100.f);
   configParam(SynthFM::CAR_R, 0.0, 1.0, 0.5, "Carrier release", " %", 0.0f, 100.f);
   // carrier ratio and morph
   configParam(SynthFM::CAR_RATIO, 0.0, 1.0, 0.5, "Modulator ratio", " %", 0.0f, 100.f);
   configParam(SynthFM::CAR_MORPH, 0.0, 1.0, 0.5, "Modulator morph", " %", 0.0f, 100.f);

   synthFM_Processor_process_init(processor);
}

void SynthFM::process(const ProcessArgs &args) {
   // retrieve current max number of channels for gate and v/oct
   // FIXME: reset notes upon count change
   int channels =
      std::max(
               std::max(inputs[GATE].getChannels(), inputs[VOCT].getChannels()),
               inputs[VEL].getChannels());
   synthFM_Processor_nbCables(processor, channels);
   // pass each note to the synth
   for (int c = 0; c < channels; c++) {
      // Reads all the input values and normalizes the values
      float gate = inputs[GATE].getPolyVoltage(c) / 10.0f;
      float voct = inputs[VOCT].getPolyVoltage(c) / 10.0f;
      float vel = inputs[VEL].getPolyVoltage(c) / 10.0f;
      synthFM_Processor_setNote(processor, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
   }

   // others input and parameters unused
   float in4 = inputs[IN4].getVoltage() / 10.0f;
   float mod_in1 = inputs[MOD_IN1].getVoltage() / 10.0f;
   float mod_in2 = inputs[MOD_IN2].getVoltage() / 10.0f;
   float mod_in3 = inputs[MOD_IN3].getVoltage() / 10.0f;
   float mod_in4 = inputs[MOD_IN4].getVoltage() / 10.0f;

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

   synthFM_Processor_process(processor, float_to_fix(in4), float_to_fix(args.sampleRate));

   outputs[OUT1].setVoltage(fix_to_float(synthFM_Processor_process_ret_0(processor) * 10.0f));
   outputs[OUT2].setVoltage(fix_to_float(synthFM_Processor_process_ret_1(processor) * 10.0f));
   outputs[OUT3].setVoltage(fix_to_float(synthFM_Processor_process_ret_2(processor) * 10.0f));
   outputs[OUT4].setVoltage(fix_to_float(synthFM_Processor_process_ret_3(processor) * 10.0f));
}

static const NVGcolor SCHEME_TOTO = nvgRGB(255, 10, 33);

template <typename TBase = GrayModuleLightWidget>
struct TTotoLight : TBase {
    TTotoLight() {
        this->addBaseColor(SCHEME_TOTO);
    }
};
using TotoLight = TTotoLight<>;

struct LEDSliderToto : VCVLightSlider<TotoLight> {};

struct SynthFMWidget : ModuleWidget {
   SynthFMWidget(SynthFM *module) {
      setModule(module);

      setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SynthFM.svg")));

      // modulator ADSR sliders
      // here and after: use heihgt of canvas since my inskscape has Y origin flow lower left
      float mod_adsr_y = 128.5-99.2;
      addParam(createParamCentered<LEDSliderToto>(mm2px(Vec(10.934, mod_adsr_y)), module, SynthFM::MOD_A));
      addParam(createParamCentered<LEDSliderToto>(mm2px(Vec(19.972, mod_adsr_y)), module, SynthFM::MOD_D));
      addParam(createParamCentered<LEDSliderToto>(mm2px(Vec(29.009, mod_adsr_y)), module, SynthFM::MOD_S));
      addParam(createParamCentered<LEDSliderToto>(mm2px(Vec(38.046, mod_adsr_y)), module, SynthFM::MOD_R));
      // modulator ratio and morph knobs, plus level
      float ratio_morph_x = 52.062;
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(ratio_morph_x, 128.5-112.286)), module, SynthFM::MOD_RATIO));
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(ratio_morph_x, 128.5-92.893)), module, SynthFM::MOD_MORPH));
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(30.480, 128.5-75.790)), module, SynthFM::MOD_LEVEL));

      // carrier ADSR sliders
      float car_adsr_y = 128.5-43.637;
      addParam(createParamCentered<LEDSliderToto>(mm2px(Vec(10.934, car_adsr_y)), module, SynthFM::CAR_A));
      addParam(createParamCentered<LEDSliderToto>(mm2px(Vec(19.972, car_adsr_y)), module, SynthFM::CAR_D));
      addParam(createParamCentered<LEDSliderToto>(mm2px(Vec(29.009, car_adsr_y)), module, SynthFM::CAR_S));
      addParam(createParamCentered<LEDSliderToto>(mm2px(Vec(38.046, car_adsr_y)), module, SynthFM::CAR_R));
      // carrier ratio and morph knobs
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(ratio_morph_x, 128.5-56.723)), module, SynthFM::CAR_RATIO));
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(ratio_morph_x, 128.5-37.330)), module, SynthFM::CAR_MORPH));

      //addParam(createParam<Rogan3PWhite>(Vec(89, 59), module, SynthFM::KNOB2));
      //addParam(createParam<Rogan3PWhite>(Vec(19, 130), module, SynthFM::KNOB3));
      //addParam(createParam<Rogan3PRed>(Vec(89, 130), module, SynthFM::KNOB4));

      for (int i = 0; i < 4; i++)
         addInput(createInput<PJ301MPort>(Vec(10 + 35 * i, 273), module, SynthFM::GATE + i));

      for (int i = 0; i < 4; i++)
         addOutput(createOutput<PJ301MPort>(Vec(10 + 35 * i, 313), module, SynthFM::OUT1 + i));
   }
};

Model *synthFM = createModel<SynthFM, SynthFMWidget>("BotaniaSynthFM");
