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
   // ease reading parameters with modulation
   float readParamCV(int PARAM, int CV_IN, int CV_AV);
};

EffectReverb::EffectReverb() {
   config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

   configParam(EffectReverb::DRY_WET, 0.0, 1.0, 0.5, "Dry/Wet", " %", 0.0f, 100.f);
   configParam(EffectReverb::REVERB, 0.001, 60.0, 10.0, "Reverberation time (T60)", " seconds");
   configParam(EffectReverb::REVERB_AV, 0.0, 1.0, 0.0, "Reverberation CV strength", " %", 0.0f, 100.f);
   // actually max delay will depend on buffer size, with 2048 buffer and 44100 fs it's only 46ms
   configParam(EffectReverb::DELAY, 1.0, 100.0, 50.0, "Delay", " ms");
   configParam(EffectReverb::DELAY_AV, 0.0, 1.0, 0.0, "Delay CV strength", " %", 0.0f, 100.f);

   // init engine and apply default parameter
   Processor_reverb_process_init(processor);
   sendParams(true);
}

// Reads the CV input values, if any, normalize and apply modulator (was attenuverter before)
// the higher the modulator, the greater the modulation
float EffectReverb::readParamCV(int PARAM, int CV_IN, int CV_AV) {
   float val = params[PARAM].getValue();
   float in_val = 1.0;
   if (inputs[CV_IN].getChannels() > 0) {
      // input range should be 0..10v
      in_val = inputs[CV_IN].getVoltage() / 10.0f;
      // values on 0..1
      in_val = clamp(in_val, 0.0, 1.0);
      // by how much we can modulate
      float mod_range = (val - paramQuantities[PARAM]->getMinValue()) *  params[CV_AV].getValue();
      val = val - mod_range * (1 - in_val);
   }
   return val;
}

void EffectReverb::sendParams(bool force) {
   Processor_reverb_setReverb(processor, float_to_fix(readParamCV(REVERB, REVERB_IN, REVERB_AV)), force);
   Processor_reverb_setDelay(processor, float_to_fix(readParamCV(DELAY, DELAY_IN, DELAY_AV)), force);
}

void EffectReverb::process(const ProcessArgs &args) {
   // update parameters
   Processor_reverb_setSamplerate(processor, float_to_fix(args.sampleRate/1000.0));
   sendParams();
   
   // input should be audio level, -5 .. 5
   // VoltageSum to somehow handle polyphony
   float in = inputs[IN].getVoltageSum() / 5.0f;

   // retrieve reverb
   float effect = fix_to_float(Processor_reverb_process(processor, float_to_fix(in)));
   // apply mix and output to max audio voltage range
   float dry_wet = params[DRY_WET].getValue();
   // from processor -1..1 
   outputs[OUT].setVoltage((in * (1 - dry_wet) + effect * dry_wet) * 5.0f);
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
