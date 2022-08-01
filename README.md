# Antinoise - Background DNA sequences dataset generation for a given foreground dataset
# Description
Chromatin immunoprecipitation (ChIP)-based high throughput technique ChIP-seq allows genome-scale mapping of transcription factors binding sites (TFBS). The lengths of derived genome loci or peaks comprise hundreds of base pairs, however a TFBS typically varied in the length from 6 to 25 bp, e.g. see [CIS-BP database](http://cisbp.ccbr.utoronto.ca/). Hence, the motif enrichment analysis, e.g. de novo motif search is required to map exact positions of sites in peaks. The task of this analysis consists in detection of motifs specific for biological function of ChIP-seq target TFs. For each motif the significance of its enrichment in peaks (foreground dataset) depends on the choice of the approach of the background dataset generation. 
Here we introduce two approaches required in de novo motif search to generate the background sequence dataset with a given foreground dataset of ChIP-seq peaks: the first one ’genomic’ compiles randomly chosen sequences from a whole genome adopting the nucleotide content from the foreground sequence set, thus modeling an expected content of noise non-specific motifs [(Tsukanov et al., 2022)](https://doi.org/10.3389/fpls.2022.938545); the second ‘synthetic’ approach destroys the significant enrichment of any motifs through the permutation of nucleotides preserving the nucleotide content. 
# Requirements
The source code is written in C++ language. To compile exetubables from the source code you need:

* In Linux system, C++ compiler, e.g. [GCC](https://gcc.gnu.org/) compiler 
* In Windiws system any VC++ package, e.g. [Microsoft Visual Studio Community](https://visualstudio.microsoft.com/vs/community/)

# Source code
Folder [**src**](https://github.com/parthian-sterlet/antinoise/tree/main/src) contains files with the source codes, they respect to  genomic and synthetic background generation approaches.

## 1. Genomic
## 2. Synthetic
