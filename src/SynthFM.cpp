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
      MOD_MORPH_PHASE,
      MOD_LEVEL,
      MOD_MODE,
      MOD_SHIFT,

      CAR_A,
      CAR_D,
      CAR_S,
      CAR_R,
      CAR_RATIO,
      CAR_MORPH,
      CAR_MORPH_PHASE,

      MOD_FDB,

      NUM_PARAMS
   };
   enum InputIds {
      VOCT,
      GATE,
      VEL,
      RETRIGGER,
      BEND,

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
   configParam(SynthFM::MOD_MORPH_PHASE, 0.0, 1.0, 0.0, "Modulator morph phase", " %", 0.0f, 100.0f);
   configParam(SynthFM::MOD_LEVEL, 0.0, 1.0, 0.1, "Modulator level", " %", 0.0f, 100.0f);
   // due to the position of the switch and label, here 1.0 phase -> "false" in DSP
   configSwitch(SynthFM::MOD_MODE, 0.0, 1.0, 1.0, "Modulator target", {"level", "phase"});
   configParam(SynthFM::MOD_SHIFT, 0.0, 1.0, 0.0, "Modulator phase shift", " %", 0.0f, 100.0f);
   configParam(SynthFM::MOD_FDB, 0.0, 1.0, 0.0, "Modulator feedback", " %", 0.0f, 100.0f);

   // carrier adsr
   configParam(SynthFM::CAR_A, 0.0, maxA, 0.0, "Carrier attack", " seconds");
   configParam(SynthFM::CAR_D, 0.0, maxD, 0.0, "Carrier decay", " seconds");
   configParam(SynthFM::CAR_S, 0.0, maxS, 0.5, "Carrier sustain", "");
   configParam(SynthFM::CAR_R, 0.0, maxR, 0.0, "Carrier release", " seconds");
   // carrier ratio and morph
   configParam(SynthFM::CAR_RATIO, -maxRatio, maxRatio, 1.0, "Carrier ratio", "");
   configParam(SynthFM::CAR_MORPH, 0.0, maxMorph, 0.0, "Carrier morph", "");
   configParam(SynthFM::CAR_MORPH_PHASE, 0.0, 1.0, 0.0, "Carrier morph phase", " %", 0.0f, 100.0f);

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
   synthFM_Processor_setModulatorWavetablePhase(processor, float_to_fix(params[MOD_MORPH_PHASE].getValue()), force);
   synthFM_Processor_setModulatorLevel(processor, float_to_fix(params[MOD_LEVEL].getValue()), force);
   synthFM_Processor_setModulatorMode(processor, float_to_fix(std::round(params[MOD_MODE].getValue())), force);
   synthFM_Processor_setModulatorPhaseShift(processor, float_to_fix(params[MOD_SHIFT].getValue()), force);
   synthFM_Processor_setModulatorFeedback(processor, float_to_fix(params[MOD_FDB].getValue()), force);

   synthFM_Processor_setCarrierADSR(processor,
                                      float_to_fix(params[CAR_A].getValue()),
                                      float_to_fix(params[CAR_D].getValue()),
                                      float_to_fix(params[CAR_S].getValue()),
                                      float_to_fix(params[CAR_R].getValue()),
                                      force
                                      );
   synthFM_Processor_setCarrierRatio(processor, float_to_fix(params[CAR_RATIO].getValue()), force);
   synthFM_Processor_setCarrierWavetable(processor, float_to_fix(params[CAR_MORPH].getValue()), force);
   synthFM_Processor_setCarrierWavetablePhase(processor, float_to_fix(params[CAR_MORPH_PHASE].getValue()), force);
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
   // also retrigger
   channels = std::max(channels, inputs[RETRIGGER].getChannels()); 
   synthFM_Processor_nbCables(processor, channels);
   // pass each note to the synth
   for (int c = 0; c < channels; c++) {
      // Reads all the input values and normalizes the values
      float voct = inputs[VOCT].getPolyVoltage(c) / 10.0f;
      float gate = inputs[GATE].getPolyVoltage(c) / 10.0f;
      float vel = inputs[VEL].getPolyVoltage(c) / 10.0f;
      float rettriger = inputs[RETRIGGER].getPolyVoltage(c) / 10.0f;
      synthFM_Processor_setNote(processor, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), float_to_fix(rettriger), c);
   }

   // pitch bend, -5: -2 seminotes, +5: +2 semitones
   synthFM_Processor_setPitchBend(processor, float_to_fix(inputs[BEND].getVoltage() / 2.5f));

   // from processor -1..1 to max audio voltage range
   outputs[OUT].setVoltage(fix_to_float(synthFM_Processor_process(processor) * 5.0f));
}

