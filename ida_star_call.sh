#!/bin/bash

micro="addtl_test_suite/microban0"
out="results/ida_star/"
filemicro="microban0"
txt=".txt"

set -o noclobber

for i in {1..9}
do
	file="$micro$i"
	echo $file
	filename="$filemicro$i"
	echo $filename
	outFile="$out$filename$txt"
	echo $outFile
	gtimeout 180 bin/ida_star_test true $file >| $outFile
done

micro="addtl_test_suite/microban"
filemicro="microban"

for i in {10..99}
do
	file="$micro$i"
        echo $file
        filename="$filemicro$i"
        echo $filename
        outFile="$out$filename$txt"
        echo $outFile
	gtimeout 180 bin/ida_star_test true $file >| $outFile
done
