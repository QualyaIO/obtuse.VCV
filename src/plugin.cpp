#include "plugin.hpp"

Plugin *pluginInstance;

void init(Plugin *p) {
   pluginInstance = p;

   p->addModel(effects);
   p->addModel(synthFM);
   p->addModel(synthSampler);
   p->addModel(synthDrummer);
}
