#include "plugin.hpp"
#include "engine_effects.h"

struct EffectSVF : Module {

   enum ParamIds {
      SWITCH,
      FREQ,
      FREQ_AV,
      Q,
      Q_AV,
      NUM_PARAMS
   };
   enum InputIds {
      FREQ_IN,
      Q_IN,

      IN,

      NUM_INPUTS
   };
   enum OutputIds {
      OUT,

      NUM_OUTPUTS
   };
   enum LightIds {
      SWITCH_LIGHT,
      LOW_LIGHT,
      HIGH_LIGHT,
      BAND_LIGHT,
      NOTCH_LIGHT,
                  
      NUM_LIGHTS
   };

   Processor_svf_process_type processor;

   EffectSVF();
   void process(const ProcessArgs &args) override;
   // pass all parameters to engine. force: engine will pass params even if not changed, use upon init
   void sendParams(bool force=false);
   // ease reading parameters with modulation
   float readParamCV(int PARAM, int CV_IN, int CV_AV);
};

EffectSVF::EffectSVF() {
   config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

   configParam(EffectSVF::FREQ, 0.0, 22.0, 5.0, "Frequency", " Hz", 0.0f, 1000.0f);
   configParam(EffectSVF::FREQ_AV, 0.0, 1.0, 0.0, "Frequency CV strength", " %", 0.0f, 100.f);
   // still unsure of range for Q
   configParam(EffectSVF::Q, 0.0, 10.0, 0.0, "Q" "");
   configParam(EffectSVF::Q_AV, 0.0, 1.0, 0.0, "Q CV strength", " %", 0.0f, 100.f);

   // init engine and apply default parameter
   Processor_svf_process_init(processor);
   sendParams(true);
}

// Reads the CV input values, if any, normalize and apply modulator (was attenuverter before)
// the higher the modulator, the greater the modulation
float EffectSVF::readParamCV(int PARAM, int CV_IN, int CV_AV) {
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

void EffectSVF::sendParams(bool force) {
   Processor_svf_setFreq(processor, float_to_fix(readParamCV(FREQ, FREQ_IN, FREQ_AV)), force);
   Processor_svf_setQ(processor, float_to_fix(readParamCV(Q, Q_IN, Q_AV)), force);
}

void EffectSVF::process(const ProcessArgs &args) {
   // update parameters
   Processor_svf_setSamplerate(processor, float_to_fix(args.sampleRate/1000.0));
   sendParams();
   
   // input should be audio level, -5 .. 5
   // VoltageSum to somehow handle polyphony
   float in = inputs[IN].getVoltageSum() / 5.0f;

   // retrieve filter
   float effect = fix_to_float(Processor_svf_process(processor, float_to_fix(in)));
   // from processor -1..1 
   outputs[OUT].setVoltage(effect * 5.0f);
}

struct EffectSVFWidget : ModuleWidget {
   EffectSVFWidget(EffectSVF *module) {
      setModule(module);
      setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SVF.svg")));

      float big_knob_x = 10.168;
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(big_knob_x, 128.5-71.085)), module, EffectSVF::FREQ));
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(big_knob_x, 128.5-42.062)), module, EffectSVF::Q));

      float av_in_x = 4.926;
      float av_knob_x = 15.509;
      float av_freq_y = 128.5-59.944;
      float av_q_y = 128.5-30.921;
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, av_freq_y)), module, EffectSVF::FREQ_AV));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, av_freq_y)), module, EffectSVF::FREQ_IN));
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, av_q_y)), module, EffectSVF::Q_AV));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, av_q_y)), module, EffectSVF::Q_IN));

      float in_out_y = 128.5-14.663;
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, in_out_y)), module, EffectSVF::IN));
      addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(av_knob_x, in_out_y)), module, EffectSVF::OUT));

      // switch to change filter
      float switch_x = 5.725;
      addParam(createLightParamCentered<VCVLightBezel<>>(mm2px(Vec(switch_x, 128.5-88.622)), module, EffectSVF::SWITCH, EffectSVF::SWITCH_LIGHT));
      // light to set current filter
      addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(switch_x, 128.5-94.774)), module, EffectSVF::LOW_LIGHT));
      addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(switch_x, 128.5-98.854)), module, EffectSVF::HIGH_LIGHT));
      addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(switch_x, 128.5-103.012)), module, EffectSVF::BAND_LIGHT));
      addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(switch_x, 128.5-106.812)), module, EffectSVF::NOTCH_LIGHT));

   }
};

Model *effectSVF = createModel<EffectSVF, EffectSVFWidget>("BotaniaSVF");
