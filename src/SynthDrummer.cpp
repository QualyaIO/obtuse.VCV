#include "plugin.hpp"
#include "engine_synthDrummer.h"

struct SynthDrummer : Module {

   enum ParamIds {
      NUM_PARAMS
   };
   enum InputIds {
      VOCT,
      GATE,
      VEL,
      NUM_INPUTS
   };
   enum OutputIds {
      OUT,
      NUM_OUTPUTS
   };
   enum LightIds { NUM_LIGHTS };

   synthDrummer_Processor_process_type processor;

   SynthDrummer();
   void process(const ProcessArgs &args) override;
};

SynthDrummer::SynthDrummer() {
   config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

   synthDrummer_Processor_process_init(processor);
}

void SynthDrummer::process(const ProcessArgs &args) {
   // update parameters
   synthDrummer_Processor_setSamplerate(processor, float_to_fix(args.sampleRate/1000.0));
 
   // retrieve current max number of channels for gate and v/oct
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

   // out is audio, set to audio range (-5..5)
   outputs[OUT].setVoltage(fix_to_float(synthDrummer_Processor_process(processor) * 5.0f));
}

struct SynthDrummerWidget : ModuleWidget {
   SynthDrummerWidget(SynthDrummer *module) {
      setModule(module);

      setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SynthDrummer.svg")));

      float port_x = 5.08;
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(port_x, 128.5-70.923)), module, SynthDrummer::VOCT));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(port_x, 128.5-57.129)), module, SynthDrummer::GATE));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(port_x, 128.5-43.362)), module, SynthDrummer::VEL));

      addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(port_x, 128.5-28.03)), module, SynthDrummer::OUT));

   }
};

Model *synthDrummer = createModel<SynthDrummer, SynthDrummerWidget>("BotaniaSynthDrummer");