struct SynthFMWidget : ModuleWidget {
   SynthFMWidget(SynthFM *module) {
      setModule(module);

      setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SynthFM.svg")));

      // modulator ADSR sliders
      // here and after: use heihgt of canvas since my inskscape has Y origin flow lower left
      float mod_adsr_y = 128.5-99.2;
      addParam(createParamCentered<LEDSliderPink>(mm2px(Vec(10.934, mod_adsr_y)), module, SynthFM::MOD_A));
      addParam(createParamCentered<LEDSliderPink>(mm2px(Vec(19.411, mod_adsr_y)), module, SynthFM::MOD_D));
      addParam(createParamCentered<LEDSliderPink>(mm2px(Vec(27.739, mod_adsr_y)), module, SynthFM::MOD_S));
      addParam(createParamCentered<LEDSliderPink>(mm2px(Vec(35.930, mod_adsr_y)), module, SynthFM::MOD_R));
      // modulator ratio and morph knobs, plus level and mode
      float ratio_x = 49.564;
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(ratio_x, 128.5-109.853)), module, SynthFM::MOD_RATIO));
      float morph_x = 44.965;
      float mod_morph_y = 128.5-93.187;
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(morph_x, mod_morph_y)), module, SynthFM::MOD_MORPH));
      float morph_phase_x = 55.183;
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(morph_phase_x, mod_morph_y)), module, SynthFM::MOD_MORPH_PHASE));
      
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(6.426, 128.5-75.768)), module, SynthFM::MOD_FDB));
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(19.080, 128.5-75.601)), module, SynthFM::MOD_LEVEL));
      addParam(createParamCentered<CKSS>(mm2px(Vec(33.538, 128.5-73.695)), module, SynthFM::MOD_MODE));
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(47.996, 128.5-75.601)), module, SynthFM::MOD_SHIFT));

      // carrier ADSR sliders
      float car_adsr_y = 128.5-43.637;
      addParam(createParamCentered<LEDSliderPink>(mm2px(Vec(10.934, car_adsr_y)), module, SynthFM::CAR_A));
      addParam(createParamCentered<LEDSliderPink>(mm2px(Vec(19.411, car_adsr_y)), module, SynthFM::CAR_D));
      addParam(createParamCentered<LEDSliderPink>(mm2px(Vec(27.739, car_adsr_y)), module, SynthFM::CAR_S));
      addParam(createParamCentered<LEDSliderPink>(mm2px(Vec(35.930, car_adsr_y)), module, SynthFM::CAR_R));
      // carrier ratio and morph knobs
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(ratio_x, 128.5-54.126)), module, SynthFM::CAR_RATIO));
      float car_morph_y = 128.5-37.330;
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(morph_x, car_morph_y)), module, SynthFM::CAR_MORPH));
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(morph_phase_x, car_morph_y)), module, SynthFM::CAR_MORPH_PHASE));

      // input: v/oct, gate, velocity
      float port_y = 128.5 - 14.625;
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.444, port_y)), module, SynthFM::VOCT));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(15.459, port_y)), module, SynthFM::GATE));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(25.474, port_y)), module, SynthFM::RETRIGGER));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.487, port_y)), module, SynthFM::VEL));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(45.504, port_y)), module, SynthFM::BEND));

      addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(55.519, port_y)), module, SynthFM::OUT));
   }
};

Model *synthFM = createModel<SynthFM, SynthFMWidget>("BotaniaSynthFM");
