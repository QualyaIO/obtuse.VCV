#include "plugin.hpp"
#include "engine_synthDrummer.h"
#include "engine_synthDrummerBbox.h"
#include "engine_synthDrummerFoleyType.h"
#include "engine_synthDrummerNes.h"
#include "engine_synthDrummerTamaRockstar.h"

// handle the various drummer
struct MetaDrummer {

   // all variants of the drummer
   synthDrummer_Processor_process_type processor808;
   synthDrummerBbox_Processor_process_type processorBbox;
   synthDrummerFoleyType_Processor_process_type processorFoleyType;
   synthDrummerNes_Processor_process_type processorNes;
   synthDrummerTamaRockstar_Processor_process_type processorTamaRockstar;

   int selectedKit = -1;

   // to sync with the actual number of drum kits...
   static int getNbKits() { return 5;};
   static std::string getKitName(int kit) {
      switch(kit) {
      case 1:
         return "Bbox";
      case 2:
         return "FoleyType";
      case 3:
         return "NES";
      case 4:
         return "TamaRockstar";
      case 0:
      default:
         return "808";
      }
   };

   // will (re)init corresponding processor upon change
   void switchTo(int kit);
   // wrapping functions
   void setSamplerate(float sr);
   void nbCables(int cables);
   void setNote(float gate, float voct, float vel, int c);
   void setPitchBend(float semitones);
   float process();

private:
   // initialize current processor
   void initProc();
};

void MetaDrummer::switchTo(int kit) {
   kit = clamp(kit, 0, getNbKits()-1);
   if (kit != selectedKit) {
      selectedKit = kit;
      initProc();
   }
}

void MetaDrummer::setSamplerate(float sr) {
   switch(selectedKit) {
   case 1:
      synthDrummerBbox_Processor_setSamplerate(processorBbox, float_to_fix(sr));
      break;
   case 2:
      synthDrummerFoleyType_Processor_setSamplerate(processorFoleyType, float_to_fix(sr));
      break;
   case 3:
      synthDrummerNes_Processor_setSamplerate(processorNes, float_to_fix(sr));
      break;
   case 4:
      synthDrummerTamaRockstar_Processor_setSamplerate(processorTamaRockstar, float_to_fix(sr));
      break;
   case 0:
   default:
      synthDrummer_Processor_setSamplerate(processor808, float_to_fix(sr));
      break;
   }
}

void MetaDrummer::nbCables(int cables) {
   switch(selectedKit) {
   case 1:
      synthDrummerBbox_Processor_nbCables(processorBbox, cables);
      break;
   case 2:
      synthDrummerFoleyType_Processor_nbCables(processorFoleyType, cables);
      break;
   case 3:
      synthDrummerNes_Processor_nbCables(processorNes, cables);
      break;
   case 4:
      synthDrummerTamaRockstar_Processor_nbCables(processorTamaRockstar, cables);
      break;
   case 0:
   default:
      synthDrummer_Processor_nbCables(processor808, cables);
      break;
   }
}


void MetaDrummer::setPitchBend(float semitones) {
   switch(selectedKit) {
   case 1:
      synthDrummerBbox_Processor_setPitchBend(processorBbox, float_to_fix(semitones));
      break;
   case 2:
      synthDrummerFoleyType_Processor_setPitchBend(processorFoleyType, float_to_fix(semitones));
      break;
   case 3:
      synthDrummerNes_Processor_setPitchBend(processorNes, float_to_fix(semitones));
      break;
   case 4:
      synthDrummerTamaRockstar_Processor_setPitchBend(processorTamaRockstar, float_to_fix(semitones));
      break;
   case 0:
   default:
      synthDrummer_Processor_setPitchBend(processor808, float_to_fix(semitones));
      break;
   }
}


