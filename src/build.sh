#!/bin/sh
g++ -o fasta_to_plain fasta_to_plain.cpp
g++ -o mix0 mix0.cpp
g++ -o background_genome_mono background_genome_mono.cpp
chmod a+x fasta_to_plain 
chmod a+x mix0
chmod a+x background_genome_mono
