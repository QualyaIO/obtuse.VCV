
/* Code automatically generated by Vult https://github.com/modlfo/vult */
#include "engine_utils.h"

void Trigg__ctx_type_0_init(Trigg__ctx_type_0 &_output_){
   Trigg__ctx_type_0 _ctx;
   bool_init_array(128,false,_ctx.triggers);
   _ctx.ticks = 0;
   _ctx.shift = 0;
   fix_init_array(128,0x0 /* 0.000000 */,_ctx.ptriggers);
   _ctx.position = 0;
   _ctx.n = 0;
   _ctx.magnitude = 0x0 /* 0.000000 */;
   _ctx.length = 0;
   _ctx.isautolength = false;
   _ctx.evolve = 0x0 /* 0.000000 */;
   _ctx.divider = 0;
   _ctx.dirty = false;
   _ctx.density = 0x0 /* 0.000000 */;
   _ctx.balance = 0x0 /* 0.000000 */;
   Trigg_default(_ctx);
   _output_ = _ctx;
   return ;
}

void Trigg__refresh(Trigg__ctx_type_0 &_ctx){
   if(_ctx.dirty || ((_ctx.evolve > 0x0 /* 0.000000 */) && (fix_random() <= _ctx.evolve))){
      int i;
      i = 0;
      while((i < 128) && (i < _ctx.length)){
         if(_ctx.dirty || ((_ctx.magnitude > 0x0 /* 0.000000 */) && (fix_random() <= _ctx.magnitude))){
            _ctx.triggers[i] = ((_ctx.ptriggers[i] > 0x0 /* 0.000000 */) && (fix_random() <= _ctx.ptriggers[i]));
         }
         i = (1 + i);
      }
   }
   _ctx.dirty = false;
}

int Trigg_process(Trigg__ctx_type_0 &_ctx){
   int trig;
   trig = 0;
   _ctx.ticks = (1 + _ctx.ticks);
   if(_ctx.length > 0){
      if((_ctx.divider > 0) && (((_ctx.shift + _ctx.ticks) % _ctx.divider) == 0)){
         if(_ctx.triggers[((_ctx.n + _ctx.position) % _ctx.length)]){
            trig = 1;
         }
         _ctx.n = (1 + _ctx.n);
      }
      if((_ctx.ticks % _ctx.divider) == 0){
         _ctx.ticks = 0;
      }
      if((_ctx.n % _ctx.length) == 0){
         Trigg__refresh(_ctx);
         _ctx.n = 0;
      }
   }
   return trig;
}

void Trigg__recompute(Trigg__ctx_type_0 &_ctx){
   fix16_t mod;
   mod = 0x0 /* 0.000000 */;
   mod = fix_div(0x10000 /* 1.000000 */,_ctx.density);
   fix16_t max_p;
   max_p = 0x10000 /* 1.000000 */;
   fix16_t min_p;
   min_p = 0x0 /* 0.000000 */;
   if((mod > 0x10000 /* 1.000000 */) && (_ctx.length > 0)){
      fix16_t fnbplus;
      fnbplus = fix_mul(_ctx.density,int_to_fix(_ctx.length));
      int nbplus;
      nbplus = fix_to_int(fnbplus);
      if((fnbplus % 0x10000 /* 1.000000 */) > 0x200 /* 0.007812 */){
         nbplus = (1 + nbplus);
      }
      int nbminus;
      nbminus = (_ctx.length + (- nbplus));
      fix16_t modp;
      modp = fix_div(int_to_fix(nbplus),int_to_fix(_ctx.length));
      if(modp >= _ctx.density){
         max_p = fix_div(fix_mul(_ctx.density,int_to_fix(_ctx.length)),int_to_fix(nbplus));
      }
      else
      {
         min_p = fix_div(((- int_to_fix(nbplus)) + fix_mul(_ctx.density,int_to_fix(_ctx.length))),int_to_fix(nbminus));
      }
   }
   int imod;
   imod = fix_to_int(mod);
   fix16_t accmod;
   accmod = 0x0 /* 0.000000 */;
   int i;
   i = 0;
   int ci;
   ci = 0;
   uint8_t upmod;
   upmod = false;
   while((i < 128) && (i < _ctx.length)){
      if(imod > 0){
         if(accmod >= 0xfe00 /* 0.992188 */){
            imod = (1 + fix_to_int(mod));
            accmod = (-0x10000 /* -1.000000 */ + accmod);
            upmod = true;
         }
         if((ci % imod) == 0){
            _ctx.ptriggers[i] = (_ctx.density + fix_mul(_ctx.balance,(max_p + (- _ctx.density))));
            if(upmod){
               imod = fix_to_int(mod);
               upmod = false;
            }
            ci = 0;
            accmod = (accmod + (mod % 0x10000 /* 1.000000 */));
         }
         else
         {
            _ctx.ptriggers[i] = (_ctx.density + (- fix_mul(_ctx.balance,(_ctx.density + (- min_p)))));
         }
      }
      else
      {
         _ctx.ptriggers[i] = _ctx.density;
      }
      ci = (1 + ci);
      i = (1 + i);
   }
}

