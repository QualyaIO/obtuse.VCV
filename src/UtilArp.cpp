#include "plugin.hpp"
#include "engine_utils.h"

// naming the modes -- to sync with DSP
struct ModeQuantity : ParamQuantity {
   std::string getDisplayValueString() override {
      switch (int(getValue())) {
      case 0:
         return std::to_string(int(getValue())) + " - up";
      case 1:
         return std::to_string(int(getValue())) + " - down";
      case 2:
         return std::to_string(int(getValue())) + " - up-down no repeat";
      case 3:
         return std::to_string(int(getValue())) + " - up-down repeat";
      case 4:
         return std::to_string(int(getValue())) + " - down-up no repeat";
      case 5:
         return std::to_string(int(getValue())) + " - down-up repeat";
      default:
         return "mode " + std::to_string(int(getValue()));
      }
   }
};

struct UtilArp : Module {

   enum ParamIds {
      MODE,
      RANDNOTES,
      RANDNOTES_AV,
      RANDOMIZE,
      RANDOMIZE_AV,
      NUM_PARAMS
   };
   enum InputIds {
      RANDNOTES_IN,
      RANDOMIZE_IN,
      VOCT,
      TRIGGER,
      RESET,
      NUM_INPUTS
   };
   enum OutputIds {
      NOTE_OUT,
      NUM_OUTPUTS
   };
   enum LightIds {
      NUM_LIGHTS
   };

   Processor_arp_process_type processor;

   UtilArp();
   void process(const ProcessArgs &args) override;
   // pass all parameters to engine. force: engine will pass params even if not changed, use upon init
   void sendParams(bool force=false);
   // ease reading parameters with modulation
   float readParamCV(int PARAM, int CV_IN, int CV_AV);
};

UtilArp::UtilArp() {
   config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

   // default to all
   configParam<ModeQuantity>(UtilArp::MODE, 0, Processor_arp_getNbModes(processor) - 1, 0, "Mode", "");
   paramQuantities[MODE]->snapEnabled = true;
   configParam(UtilArp::RANDNOTES, 0.0, 1.0, 0.0, "Amount of random notes.", "");
   configParam(UtilArp::RANDOMIZE, 0.0, 1.0, 0.0, "Probblity to randomize upon next sequence.", "");

   // init engine and apply default parameter
   Processor_arp_process_init(processor);
   sendParams(true);
}

// Reads the CV input values, if any, normalize and apply modulator (was attenuverter before)
// the higher the modulator, the greater the modulation
float UtilArp::readParamCV(int PARAM, int CV_IN, int CV_AV) {
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

void UtilArp::sendParams(bool force) {
   Processor_arp_setMode(processor, int(params[MODE].getValue() + 0.5), force);
   Processor_arp_setPRandomNotes(processor, float_to_fix(readParamCV(RANDNOTES, RANDNOTES_IN, RANDNOTES_AV)), force);
   Processor_arp_setPRandomize(processor, float_to_fix(readParamCV(RANDOMIZE, RANDOMIZE_IN, RANDOMIZE_AV)), force);
}

void UtilArp::process(const ProcessArgs &args) {
   // update parameters
   sendParams();

   // set notes
   int nbChans = inputs[VOCT].getChannels();
   int notes[16];
   int i = 0;
   // retrieve connected cables
   for(; i < nbChans; i++) {
      // norm and convert in place
      notes[i] = Processor_arp_cvToPitch(float_to_fix(inputs[VOCT].getPolyVoltage(i)/10.0f));
   }
   // disable remaining notes
   for(; i < Processor_arp_getMaxNbNotes(processor); i++) {
      notes[i] = -1;
   }
   // send to arp
   Processor_arp_setNotes(processor, notes);

   
   // run clock, retrieve notes, scale
   fix16_t out = Processor_arp_process(
                           processor,
                           float_to_fix(inputs[TRIGGER].getVoltage() / 10.0f),
                           float_to_fix(inputs[RESET].getVoltage() / 10.0f)
                           ) * 10.0f;

   outputs[NOTE_OUT].setVoltage(fix_to_float(out));
}

struct UtilArpWidget : ModuleWidget {
   UtilArpWidget(UtilArp *module) {
      setModule(module);
      setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Arp.svg")));

      float big_knob_x = 10.160;
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(big_knob_x, 128.5-101.386)), module, UtilArp::MODE));
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(big_knob_x, 128.5-81.229)), module, UtilArp::RANDNOTES));
      addParam(createParamCentered<Rogan3PRed>(mm2px(Vec(big_knob_x, 128.5-53.116)), module, UtilArp::RANDOMIZE));

      float av_in_x = 4.928;
      float av_knob_x = 15.509;
      float av_randnotes_y = 128.5-70.092;
      float av_randomize_y = 128.5-41.979;

      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, av_randnotes_y)), module, UtilArp::RANDNOTES_IN));
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, av_randnotes_y)), module, UtilArp::RANDNOTES_AV));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, av_randomize_y)), module, UtilArp::RANDOMIZE_IN));
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, av_randomize_y)), module, UtilArp::RANDOMIZE_AV));

      float ports_row1_y = 128.5-27.625;
      float ports_row2_y = 128.5-13.609;
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, ports_row1_y)), module, UtilArp::TRIGGER));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_knob_x, ports_row1_y)), module, UtilArp::RESET));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, ports_row2_y)), module, UtilArp::VOCT));
      addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(av_knob_x, ports_row2_y)), module, UtilArp::NOTE_OUT));

   }
};

Model *utilArp = createModel<UtilArp, UtilArpWidget>("ObtuseArp");
