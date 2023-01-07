#include "plugin.hpp"
#include "engine_effects.h"

struct EffectReverb : Module {

   enum ParamIds {
      DRY_WET,
      REVERB,
      REVERB_AV,
      DELAY,
      DELAY_AV,
      NUM_PARAMS
   };
   enum InputIds {
      REVERB_IN,
      DELAY_IN,

      IN,

      NUM_INPUTS
   };
   enum OutputIds {
      OUT,

      NUM_OUTPUTS
   };
   enum LightIds { NUM_LIGHTS };

   Processor_reverb_process_type processor;

   EffectReverb();
   void process(const ProcessArgs &args) override;
   // pass all parameters to engine. force: engine will pass params even if not changed, use upon init
   void sendParams(bool force=false);
};

EffectReverb::EffectReverb() {
   config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

   configParam(EffectReverb::DRY_WET, 0.0, 1.0, 0.5, "Dry/Wet", " %", 0.0f, 100.f);
   configParam(EffectReverb::REVERB, 0.001, 60.0, 10.0, "Reverberation time (T60)", " seconds");
   configParam(EffectReverb::REVERB_AV, -1.0, 1.0, 0.0, "Reverberation attenuverter", "");
   // actually max delay will depend on buffer size, with 2048 buffer and 44100 fs it's only 46ms
   configParam(EffectReverb::DELAY, 1.0, 100.0, 50.0, "Delay", " ms");
   configParam(EffectReverb::DELAY_AV, -1.0, 1.0, 0.0, "Delay attenuverter", "");

   // init engine and apply default parameter
   Processor_reverb_process_init(processor);
   sendParams(true);
}

void EffectReverb::sendParams(bool force) {
   //Processor_reverb_process_setWetDry(processor, float_to_fix(params[WET_DRY].getValue()), force);
   //Processor_reverb_process_setDelay(processor, float_to_fix(params[DELAY].getValue()), force);
   //Processor_reverb_process_setReverb(processor, float_to_fix(params[REVERB].getValue()), force);
}

void EffectReverb::process(const ProcessArgs &args) {
   // update parameters
   Processor_reverb_setSamplerate(processor, float_to_fix(args.sampleRate/1000.0));
   sendParams();

   // Reads all the input values, normalizes the values, apply attenuverters
   float in_reverb = inputs[REVERB_IN].getVoltage() / 10.0f * params[REVERB_AV].getValue();
   float in_delay = inputs[DELAY_IN].getVoltage() / 10.0f * params[DELAY_AV].getValue();
   // TODO: apply CV
   
   // input should be audio level, -5 .. 5
   float in = inputs[IN].getVoltage() / 5.0f;

   // from processor -1..1 to max audio voltage range
   outputs[OUT].setVoltage(fix_to_float(Processor_reverb_process(processor, float_to_fix(in)) * 5.0f));
   
}

struct EffectReverbWidget : ModuleWidget {
   EffectReverbWidget(EffectReverb *module) {
      setModule(module);
      setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Reverb.svg")));

      float big_knob_x = 10.168;
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(big_knob_x, 128.5-96.988)), module, EffectReverb::DRY_WET));
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(big_knob_x, 128.5-74.085)), module, EffectReverb::REVERB));
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(big_knob_x, 128.5-43.062)), module, EffectReverb::DELAY));

      float av_in_x = 4.926;
      float av_knob_x = 15.509;
      float av_reverb_y = 128.5-62.944;
      float av_delay_y = 128.5-31.921;
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, av_reverb_y)), module, EffectReverb::REVERB_AV));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, av_reverb_y)), module, EffectReverb::REVERB_IN));
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, av_delay_y)), module, EffectReverb::DELAY_AV));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, av_delay_y)), module, EffectReverb::DELAY_IN));

      float in_out_y = 128.5-14.663;
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, in_out_y)), module, EffectReverb::IN));
      addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(av_knob_x, in_out_y)), module, EffectReverb::OUT));
   }
};

Model *effectReverb = createModel<EffectReverb, EffectReverbWidget>("BotaniaReverb");
