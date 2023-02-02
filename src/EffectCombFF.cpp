#include "plugin.hpp"
#include "engine_effects_extra.h"

struct EffectCombFF : Module {

   enum ParamIds {
      DRY_WET,
      DECAY,
      DECAY_AV,
      DELAY,
      DELAY_AV,
      NUM_PARAMS
   };
   enum InputIds {
      DECAY_IN,
      DELAY_IN,

      IN,

      NUM_INPUTS
   };
   enum OutputIds {
      OUT,

      NUM_OUTPUTS
   };
   enum LightIds { NUM_LIGHTS };

   extra_Processor_combFF_process_type processor;

   EffectCombFF();
   void process(const ProcessArgs &args) override;
   // pass all parameters to engine. force: engine will pass params even if not changed, use upon init
   void sendParams(bool force=false);
   // ease reading parameters with modulation
   float readParamCV(int PARAM, int CV_IN, int CV_AV);
};

EffectCombFF::EffectCombFF() {
   config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

   configParam(EffectCombFF::DRY_WET, 0.0, 1.0, 0.5, "Dry/Wet", " %", 0.0f, 100.f);
   configParam(EffectCombFF::DECAY, 0.0, 1.0, 0.5, "Decay", "");
   configParam(EffectCombFF::DECAY_AV, 0.0, 1.0, 0.0, "Decay CV strength", " %", 0.0f, 100.f);
   // actually max delay will depend on buffer size, with XL 16384 buffer and 44100 fs it's only 371ms
   configParam(EffectCombFF::DELAY, 1.0, 1000.0, 50.0, "Delay", " ms");
   configParam(EffectCombFF::DELAY_AV, 0.0, 1.0, 0.0, "Delay CV strength", " %", 0.0f, 100.f);

   // init engine and apply default parameter
   extra_Processor_combFF_process_init(processor);
   sendParams(true);
}

// Reads the CV input values, if any, normalize and apply modulator (was attenuverter before)
// the higher the modulator, the greater the modulation
float EffectCombFF::readParamCV(int PARAM, int CV_IN, int CV_AV) {
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

void EffectCombFF::sendParams(bool force) {
   extra_Processor_combFF_setDecay(processor, float_to_fix(readParamCV(DECAY, DECAY_IN, DECAY_AV)), force);
   extra_Processor_combFF_setDelay(processor, float_to_fix(readParamCV(DELAY, DELAY_IN, DELAY_AV)), force);
}

void EffectCombFF::process(const ProcessArgs &args) {
   // update parameters
   extra_Processor_combFF_setSamplerate(processor, float_to_fix(args.sampleRate/1000.0));
   sendParams();
   
   // input should be audio level, -5 .. 5
   // VoltageSum to somehow handle polyphony
   float in = inputs[IN].getVoltageSum() / 5.0f;

   // retrieve comb
   float effect = fix_to_float(extra_Processor_combFF_process(processor, float_to_fix(in)));
   // apply mix and output to max audio voltage range
   float dry_wet = params[DRY_WET].getValue();
   // from processor -1..1 
   outputs[OUT].setVoltage((in * (1 - dry_wet) + effect * dry_wet) * 5.0f);
}

struct EffectCombFFWidget : ModuleWidget {
   EffectCombFFWidget(EffectCombFF *module) {
      setModule(module);
      setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CombFF.svg")));

      float big_knob_x = 10.168;
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(big_knob_x, 128.5-96.988)), module, EffectCombFF::DRY_WET));
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(big_knob_x, 128.5-74.085)), module, EffectCombFF::DECAY));
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(big_knob_x, 128.5-43.062)), module, EffectCombFF::DELAY));

      float av_in_x = 4.926;
      float av_knob_x = 15.509;
      float av_decay_y = 128.5-62.944;
      float av_delay_y = 128.5-31.921;
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, av_decay_y)), module, EffectCombFF::DECAY_AV));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, av_decay_y)), module, EffectCombFF::DECAY_IN));
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, av_delay_y)), module, EffectCombFF::DELAY_AV));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, av_delay_y)), module, EffectCombFF::DELAY_IN));

      float in_out_y = 128.5-14.663;
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, in_out_y)), module, EffectCombFF::IN));
      addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(av_knob_x, in_out_y)), module, EffectCombFF::OUT));
   }
};

Model *effectCombFF = createModel<EffectCombFF, EffectCombFFWidget>("BotaniaCombFF");
