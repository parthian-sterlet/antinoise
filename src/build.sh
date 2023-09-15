#!/bin/sh
g++ -o background_genome_mono.exe background_genome_mono.cpp
g++ -o bed_chr_mask.exe bed_chr_mask.cpp
g++ -o bed_chr_separation.exe bed_chr_separation.cpp
g++ -o bed_sort.exe bed_sort.cpp
g++ -o fasta_muliplefiles.exe fasta_muliplefiles.cpp
g++ -o fasta_to_plain0.exe fasta_to_plain0.cpp
g++ -o longext_many.exe longext_many.cpp
g++ -o mix0 mix0.cpp

chmod a+x background_genome_mono.exe
chmod a+x bed_chr_mask.exe
chmod a+x bed_chr_separation.exe
chmod a+x bed_sort.exe
chmod a+x fasta_muliplefiles.exe
chmod a+x fasta_to_plain0.exe
chmod a+x longext_many.exe
chmod a+x mix0.exe
chmod a+x mask.pl
chmod a+x no_mask.pl
chmod a+x mask_run
chmod a+x no_mask_run
