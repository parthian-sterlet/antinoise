#!/bin/sh
#!/bin/sh

chmod a+x mask.pl
chmod a+x no_mask.pl
chmod a+x command_line_simple
chmod a+x command_line_no_mask
chmod a+x command_line_blacklisted
chmod a+x command_line_whitelisted

cd ..
cd src

g++ -o area_self_overlap.exe area_self_overlap.cpp
g++ -o background_genome_mono.exe background_genome_mono.cpp
g++ -o bed_chr_mask.exe bed_chr_mask.cpp
g++ -o bed_chr_separation.exe bed_chr_separation.cpp
g++ -o bed_sort.exe bed_sort.cpp
g++ -o fasta_muliplefiles.exe fasta_muliplefiles.cpp
g++ -o fasta_to_plain0.exe fasta_to_plain0.cpp
g++ -o longext_many.exe longext_many.cpp
g++ -o mix0.exe mix0.cpp

chmod a+x area_self_overlap.exe
chmod a+x background_genome_mono.exe
chmod a+x bed_chr_mask.exe
chmod a+x bed_chr_separation.exe
chmod a+x bed_sort.exe
chmod a+x fasta_muliplefiles.exe
chmod a+x fasta_to_plain0.exe
chmod a+x longext_many.exe
chmod a+x mix0.exe
