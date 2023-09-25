# AntiNoise - Extraction of genomic background set of DNA sequences for a given foreground set of sequences for subsequent *de novo* motif discovery
# Description
The AntiNoise tool extract a set of background DNA sequences for given foreground set of sequences, background sequences are required to perform the motif enrichment analysis in the foreground sequence set, in particuler, for *de novo* motif discovery. Chromatin immunoprecipitation (ChIP)-based high throughput technique ChIP-seq allows genome-scale mapping of transcription factors binding sites (TFBS). The lengths of derived genome loci or peaks comprise hundreds of base pairs, however the length of TFBS motifs typically varied from 6 to 20 bp, e.g. see [CIS-BP database](http://cisbp.ccbr.utoronto.ca/). *De novo* motif search is required to map exact positions of potential sites in peaks. The task of this analysis consists in detection of motifs specific for biological function of ChIP-seq target TFs. To differentiate between various enriched motifs and to select the exact values of parameters of a motif model, and additiobal set of background sequences is applied as a complement to the foreground set. This background set can exclude from the results of *de novo* motif search artifact motifs related to a genome-specific sequence content bias, e.g. polyA tracts. For each motif the significance of its enrichment in peaks depends on excpected recognition rates for various motifs in the background sequences. Hence, the choice of the approach of the background sequence generation is very importnat to define a motif of the target TF correctly. Any custom sequence set lacking enrichments of motifs of a target TF can be used as a background set. But a background set reflecting the bias of a genome, i.e. the expected distribution of frequencies of oligonucleotides respecting in lentghs to potential motifs, is certainly beneficial compared to any other one. Also, the number of sequences in a background set should be at least several times greater than that for a foreground set.
Here we introduce the approach required in *de novo* motif search to generate the background sequence set with a given foreground set of genomic sequences, e.g. ChIP-seq peaks. This ’genomic’ approach compiles randomly chosen sequences from a whole genome adopting the nucleotide content according to sequences from a foreground set, thus modeling an expected content of noise non-specific motifs [(Tsukanov et al., 2022)](https://doi.org/10.3389/fpls.2022.938545). To prove the efficency of this approach we provide also another ‘synthetic’ approach destroying the significant enrichment of any motifs through the permutation of nucleotides preserving the nucleotide content. Our experience definitely promoted the genomic approach as more correct. The web service [AntiNoise](https://denovosea.icgbio.ru/antinoise/) implements the genomic approach of background sequences generation. Additionally, we provide the command line version including two perl scripts performing the generation of genomic background sequences using the input data of (a) source DNA sequences (peaks) or their whole genome annotation in BED format, (b) whole genome sequences of the reference genome in FASTA format (this file is conventionally extracted from any public database) and, optionally, (c1) the background sequences are generated through the application of the reference genome sequences, or (c2) an arbitrary whole genome annotation of 'blacklisted' fragments in BED format additionally exclude from the reference genome sequences, thus more rigorous selection of genomic background sequences is provided.

# Requirements
The source code is written in C++ language. To compile exetubables from the source code you need:

* In Linux system, C++ compiler, e.g. [GCC](https://gcc.gnu.org/) compiler 
* In Windows system any VC++ package, e.g. [Microsoft Visual Studio Community](https://visualstudio.microsoft.com/vs/community/)

# Source code
Folder [**src**](https://github.com/parthian-sterlet/antinoise/tree/main/src) contains files with the source codes, they respect to  genomic and synthetic background generation approaches.
## 1. Genomic
The propgram [background_genome_mono.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/background_genome_mono.cpp) finds the specific background sequences for the certain genome (hg38, mm10, tair10, etc.). The output FASTA file respects the input FASTA file by the mononucleotide content. 
## 2. Synthetic
The program [mix0.cpp](https://github.com/parthian-sterlet/sitega/blob/master/src/mix0.cpp) generates synthetic sequences matching the nucleotide content.

## Additional supporting programs
* The program [area_self_overlap.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/area_self_overlap.cpp) converts a genomic annotation file in BED format with possible overlapping of genomic fragments to a file in the same BED format with not overlapped genomic fragments.
* The program [bed_chr_mask.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/bed_chr_mask.cpp) masks the reference genome sequences in PLAIN format accoridng a given input annotation in BED format. Masking with 'N' as options is performed either (a) for all fragments listed in BED file, or (b) for all the remaining parts of the reference genome. This program uses any file in BED format with any 'blacklisted' genomic regions to mask the reference genome in PLAIN format. Hence, 'blacklisted' genomic regions will be excluded from a consequent analysis completely.
* The program [bed_chr_separation.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/bed_chr_separation.cpp) partitions a file in BED format into multiple BED files so that each of them lists annotatios for the same chromosome.
* The program [bed_sort.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/bed_sort.cpp) sorts DNA annotations in BED format according to the designations of chromosomes and positions.
* The program [fasta_muliplefiles.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/fasta_muliplefiles.cpp) partitions DNA sequence file in FASTA format with muliple sequences into multiple files so that all resulted output FASTA files repect individual sequences. In particular, this program is used to convert the reference genome in one FASTA file with sequences of all chromosomes joined together into multiple FASTA files of individual chromosomes. Genomes in FASTA format are available in many public servers, e.g. Ensembl for [human](https://ftp.ensembl.org/pub/release-110/fasta/homo_sapiens/dna/). Hence, a simple way to get access to the refernce genome is to download it as one file (e.g. these ones for [human](https://ftp.ensembl.org/pub/release-110/fasta/homo_sapiens/dna/Homo_sapiens.GRCh38.dna.primary_assembly.fa.gz)) and [mouse](https://ftp.ensembl.org/pub/release-102/fasta/mus_musculus/dna/Mus_musculus.GRCm38.dna.primary_assembly.fa.gz)), and then to partition it into chromosome-specific FASTA files.
* The program [fasta_to_plain0.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/fasta_to_plain0.cpp) converts DNA sequences of a reference genome sequences from FASTA format to PLAIN format. This program make the reference more convinient for consequent analysis and treatement. Plain format is more convinient for subsequent applications than the default FASTA format of a DNA sequence. Unlike FASTA format, (a) the PLAIN format does not contain lines of sequence headers starting with '>'symbol, (b) the end of line symbols ('\n' in Linux or '\r\n' in Windows) mean only the end of a DNA sequence. Consequently, if a file in PLAIN format contains only one chromosome, then the end of a line is allowed only at the end of this file.
* The program [longext_many.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/longext_many.cpp) converts a file in BED format to DNA sequences in FASTA format using the reference genome sequences in PLAIN format. 

## Scripts to run AntiNoise with the support of the reference genome masking
* No masking
Perl script [no_mask.pl](https://github.com/parthian-sterlet/antinoise/blob/main/src/no_mask.pl) shows the example application of the genomic approach for the background generation for a tested annotation of peaks in BED format. Background sequences are searhed in the full-length sequences of the reference genome. The script starts from one FASTA file containing all chromosomes of certain reference genome. This file should taken in the public database, e.g. for [human](https://ftp.ensembl.org/pub/release-110/fasta/homo_sapiens/dna/Homo_sapiens.GRCh38.dna.primary_assembly.fa.gz) and [mouse](https://ftp.ensembl.org/pub/release-102/fasta/mus_musculus/dna/Mus_musculus.GRCm38.dna.primary_assembly.fa.gz). For any further releases the chromosome lengths should be updated in the [header](https://github.com/parthian-sterlet/antinoise/blob/main/src/chromosome_len.h) file according to the stadard chromosome names from another [header](https://github.com/parthian-sterlet/antinoise/blob/main/src/chromosome_name.h) file. 
* Blacklisted regions masking, the analysis is restricted to remaining genomic loci
Perl script [mask.pl](https://github.com/parthian-sterlet/antinoise/blob/main/src/mask.pl) shows the example application of the genomic approach for the background generation for a tested annotation of peaks in BED format with application of additional annotation of blacklisted regions of a genome in BED format, e.g. this one for [human](https://github.com/parthian-sterlet/antinoise/blob/main/src/GRCh38_unified_blacklist.bed) from [ENCODE](https://www.encodeproject.org/files/ENCFF356LFX/) and this one for [mouse](https://github.com/parthian-sterlet/antinoise/blob/main/src/ENCODE_ENCFF547MET_mm10.bed) from [ENCODE](https://www.encodeproject.org/files/ENCFF547MET/), see [(Amemiya et al., 2019)](https://doi.org/10.1038/s41598-019-45839-z). This analysis implies masking of genomic fragments of a given annotation in BED format (blacklisted regions), i.e. these regions are excluded from the analysis and they will be omitted in output background genomic sequences
* Whitelisted regions application, the analysis is restricted to only these whitelisted regions, all remaining genomic loci are excluded
Perl script [mask_rev.pl](https://github.com/parthian-sterlet/antinoise/blob/main/src/mask.pl) shows the example application of the genomic approach for the background generation for a tested annotation of peaks in BED format with application of additional annotation of 'whitelisted' regions of a genome in BED format, i.e. only these regions will proceed to output data, all the rest genomic regions will be masked. The file contains upstream 5kb long regions of mouse protein coding genes [ups5kb.bed](https://github.com/parthian-sterlet/antinoise/blob/main/src/ups5kb.bed) based on Genecode annotation [version M25](https://ftp.ebi.ac.uk/pub/databases/gencode/Gencode_mouse/release_M25/).
All three scripts presumed input sequences in BED format, if you have already FASTA sequences, the conversion step from BED to FASTA should be omitted.

# How to compile
* In Linux system: 

git clone https://github.com/parthian-sterlet/antinoise

cd antinoise\src\
chmod a+x build.sh\
./build.sh

* In Windows system:

separate compilation of all source files in VC++
## Background sequences generaration: Genomic

[background_genome_mono.cpp](https://github.com/parthian-sterlet/sitega/blob/master/src/background_genome_mono.cpp)
1. path to whole genome sequences of chromosomes in plain format (see the paragraph below, the last symbol of path must be '/' and '\\' for Linux and Windows OS, respectively)
2. input FASTA file (foreground set)
3. output FASTA file name without extension (background set), two extensions ".fa" and ".bed" define output files in FASTA and BED formats
4. required number of found background sequences per one foreground sequence, Rbf (default value 5)
5. deviation δ of the A/T nucleotide content of a background sequence from that for a foreground sequence, (default value 0.01)
6. total average number of attempts Na to get background sequences from genome per one foreground sequence (default value 10000)
7. species and genome release (values hg38, mm10, rn6, zf11, dm6, and ce235; at10, gm21, zm73, and mp61; sc64 and sch294 stand for animals: human *Homo sapiens* hg38, mouse *Mus musculus* mm10, rat *Rattus norvegicus* Rnor_6.0, zebrafish *Danio rerio* GRCz11, fly *Drosophila melanogaster* dm6, and roundworm *Caenorhabditis elegans* WBcel235; plants: arabidopsis *Arabidopsis thaliana* TAIR10, soybean *Glycine max* v2.1, maize *Zea mays* B73, and liverwort *Marchantia polymorpha* MpTak v6.1; fungi: baker's yeast *Saccharomyces cerevisiae* R64-1-1 and fission yeast *Schizosaccharomyces pombe* ASM294v2, respectively)
8. threshold for the fraction of completely processed input sequences allowing to stop calculations (default value 0.99)
9. output file, additional output table compares the A/T content in the foreground and background sequence sets
10. output file, additional output table compares the dinucleotide frequencies in the foreground and background sequence sets
11. output file, additional output table compares (a) the A/T content for all input sequences that did not achieve the required number of found background sequences per one foreground sequence Rbf and (b) the average A/T content for the foreground sequnce set.
12. output file, additional output table compares (a) the dinucleotide frequencies in all input sequences that did not achieve the required number of found background sequences per one foreground sequence Rbf and (b) the average dinucleotide frequencies for the foreground sequnce set.
13. output file, current progress in calculation, the fraction of completely processed foreground sequences, i.e. for each such foreground sequence exactly Rbf background sequences were found 

Whole chromosome sequences in plain format are required to run the program, i.e. headers lines >... should be deleted from the whole chromosome files in FASTA format. These plain files should contain only nucleotides A, T, G, C, N, all other degenerate nucleotides for simplicity are replaced by 'N'. The symbols like ' ', '\t' etc. are deleted, e.g. for *A. thaliana* genome five files are required: chr1.plain, chr2.plain, chr3.plain, chr4.plain, chr5.plain, for human/mouse respective files refer to whole chromosomes 1-22,X,Y / 1-19,X,Y. Additional scripts described above [no_mask_pl](https://github.com/parthian-sterlet/antinoise/blob/main/src/no_mask.pl) and [mask_pl](https://github.com/parthian-sterlet/antinoise/blob/main/src/mask.pl) are applied to consruct functional pipelines including generation of these files in PLAIN format

## Background sequences generation: Synthetic
[mix0.cpp](https://github.com/parthian-sterlet/sitega/blob/master/src/mix0.cpp)
1. input FASTA file (foreground set)
2. output FASTA file (background set)
3. required number of found background sequences per one foreground sequence, Rbf (default value 5)

## BED format conversion removing overlaps of genomic fragments
  [area_self_overlap.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/area_self_overlap.cpp)
1. input BED format file, overlapping of fragments is allowed
2. output BED format file, overlapping of fragments is absent
3. species and genome release (values hg38, mm10, rn6, zf11, dm6, and ce235; at10, gm21, zm73, and mp61; sc64 and sch294 stand for animals: human *Homo sapiens* hg38, mouse *Mus musculus* mm10, rat *Rattus norvegicus* Rnor_6.0, zebrafish *Danio rerio* GRCz11, fly *Drosophila melanogaster* dm6, and roundworm *Caenorhabditis elegans* WBcel235; plants: arabidopsis *Arabidopsis thaliana* TAIR10, soybean *Glycine max* v2.1, maize *Zea mays* B73, and liverwort *Marchantia polymorpha* MpTak v6.1; fungi: baker's yeast *Saccharomyces cerevisiae* R64-1-1 and fission yeast *Schizosaccharomyces pombe* ASM294v2, respectively)

## Partitiong of BED annotation for multiple chromosomes into multiples chromosome-specific BED annotations
  [bed_chr_separation.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/bed_срк_separation.cpp) 
1. input BED format file
2. output BED format base name of file, value ZZZ results output files ZZZ_chr1.bed, ZZZ_chr2.bed for chr1 and chr2, respectively. 
3. species and genome release (values hg38, mm10, rn6, zf11, dm6, and ce235; at10, gm21, zm73, and mp61; sc64 and sch294 stand for animals: human *Homo sapiens* hg38, mouse *Mus musculus* mm10, rat *Rattus norvegicus* Rnor_6.0, zebrafish *Danio rerio* GRCz11, fly *Drosophila melanogaster* dm6, and roundworm *Caenorhabditis elegans* WBcel235; plants: arabidopsis *Arabidopsis thaliana* TAIR10, soybean *Glycine max* v2.1, maize *Zea mays* B73, and liverwort *Marchantia polymorpha* MpTak v6.1; fungi: baker's yeast *Saccharomyces cerevisiae* R64-1-1 and fission yeast *Schizosaccharomyces pombe* ASM294v2, respectively)

## Masking of whole genome sequences in PLAIN format according to genomic fragments from file in BED format
[bed_chr_mask.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/bed_chr_mask.cpp)
1. path to input whole genome sequences of chromosomes in plain format (see the paragraph below, the last symbol of path must be '/' and '\\' for Linux and Windows OS, respectively)
2. path to output whole genome sequences of chromosomes in plain format (see the paragraph below, the last symbol of path must be '/' and '\\' for Linux and Windows OS, respectively)
3. input BED format file - tab-delimited txt format, first column contains chromosome name (e.g. chr1, chr2, etc.), second/third columns contain starting/ending positions of genomic fragments
4. input PLAIN format base name without default extension ".plain" (default value "chr", so that file name are chr1.plain, chr2.plain, etc.)
5. output PLAIN format base name without default extension ".plain" (default value "chr", so that file name are chr1.plain, chr2.plain, etc., names are the same as input ones since input and output paths should be distinct)
6. int masking option, value -1 implies masking with polyN tracks for genomic fragments from the input BED files, all genome loci are preserved the same as in input reference genome; value -1 implies masking with polyN tracks for all the genomic loci regions besides fragments from the input BED files, only genomic fragments from the input BED files are preserved the same as in input reference genome
7. species and genome release (values hg38, mm10, rn6, zf11, dm6, and ce235; at10, gm21, zm73, and mp61; sc64 and sch294 stand for animals: human *Homo sapiens* hg38, mouse *Mus musculus* mm10, rat *Rattus norvegicus* Rnor_6.0, zebrafish *Danio rerio* GRCz11, fly *Drosophila melanogaster* dm6, and roundworm *Caenorhabditis elegans* WBcel235; plants: arabidopsis *Arabidopsis thaliana* TAIR10, soybean *Glycine max* v2.1, maize *Zea mays* B73, and liverwort *Marchantia polymorpha* MpTak v6.1; fungi: baker's yeast *Saccharomyces cerevisiae* R64-1-1 and fission yeast *Schizosaccharomyces pombe* ASM294v2, respectively)

## BED annotation sorting by chromosomes and positions
  [bed_sort.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/bed_sort.cpp)
1. input BED format file, unsorted annotations
2. output BED format file, sorted annotations
3. species and genome release (values hg38, mm10, rn6, zf11, dm6, and ce235; at10, gm21, zm73, and mp61; sc64 and sch294 stand for animals: human *Homo sapiens* hg38, mouse *Mus musculus* mm10, rat *Rattus norvegicus* Rnor_6.0, zebrafish *Danio rerio* GRCz11, fly *Drosophila melanogaster* dm6, and roundworm *Caenorhabditis elegans* WBcel235; plants: arabidopsis *Arabidopsis thaliana* TAIR10, soybean *Glycine max* v2.1, maize *Zea mays* B73, and liverwort *Marchantia polymorpha* MpTak v6.1; fungi: baker's yeast *Saccharomyces cerevisiae* R64-1-1 and fission yeast *Schizosaccharomyces pombe* ASM294v2, respectively)

## Partitiong of one FASTA file with multiple sequences into multiple file with individual sequences 
  [fasta_muliplefiles.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/fasta_muliplefiles.cpp)
1. input FASTA format file, mutiple sequences
2. base name of output FASTA files, value ZZZ results output files ZZZ1.fa and ZZZ2.fa output file for the first and second sequences in input file, and so on next
3. int mode for output filenames: values 1 means the order 1,2,3, etc., i.e. filenames do not depend on the information in sequence headers after '>' in input FASTA file; 0 = filenames are defined by the information in sequence headers after '>' in input FASTA file. For example, for human genome with headers of chromosomes { >chr1, >chr2, ... , >chr22, >chrX and >chrY } and value 0 provides exactly {chr1.fa, chr2.fa, ... , chr22.fa, chrX.fa and chrY.fa }, while value 1 does not

## Whole genome conversion from FASTA to PLAIN format
[fasta_to_plain0.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/fasta_to_plain0.cpp)
1. path to whole genome sequences of chromosomes in plain format (see the paragraph below, the last symbol of path must be '/' and '\\' for Linux and Windows OS, respectively)
2. species and genome release (values hg38, mm10, rn6, zf11, dm6, and ce235; at10, gm21, zm73, and mp61; sc64 and sch294 stand for animals: human *Homo sapiens* hg38, mouse *Mus musculus* mm10, rat *Rattus norvegicus* Rnor_6.0, zebrafish *Danio rerio* GRCz11, fly *Drosophila melanogaster* dm6, and roundworm *Caenorhabditis elegans* WBcel235; plants: arabidopsis *Arabidopsis thaliana* TAIR10, soybean *Glycine max* v2.1, maize *Zea mays* B73, and liverwort *Marchantia polymorpha* MpTak v6.1; fungi: baker's yeast *Saccharomyces cerevisiae* R64-1-1 and fission yeast *Schizosaccharomyces pombe* ASM294v2, respectively)

## BED to FASTA conversion
[longext_many.cpp](https://github.com/parthian-sterlet/antinoise/blob/main/src/longext_many.cpp)
1. path to whole genome sequences of chromosomes in plain format (see the paragraph below, the last symbol of path must be '/' and '\\' for Linux and Windows OS, respectively)
2. input BED format file - tab-delimited txt format, first column contains chromosome name (e.g. chr1, chr2, etc.), second/third columns contain starting/ending positions of genomic fragments, in subsequent columns symbols '+'/'-' designate DNA strand, and arbitrary identifier (e.g. peak quiality, gene names) are allowed
3. output FASTA format file
4. integer value, extention of all fragment sequences in 5' direction (default value 0)
5. int maximal length of one FASTA sequence
6. species and genome release (values hg38, mm10, rn6, zf11, dm6, and ce235; at10, gm21, zm73, and mp61; sc64 and sch294 stand for animals: human *Homo sapiens* hg38, mouse *Mus musculus* mm10, rat *Rattus norvegicus* Rnor_6.0, zebrafish *Danio rerio* GRCz11, fly *Drosophila melanogaster* dm6, and roundworm *Caenorhabditis elegans* WBcel235; plants: arabidopsis *Arabidopsis thaliana* TAIR10, soybean *Glycine max* v2.1, maize *Zea mays* B73, and liverwort *Marchantia polymorpha* MpTak v6.1; fungi: baker's yeast *Saccharomyces cerevisiae* R64-1-1 and fission yeast *Schizosaccharomyces pombe* ASM294v2, respectively)
7. log file informing about abnormal termination of program due to errors in BED file (start/end positions are located beyond the chromosomes, etc.), correct completion of a conversion implies that this file is empty
