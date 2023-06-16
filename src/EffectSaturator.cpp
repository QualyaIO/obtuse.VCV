#include "plugin.hpp"
#include "engine_effects.h"

struct EffectSaturator : Module {

   enum ParamIds {
      COEFF,
      COEFF_AV,
      THRESH,
      THRESH_AV,
      NUM_PARAMS
   };
   enum InputIds {
      COEFF_IN,
      THRESH_IN,

      IN,

      NUM_INPUTS
   };
   enum OutputIds {
      OUT,

      NUM_OUTPUTS
   };
   enum LightIds { NUM_LIGHTS };

   Processor_saturator_process_type processor;

   EffectSaturator();
   void process(const ProcessArgs &args) override;
   // pass all parameters to engine. force: engine will pass params even if not changed, use upon init
   void sendParams(bool force=false);
   // ease reading parameters with modulation
   float readParamCV(int PARAM, int CV_IN, int CV_AV);
};

EffectSaturator::EffectSaturator() {
   config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

   configParam(EffectSaturator::COEFF, fix_to_float(Processor_saturator_getMinCoeff()), fix_to_float(Processor_saturator_getMaxCoeff()), 1.0, "Coefficient", "");
   configParam(EffectSaturator::COEFF_AV, 0.0, 1.0, 0.0, "Coefficient CV strength", " %", 0.0f, 100.f);
   configParam(EffectSaturator::THRESH, 0.0, 1.0, 0.8, "Threshold", "");
   configParam(EffectSaturator::THRESH_AV, 0.0, 1.0, 0.0, "Threshold CV strength", " %", 0.0f, 100.f);

   // init engine and apply default parameter
   Processor_saturator_process_init(processor);
   sendParams(true);
}

// Reads the CV input values, if any, normalize and apply modulator (was attenuverter before)
// the higher the modulator, the greater the modulation
float EffectSaturator::readParamCV(int PARAM, int CV_IN, int CV_AV) {
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

void EffectSaturator::sendParams(bool force) {
   Processor_saturator_setCoeff(processor, float_to_fix(readParamCV(COEFF, COEFF_IN, COEFF_AV)), force);
   Processor_saturator_setThreshold(processor, float_to_fix(readParamCV(THRESH, THRESH_IN, THRESH_AV)), force);
}

void EffectSaturator::process(const ProcessArgs &args) {
   // update parameters
   sendParams();
   
   // input should be audio level, -5 .. 5
   // VoltageSum to somehow handle polyphony
   float in = inputs[IN].getVoltageSum() / 5.0f;

   // retrieve saturator
   float out = fix_to_float(Processor_saturator_process(processor, float_to_fix(in)));
   // from processor -1..1 
   outputs[OUT].setVoltage((out * 5.0f));
}

struct EffectSaturatorWidget : ModuleWidget {
   EffectSaturatorWidget(EffectSaturator *module) {
      setModule(module);
      setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Saturator.svg")));

      float big_knob_x = 10.168;
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(big_knob_x, 128.5-90.471)), module, EffectSaturator::COEFF));
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(big_knob_x, 128.5-52.904)), module, EffectSaturator::THRESH));

      float av_in_x = 4.926;
      float av_knob_x = 15.509;
      float av_coeff_y = 128.5-78.994;
      float av_thresh_y = 128.5-41.767;
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, av_coeff_y)), module, EffectSaturator::COEFF_AV));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, av_coeff_y)), module, EffectSaturator::COEFF_IN));
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, av_thresh_y)), module, EffectSaturator::THRESH_AV));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, av_thresh_y)), module, EffectSaturator::THRESH_IN));

      float in_out_y = 128.5-14.663;
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, in_out_y)), module, EffectSaturator::IN));
      addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(av_knob_x, in_out_y)), module, EffectSaturator::OUT));
   }
};

Model *effectSaturator = createModel<EffectSaturator, EffectSaturatorWidget>("BotaniaSaturator");
