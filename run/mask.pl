#!/usr/bin/perl
use 5.8.1; use strict; use warnings; 

my ($cmd, $path_exe, $path_in, $path_bed, $path_out, $black_or_white, $check_overlap, $prepare_genome, $genome, $genome_fa);
my ($bed_list_file_old, $bed_list_file_new, $bed_list_file, $bed_chipseq_file_old, $bed_chipseq_file_new, $bed_chipseq_file, $file_overlap_sta);
my ($bed_list_file_sorted, $bed_list_file_sorted_no_over, $bedext, $chr, $backext, $faext,$bederr, $noovext, $len_back);
my ($gb_fold, $gb_at, $gb_limit, $gb_done, $gb_ext1, $gb_ext2, $gb_ext3, $gb_ext4, $gb_ext5);

if(scalar(@ARGV)==0){ die "Wrong arguments!";}

$path_exe=           $ARGV[0]; # path to executable: fasta_muliplefiles.exe, bed_chr_separation.exe, background_genome_mono.exe, fasta_to_plain0.exe, longext_many.exe, bed_chr_mask.exe, bed_sort.exe
$path_in=            $ARGV[1]; # reference genome in FASTA format, respective genome in PLAIN format also will be there
$path_bed=           $ARGV[2]; # path for whitelisted/blacklisted BED, ChIP-seq BED
$path_out=           $ARGV[3]; # output path, masked genome also will be there
$genome_fa=          $ARGV[4]; # reference genome in FASTA format, should be placed in the folder $path_in (see below), e.g. Homo_sapiens.GRCh38.dna.primary_assembly.fa from https://ftp.ensembl.org/pub/release-110/fasta/homo_sapiens/dna/Homo_sapiens.GRCh38.dna.primary_assembly.fa.gz
$prepare_genome=     $ARGV[5]; # 1 = start from the reference genome in FASTA, 0 = genome is already done in PLAIN format
$bed_list_file=      $ARGV[6]; # BED file, blacklisted or whitellisted regions
$black_or_white=     $ARGV[7]; # -1 = blacklist, 1 = whitelist
$check_overlap=      $ARGV[8]; # check self-overlaps in blacklist or whitelist files
$bed_chipseq_file=   $ARGV[9]; # BED file tested, without extention ".bed"
$len_back=           $ARGV[10]; # 0 means exact correspondence between forground and background, ny other value greater than zero will set the length of sequences in the background set 
$genome=             $ARGV[11]; # genome, hg38 mm10 rn6 zf11 dm6 ce235 sc64 sch294 at10 gm21 zm73 mp61
$gb_fold=            $ARGV[12]; # number of found background sequences per one foreground sequence, (default value 5)
$gb_at=              $ARGV[13]; # deviation of the A/T nucleotide content of a background sequence from that for a foreground sequence, (default value 0.01)
$gb_limit=           $ARGV[14]; # if a given number of attempts Na to find any background sequence is unsuccessful, then the algorithm is exited (default value 50000)
$gb_done=            $ARGV[15]; # the fraction of completely processed input sequences allowing to stop calculations (default value 0.99)

$bedext = ".bed", $faext = ".fa", $chr = "chr", $backext = "_gb", $noovext = "_no_over_", $bederr = "bed_errors.txt", $gb_ext1 = ".outm", $gb_ext2 = ".outd", $gb_ext3 = ".outm_one", $gb_ext4 = ".outd_one", $gb_ext5 = ".outlog";
$file_overlap_sta = "area_self_overlap.txt";

if($black_or_white == 1){
$bed_list_file_sorted = "whitelist_sorted";
}
else{
$bed_list_file_sorted = "blacklist_sorted";
}

$bed_list_file_old =  $path_bed . $bed_list_file;
$bed_list_file_new =  $path_out . $bed_list_file;

$bed_chipseq_file_old = $path_bed . $bed_chipseq_file;
$bed_chipseq_file_old = $bed_chipseq_file_old . $bedext;
$bed_chipseq_file_new = $path_out . $bed_chipseq_file;
$bed_chipseq_file_new = $bed_chipseq_file_new . $bedext;

if($prepare_genome == 1){

if ( -d "$path_out"){
    print "Directory already exist.\n";
}
else{
   mkdir($path_out)
   or die("Can't create directory \"$path_out\": $!\n");
}

$cmd= "$path_exe/fasta_muliplefiles.exe ${path_in}${genome_fa} ${path_in}${chr} 0 .fa";
print "$cmd\n";
system $cmd;

$cmd= "$path_exe/fasta_to_plain0.exe ${path_in} ${genome}";
print "$cmd\n";
system $cmd;

}

$cmd= "cp $bed_list_file_old $bed_list_file_new";
print "$cmd\n";
system $cmd;

$cmd= "cp $bed_chipseq_file_old $bed_chipseq_file_new";
print "$cmd\n";
system $cmd;

$cmd= "$path_exe/bed_sort.exe ${path_out}${bed_list_file} ${path_out}${bed_list_file_sorted}${bedext} ${genome}";
print "$cmd\n";
system $cmd;

$cmd= "$path_exe/bed_chr_separation.exe ${path_out}${bed_list_file_sorted}${bedext} ${path_out}${bed_list_file_sorted} ${genome}";
print "$cmd\n";
system $cmd;

if($check_overlap == 1)
{
$bed_list_file_sorted_no_over = $bed_list_file_sorted . $noovext;
$cmd= "$path_exe/area_self_overlap.exe ${path_out}${bed_list_file_sorted} ${path_out}${bed_list_file_sorted_no_over} ${genome} ${path_out}${file_overlap_sta}";
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

$cmd= "$path_exe/background_genome_mono.exe ${path_out} ${path_out}${bed_chipseq_file}${faext} ${path_out}${bed_chipseq_file}${backext} ${gb_fold} ${gb_at} ${gb_limit} ${genome} ${gb_done} ${len_back} ${path_out}${bed_chipseq_file}${gb_ext1} ${path_out}${bed_chipseq_file}${gb_ext2} ${path_out}${bed_chipseq_file}${gb_ext3} ${path_out}${bed_chipseq_file}${gb_ext4} ${path_out}${bed_chipseq_file}${gb_ext5}";
print "$cmd\n";
system $cmd;

