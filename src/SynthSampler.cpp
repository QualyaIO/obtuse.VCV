#include "plugin.hpp"
#include "engine_synthSampler.h"

struct SynthSampler : Module {

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

   synthSampler_Processor_process_type processor;

   SynthSampler();
   void process(const ProcessArgs &args) override;
};

SynthSampler::SynthSampler() {
   config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

   synthSampler_Processor_process_init(processor);
}

void SynthSampler::process(const ProcessArgs &args) {
   // update parameters
   synthSampler_Processor_setSamplerate(processor, float_to_fix(args.sampleRate/1000.0));

   // retrieve current max number of channels for gate and v/oct
   int channels =
      std::max(
               std::max(inputs[GATE].getChannels(), inputs[VOCT].getChannels()),
               inputs[VEL].getChannels());
   synthSampler_Processor_nbCables(processor, channels);
   // pass each note to the synth
   for (int c = 0; c < channels; c++) {
      // Reads all the input values and normalizes the values
      float gate = inputs[GATE].getPolyVoltage(c) / 10.0f;
      float voct = inputs[VOCT].getPolyVoltage(c) / 10.0f;
      float vel = inputs[VEL].getPolyVoltage(c) / 10.0f;
      synthSampler_Processor_setNote(processor, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
   }

   // out is audio, set to audio range (-5..5)
   outputs[OUT].setVoltage(fix_to_float(synthSampler_Processor_process(processor) * 5.0f));
}

struct SynthSamplerWidget : ModuleWidget {
   SynthSamplerWidget(SynthSampler *module) {
      setModule(module);

      setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SynthSampler.svg")));

      float port_x = 5.08;
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(port_x, 128.5-70.923)), module, SynthSampler::VOCT));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(port_x, 128.5-57.129)), module, SynthSampler::GATE));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(port_x, 128.5-43.362)), module, SynthSampler::VEL));

      addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(port_x, 128.5-28.03)), module, SynthSampler::OUT));
   }
};

Model *synthSampler = createModel<SynthSampler, SynthSamplerWidget>("BotaniaSynthSampler");
