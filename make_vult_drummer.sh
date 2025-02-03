#!/bin/bash

# transpiling all drummers.
# 1st parameter: name / path to vultc
# 2nd parameter: path to the processor wrapper

# loop all instruments in the sampler, retrieve id
for i in `ls -d obtuse/vult/synth_drummer/*/ | cut -f4 -d'/'`; do
    echo "Generate Drummer synth $i"
    # uppercase first letter of id 
    # WARNING: only works with bash >= 4
    PREFIX="synthDrummer${i^}"
    # special treatment for default instrument
    if [ $i == "808" ] ; then
	PREFIX="synthDrummer"
    fi
    $1 -ccode $2 -i obtuse/vult -i obtuse/vult/synth_drummer -i obtuse/vult/buffer_medium -i obtuse/vult/synth_drummer/$i -o src/engine_${PREFIX} -output-prefix ${PREFIX}_ -real fixed 
done

