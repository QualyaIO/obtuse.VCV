#include "plugin.hpp"

Plugin *pluginInstance;

void init(Plugin *p) {
   pluginInstance = p;

   p->addModel(effectReverb);
   p->addModel(effectSVF);
   p->addModel(effectCombFF);
   p->addModel(effectCombFB);
   p->addModel(effectAllpass);
   p->addModel(effectSaturator);
   p->addModel(synthFM);
   p->addModel(synthSampler);
   p->addModel(synthDrummer);
   p->addModel(utilTrigg);
   p->addModel(utilClock);
   p->addModel(utilChord);
   p->addModel(utilArp);
   p->addModel(utilGate);
}