void MetaDrummer::setNote(float gate, float voct, float vel, int c) {
   switch(selectedKit) {
   case 1:
      synthDrummerBbox_Processor_setNote(processorBbox, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 2:
      synthDrummerFoleyType_Processor_setNote(processorFoleyType, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 3:
      synthDrummerNes_Processor_setNote(processorNes, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 4:
      synthDrummerTamaRockstar_Processor_setNote(processorTamaRockstar, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   case 0:
   default:
      synthDrummer_Processor_setNote(processor808, float_to_fix(gate), float_to_fix(voct), float_to_fix(vel), c);
      break;
   }
}

float MetaDrummer::process() {
   switch(selectedKit) {
   case 1:
      return fix_to_float(synthDrummerBbox_Processor_process(processorBbox));
   case 2:
      return fix_to_float(synthDrummerFoleyType_Processor_process(processorFoleyType));
   case 3:
      return fix_to_float(synthDrummerNes_Processor_process(processorNes));
   case 4:
      return fix_to_float(synthDrummerTamaRockstar_Processor_process(processorTamaRockstar));
   case 0:
   default:
      return fix_to_float(synthDrummer_Processor_process(processor808));
   }
}

void MetaDrummer::initProc() {
   switch(selectedKit) {
   case 1:
      synthDrummerBbox_Processor_process_init(processorBbox);
      break;
   case 2:
      synthDrummerFoleyType_Processor_process_init(processorFoleyType);
      break;
   case 3:
      synthDrummerNes_Processor_process_init(processorNes);
      break;
   case 4:
      synthDrummerTamaRockstar_Processor_process_init(processorTamaRockstar);
      break;
   case 0:
   default:
      synthDrummer_Processor_process_init(processor808);
      break;
   }
}

// naming the kits
struct KitQuantity : ParamQuantity {
	std::string getDisplayValueString() override {
           return std::to_string(int(getValue())) + " - " + MetaDrummer::getKitName(int(getValue()));
	}
};


struct SynthDrummer : Module {

   enum ParamIds {
      KIT,
      NUM_PARAMS
   };
   enum InputIds {
      VOCT,
      GATE,
      VEL,
      BEND,
      NUM_INPUTS
   };
   enum OutputIds {
      OUT,
      NUM_OUTPUTS
   };
   enum LightIds { NUM_LIGHTS };

   MetaDrummer drummer;

   SynthDrummer();
   // pass all parameters to engine. force: engine will pass params even if not changed, use upon init
   void sendParams(bool force=false);
   void process(const ProcessArgs &args) override;
};

SynthDrummer::SynthDrummer() {
   config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

   configParam<KitQuantity>(SynthDrummer::KIT, 0, MetaDrummer::getNbKits()-1, 0, "Kit", "");
   paramQuantities[KIT]->snapEnabled = true;

   sendParams(true);
}

void SynthDrummer::sendParams(bool force) {
   // sync current processor
   drummer.switchTo(int(params[KIT].getValue()));
}

void SynthDrummer::process(const ProcessArgs &args) {
   // update parameters
   drummer.setSamplerate(args.sampleRate/1000.0);
   sendParams();
 
   // retrieve current max number of channels for gate and v/oct
   int channels =
      std::max(
               std::max(inputs[GATE].getChannels(), inputs[VOCT].getChannels()),
               inputs[VEL].getChannels());
   drummer.nbCables(channels);
   // pass each note to the synth
   for (int c = 0; c < channels; c++) {
      // Reads all the input values and normalizes the values
      float gate = inputs[GATE].getPolyVoltage(c) / 10.0f;
      float voct = inputs[VOCT].getPolyVoltage(c) / 10.0f;
      float vel = inputs[VEL].getPolyVoltage(c) / 10.0f;
      drummer.setNote(gate, voct, vel, c);
   }

   // pitch bend, -5: -2 seminotes, +5: +2 semitones
   drummer.setPitchBend(inputs[BEND].getVoltage() / 2.5f);

   // out is audio, set to audio range (-5..5)
   outputs[OUT].setVoltage(drummer.process() * 5.0f);
}

struct SynthDrummerWidget : ModuleWidget {
   SynthDrummerWidget(SynthDrummer *module) {
      setModule(module);

      setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SynthDrummer.svg")));

      float port_x = 5.082;
      addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(port_x, 128.5-78.258)), module, SynthDrummer::KIT));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(port_x, 128.5-66.330)), module, SynthDrummer::VOCT));
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(port_x, 128.5-55.190)), module, SynthDrummer::GATE));

      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(port_x, 128.5-43.745)), module, SynthDrummer::VEL));

      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(port_x, 128.5-32.310)), module, SynthDrummer::BEND));

      addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(port_x, 128.5-19.564)), module, SynthDrummer::OUT));

   }
};

Model *synthDrummer = createModel<SynthDrummer, SynthDrummerWidget>("BotaniaSynthDrummer");
