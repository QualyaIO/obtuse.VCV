#include "plugin.hpp"
#include "engine_utils.h"

// TODO: make it polyphonic?

struct UtilTrigg : Module {

   enum ParamIds {
      DIVIDER,
      DIVIDER_AV,
      SHIFT,
      SHIFT_AV,
      LENGTH,
      LENGTH_AV,
      POSITION,
      POSITION_AV,
      DENSITY,
      DENSITY_AV,
      BALANCE,
      BALANCE_AV,
      EVOLVE,
      EVOLVE_AV,
      MAGNITUDE,
      MAGNITUDE_AV,
      NUM_PARAMS
   };
   enum InputIds {
      DIVIDER_IN,
      SHIFT_IN,
      LENGTH_IN,
      POSITION_IN,
      DENSITY_IN,
      BALANCE_IN,
      EVOLVE_IN,
      MAGNITUDE_IN,
      CLOCK,
      RESET,

      NUM_INPUTS
   };
   enum OutputIds {
      TRIGGER,

      NUM_OUTPUTS
   };
   enum LightIds { NUM_LIGHTS };

   Processor_trigg_process_type processor;

   UtilTrigg();
   void process(const ProcessArgs &args) override;
   // pass all parameters to engine. force: engine will pass params even if not changed, use upon init
   void sendParams(bool force=false);
   // ease reading parameters with modulation
   float readParamCV(int PARAM, int CV_IN, int CV_AV);
};

UtilTrigg::UtilTrigg() {
   config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

   // arbitrary max divider
   configParam(UtilTrigg::DIVIDER, 1, 1024, 2, "Clock divider", "");
   paramQuantities[DIVIDER]->snapEnabled = true;
   configParam(UtilTrigg::SHIFT, 0, 1023, 0, "Clock shift", "");
   paramQuantities[SHIFT]->snapEnabled = true;
   // correspond to implemeted max -- TODO: read that. 0 will be autolength.
   configParam(UtilTrigg::LENGTH, 0, 128, 16, "Loop length", " steps");
   paramQuantities[LENGTH]->snapEnabled = true;
   configParam(UtilTrigg::POSITION, 0, 127, 0, "Loop starting position", "");
   paramQuantities[POSITION]->snapEnabled = true;

   configParam(UtilTrigg::DENSITY, 0.0, 1.0, 0.5, "Density", " %", 0.0f, 100.f);
   configParam(UtilTrigg::BALANCE, 0.0, 1.0, 0.5, "Balance", " %", 0.0f, 100.f);
   configParam(UtilTrigg::EVOLVE, 0.0, 1.0, 0.5, "Evolve", " %", 0.0f, 100.f);
   configParam(UtilTrigg::MAGNITUDE, 0.0, 1.0, 0.5, "Magnitude", " %", 0.0f, 100.f);

   // init engine and apply default parameter
   Processor_trigg_process_init(processor);
   // different seed for each instance of the module
   Processor_trigg_setSeed(processor, random::u32());

   sendParams(true);
}

