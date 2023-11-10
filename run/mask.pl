#!/usr/bin/perl
use 5.8.1; use strict; use warnings;

my ($cmd, $path_exe, $path_in, $path_out, $bed_list_file, $black_or_white, $check_overlap, $genome, $genome_fa, $bed_chipseq_file, $file_overlap_sta);
my ($bed_list_file_sorted, $bed_list_file_sorted_no_over, $bedext, $chr, $backext, $faext,$bederr, $noovext);
my ($gb_fold, $gb_at, $gb_limit, $gb_done, $gb_ext1, $gb_ext2, $gb_ext3, $gb_ext4, $gb_ext5);

if(scalar(@ARGV)==0){ die "Wrong arguments!";}

$path_exe=           $ARGV[0]; # path to executable: fasta_muliplefiles.exe, bed_chr_separation.exe, background_genome_mono.exe, fasta_to_plain0.exe, longext_many.exe, bed_chr_mask.exe, bed_sort.exe
$path_in=            $ARGV[1]; # reference genome in FASTA format, respective genome in PLAIN format also will be there
$path_out=           $ARGV[2]; # output path, place balacklist file there, masked genome also will be there
$genome_fa=          $ARGV[3]; # reference genome in FASTA format, should be placed in the folder $path_in (see below), e.g. Homo_sapiens.GRCh38.dna.primary_assembly.fa from https://ftp.ensembl.org/pub/release-110/fasta/homo_sapiens/dna/Homo_sapiens.GRCh38.dna.primary_assembly.fa.gz
$bed_list_file=      $ARGV[4]; # BED file, blacklist or whitellist regions
$black_or_white=     $ARGV[5]; # 0 = blacklist, 1 = whitelist
$check_overlap=      $ARGV[6]; # check self-overlaps in blacklist or whitelist files
$bed_chipseq_file=   $ARGV[7]; # BED file tested, without extention ".bed"
$genome=             $ARGV[8]; # genome, hg38 mm10 rn6 zf11 dm6 ce235 sc64 sch294 at10 gm21 zm73 mp61
$gb_fold=            $ARGV[9]; # number of found background sequences per one foreground sequence, (default value 5)
$gb_at=              $ARGV[10]; # deviation of the A/T nucleotide content of a background sequence from that for a foreground sequence, (default value 0.01)
$gb_limit=           $ARGV[11]; # total average number of attempts Na to get background sequences from genome per one foreground sequence (default value 10000)
$gb_done=            $ARGV[12]; # the fraction of completely processed input sequences allowing to stop calculations (default value 0.99)

if($black_or_white == 1){
$bed_list_file_sorted = "whitelist_sorted";
}
else{
$bed_list_file_sorted = "blacklist_sorted";
}

$bedext = ".bed", $faext = ".fa", $chr = "chr", $backext = "_gb", $noovext = "_no_over_", $bederr = "bed_errors.txt", $gb_ext1 = ".outm", $gb_ext2 = ".outd", $gb_ext3 = ".outm_one", $gb_ext4 = ".outd_one", $gb_ext5 = ".outlog";
$file_overlap_sta = "area_self_overlap.txt";

$cmd= "$path_exe/fasta_muliplefiles.exe ${path_in}${genome_fa} ${path_in}${chr} 0";
print "$cmd\n";
system $cmd;

$cmd= "$path_exe/fasta_to_plain0.exe ${path_in} ${genome}";
print "$cmd\n";
system $cmd;

$cmd= "$path_exe/bed_sort.exe ${path_out}${bed_list_file} ${path_out}${bed_list_file_sorted}${bedext} ${genome}";
print "$cmd\n";
system $cmd;

$cmd= "$path_exe/bed_chr_separation.exe ${path_out}${bed_list_file_sorted}${bedext} ${path_out}${bed_list_file_sorted} ${genome}";
print "$cmd\n";
system $cmd;

if($check_overlap == 1){
$bed_list_file_sorted_no_over = $bed_list_file_sorted . $noovext;
$cmd= "$path_exe/area_self_overlap.exe ${path_out}${bed_list_file_sorted} ${path_out}${bed_list_file_sorted_no_over} ${genome}" ${path_out}${$file_overlap_sta};
print "$cmd\n";
system $cmd;
}
else{
$bed_list_file_sorted_no_over = $bed_list_file_sorted;
}

$cmd= "$path_exe/bed_chr_mask.exe ${path_in} ${path_out} ${bed_list_file_sorted_no_over} ${chr} ${chr} ${black_or_white} ${genome}";
print "$cmd\n";
system $cmd;

$cmd= "$path_exe/longext_many.exe ${path_in} ${path_out}${bed_chipseq_file}${bedext} ${path_out}${bed_chipseq_file}${faext} 0 0 3000 ${genome} ${path_out}${bederr}";
print "$cmd\n";
system $cmd;

$cmd= "$path_exe/background_genome_mono.exe ${path_out} ${path_out}${bed_chipseq_file}${faext} ${path_out}${bed_chipseq_file}${backext} ${gb_fold} ${gb_at} ${gb_limit} ${genome} ${gb_done} ${path_out}${bed_chipseq_file}${gb_ext1} ${path_out}${bed_chipseq_file}${gb_ext2} ${path_out}${bed_chipseq_file}${gb_ext3} ${path_out}${bed_chipseq_file}${gb_ext4} ${path_out}${bed_chipseq_file}${gb_ext5}";
print "$cmd\n";
system $cmd;

