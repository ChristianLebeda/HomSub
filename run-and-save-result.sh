#!/usr/bin/env bash

if (($#)); then
    DATE="`date +%y-%m-%d_%H-%M-%S`"
    HOST="`hostname`"
    OUTDIR="ExperimentsResults/logs/$DATE""_$HOST"
    mkdir -p $OUTDIR
    echo "Running experiement $@"
    echo "Saving result in $OUTDIR"
    time(
        echo "Using git revision `git rev-parse HEAD`"
        $@ -csv > $OUTDIR/experiment.csv
    ) &> $OUTDIR/experiment.log
else
    echo "Missing name of output from experiment"
fi
