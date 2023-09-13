#!/usr/bin/perl";
use 5.8.1; use strict; use warnings;

my ($cmd, $path_exe, $bed_blacklist_file, $genome, $path_in, $path_out, $bed_chipseq_file);
my ($bed_blacklist_file_sorted, $bedext, $chr, $sep, $backext);
my ($gb_fold, $gb_at, $gb_limit, $gb_done, $gb_ext1, $gb_ext2, $gb_ext3, $gb_ext4, $gb_ext5);

if(scalar(@ARGV)==0){ die "Wrong arguments!";}

$path_exe=           $ARGV[0]; # path to executable: fasta_muliplefiles.exe, bed_chr_separation.exe, background_genome_mono.exe, fasta_to_plain0.exe, longext_many.exe, bed_chr_mask.exe, bed_sort.exe
$genome_fa=          $ARGV[1]; # reference genome in FASTA format should be placed in this folder, e.g. Homo_sapiens.GRCh38.dna.primary_assembly.fa from https://ftp.ensembl.org/pub/release-110/fasta/homo_sapiens/dna/Homo_sapiens.GRCh38.dna.primary_assembly.fa.gz
$bed_blacklist_file= $ARGV[2]; # BED file, blacklist regions
$genome=             $ARGV[3]; # genome, hg38 mm10 rn6 zf11 dm6 ce235 sc64 sch294 at10 gm21 zm73 mp61
$path_in=            $ARGV[4]; # reference genome in FASTA format, respective genome in PLAIN format also will be there
$path_out=           $ARGV[5]; # output path, place balacklist file there, masked genome also will be there
$bed_chiseq_file=    $ARGV[6]; # BED file tested, without extention ".bed"
$gb_fold=            $ARGV[7]; # number of found background sequences per one foreground sequence, (default value 5)
$gb_at=              $ARGV[8]; # deviation of the A/T nucleotide content of a background sequence from that for a foreground sequence, (default value 0.01)
$gb_limit=           $ARGV[9]; # total average number of attempts Na to get background sequences from genome per one foreground sequence (default value 10000)
$gb_done=            $ARGV[10]; # the fraction of completely processed input sequences allowing to stop calculations (default value 0.99)

$bed_blacklist_file_sorted = "blacklist_sorted";
$bedext = ".bed", $faext = ".fa", $chr = "chr", $sep = "_", $backext = "_gb";
$gb_ext1 = ".outm", $gb_ext2 = ".outd", $gb_ext3 = ".outm_one", $gb_ext4 = ".outd_one", $gb_ext5 = ".outlog";

$cmd= "$path_exe/fasta_muliplefiles.exe ${path_in}${genome_fa} ${path_in}${chr}";
print "$cmd\n";
system $cmd;                                                                                               

$cmd= "$path_exe/bed_sort.exe ${bed_blacklist_file} ${bed_blacklist_file_sorted}${bedext} ${genome}";
print "$cmd\n";
system $cmd;                                                                                               

$cmd= "$path_exe/bed_chr_separation.exe ${bed_blacklist_file_sorted}${bedext} ${bed_blacklist_file_sorted}${sep} ${genome}";
print "$cmd\n";
system $cmd;                                                                                               

$cmd= "$path_exe/bed_chr_mask.exe ${path_in} ${path_out} ${bed_blacklist_file_sorted}${sep} ${chr} ${chr} -1 ${genome}";
print "$cmd\n";
system $cmd;                                                                                               

$cmd= "$path_exe/longext_many.exe ${path_out} ${bed_chipseq_file} ${bed_chipseq_file}${faext} 0 0 3000 ${genome}";
print "$cmd\n";
system $cmd;                                                                                               

$cmd= "$path_exe/background_genome_mono.exe ${bed_chipseq_file}${faext} ${bed_chipseq_file}${$backext}${faext} ${gb_at} ${gb_limit} ${genome} ${gb_done} ${bed_chipseq_file}${gb_ext1} ${bed_chipseq_file}${gb_ext2} ${bed_chipseq_file}${gb_ext3} ${bed_chipseq_file}${gb_ext4} ${bed_chipseq_file}${gb_ext5}";
print "$cmd\n";
system $cmd;                                                                                               
