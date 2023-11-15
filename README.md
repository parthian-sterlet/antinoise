# AntiNoise - Extraction of genomic background set of DNA sequences for a given foreground set of sequences for subsequent *de novo* motif discovery
# Description
The AntiNoise tool extracts a set of background DNA sequences for given foreground set of sequences. The background sequences are required to perform the motif enrichment analysis in the foreground sequence set, in particular, for *de novo* motif search. Chromatin immunoprecipitation (ChIP)-based high throughput technique ChIP-seq allows genome-scale mapping of transcription factors binding sites (TFBS). Genomic loci or peaks obtained using ChIP-seq technology are hundreds of base pairs in length, but TFBS motifs typically range from 6 to 20 bp in length, e.g. see [CIS-BP database](http://cisbp.ccbr.utoronto.ca/). *De novo* motif search is required to map exact positions of potential TFBS in peaks. The task of *de novo* motif search is to ddiscover motifs specific for the biological function of a target transcription factor (TF) from a ChIP-seq experiment. The *de novo* motif search as a process implies competition between several distinct enriched motifs. To better differentiate between them them and to select the exact values of parameters of each motif model, and additiobal set of background sequences is applied as a complement to the foreground set. This background set excludes artifactual motifs associated with genome-specific sequence content bias such as polyA tracts from the results of *de novo* motif search. For each motif the significance of its enrichment in peaks depends on its excpected recognition rate in the background sequences. Hence, the choice of the background sequence generation approach is very important for the correct definition of the target TF motif. Any custom sequence set  that is not enriched with target TF motifs can be used as a background set. But the genomic background set will reflect the bias of the entire genome, i.e. the expected distribution of frequencies of oligonucleotides of the same lentghs as potential TFBS motifs. The number of sequences in the background set should be at least several times larger than in the foreground set.
Here we introduce a tool that implements an approach to generate a set of background sequences for a given set of foreground sequences derived from a *de novo* motif search. This ’genomic’ approach compiles randomly chosen sequences from the entire reference genome sequences adopting the content of A/T nucleotides according to the sequences from the foreground set, thus modeling an expected content of noise non-specific motifs [(Tsukanov et al., 2022)](https://doi.org/10.3389/fpls.2022.938545). To show the efficency of this 'genomic' approach we provide also another ‘synthetic’ approach destroying the significant enrichment of any motifs through the permutation of nucleotides preserving the nucleotide content. All our experience has definitely supported the genomic approach as the more correct than the synthetic approach. 

Input data of this tool include foreground sequences in BED or FASTA format, and the reference genome sequences in PLAIN format. 

The [major](https://github.com/parthian-sterlet/antinoise/blob/main/src/background_genome_mono.cpp) propgram runs from a [command_line_simple](https://github.com/parthian-sterlet/antinoise/blob/main/run/command_line_simple) using a perl script [simple.pl](https://github.com/parthian-sterlet/antinoise/blob/main/run/simple.pl). This run requires a version of the reference genome in PLAIN format, this version can be either unmasked or masked. 

Two perl scripts [no_mask.pl](https://github.com/parthian-sterlet/antinoise/blob/main/run/no_mask.pl) and [mask.pl](https://github.com/parthian-sterlet/antinoise/blob/main/run/mask.pl) prepare an unmasked version of the reference genome or to apply a particular type of masking to it:
+ (a) background sequences are extracted from an unmasked reference genome, [no_mask.pl](https://github.com/parthian-sterlet/antinoise/blob/main/run/no_mask.pl), [command_line_no_mask](https://github.com/parthian-sterlet/antinoise/blob/main/run/command_line_no_mask), or 
+ (b) background sequences are extracted from a masked reference genome: either 'Exclusion of blacklisted regions' or 'Retention of whitelisted regions' options are available, [mask.pl](https://github.com/parthian-sterlet/antinoise/blob/main/run/mask.pl). 
The blacklisted option excludes specific genomic loci from the entire reference genome, the extraction procedure is applied to the remaining genomic loci, [command_line_blacklisted](https://github.com/parthian-sterlet/antinoise/blob/main/run/command_line_blacklisted). The whitelisted option extracts background sequences only from particular given regions, all remaining loci are excluded from the analysis, [command_line_whitelisted](https://github.com/parthian-sterlet/antinoise/blob/main/run/command_line_whitelisted).

The web service [AntiNoise](https://denovosea.icgbio.ru/antinoise/) implements the genomic approach of background sequences extraction.

# Requirements
The source code is written in C++ language. To compile exetubables from the source code you need:

* In Linux system, C++ compiler, e.g. [GCC](https://gcc.gnu.org/) compiler 
* In Windows system any VC++ package, e.g. [Microsoft Visual Studio Community](https://visualstudio.microsoft.com/vs/community/)

# Repository structure
Folder [**src**](https://github.com/parthian-sterlet/antinoise/tree/main/src) contains the [major](https://github.com/parthian-sterlet/antinoise/blob/main/src/background_genome_mono.cpp) and eight supporting C++ source code files.  

Folder [**run**](https://github.com/parthian-sterlet/antinoise/tree/main/run) contains the three perl scripts and four command line examples, implementing the genomic background sequence extraction approach.

Folder [**examples**](https://github.com/parthian-sterlet/antinoise/tree/main/bin/examples) contains files required as the functional examples of the genomic background sequence extraction approach.

Folder [**genomes/sc64**](https://github.com/parthian-sterlet/antinoise/tree/main/genomes/sc64) contains [whole genome sequences of baker's yeasts *S. cerevisiae*](https://github.com/parthian-sterlet/antinoise/tree/main/genomes/sc64) required for mentioned above functional examples. It is recommended that the reference genomes of other species be placed in the respective subfolders of the [genomes](https://github.com/parthian-sterlet/antinoise/tree/main/genomes) folder for subsequent analysis.

Folder [**bin**](https://github.com/parthian-sterlet/antinoise/tree/main/bin) includes subfolders [**linux**](https://github.com/parthian-sterlet/antinoise/tree/main/bin/linux) and [**windows**](https://github.com/parthian-sterlet/antinoise/tree/main/bin/windows). They contain binary files compiled for linux/windows platforms from all C++ source files.

## 1. Genomic background sequence generation approach
The [major](https://github.com/parthian-sterlet/antinoise/blob/main/src/background_genome_mono.cpp) propgram of this tool finds the genomic background sequences for a particular genome (hg38, mm10, tair10, etc.). The background sequences match almost perfectly A/T content and match exactly the length of DNA sequences from the foreground set.
## 2. Synthetic background sequence generation approach
The alternative program [mix0.cpp](https://github.com/parthian-sterlet/sitega/blob/master/src/mix0.cpp) generates synthetic background sequences that exactly match the nucleotide content of the foreground sequences.

## Supporting C++ programs for the genomic approach
* The program [area_self_overlap.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/area_self_overlap.cpp) converts a genomic annotation file in BED format with possibly overlapping genomic fragments to a file in the same BED format with non- overlapping genomic fragments.
* The program [bed_chr_mask.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/bed_chr_mask.cpp) masks the reference genome sequences in PLAIN format accoridng to the given input annotation in BED format. Masking with 'N' nucleotides is optionally performed either (a) for all fragments listed in the BED file, or (b) for all remaining parts of the reference genome. To mask the reference genome in PLAIN format, the program needs a file in BED format with any c non-overlapping genomic regions. 
* The program [bed_chr_separation.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/bed_chr_separation.cpp) splits a BED file into multiple BED files so that each output file lists annotations for the same chromosome.
* The program [bed_sort.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/bed_sort.cpp) sorts DNA annotations in BED format according to chromosome names and positions.
* The program [fasta_muliplefiles.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/fasta_muliplefiles.cpp) splits a FASTA file with muliple sequences into multiple files so that all output FASTA files match individual sequences. In particular, this program is used to convert a reference genome in one FASTA file with the sequences of all chromosomes merged together into multiple FASTA files of individual chromosomes. Genomes in FASTA format are available on many public servers, e.g. Ensembl for [human](https://ftp.ensembl.org/pub/release-110/fasta/homo_sapiens/dna/). Hence, an easy way to  access the refernce genome is to download it as a single file (e.g. these ones for [human](https://ftp.ensembl.org/pub/release-110/fasta/homo_sapiens/dna/Homo_sapiens.GRCh38.dna.primary_assembly.fa.gz) and [mouse](https://ftp.ensembl.org/pub/release-102/fasta/mus_musculus/dna/Mus_musculus.GRCm38.dna.primary_assembly.fa.gz)), and then to split it into chromosome-specific FASTA files.
* The program [fasta_to_plain0.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/fasta_to_plain0.cpp) converts reference genome DNA sequences  from FASTA format to PLAIN format. This program make the reference genome sequence more convinient for downstream analysis and processing. Unlike the FASTA format, (a) the PLAIN format does not contain the sequence header lines with the first '>' character, (b) the end of line character ('\n' in Linux or '\r\n' in Windows) means only the end of the DNA sequence. Therefore, if a PLAIN file contains only one chromosome, then the end of a line is only allowed at the end of the file.
* The program [longext_many.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/longext_many.cpp) converts a BED file to DNA sequences in FASTA format using reference genome sequences in PLAIN format. 

## Scripts to run AntiNoise starting from the reference genome

* No masking, application to the entire genome as is, without any masking
  
Command line file [command_line_no_mask](https://github.com/parthian-sterlet/antinoise/blob/main/run/command_line_no_mask) and Perl script [no_mask.pl](https://github.com/parthian-sterlet/antinoise/blob/main/run/no_mask.pl) show the example application of the genomic background sequence extraction for a test foreground set in BED format from the *S. cerevisiae* genome. Background sequences are searhed in the full-length sequences of the reference genome. The script starts from one FASTA file containing all chromosomes of certain reference genome, e.g. [the reference sequence of *S. cerevisiae* genome](https://github.com/parthian-sterlet/antinoise/blob/main/genomes/sc64/Saccharomyces_cerevisiae.R64-1-1.dna.toplevel.fa)  This file should taken in the public database, e.g. for [human](https://ftp.ensembl.org/pub/release-110/fasta/homo_sapiens/dna/Homo_sapiens.GRCh38.dna.primary_assembly.fa.gz) and [mouse](https://ftp.ensembl.org/pub/release-102/fasta/mus_musculus/dna/Mus_musculus.GRCm38.dna.primary_assembly.fa.gz). 

* Masking of blacklisted regions, application to the entire genome lacking certain specific blacklisted regions

Command line file [command_line_blacklisted](https://github.com/parthian-sterlet/antinoise/blob/main/run/command_line_blacklisted) and Perl script [mask.pl](https://github.com/parthian-sterlet/antinoise/blob/main/run/mask.pl) show the example application of the genomic background sequence extraction for a test foreground set in BED format from the *S. cerevisiae* genome. This example applies the additional BED file of 'blacklisted' regions. E.g.. those ones for [human](https://github.com/parthian-sterlet/antinoise/blob/main/examples/blacklisted/GRCh38_unified_blacklist.bed) from [ENCODE](https://www.encodeproject.org/files/ENCFF356LFX/) and for [mouse](https://github.com/parthian-sterlet/antinoise/blob/main/examples/blacklisted/ENCODE_ENCFF547MET_mm10.bed) from [ENCODE](https://www.encodeproject.org/files/ENCFF547MET/), see [(Amemiya et al., 2019)](https://doi.org/10.1038/s41598-019-45839-z). This analysis implies masking of genomic fragments of a given annotation in BED format (blacklisted regions), i.e. these regions are excluded from the analysis and they will be omitted in output background genomic sequences

* Retention of whitelisted regions, application is limited to only specific whitelisted regions, all remaining genomic loci are excluded

Command line file [command_line_whitelisted](https://github.com/parthian-sterlet/antinoise/blob/main/run/command_line_blacklisted) and Perl script [mask.pl](https://github.com/parthian-sterlet/antinoise/blob/main/run/mask.pl) show the example application of the genomic background sequence extraction for a test foreground set in BED format from the *S. cerevisiae* genome. This example applies the additional BED file of 'whitelisted' regions. Only these regions  will be able to pass into the output, all other genomic regions will be masked and are subsequently excluded. E.g., an example of whitelisted regions contains promoter regions (5 kb upstream and 100 bp downstream) of mouse protein coding genes [mm10_m5kb_p100_pc.bed](https://github.com/parthian-sterlet/antinoise/blob/main/examples/whitelisted/mm10_m5kb_p100_pc.bed) based on annotation from Genecode [version M25](https://ftp.ebi.ac.uk/pub/databases/gencode/Gencode_mouse/release_M25/).

# How to compile
* In Linux system: 

git clone https://github.com/parthian-sterlet/antinoise

cd antinoise/run

chmod a+x build_linux.sh

./build_linux.sh

* In Windows system:

separate compilation of all source files in VC++
## 1. Background sequences generaration: Genomic

[background_genome_mono.cpp](https://github.com/parthian-sterlet/sitega/blob/master/src/background_genome_mono.cpp)
1. path to whole genome sequences of chromosomes in plain format (the last symbol of path must be '/' and '\\' for Linux and Windows platforms, respectively), see the example of these files in PLAIN format for [the reference sequence of *S. cerevisiae* genome](https://github.com/parthian-sterlet/antinoise/blob/main/genomes/sc64/Saccharomyces_cerevisiae.R64-1-1.dna.toplevel.fa) in [this folder](https://github.com/parthian-sterlet/antinoise/tree/main/genomes/sc64)
2. input FASTA file (foreground set)
3. output FASTA file name without extension (background set), two extensions ".fa" and ".bed" define output files in FASTA and BED formats
4. required number of found background sequences per one foreground sequence, Rbf (default value 5)
5. deviation δ of the A/T nucleotide content of a background sequence from that for a foreground sequence, (default value 0.01)
6. total average number of attempts Na to get background sequences from genome per one foreground sequence (default value 10000)
7. species and genome release (values hg38, mm10, rn6, zf11, dm6, and ce235; at10, gm21, zm73, and mp61; sc64 and sch294). The animals inludes human *Homo sapiens* hg38, mouse *Mus musculus* mm10, rat *Rattus norvegicus* Rnor_6.0, zebrafish *Danio rerio* GRCz11, fly *Drosophila melanogaster* dm6, and roundworm *Caenorhabditis elegans* WBcel235; the plants are arabidopsis *Arabidopsis thaliana* TAIR10, soybean *Glycine max* v2.1, maize *Zea mays* B73, and liverwort *Marchantia polymorpha* MpTak v6.1; the fungi are baker's yeast *Saccharomyces cerevisiae* R64-1-1 and fission yeast *Schizosaccharomyces pombe* ASM294v2.
8. threshold for the fraction of completely processed input sequences allowing to stop calculations (default value 0.99)
9. output file, additional output table compares the A/T content in the foreground and background sequence sets
10. output file, additional output table compares the dinucleotide frequencies in the foreground and background sequence sets
11. output file, additional output table compares (a) the A/T content for all input sequences that did not achieve the required number of found background sequences per one foreground sequence Rbf and (b) the average A/T content for the foreground sequnce set.
12. output file, additional output table compares (a) the dinucleotide frequencies in all input sequences that did not achieve the required number of found background sequences per one foreground sequence Rbf and (b) the average dinucleotide frequencies for the foreground sequnce set.
13. output file, current progress in calculation, the fraction of completely processed foreground sequences, i.e. for each such foreground sequence exactly Rbf background sequences were found 

Example run [command_line_simple](https://github.com/parthian-sterlet/antinoise/blob/main/run/command_line_simple) uses a Perl script [simple.pl](https://github.com/parthian-sterlet/antinoise/blob/main/run/simple.pl). Top 1000 peaks from [GTRD](https://gtrd20-06.biouml.org/) for [ChIP-seq data](https://www.ncbi.nlm.nih.gov/geo/query/acc.cgi?acc=GSM1470164) for TF GCN4 [(Spivak and Stormo, 2016)](https://doi.org/10.1534/g3.115.024331), [*S. cerevisiae* genome](https://ftp.ensemblgenomes.ebi.ac.uk/pub/fungi/release-57/fasta/saccharomyces_cerevisiae/dna/Saccharomyces_cerevisiae.R64-1-1.dna.toplevel.fa.gz) here and below provide examples of the tool.

## Script to run AntiNoise starting from FASTA or BED foregrand sequences and the reference genome in PLAIN format
* [simple.pl](https://github.com/parthian-sterlet/antinoise/blob/main/run/simple.pl)
1. path to executables for all desribed above c++ files from this github repository
2. path to the reference genome in FASTA format, this file must contain all chromosomes
3. path to input BED file of peaks (foreground sequences)
4. path to output data, all results will in this folder
5. BED or FASTA filename without extention ".bed" or ".fa", peaks (foreground sequences)
6. file extention, values ".bed" and ".fa" indicate whether it BED or FASTA 
7. species and genome release (values hg38, mm10, rn6, zf11, dm6, and ce235; at10, gm21, zm73, and mp61; sc64 and sch294). The animals inludes human *Homo sapiens* hg38, mouse *Mus musculus* mm10, rat *Rattus norvegicus* Rnor_6.0, zebrafish *Danio rerio* GRCz11, fly *Drosophila melanogaster* dm6, and roundworm *Caenorhabditis elegans* WBcel235; the plants are arabidopsis *Arabidopsis thaliana* TAIR10, soybean *Glycine max* v2.1, maize *Zea mays* B73, and liverwort *Marchantia polymorpha* MpTak v6.1; the fungi are baker's yeast *Saccharomyces cerevisiae* R64-1-1 and fission yeast *Schizosaccharomyces pombe* ASM294v2.
8. required number of found background sequences per one foreground sequence, Rbf (default value 5)
9. deviation δ of the A/T nucleotide content of a background sequence from that for a foreground sequence, (default value 0.01)
10. total average number of attempts Na to get background sequences from genome per one foreground sequence (default value 10000)
11. threshold for the fraction of completely processed input sequences allowing to stop calculations (default value 0.99)

Whole chromosome sequences in plain format are required to run the program, i.e. headers lines >... should be deleted from the whole chromosome files in FASTA format. These plain files should contain only nucleotides A, T, G, C, N, all other degenerate nucleotides for simplicity are replaced by 'N'. The symbols like ' ', '\t' etc. are deleted, e.g. for *A. thaliana* genome five files are required: chr1.plain, chr2.plain, chr3.plain, chr4.plain, chr5.plain, for human/mouse respective files refer to whole chromosomes 1-22,X,Y / 1-19,X,Y. Two additional scripts are applied to consruct functional pipelines including generation of these files in PLAIN format: [no_mask.pl](https://github.com/parthian-sterlet/antinoise/blob/main/run/no_mask.pl), [mask.pl](https://github.com/parthian-sterlet/antinoise/blob/main/run/mask.pl) The first one means the extraction of background sequences from the entire reference genome, the second one means this the extraction restricted to either the entire reference genome lacking specific blacklisted regions, or it denotes that background sequences are extracted only from specifc whitelisted regions of the entire genomes. Files *m5kb_p100_pc.bed in the folder [whitelisted](https://github.com/parthian-sterlet/antinoise/tree/main/examples/whitelisted) of this github repository (e.g. file of mouse whitelisted regions [mm10_m5kb_p100_pc.bed](https://github.com/parthian-sterlet/antinoise/blob/main/examples/whitelisted/mm10_m5kb_p100_pc.bed) provide the examples of such whitelisted regions for genome releases of all species, each file represents (-5000; +100) regions relative to transcription start sites of all protein-coding genes.

## 2. Background sequences generation: Synthetic
[mix0.cpp](https://github.com/parthian-sterlet/sitega/blob/master/src/mix0.cpp)
1. input FASTA file (foreground set)
2. output FASTA file (background set)
3. required number of found background sequences per one foreground sequence, Rbf (default value 5)

## Supporting C++ programs for the genomic approach
* BED format conversion removing overlaps of genomic fragments, [area_self_overlap.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/area_self_overlap.cpp)
1. input BED format file, overlapping of fragments is allowed
2. output BED format file, overlapping of fragments is absent
3. species and genome release (values hg38, mm10, rn6, zf11, dm6, and ce235; at10, gm21, zm73, and mp61; sc64 and sch294). The animals inludes human *Homo sapiens* hg38, mouse *Mus musculus* mm10, rat *Rattus norvegicus* Rnor_6.0, zebrafish *Danio rerio* GRCz11, fly *Drosophila melanogaster* dm6, and roundworm *Caenorhabditis elegans* WBcel235; the plants are arabidopsis *Arabidopsis thaliana* TAIR10, soybean *Glycine max* v2.1, maize *Zea mays* B73, and liverwort *Marchantia polymorpha* MpTak v6.1; the fungi are baker's yeast *Saccharomyces cerevisiae* R64-1-1 and fission yeast *Schizosaccharomyces pombe* ASM294v2.

* Partitiong of BED annotation for multiple chromosomes into multiples chromosome-specific BED annotations, [bed_chr_separation.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/bed_chr_separation.cpp) 
1. input BED format file
2. output BED format base name of file, value ZZZ results output files ZZZ_chr1.bed, ZZZ_chr2.bed for chr1 and chr2, respectively. 
3. species and genome release (values hg38, mm10, rn6, zf11, dm6, and ce235; at10, gm21, zm73, and mp61; sc64 and sch294 stand for animals: human *Homo sapiens* hg38, mouse *Mus musculus* mm10, rat *Rattus norvegicus* Rnor_6.0, zebrafish *Danio rerio* GRCz11, fly *Drosophila melanogaster* dm6, and roundworm *Caenorhabditis elegans* WBcel235; plants: arabidopsis *Arabidopsis thaliana* TAIR10, soybean *Glycine max* v2.1, maize *Zea mays* B73, and liverwort *Marchantia polymorpha* MpTak v6.1; fungi: baker's yeast *Saccharomyces cerevisiae* R64-1-1 and fission yeast *Schizosaccharomyces pombe* ASM294v2, respectively)
4. output file with total statistics on overlapping regions

* Masking of whole genome sequences in PLAIN format according to genomic fragments from file in BED format, [bed_chr_mask.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/bed_chr_mask.cpp)
1. path to input whole genome sequences of chromosomes in plain format (see the paragraph below, the last symbol of path must be '/' and '\\' for Linux and Windows OS, respectively), see the example of files in PLAIN format for [the reference sequence of *S. cerevisiae* genome](https://github.com/parthian-sterlet/antinoise/blob/main/genomes/sc64/Saccharomyces_cerevisiae.R64-1-1.dna.toplevel.fa) in [this folder](https://github.com/parthian-sterlet/antinoise/tree/main/genomes/sc64)
2. path to output whole genome sequences of chromosomes in plain format (see the paragraph below, the last symbol of path must be '/' and '\\' for Linux and Windows OS, respectively)
3. input BED format file - tab-delimited txt format, first column contains chromosome name (e.g. chr1, chr2, etc.), second/third columns contain starting/ending positions of genomic fragments
4. input PLAIN format base name without default extension ".plain" (default value "chr", so that file name are chr1.plain, chr2.plain, etc.)
5. output PLAIN format base name without default extension ".plain" (default value "chr", so that file name are chr1.plain, chr2.plain, etc., names are the same as input ones since input and output paths should be distinct)
6. int masking option, value -1 implies masking with polyN tracks for genomic fragments from the input BED files, all genome loci are preserved the same as in input reference genome; value 1 implies masking with polyN tracks for all the genomic loci regions besides fragments from an input BED file, only genomic fragments from this input BED file are preserved the same as in input reference genome
7. species and genome release (values hg38, mm10, rn6, zf11, dm6, and ce235; at10, gm21, zm73, and mp61; sc64 and sch294 stand for animals: human *Homo sapiens* hg38, mouse *Mus musculus* mm10, rat *Rattus norvegicus* Rnor_6.0, zebrafish *Danio rerio* GRCz11, fly *Drosophila melanogaster* dm6, and roundworm *Caenorhabditis elegans* WBcel235; plants: arabidopsis *Arabidopsis thaliana* TAIR10, soybean *Glycine max* v2.1, maize *Zea mays* B73, and liverwort *Marchantia polymorpha* MpTak v6.1; fungi: baker's yeast *Saccharomyces cerevisiae* R64-1-1 and fission yeast *Schizosaccharomyces pombe* ASM294v2, respectively)

* BED annotation sorting by chromosomes and positions, [bed_sort.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/bed_sort.cpp)
1. input BED format file, unsorted annotations
2. output BED format file, sorted annotations
3. species and genome release (values hg38, mm10, rn6, zf11, dm6, and ce235; at10, gm21, zm73, and mp61; sc64 and sch294 stand for animals: human *Homo sapiens* hg38, mouse *Mus musculus* mm10, rat *Rattus norvegicus* Rnor_6.0, zebrafish *Danio rerio* GRCz11, fly *Drosophila melanogaster* dm6, and roundworm *Caenorhabditis elegans* WBcel235; plants: arabidopsis *Arabidopsis thaliana* TAIR10, soybean *Glycine max* v2.1, maize *Zea mays* B73, and liverwort *Marchantia polymorpha* MpTak v6.1; fungi: baker's yeast *Saccharomyces cerevisiae* R64-1-1 and fission yeast *Schizosaccharomyces pombe* ASM294v2, respectively)

* Partitiong of one FASTA file with multiple sequences into multiple file with individual sequences, [fasta_muliplefiles.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/fasta_muliplefiles.cpp)
1. input FASTA format file, mutiple sequences, see [the reference sequence of *S. cerevisiae* genome](https://github.com/parthian-sterlet/antinoise/blob/main/genomes/sc64/Saccharomyces_cerevisiae.R64-1-1.dna.toplevel.fa) as an example
2. base name of output FASTA files, value ZZZ results the output files ZZZ1.fa and ZZZ2.fa output file for the first and second sequences in input file, and so on next
3. int mode, output filenames: (a) the value 1 means that the names of output files do not depend on the information in the sequence headers of the input FASTA file, in the lines after the first symbols '>', output filenames {ZZZ1.fa, ZZZ2.fa, ZZZ3.fa, etc.} respect the serial numbers {1, 2, 3, etc.} ; (b) the value 0 means filenames are defined by the information in sequence headers after '>' in input FASTA file. For example, for human genome with headers of chromosomes { >chr1, >chr2, ... , >chr22, >chrX and >chrY } and value 0 provides exactly {chr1.fa, chr2.fa, ... , chr22.fa, chrX.fa and chrY.fa }

* Whole genome conversion from FASTA to PLAIN format, [fasta_to_plain0.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/fasta_to_plain0.cpp)
1. path to whole genome sequences of chromosomes in plain format (see the paragraph below, the last symbol of path must be '/' and '\\' for Linux and Windows OS, respectively)
2. species and genome release (values hg38, mm10, rn6, zf11, dm6, and ce235; at10, gm21, zm73, and mp61; sc64 and sch294 stand for animals: human *Homo sapiens* hg38, mouse *Mus musculus* mm10, rat *Rattus norvegicus* Rnor_6.0, zebrafish *Danio rerio* GRCz11, fly *Drosophila melanogaster* dm6, and roundworm *Caenorhabditis elegans* WBcel235; plants: arabidopsis *Arabidopsis thaliana* TAIR10, soybean *Glycine max* v2.1, maize *Zea mays* B73, and liverwort *Marchantia polymorpha* MpTak v6.1; fungi: baker's yeast *Saccharomyces cerevisiae* R64-1-1 and fission yeast *Schizosaccharomyces pombe* ASM294v2, respectively)

* BED to FASTA conversion, [longext_many.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/longext_many.cpp)
1. path to whole genome sequences of chromosomes in plain format (see the paragraph below, the last symbol of path must be '/' and '\\' for Linux and Windows OS, respectively)
2. input BED format file - tab-delimited txt format, first column contains chromosome name (e.g. chr1, chr2, etc.), second/third columns contain starting/ending positions of genomic fragments, in subsequent columns symbols '+'/'-' designate DNA strand, and arbitrary identifier (e.g. peak quiality, gene names) are allowed
3. output FASTA format file
4. integer value, extention of all fragment sequences in 5' direction (default value 0)
5. int maximal length of one FASTA sequence
6. species and genome release (values hg38, mm10, rn6, zf11, dm6, and ce235; at10, gm21, zm73, and mp61; sc64 and sch294). The animals inludes human *Homo sapiens* hg38, mouse *Mus musculus* mm10, rat *Rattus norvegicus* Rnor_6.0, zebrafish *Danio rerio* GRCz11, fly *Drosophila melanogaster* dm6, and roundworm *Caenorhabditis elegans* WBcel235; the plants are arabidopsis *Arabidopsis thaliana* TAIR10, soybean *Glycine max* v2.1, maize *Zea mays* B73, and liverwort *Marchantia polymorpha* MpTak v6.1; the fungi are baker's yeast *Saccharomyces cerevisiae* R64-1-1 and fission yeast *Schizosaccharomyces pombe* ASM294v2.
7. log file reporing abnormal program termination due to errors in BED file (start/end positions are located outside the chromosome borders, etc.), correct program termination assumes that this file is empty

## Scripts to run AntiNoise starting from the reference genome
* No masking, application to the entire genome as is, without any masking, [no_mask.pl](https://github.com/parthian-sterlet/antinoise/blob/main/run/no_mask.pl)
1. path to executables for all desribed above c++ files from this github repository
2. path to the reference genome in FASTA format, this file must contain all chromosomes
3. path to input BED file of peaks (foreground sequences)
4. path to output data, all results will in this folder
5. reference genome in FASTA format, e.g. [Homo_sapiens.GRCh38.dna.primary_assembly.fa.gz](https://ftp.ensembl.org/pub/release-110/fasta/homo_sapiens/dna/Homo_sapiens.GRCh38.dna.primary_assembly.fa.gz)
6. integer value indicating the necessity (1) or lack thereof (0) of FASTA -> PLAIN transformation of the reference genome (if such transformation has already been performed, it is omitted in subsequent runs)
7. BED filename without extention ".bed", peaks (foreground sequences)
8. species and genome release (values hg38, mm10, rn6, zf11, dm6, and ce235; at10, gm21, zm73, and mp61; sc64 and sch294). The animals inludes human *Homo sapiens* hg38, mouse *Mus musculus* mm10, rat *Rattus norvegicus* Rnor_6.0, zebrafish *Danio rerio* GRCz11, fly *Drosophila melanogaster* dm6, and roundworm *Caenorhabditis elegans* WBcel235; the plants are arabidopsis *Arabidopsis thaliana* TAIR10, soybean *Glycine max* v2.1, maize *Zea mays* B73, and liverwort *Marchantia polymorpha* MpTak v6.1; the fungi are baker's yeast *Saccharomyces cerevisiae* R64-1-1 and fission yeast *Schizosaccharomyces pombe* ASM294v2.
9. required number of found background sequences per one foreground sequence, Rbf (default value 5)
10. deviation δ of the A/T nucleotide content of a background sequence from that for a foreground sequence, (default value 0.01)
11. total average number of attempts Na to get background sequences from genome per one foreground sequence (default value 10000)
12. threshold for the fraction of completely processed input sequences allowing to stop calculations (default value 0.99)

* Options for genome masking: exlusion of blacklisted regions and retention of whitelisted regions, [mask.pl](https://github.com/parthian-sterlet/antinoise/blob/main/run/mask.pl)

 This file implies extraction of background sequences either only from certain specific, whitelisted regions (e.g. promoter regions of genes) or it from the entire reference genome excluding certain blacklisted regions of the genome, such as specific regions of the genome that should be avoided in the output background sequences
1. path to executables for all desribed above c++ files from this github repository
2. path to the reference genome in FASTA format, this file must contain all chromosomes
3. path to input BED files: peaks (foreground sequences) and whitelist/blacklist annotations
4. path to output data, the masked genome all results will in this folder
5. reference genome in FASTA format, e.g. [Homo_sapiens.GRCh38.dna.primary_assembly.fa](https://ftp.ensembl.org/pub/release-110/fasta/homo_sapiens/dna/Homo_sapiens.GRCh38.dna.primary_assembly.fa.gz)
6. integer value indicating the necessity (1) or lack thereof (0) of FASTA -> PLAIN transformation of the reference genome (if such transformation has already been performed, it is omitted in subsequent runs)
7. BED file name, whitelisted/blacklisted regions
8. integer value indicating the blacklisted (-1) or whitelisted (1) masking option
9. integer value indicating the necessity (1) or lack thereof (0) to check self-overlapping for the BED file applied for masking, e.g. promoters of genes are overlapped but subsequent masking program requires the absence of  overlaps within a BED file. 
10. BED file name without extention ".bed", peaks (foreground sequences)
11. species and genome release (values hg38, mm10, rn6, zf11, dm6, and ce235; at10, gm21, zm73, and mp61; sc64 and sch294). The animals inludes human *Homo sapiens* hg38, mouse *Mus musculus* mm10, rat *Rattus norvegicus* Rnor_6.0, zebrafish *Danio rerio* GRCz11, fly *Drosophila melanogaster* dm6, and roundworm *Caenorhabditis elegans* WBcel235; the plants are arabidopsis *Arabidopsis thaliana* TAIR10, soybean *Glycine max* v2.1, maize *Zea mays* B73, and liverwort *Marchantia polymorpha* MpTak v6.1; the fungi are baker's yeast *Saccharomyces cerevisiae* R64-1-1 and fission yeast *Schizosaccharomyces pombe* ASM294v2.
12. required number of found background sequences per one foreground sequence, Rbf (default value 5)
13. deviation δ of the A/T nucleotide content of a background sequence from that for a foreground sequence, (default value 0.01)
14. total average number of attempts Na to get background sequences from genome per one foreground sequence (default value 10000)
15. threshold for the fraction of completely processed input sequences allowing to stop calculations (default value 0.99)

Сommand line examples [command_line_no_mask](https://github.com/parthian-sterlet/antinoise/blob/main/run/command_line_no_mask), [command_line_blacklisted](https://github.com/parthian-sterlet/antinoise/blob/main/run/command_line_blacklisted), and [command_line_whitelisted](https://github.com/parthian-sterlet/antinoise/blob/main/run/command_line_whitelisted).
Tracks of repeats [simple sequence repeats](https://hgdownload.soe.ucsc.edu/goldenPath/sacCer3/database/simpleRepeat.txt.gz) and 	
[microsatellites (di- and trinucleotide repeats)](https://hgdownload.soe.ucsc.edu/goldenPath/sacCer3/database/microsat.txt.gz) [(Benson et al., 1999)](https://doi.org/10.1093/nar/27.2.573), regulatory elements [probes from ChIP-chip experiments for transcription regulatory elements](https://hgdownload.soe.ucsc.edu/goldenPath/sacCer3/database/transRegCodeProbe.txt.gz) [(Harbison et al., 2004)](https://doi.org/10.1038/nature02800) and conserved regions [Conservation - multiz alignment & conservation (7 yeasts)](https://hgdownload.soe.ucsc.edu/goldenPath/sacCer3/database/phastCons7way.txt.gz) ([Felsenstein and Churchill, 1996](https://doi.org/10.1093/oxfordjournals.molbev.a025575); [Blanchette et al., 2004](https://doi.org/10.1101/gr.1933104)) for [*S. cerevisiae* genome](https://ftp.ensemblgenomes.ebi.ac.uk/pub/fungi/release-57/fasta/saccharomyces_cerevisiae/dna/Saccharomyces_cerevisiae.R64-1-1.dna.toplevel.fa.gz) were used as examples for the blacklisted and whitelisted command line run files.
