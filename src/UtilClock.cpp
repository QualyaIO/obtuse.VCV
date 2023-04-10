#include "plugin.hpp"
#include "engine_utils.h"

// Note that the CV input for frequency is *not* V/Oct as per VCV Rack guidelines, but mapped linearly from 0v to 10v to min/max BPM.

struct UtilClock : Module {

   enum ParamIds {
      BPM,
      BPM_AV,
      SWING,
      SWING_AV,
      ORDER,
      SIZE,
      SIZE_AV,
      RATIO,
      RATIO_AV,
      NUM_PARAMS
   };
   enum InputIds {
      BPM_IN,
      SWING_IN,
      SIZE_IN,
      RATIO_IN,
      NUM_INPUTS
   };
   enum OutputIds {
      CLOCK,
      NEW,
      GROUP1,
      GROUP2,
      NUM_OUTPUTS
   };
   enum LightIds { NUM_LIGHTS };

   Processor_clock_process_type processor;

   UtilClock();
   void process(const ProcessArgs &args) override;
   // pass all parameters to engine. force: engine will pass params even if not changed, use upon init
   void sendParams(bool force=false);
   // ease reading parameters with modulation
   float readParamCV(int PARAM, int CV_IN, int CV_AV);
};

UtilClock::UtilClock() {
   config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

   configParam(UtilClock::BPM, fix_to_float(Processor_clock_getMinBPM()), fix_to_float(Processor_clock_getMaxBPM()), 120.0, "BPM", " BPM");
   configParam(UtilClock::SWING, 0.0, 1.0, 0.5, "Swing", "");

   configParam(UtilClock::SIZE, Processor_clock_getMinGroupSize(), Processor_clock_getMaxGroupSize(), 4, "Group size", " beats");
   configParam(UtilClock::RATIO, 0.0, 1.0, 0.5, "Group Ratio", "");

   // init engine and apply default parameter
   Processor_clock_process_init(processor);
   sendParams(true);
}

// Reads the CV input values, if any, normalize and apply modulator (was attenuverter before)
// the higher the modulator, the greater the modulation
float UtilClock::readParamCV(int PARAM, int CV_IN, int CV_AV) {
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

void UtilClock::sendParams(bool force) {
   // rounding all parameters
   Processor_clock_setBPM(processor, float_to_fix(readParamCV(BPM, BPM_IN, BPM_AV)), force);
   Processor_clock_setSwing(processor, float_to_fix(readParamCV(SWING, SWING_IN, SWING_AV)), force);
   Processor_clock_setGroupSize(processor, int(readParamCV(SIZE, SIZE_IN, SIZE_AV) + 0.5), force);
   Processor_clock_setGroupRatio(processor, float_to_fix(readParamCV(RATIO, RATIO_IN, RATIO_AV)), force);
}

void UtilClock::process(const ProcessArgs &args) {
   // TODO: ad-hoc variable for time?
   static float time = 0.0;
   time += 1./args.sampleRate;

   // update parameters
   sendParams();
   // run clock, retrieve all 4 outputs
   Processor_clock_process(processor, float_to_fix(time));
   outputs[CLOCK].setVoltage(fix_to_float(Processor_clock_process_ret_0(processor)) * 5.0);
   outputs[NEW].setVoltage(fix_to_float(Processor_clock_process_ret_1(processor)) * 5.0);
   outputs[GROUP1].setVoltage(fix_to_float(Processor_clock_process_ret_2(processor)) * 5.0);
   outputs[GROUP2].setVoltage(fix_to_float(Processor_clock_process_ret_3(processor)) * 5.0);
}

struct UtilClockWidget : ModuleWidget {
   UtilClockWidget(UtilClock *module) {
      setModule(module);
      setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Clock.svg")));

      float big_knob_x = 18.506;
      float av_in_x = 28.364;
      float av_knob_x = 36.361;

      float bpm_y = 128.5 - 115.455;
      float swing_y = 128.5 - 103.105;

      float size_y = 128.5 - 78.206;
      float ratio_y = 128.5 - 66.054;

      addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(big_knob_x, bpm_y)), module, UtilClock::BPM));
      addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(big_knob_x, swing_y)), module, UtilClock::SWING));
      addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(big_knob_x, size_y)), module, UtilClock::SIZE));
      addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(big_knob_x, ratio_y)), module, UtilClock::RATIO));

      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, bpm_y)), module, UtilClock::BPM_AV));
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, swing_y)), module, UtilClock::SWING_AV));
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, size_y)), module, UtilClock::SIZE_AV));
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, ratio_y)), module,  UtilClock::RATIO_AV));

      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, bpm_y)), module, UtilClock::BPM_IN));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, swing_y)), module, UtilClock::SWING_IN));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, size_y)), module, UtilClock::SIZE_IN));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, ratio_y)), module, UtilClock::RATIO_IN));
           
      addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(20.322, 128.5-34.776)), module, UtilClock::CLOCK));
      float outs_y = 128.5-18.901;
      addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.620, outs_y)), module, UtilClock::NEW));
      addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(20.322, outs_y)), module, UtilClock::GROUP1));
      addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(33.022, outs_y)), module, UtilClock::GROUP2));
      
   }
};

Model *utilClock = createModel<UtilClock, UtilClockWidget>("BotaniaClock");
