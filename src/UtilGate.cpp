#include "plugin.hpp"
#include "engine_utils.h"

struct UtilGate : Module {

   enum ParamIds {
      DURATION,
      DURATION_AV,
      NUM_PARAMS
   };
   enum InputIds {
      DURATION_IN,
      VOCT,
      TRIGGER,
      NUM_INPUTS
   };
   enum OutputIds {
      GATE_OUT,
      VOCT_OUT,
      NUM_OUTPUTS
   };
   enum LightIds {
      NUM_LIGHTS
   };

   Processor_gate_process_type processor;

   UtilGate();
   void process(const ProcessArgs &args) override;
   // pass all parameters to engine. force: engine will pass params even if not changed, use upon init
   void sendParams(bool force=false);
   // ease reading parameters with modulation
   float readParamCV(int PARAM, int CV_IN, int CV_AV);
};

UtilGate::UtilGate() {
   config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

   // same range than base VCV gate, 1ms to 10s
   configParam(UtilGate::DURATION, 0.001, 10.0, 0.2, "Duration", " ms", 0.0f, 1000.0f);

   // init engine and apply default parameter
   Processor_gate_process_init(processor);
   sendParams(true);
}

// Reads the CV input values, if any, normalize and apply modulator (was attenuverter before)
// the higher the modulator, the greater the modulation
float UtilGate::readParamCV(int PARAM, int CV_IN, int CV_AV) {
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

void UtilGate::sendParams(bool force) {
   Processor_gate_setDuration(processor, float_to_fix(readParamCV(DURATION, DURATION_IN, DURATION_AV)), force);
}

void UtilGate::process(const ProcessArgs &args) {
   // update parameters
   sendParams();

   int channels = std::max(inputs[TRIGGER].getChannels(), inputs[VOCT].getChannels());
   /*
   int notes[16];
   int i = 0;
   // retrieve connected cables
   for(; i < nbChans; i++) {
      // norm and convert in place
      notes[i] = Processor_Gate_cvToPitch(float_to_fix(inputs[VOCT].getPolyVoltage(i)/10.0f));
   }
   // disable remaining notes
   for(; i < Processor_Gate_getMaxNbNotes(processor); i++) {
      notes[i] = -1;
   }
   // send to arp
   Processor_Gate_setNotes(processor, notes);
   
   */

   Processor_gate_process(processor);

}

struct UtilGateWidget : ModuleWidget {
   UtilGateWidget(UtilGate *module) {
      setModule(module);
      setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Gate.svg")));

      float big_knob_x = 10.160;
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(big_knob_x, 128.5-81.229)), module, UtilGate::DURATION));

      float av_in_x = 4.928;
      float av_knob_x = 15.509;
      float av_duration_y = 128.5-70.092;

      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, av_duration_y)), module, UtilGate::DURATION_IN));
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, av_duration_y)), module, UtilGate::DURATION_AV));

      float ports_row1_y = 128.5-27.625;
      float ports_row2_y = 128.5-13.609;
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, ports_row1_y)), module, UtilGate::VOCT));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_knob_x, ports_row1_y)), module, UtilGate::TRIGGER));
      addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(av_in_x, ports_row2_y)), module, UtilGate::VOCT_OUT));
      addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(av_knob_x, ports_row2_y)), module, UtilGate::GATE_OUT));

   }
};

Model *utilGate = createModel<UtilGate, UtilGateWidget>("BotaniaGate");
