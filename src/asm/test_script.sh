#!/bin/bash

for	i in tests/subjects/*.s; do
	echo "assembling original source file using zaz's assembler: $i"
	./tests/asm $i
	j=`echo $i | sed 's/\.s/\.cor/'`
	echo -n "md5 of zaz's file: "
	md5 $j

	rm -rf assembler.output
	echo ""
	echo ".. assembling using alex's assembler:"
	./asm $i
	echo -n "md5 of alex's file "
	md5 assembler.output
	echo ""
	echo "press 'c' to compare hexdumps, 'q' to quit - or - press any other key for next"
	read -rsn1 input
	if [[ "$input" = "c" ]]; then
		rm -rf zazfile.hex alexfile.hex
		hexdump -C $j > zazfile.hex
		hexdump -C assembler.output > alexfile.hex
		diff -w -y zazfile.hex alexfile.hex
		echo "press any key when done"
		read -rsn1 unused
	elif [[ "$input" = "q" ]]; then
		rm -rf subjects/*.cor
		rm -rf assembler.output
		rm -rf zazfile.hex alexfile.hex
		exit
	fi
done
