#!/bin/sh

## look for beginning of desired summary table
start="TrigReport............Modules.in.Path:.p1"
a=`sed -ne /$start/= $1`

## determine end of desired summary table from beginning of next table
end="TrigReport............Module.Summary"
z=`sed -ne /$end/= $1`
z=`expr $z - 2`

## output table (from line a to z)
head -n $z $1 | tail -n+$a
