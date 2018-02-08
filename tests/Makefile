

test-assemble/%: ../asm
	rm -f /tmp/our-champ.cor
	rm -f /tmp/their-champ.cor
	../asm ../resources/$* -o /tmp/our-champ.cor
	$(REFERENCE_ASM) ../resources/$* -o /tmp/their-champ.cor
	bash -c 'diff <(xxd /tmp/our-champ.cor) <(xxd /tmp/their-champ.cor)'

