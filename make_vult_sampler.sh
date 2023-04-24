#!/bin/bash

# transpiling all samplers.
# 1st parameter: name / path to vultc
# 2nd parameter: path to the processor wrapper

# loop all instruments in the sampler, retrieve id
for i in `ls -d botania/vult/synth_sampler/*/ | cut -f4 -d'/'`; do
    echo "Generate Sampler synth $i"
    # uppercase first letter of id 
    # WARNING: only works with bash >= 4
    PREFIX="synthSampler${i^}"
    # special treatment for default instrument
    if [ $i == "ocarina" ] ; then
	PREFIX="synthSampler"
    fi
    $1 -ccode $2 -i botania/vult -i botania/vult/synth_sampler -i botania/vult/buffer_medium -i botania/vult/synth_sampler/$i -o src/engine_${PREFIX} -output-prefix ${PREFIX}_ -real fixed 
done

