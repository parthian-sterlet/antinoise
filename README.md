# AntiNoise - Generation of background dataset of DNA sequences for given foreground dataset for de novo motif discovery
# Description
Chromatin immunoprecipitation (ChIP)-based high throughput technique ChIP-seq allows genome-scale mapping of transcription factors binding sites (TFBS). The lengths of derived genome loci or peaks comprise hundreds of base pairs, however a TFBS typically varied in the length from 6 to 25 bp, e.g. see [CIS-BP database](http://cisbp.ccbr.utoronto.ca/). Hence, the motif enrichment analysis, e.g. de novo motif search is required to map exact positions of sites in peaks. The task of this analysis consists in detection of motifs specific for biological function of ChIP-seq target TFs. For each motif the significance of its enrichment in peaks (foreground dataset) depends on the choice of the approach of the background dataset generation. The background (negative) dataset is required as a complement to the foreground (positive) dataset to select the parameters of motif model. The main purpose of the background dataset is to exclude from the results of de novo motif search artifact motifs related to a genome-specific sequence content bias, e.g. polyA. The background sequences notably influence the excpected false positive rate for various motifs in the consequent bootstrap cross-validation procedure. Any custom sequence set may be used as a background dataset, but it is recommended that this dataset (1) reflects the bias of a genome, i.e. the expected distribution of frequencies of nucleotides (respecting the motif lentghs) and (2) is at least several times larger that the foreground dataset
Here we introduce two approaches required in de novo motif search to generate the background sequence dataset with a given foreground dataset of ChIP-seq peaks: the first one ’genomic’ compiles randomly chosen sequences from a whole genome adopting the nucleotide content from the foreground sequence set, thus modeling an expected content of noise non-specific motifs [(Tsukanov et al., 2022)](https://doi.org/10.3389/fpls.2022.938545); the second ‘synthetic’ approach destroys the significant enrichment of any motifs through the permutation of nucleotides preserving the nucleotide content. 
# Requirements
The source code is written in C++ language. To compile exetubables from the source code you need:

* In Linux system, C++ compiler, e.g. [GCC](https://gcc.gnu.org/) compiler 
* In Windiws system any VC++ package, e.g. [Microsoft Visual Studio Community](https://visualstudio.microsoft.com/vs/community/)

# Source code
Folder [**src**](https://github.com/parthian-sterlet/antinoise/tree/main/src) contains files with the source codes, they respect to  genomic and synthetic background generation approaches.
## 1. Genomic
The propgram [background_genome_mono.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/background_genome_mono.cpp) generates the specific background dataset for the certain genome (hg38, mm10, at10). The output fasta file respects the input fasta file by the mononucleotide content. 
## 2. Synthetic
The program [mix0.cpp](https://github.com/parthian-sterlet/sitega/blob/master/src/mix0.cpp) generates synthetic sequences matching the nucleotide content.
# How to compile
* In Linux system: 

git clone https://github.com/parthian-sterlet/antinoise
cd antinoise\src\
chmod a+x build.sh\
./build.sh

* In Windiws system:

separate compilation of all source files in VC++
## Background dataset generation: Genomic

[background_genome_mono.cpp](https://github.com/parthian-sterlet/sitega/blob/master/src/background_genome_mono.cpp)
1. path to whole genome sequences of chromosomes in plain format (see the paragraph below, the last symbol of path must be '/' and '\\' for Linux and Windows OS, respectively)
2. input fasta file
3. output fasta file with genome sequences adopted by  A/T-content
4. maximal number of background sequences per one foreground sequence, H (default value 2)
5. deviation of mononucleitide content of a background sequence from that for a foreground sequence (default value 0.01)
6. total average number of attempts to get background sequences from genome per one foreground sequence (default value 1000)
7. genome release (hg38, mm10, dm6, ce235, sc64 and at10 for H. sapiens, M. musculus, D. melanogaster, C. elegans, S. cerevisiae and A. thaliana genomes, respectively)
8. threshold for the fraction of completely processed input sequences allowing to stop calculations (default value 0.99)
9. output file, table for all input sequences showing A/T-content of input sequence and number of generated background sequences 
10. output file, table listing frequncies of 16 dinucleotide for all input sequences for which the maximal number (H) of background sequences did not achieved
11. output file, current progress in calculation showing the fraction of completely processed input sequences, i.e. for each such sequence H background sequences were found 

Whole chromosome sequences in plain format are required to run the program, i.e. headers lines >... should be deleted from the whole chromosome files in fasta format. These plain files should contain only nucleotide letters, IUPAC nucleotides codes N,W,S etc. are ignored by program, all other symbols like ' ', '\t' etc. should deleted, e.g. for Arabidopsis five files are required: chr1.plain, chr2.plain, chr3.plain, chr4.plain, chr5.plain, for human/mouse respective files refer to whole chromosomes 1-22,X,Y / 1-19,X,Y. Use [ftp](https://github.com/parthian-sterlet/antinoise/blob/main/src/ftp) to generate these files in plain format from the conventional genome sequences in fasta format. To see example unzip chr4.plain file from folder [genomes](https://github.com/parthian-sterlet/sitega/tree/master/genomes). 

## Background dataset generation: Synthetic
[mix0.cpp](https://github.com/parthian-sterlet/sitega/blob/master/src/mix0.cpp)
1. input fasta file (the foreground dataset)
2. output fasta file (the background dataset)
3. number of background sequences per one peak (default value 5)
