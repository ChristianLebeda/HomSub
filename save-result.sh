#!/usr/bin/env bash

if (($#)); then
    DATE="`date +%y-%m-%d_%H-%M-%S`"
    HOST="`hostname`"
    OUTDIR="ExperimentsResults/logs/$DATE""_$HOST"
    mkdir -p $OUTDIR
    echo "Copying $1 to $OUTDIR"
    cp $1 "$OUTDIR/"
    echo "Using git revision `git rev-parse HEAD`" > $OUTDIR/experiment.log
else
    echo "Missing name of output from experiment"
fi
