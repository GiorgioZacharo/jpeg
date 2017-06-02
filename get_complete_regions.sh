grep complete  REG_*/aladdin_run/conf-cyclic &> complete_regs.txt
for i in {0..19}; do grep REG_$i/ complete_regs.txt |  tee /dev/tty | wc -l &>> complete_regs_number.txt; done
