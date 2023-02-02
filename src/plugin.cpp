#include "plugin.hpp"

Plugin *pluginInstance;

void init(Plugin *p) {
   pluginInstance = p;

   p->addModel(effectReverb);
   p->addModel(effectSVF);
   p->addModel(effectCombFF);
   p->addModel(effectCombFB);
   p->addModel(synthFM);
   p->addModel(synthSampler);
   p->addModel(synthDrummer);
}