// Reads the CV input values, if any, normalize and apply modulator (was attenuverter before)
// the higher the modulator, the greater the modulation
float UtilTrigg::readParamCV(int PARAM, int CV_IN, int CV_AV) {
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

void UtilTrigg::sendParams(bool force) {
   // rounding all parameters
   Processor_trigg_setDivider(processor, int(readParamCV(DIVIDER, DIVIDER_IN, DIVIDER_AV) + 0.5), force);
   Processor_trigg_setShift(processor, int(readParamCV(SHIFT, SHIFT_IN, SHIFT_AV) + 0.5), force);
   Processor_trigg_setLength(processor, int(readParamCV(LENGTH, LENGTH_IN, LENGTH_AV) + 0.5), force);
   Processor_trigg_setPosition(processor, int(readParamCV(POSITION, POSITION_IN, POSITION_AV) + 0.5), force);

   Processor_trigg_setDensity(processor, float_to_fix(readParamCV(DENSITY, DENSITY_IN, DENSITY_AV)), force);
   Processor_trigg_setBalance(processor, float_to_fix(readParamCV(BALANCE, BALANCE_IN, BALANCE_AV)), force);
   Processor_trigg_setEvolve(processor, float_to_fix(readParamCV(EVOLVE, EVOLVE_IN, EVOLVE_AV)), force);
   Processor_trigg_setMagnitude(processor, float_to_fix(readParamCV(MAGNITUDE, MAGNITUDE_IN, MAGNITUDE_AV)), force);
}

void UtilTrigg::process(const ProcessArgs &args) {
   // update parameters
   Processor_trigg_setSamplerate(processor, float_to_fix(args.sampleRate/1000.0));
   sendParams();
   
   // input at clock and reset should be audio level, 0 .. 10
   float clock = inputs[CLOCK].getVoltage() / 10.0f;
   float reset = inputs[RESET].getVoltage() / 10.0f;

   // from processor 0 / 1 
   int trigger = Processor_trigg_process(processor, float_to_fix(clock), float_to_fix(reset));
   outputs[TRIGGER].setVoltage(trigger * 5.0f);
}

struct UtilTriggWidget : ModuleWidget {
   UtilTriggWidget(UtilTrigg *module) {
      setModule(module);
      setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Trigg.svg")));

      float big_knob_x = 18.506;
      float av_in_x = 28.364;
      float av_knob_x = 36.361;

      float divider_y = 128.5 - 115.455;
      float shift_y = 128.5 - 103.105;
      float length_y = 128.5 - 91.104;
      float position_y = 128.5 - 78.206;
      float density_y = 128.5 - 66.054;
      float balance_y = 128.5 - 53.505;
      float evolve_y = 128.5 - 41.155;
      float magnitude_y = 128.5 - 28.804;
      addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(big_knob_x, divider_y)), module, UtilTrigg::DIVIDER));
      addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(big_knob_x, shift_y)), module, UtilTrigg::SHIFT));
      addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(big_knob_x, length_y)), module, UtilTrigg::LENGTH));
      addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(big_knob_x, position_y)), module, UtilTrigg::POSITION));
      addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(big_knob_x, density_y)), module, UtilTrigg::DENSITY));
      addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(big_knob_x, balance_y)), module, UtilTrigg::BALANCE));
      addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(big_knob_x, evolve_y)), module, UtilTrigg::EVOLVE));
      addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(big_knob_x, magnitude_y)), module, UtilTrigg::MAGNITUDE));

      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, divider_y)), module, UtilTrigg::DIVIDER_AV));
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, shift_y)), module, UtilTrigg::SHIFT_AV));
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, length_y)), module, UtilTrigg::LENGTH_AV));
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, position_y)), module,  UtilTrigg::POSITION_AV));
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, density_y)), module, UtilTrigg::DENSITY_AV));
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, balance_y)), module, UtilTrigg::BALANCE_AV));
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, evolve_y)), module, UtilTrigg::EVOLVE_AV));
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, magnitude_y)), module, UtilTrigg::MAGNITUDE_AV));

      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, divider_y)), module, UtilTrigg::DIVIDER_IN));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, shift_y)), module, UtilTrigg::SHIFT_IN));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, length_y)), module, UtilTrigg::LENGTH_IN));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, position_y)), module, UtilTrigg::POSITION_IN));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, density_y)), module, UtilTrigg::DENSITY_IN));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, balance_y)), module, UtilTrigg::BALANCE_IN));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, evolve_y)), module, UtilTrigg::EVOLVE_IN));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, magnitude_y)), module, UtilTrigg::MAGNITUDE_IN));
      
      float in_out_y = 128.5-13.609;
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.320, in_out_y)), module, UtilTrigg::CLOCK));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20.020, in_out_y)), module, UtilTrigg::RESET));
      addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(32.718, in_out_y)), module, UtilTrigg::TRIGGER));
      
   }
};

Model *utilTrigg = createModel<UtilTrigg, UtilTriggWidget>("ObtuseTrigg");
