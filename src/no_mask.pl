#!/usr/bin/perl
use 5.8.1; use strict; use warnings;

my ($cmd, $path_exe, $path_in, $path_out, $genome, $genome_fa, $bed_chipseq_file);
my ($bedext, $chr, $backext, $faext);
my ($gb_fold, $gb_at, $gb_limit, $gb_done, $gb_ext1, $gb_ext2, $gb_ext3, $gb_ext4, $gb_ext5);

if(scalar(@ARGV)==0){ die "Wrong arguments!";}

$path_exe=           $ARGV[0]; # path to executable: fasta_muliplefiles.exe, bed_chr_separation.exe, background_genome_mono.exe, fasta_to_plain0.exe, longext_many.exe, bed_chr_mask.exe, bed_sort.exe
$path_in=            $ARGV[1]; # reference genome in FASTA format, respective genome in PLAIN format also will be there
$path_out=           $ARGV[2]; # output path, place balacklist file there, masked genome also will be there
$genome_fa=          $ARGV[3]; # reference genome in FASTA format, should be placed in the folder $path_in (see below), e.g. Homo_sapiens.GRCh38.dna.primary_assembly.fa from https://ftp.ensembl.org/pub/release-110/fasta/homo_sapiens/dna/Homo_sapiens.GRCh38.dna.primary_assembly.fa.gz
$bed_chipseq_file=   $ARGV[4]; # BED file tested, without extention ".bed"
$genome=             $ARGV[5]; # genome, hg38 mm10 rn6 zf11 dm6 ce235 sc64 sch294 at10 gm21 zm73 mp61
$gb_fold=            $ARGV[6]; # number of found background sequences per one foreground sequence, (default value 5)
$gb_at=              $ARGV[7]; # deviation of the A/T nucleotide content of a background sequence from that for a foreground sequence, (default value 0.01)
$gb_limit=           $ARGV[8]; # total average number of attempts Na to get background sequences from genome per one foreground sequence (default value 10000)
$gb_done=            $ARGV[9]; # the fraction of completely processed input sequences allowing to stop calculations (default value 0.99)

$bedext = ".bed", $faext = ".fa", $chr = "chr", $backext = "_gb";
$gb_ext1 = ".outm", $gb_ext2 = ".outd", $gb_ext3 = ".outm_one", $gb_ext4 = ".outd_one", $gb_ext5 = ".outlog";

$cmd= "$path_exe/fasta_muliplefiles.exe ${path_in}${genome_fa} ${path_in}${chr} 0";
print "$cmd\n";
system $cmd;

$cmd= "$path_exe/fasta_to_plain0.exe ${path_in} ${genome}";
print "$cmd\n";
system $cmd;

$cmd= "$path_exe/longext_many.exe ${path_in} ${bed_chipseq_file}${bedext} ${bed_chipseq_file}${faext} 0 0 3000 ${genome}";
print "$cmd\n";
system $cmd;

$cmd= "$path_exe/background_genome_mono.exe ${path_in} ${path_out}${bed_chipseq_file}${faext} ${path_out}${bed_chipseq_file}${backext}${faext} ${gb_fold} ${gb_at} ${gb_limit} ${genome} ${gb_done} ${path_out}${bed_chipseq_file}${gb_ext1} ${path_out}${bed_chipseq_file}${gb_ext2} ${path_out}${bed_chipseq_file}${gb_ext3} ${path_out}${bed_chipseq_file}${gb_ext4} ${path_out}${bed_chipseq_file}${gb_ext5}";
print "$cmd\n";
system $cmd;