int Trigg__getAutolength(Trigg__ctx_type_0 &_ctx){
   if(_ctx.density <= 0x0 /* 0.000000 */){
      return 0;
   }
   fix16_t mod;
   mod = fix_div(0x10000 /* 1.000000 */,_ctx.density);
   fix16_t autolength;
   autolength = fix_floor(mod);
   int iautolength;
   iautolength = fix_to_int(autolength);
   fix16_t mine;
   mine = 0x200 /* 0.007812 */;
   if((mod % 0x10000 /* 1.000000 */) > mine){
      autolength = fix_mul(mod,fix_div(0x10000 /* 1.000000 */,(mod % 0x10000 /* 1.000000 */)));
      if((autolength % 0x10000 /* 1.000000 */) > mine){
         iautolength = fix_to_int((0x10000 /* 1.000000 */ + autolength));
      }
      else
      {
         iautolength = fix_to_int(autolength);
      }
   }
   return iautolength;
}

uint8_t Trigg__applyLength(Trigg__ctx_type_0 &_ctx, int newLength){
   newLength = int_clip(newLength,0,128);
   if(newLength != _ctx.length){
      _ctx.length = newLength;
      Trigg__recompute(_ctx);
      _ctx.dirty = true;
      if(_ctx.length <= _ctx.n){
         Trigg_restartLoop(_ctx);
      }
      else
      {
         Trigg__refresh(_ctx);
      }
      return true;
   }
   return false;
}

void Trigg_setLength(Trigg__ctx_type_0 &_ctx, int newLength){
   newLength = int_clip(newLength,0,128);
   if((newLength == 0) && bool_not(_ctx.isautolength)){
      _ctx.isautolength = true;
      newLength = Trigg__getAutolength(_ctx);
   }
   else
   {
      if((newLength > 0) && _ctx.isautolength){
         _ctx.isautolength = false;
      }
   }
   Trigg__applyLength(_ctx,newLength);
}

void Trigg_setBalance(Trigg__ctx_type_0 &_ctx, fix16_t newBalance){
   newBalance = fix_clip(newBalance,0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
   if(newBalance != _ctx.balance){
      _ctx.balance = newBalance;
      Trigg__recompute(_ctx);
      _ctx.dirty = true;
      Trigg__refresh(_ctx);
   }
}

void Trigg_setDensity(Trigg__ctx_type_0 &_ctx, fix16_t newDensity){
   newDensity = fix_clip(newDensity,0x0 /* 0.000000 */,0x10000 /* 1.000000 */);
   if(newDensity != _ctx.density){
      _ctx.density = newDensity;
      uint8_t update;
      update = true;
      if(_ctx.isautolength){
         update = bool_not(Trigg__applyLength(_ctx,Trigg__getAutolength(_ctx)));
      }
      if(update){
         Trigg__recompute(_ctx);
         _ctx.dirty = true;
         Trigg__refresh(_ctx);
      }
   }
}

void Trigg_default(Trigg__ctx_type_0 &_ctx){
   _ctx.divider = 1;
   _ctx.length = 16;
   _ctx.density = 0x8000 /* 0.500000 */;
   _ctx.balance = 0x8000 /* 0.500000 */;
   _ctx.evolve = 0x3333 /* 0.200000 */;
   _ctx.magnitude = 0x4000 /* 0.250000 */;
   Trigg__recompute(_ctx);
   _ctx.dirty = true;
   Trigg__refresh(_ctx);
}

void Processor_trigg__ctx_type_0_init(Processor_trigg__ctx_type_0 &_output_){
   Processor_trigg__ctx_type_0 _ctx;
   _ctx.trign = 0;
   Trigg__ctx_type_0_init(_ctx.trigg);
   _ctx.tail = 0;
   _ctx.fs = 0x0 /* 0.000000 */;
   Util__ctx_type_3_init(_ctx._inst73b);
   Util__ctx_type_1_init(_ctx._inst551);
   Util__ctx_type_3_init(_ctx._inst43b);
   Util__ctx_type_1_init(_ctx._inst351);
   Util__ctx_type_3_init(_ctx._inst223b);
   Util__ctx_type_3_init(_ctx._inst193b);
   Util__ctx_type_3_init(_ctx._inst163b);
   Util__ctx_type_3_init(_ctx._inst13b);
   Util__ctx_type_3_init(_ctx._inst133b);
   Util__ctx_type_3_init(_ctx._inst103b);
   _output_ = _ctx;
   return ;
}

int Processor_trigg_process(Processor_trigg__ctx_type_0 &_ctx, fix16_t clock, fix16_t reset){
   int trigger;
   trigger = 0;
   if((_ctx.trign > 0) && (_ctx.trign < _ctx.tail)){
      _ctx.trign = (1 + _ctx.trign);
      trigger = 1;
   }
   else
   {
      _ctx.trign = 0;
   }
   if(Util_edge(_ctx._inst351,(reset >= 0x1999 /* 0.100000 */))){
      Trigg_reset(_ctx.trigg);
   }
   if(Util_edge(_ctx._inst551,(clock >= 0x1999 /* 0.100000 */))){
      int newTrigger;
      newTrigger = Trigg_process(_ctx.trigg);
      if(newTrigger > 0){
         trigger = 1;
         _ctx.trign = 1;
      }
   }
   return trigger;
}


