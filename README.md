# AntiNoise - Generation of background DNA sequences for a given set of foreground sequences for *de novo* motif search
# Description
The AntiNoise tool generates a set of background sequence set DNA sequences for given foreground set of sequences, background sequences are required to perform the motif enrichment analysis in the foreground sequence set, in particuler, for *de novo* motif discovery. Chromatin immunoprecipitation (ChIP)-based high throughput technique ChIP-seq allows genome-scale mapping of transcription factors binding sites (TFBS). The lengths of derived genome loci or peaks comprise hundreds of base pairs, however the length of TFBS motifs typically varied from 6 to 20 bp, e.g. see [CIS-BP database](http://cisbp.ccbr.utoronto.ca/). *De novo* motif search is required to map exact positions of potential sites in peaks. The task of this analysis consists in detection of motifs specific for biological function of ChIP-seq target TFs. The background set is required as a complement to the foreground set to differentiate between various enriched motifs and to select the exact values of parameters of a motif model. The main purpose of the background set is to exclude from the results of *de novo* motif search artifact motifs related to a genome-specific sequence content bias, e.g. polyA tracts. For each motif the significance of its enrichment in peaks (foreground set) depends on excpected recognition rates for various motifs in the subsequent bootstrap cross-validation procedure. This procedure is required to estimate the performance of a motif model.  hence, the choice of the approach of the background sequence generation is very importnat to define a motif of the target TF correctly. Any custom sequence set lacking enrichments of motifs of a target TF can be used as a background set. But a background set reflecting the bias of a genome, i.e. the expected distribution of frequencies of oligonucleotides respecting in lentghs to potential motifs, is certainly beneficial compared to any other one. Also, the number of sequences in a background set should be at least several times greater than that for a foreground set.
Here we introduce the approach required in *de novo* motif search to generate the background sequence set with a given foreground set of genomic sequences, e.g. ChIP-seq peaks. This ’genomic’ approach compiles randomly chosen sequences from a whole genome adopting the nucleotide content according to sequences from a foreground set, thus modeling an expected content of noise non-specific motifs [(Tsukanov et al., 2022)](https://doi.org/10.3389/fpls.2022.938545). To prove the efficency of this approach we provide also another ‘synthetic’ approach destroying the significant enrichment of any motifs through the permutation of nucleotides preserving the nucleotide content. Our experience definitely promoted the genomic approach as more correct.

# Requirements
The source code is written in C++ language. To compile exetubables from the source code you need:

* In Linux system, C++ compiler, e.g. [GCC](https://gcc.gnu.org/) compiler 
* In Windiws system any VC++ package, e.g. [Microsoft Visual Studio Community](https://visualstudio.microsoft.com/vs/community/)

# Source code
Folder [**src**](https://github.com/parthian-sterlet/antinoise/tree/main/src) contains files with the source codes, they respect to  genomic and synthetic background generation approaches.
## 1. Genomic
The propgram [background_genome_mono.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/background_genome_mono.cpp) finds the specific background sequences for the certain genome (hg38, mm10, at10). The output fasta file respects the input fasta file by the mononucleotide content. 
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
## Background sequences generaration: Genomic

[background_genome_mono.cpp](https://github.com/parthian-sterlet/sitega/blob/master/src/background_genome_mono.cpp)
1. path to whole genome sequences of chromosomes in plain format (see the paragraph below, the last symbol of path must be '/' and '\\' for Linux and Windows OS, respectively)
2. input fasta file (foreground set)
3. output fasta file (background set)
4. required number of found background sequences per one foreground sequence, Rbf (default value 5)
5. deviation δ of the A/T nucleotide content of a background sequence from that for a foreground sequence, (default value 0.01)
6. total average number of attempts Na to get background sequences from genome per one foreground sequence (default value 10000)
7. genome release (hg38, mm10, rn6, zf11, dm6, ce235, at10, gm21, zm73, mp61, sc64 and sch294 for *Homo sapiens, Mus musculus, Rattus norvegicus, Danio rerio, Drosophila melanogaster, Caenorhabditis elegans, Arabidopsis thaliana, Glycine max, Zea mays, Marchantia polymorpha, Saccharomyces cerevisiae* and *Schizosaccharomyces pombe* genomes, respectively)
8. threshold for the fraction of completely processed input sequences allowing to stop calculations (default value 0.99)
9. output file, additional output table compares the A/T content in the foreground and background sequence sets
10. output file, additional output table compares the dinucleotide frequencies in the foreground and background sequence sets
11. output file, additional output table compares (a) the A/T content for all input sequences that did not achieve the required number of found background sequences per one foreground sequence Rbf and (b) the average A/T content for the foreground sequnce set.
12. output file, additional output table compares (a) the dinucleotide frequencies in all input sequences that did not achieve the required number of found background sequences per one foreground sequence Rbf and (b) the average dinucleotide frequencies for the foreground sequnce set.
13. output file, current progress in calculation, the fraction of completely processed foreground sequences, i.e. for each such foreground sequence exactly Rbf background sequences were found 

Whole chromosome sequences in plain format are required to run the program, i.e. headers lines >... should be deleted from the whole chromosome files in fasta format. These plain files should contain only nucleotide letters, IUPAC nucleotides codes N,W,S etc. are ignored by program, all other symbols like ' ', '\t' etc. should deleted, e.g. for Arabidopsis five files are required: chr1.plain, chr2.plain, chr3.plain, chr4.plain, chr5.plain, for human/mouse respective files refer to whole chromosomes 1-22,X,Y / 1-19,X,Y. Use [ftp](https://github.com/parthian-sterlet/antinoise/blob/main/src/ftp) to generate these files in plain format from the conventional genome sequences in fasta format. To see example unzip chr4.plain file from folder [genomes](https://github.com/parthian-sterlet/sitega/tree/master/genomes). 

## Background sequences generation: Synthetic
[mix0.cpp](https://github.com/parthian-sterlet/sitega/blob/master/src/mix0.cpp)
1. input fasta file (foreground set)
2. output fasta file (background set)
3. required number of found background sequences per one foreground sequence, Rbf (default value 5)
