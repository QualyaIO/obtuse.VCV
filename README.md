

Based on Vult Playground for VCV Rack -- testing Botania DSP within VCV.


# How-to

Define `RACK_DIR` and ponit to Rack SDK folder (to be downloaded separately). Then `make`.

To install, place or link the folder in VCV plugins folder, e.g. on Linux `~/.Rack2/plugins`.

# Modifying the code

All the code is contained in the file `processor.vult`. This file contains the function `process` that receives four inputs and returns four outputs. Here are a few code examples:

Four Channels Mixer
```
fun process(in1:real, in2:real, in3:real, in4:real) {
   mem param1, param2, param3, param4;
   val out1, out2, out3, out4 = 0.0, 0.0, 0.0, 0.0;

   // all inputs mixed to out1
   out1 = in1 * param1 + param2 * in2 + param3 * in3 + param4 * in3;

   return out1, out2, out3, out4;
}
```

Simple VCA
```
fun process(in1:real, in2:real, in3:real, in4:real) {
   mem param1, param2, param3, param4;
   val out1, out2, out3, out4 = 0.0, 0.0, 0.0, 0.0;

   out1 = in1 * in2;

   return out1, out2, out3, out4;
}
```
