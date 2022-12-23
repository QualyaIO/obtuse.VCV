#include "plugin.hpp"
#include "engine_synthDrummer.h"

struct SynthDrummer : Module {

   enum ParamIds {
      KNOB1,
      KNOB2,
      KNOB3,
      KNOB4,

      MOD1,
      MOD2,
      MOD3,
      MOD4,

      NUM_PARAMS
   };
   enum InputIds {
      MOD_IN1,
      MOD_IN2,
      MOD_IN3,
      MOD_IN4,

      GATE,
      VOCT,
      VEL,
      IN4,

      NUM_INPUTS
   };
   enum OutputIds {
      OUT1,
      OUT2,
      OUT3,
      OUT4,

      NUM_OUTPUTS
   };
   enum LightIds { NUM_LIGHTS };

   synthDrummer_Processor_process_type processor;

   SynthDrummer();
   void process(const ProcessArgs &args) override;
};

SynthDrummer::SynthDrummer() {
   config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

   configParam(SynthDrummer::KNOB1, 0.0, 1.0, 0.5, "Knob 1", " %", 0.0f, 100.f);
   configParam(SynthDrummer::KNOB2, 0.0, 1.0, 0.5, "Knob 2", " %", 0.0f, 100.f);
   configParam(SynthDrummer::KNOB3, 0.0, 1.0, 0.5, "Knob 3", " %", 0.0f, 100.f);
   configParam(SynthDrummer::KNOB4, 0.0, 1.0, 0.5, "Knob 4", " %", 0.0f, 100.f);

   configParam(SynthDrummer::MOD1, -1.0, 1.0, 0.0, "Mod 1", " %", 0.0f, 100.f);
   configParam(SynthDrummer::MOD2, -1.0, 1.0, 0.0, "Mod 2", " %", 0.0f, 100.f);
   configParam(SynthDrummer::MOD3, -1.0, 1.0, 0.0, "Mod 3", " %", 0.0f, 100.f);
   configParam(SynthDrummer::MOD4, -1.0, 1.0, 0.0, "Mod 4", " %", 0.0f, 100.f);

   synthDrummer_Processor_process_init(processor);
}

void SynthDrummer::process(const ProcessArgs &args) {
   // retrieve current max number of channels for gate and v/oct
   // FIXME: reset notes upon count change
   int channels =
      std::max(
               std::max(inputs[GATE].getChannels(), inputs[VOCT].getChannels()),
               inputs[VEL].getChannels());
   synthDrummer_Processor_nbCables(processor, channels);
   // pass each note to the synth
   for (int c = 0; c < channels; c++) {
      // Reads all the input values and normalizes the values
      float gate = inputs[GATE].getPolyVoltage(c) / 10.0f;
      float voct = inputs[VOCT].getPolyVoltage(c) / 10.0f;
      float vel = inputs[VEL].getPolyVoltage(c) / 10.0f;
      synthDrummer_Processor_setNote(processor, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
   }

   // others input and parameters unused
   float in4 = inputs[IN4].getVoltage() / 10.0f;
   float mod_in1 = inputs[MOD_IN1].getVoltage() / 10.0f;
   float mod_in2 = inputs[MOD_IN2].getVoltage() / 10.0f;
   float mod_in3 = inputs[MOD_IN3].getVoltage() / 10.0f;
   float mod_in4 = inputs[MOD_IN4].getVoltage() / 10.0f;

   // Reads all the parameters and sets them.
   // The parameters could be set at a lower rate if needed
   {
      float knob1 = params[KNOB1].getValue();
      float knob2 = params[KNOB2].getValue();
      float knob3 = params[KNOB3].getValue();
      float knob4 = params[KNOB4].getValue();
      float mod1 = params[MOD1].getValue();
      float mod2 = params[MOD2].getValue();
      float mod3 = params[MOD3].getValue();
      float mod4 = params[MOD4].getValue();

      synthDrummer_Processor_setParam1(processor, knob1, mod1, mod_in1);
      synthDrummer_Processor_setParam2(processor, knob2, mod2, mod_in2);
      synthDrummer_Processor_setParam3(processor, knob3, mod3, mod_in3);
      synthDrummer_Processor_setParam4(processor, knob4, mod4, mod_in4);
   }

   synthDrummer_Processor_process(processor, float_to_fix(in4), float_to_fix(args.sampleRate));

   outputs[OUT1].setVoltage(fix_to_float(synthDrummer_Processor_process_ret_0(processor) * 10.0f));
   outputs[OUT2].setVoltage(fix_to_float(synthDrummer_Processor_process_ret_1(processor) * 10.0f));
   outputs[OUT3].setVoltage(fix_to_float(synthDrummer_Processor_process_ret_2(processor) * 10.0f));
   outputs[OUT4].setVoltage(fix_to_float(synthDrummer_Processor_process_ret_3(processor) * 10.0f));
}

struct SynthDrummerWidget : ModuleWidget {
   SynthDrummerWidget(SynthDrummer *module) {
      setModule(module);

      setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SynthDrummer.svg")));

      addChild(createWidget<ScrewBlack>(Vec(15, 3)));
      addChild(createWidget<ScrewBlack>(Vec(box.size.x - 30, 3)));
      addChild(createWidget<ScrewBlack>(Vec(15, 367)));
      addChild(createWidget<ScrewBlack>(Vec(box.size.x - 30, 367)));

      addParam(createParam<Rogan3PWhite>(Vec(19, 59), module, SynthDrummer::KNOB1));
      addParam(createParam<Rogan3PWhite>(Vec(89, 59), module, SynthDrummer::KNOB2));
      addParam(createParam<Rogan3PWhite>(Vec(19, 130), module, SynthDrummer::KNOB3));
      addParam(createParam<Rogan3PWhite>(Vec(89, 130), module, SynthDrummer::KNOB4));

      for (int i = 0; i < 4; i++) {
         addParam(createParam<RoundSmallBlackKnob>(Vec(10 + 35 * i, 204), module, SynthDrummer::MOD1 + i));
         addInput(createInput<PJ301MPort>(Vec(10 + 35 * i, 238), module, SynthDrummer::MOD_IN1 + i));
      }

      for (int i = 0; i < 4; i++)
         addInput(createInput<PJ301MPort>(Vec(10 + 35 * i, 273), module, SynthDrummer::GATE + i));

      for (int i = 0; i < 4; i++)
         addOutput(createOutput<PJ301MPort>(Vec(10 + 35 * i, 313), module, SynthDrummer::OUT1 + i));
   }
};

Model *synthDrummer = createModel<SynthDrummer, SynthDrummerWidget>("BotaniaSynthDrummer");
