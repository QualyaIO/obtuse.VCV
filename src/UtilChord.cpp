#include "plugin.hpp"
#include "engine_utils.h"

struct UtilChord : Module {

   enum ParamIds {
      SCALE,
      SCALE_AV,
      CHORD,
      CHORD_AV,
      CHORD_SPREAD,
      CHORD_SPREAD_AV,
      INV_SPREAD,
      INV_SPREAD_AV,
      JUMP,
      JUMP_AV,
      NUM_PARAMS
   };
   enum InputIds {
      SCALE_IN,
      CHORD_IN,
      CHORD_SPREAD_IN,
      INV_SPREAD_IN,
      JUMP_IN,
      ROOT,
      TRIGGER,
      RESET,
      NUM_INPUTS
   };
   enum OutputIds {
      CHORD_OUT,
      SCALE_OUT,
      NUM_OUTPUTS
   };
   enum LightIds {
      NUM_LIGHTS
   };

   Processor_chord_process_type processor;

   UtilChord();
   void process(const ProcessArgs &args) override;
   // pass all parameters to engine. force: engine will pass params even if not changed, use upon init
   void sendParams(bool force=false);
   // ease reading parameters with modulation
   float readParamCV(int PARAM, int CV_IN, int CV_AV);
};

UtilChord::UtilChord() {
   config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

   // default to all
   configParam(UtilChord::SCALE, 0, Processor_chord_getNbScales(processor) - 1, 0, "Scale", "");
   // default to augmented
   configParam(UtilChord::CHORD, 0, Processor_chord_getNbChords(processor) - 1, 0, "Main chord", "");
   configParam(UtilChord::CHORD_SPREAD, 0.0, 1.0, 0.5, "Chord spread", "");
   configParam(UtilChord::INV_SPREAD, 0.0, 1.0, 0.5, "Inversion spread", "");
   configParam(UtilChord::JUMP, 0.0, 1.0, 0.5, "Probability to jump to another note", "");

   // init engine and apply default parameter
   Processor_chord_process_init(processor);
   sendParams(true);
}

// Reads the CV input values, if any, normalize and apply modulator (was attenuverter before)
// the higher the modulator, the greater the modulation
float UtilChord::readParamCV(int PARAM, int CV_IN, int CV_AV) {
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

void UtilChord::sendParams(bool force) {
   // rounding all parameters
   Processor_chord_setScale(processor, int(readParamCV(SCALE, SCALE_IN, SCALE_AV) + 0.5), force);
   Processor_chord_setChord(processor, int(readParamCV(CHORD, CHORD_IN, CHORD_AV) + 0.5), force);
   Processor_chord_setChordSpread(processor, float_to_fix(readParamCV(CHORD_SPREAD, CHORD_SPREAD_IN, CHORD_SPREAD_AV)), force);
   Processor_chord_setInversionSpread(processor, float_to_fix(readParamCV(INV_SPREAD, INV_SPREAD_IN, INV_SPREAD_AV)), force);
   Processor_chord_setJump(processor, float_to_fix(readParamCV(JUMP, JUMP_IN, JUMP_AV)), force);

   // root from corresponding input
   Processor_chord_setRoot(processor, float_to_fix(inputs[ROOT].getVoltage() / 10.0f), force);
}

void UtilChord::process(const ProcessArgs &args) {
   // update parameters
   sendParams();

   // run clock, retrieve notes
   Processor_chord_process(
                           processor,
                           float_to_fix(inputs[TRIGGER].getVoltage() / 10.0f),
                           float_to_fix(inputs[RESET].getVoltage() / 10.0f)
                           );

   // output chord, cv/oct
   outputs[CHORD_OUT].setVoltage(fix_to_float(Processor_chord_process_ret_0(processor)) * 10.0, 0);
   outputs[CHORD_OUT].setVoltage(fix_to_float(Processor_chord_process_ret_1(processor)) * 10.0, 1);
   outputs[CHORD_OUT].setVoltage(fix_to_float(Processor_chord_process_ret_2(processor)) * 10.0, 2);
   outputs[CHORD_OUT].setChannels(3);
   // output scale, cv/oct
   fix16_t scale[12];
   int nbNotes = Processor_chord_getScale(processor, scale);
   for (int i = 0; i < nbNotes && i < 12; i++) {
      outputs[SCALE_OUT].setVoltage(fix_to_float(scale[i]) * 10.0, i);
   }
   outputs[SCALE_OUT].setChannels(nbNotes);
}

struct UtilChordWidget : ModuleWidget {
   UtilChordWidget(UtilChord *module) {
      setModule(module);
      setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Chord.svg")));

      float big_knob_x = 18.506;
      float av_in_x = 28.364;
      float av_knob_x = 36.361;

      float scale_y = 128.5 - 115.455;
      float chord_y = 128.5 - 103.105;
      float chord_spread_y = 128.5 - 91.104;
      float inv_spread_y = 128.5 - 78.206;
      float jump_y = 128.5 - 66.054;

      addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(big_knob_x, scale_y)), module, UtilChord::SCALE));
      addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(big_knob_x, chord_y)), module, UtilChord::CHORD));
      addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(big_knob_x, chord_spread_y)), module, UtilChord::CHORD_SPREAD));
      addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(big_knob_x, inv_spread_y)), module, UtilChord::INV_SPREAD));
      addParam(createParamCentered<Rogan1PRed>(mm2px(Vec(big_knob_x, jump_y)), module, UtilChord::JUMP));

      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, scale_y)), module, UtilChord::SCALE_AV));
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, chord_y)), module, UtilChord::CHORD_AV));
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, chord_spread_y)), module, UtilChord::CHORD_SPREAD_AV));
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, inv_spread_y)), module,  UtilChord::INV_SPREAD_AV));
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(av_knob_x, jump_y)), module,  UtilChord::JUMP_AV));

      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, scale_y)), module, UtilChord::SCALE_IN));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, chord_y)), module, UtilChord::CHORD_IN));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, chord_spread_y)), module, UtilChord::CHORD_SPREAD_IN));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, inv_spread_y)), module, UtilChord::INV_SPREAD_IN));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(av_in_x, jump_y)), module, UtilChord::JUMP_IN));

      float ins_y = 128.5-28.422;
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.720, ins_y)), module, UtilChord::ROOT));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20.422, ins_y)), module, UtilChord::TRIGGER));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(33.120, ins_y)), module, UtilChord::RESET));

      float outs_y = 128.5-13.609;
      addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.720, outs_y)), module, UtilChord::CHORD_OUT));
      addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(33.120, outs_y)), module, UtilChord::SCALE_OUT));
   }
};

Model *utilChord = createModel<UtilChord, UtilChordWidget>("BotaniaChord");
