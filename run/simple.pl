#!/usr/bin/perl
use 5.8.1; use strict; use warnings;

my ($cmd, $path_exe, $path_in, $path_bed, $path_out, $genome, $chipseq_file_old, $chipseq_file_new, $chipseq_file,$len_back);
my ($bedext, $backext, $faext, $bed_or_fasta, $bederr);
my ($gb_fold, $gb_at, $gb_limit, $gb_done, $gb_ext1, $gb_ext2, $gb_ext3, $gb_ext4, $gb_ext5);

if(scalar(@ARGV)==0){ die "Wrong arguments!";}

$path_exe=           $ARGV[0]; # path to executable: fasta_muliplefiles.exe, bed_chr_separation.exe, background_genome_mono.exe, fasta_to_plain0.exe, longext_many.exe, bed_chr_mask.exe, bed_sort.exe
$path_in=            $ARGV[1]; # reference genome in FASTA format, respective genome in PLAIN format also will be there
$path_bed=           $ARGV[2]; # path for whitelisted/blacklisted BED, ChIP-seq BED
$path_out=           $ARGV[3]; # output path, place balacklist file there, masked genome also will be there
$chipseq_file=       $ARGV[4]; # FASTA or BED file tested, without extention ".bed"
$bed_or_fasta=       $ARGV[5]; # chipseq file extention: ".bed" = BED file, otherwise ".fa" or ".seq" = FASTA file
$len_back=           $ARGV[6]; # 0 means exact correspondence between forground and background, any other value greater than zero will set the length of sequences in the background set
$genome=             $ARGV[7]; # genome, hg38 mm10 rn6 zf11 dm6 ce235 sc64 sch294 at10 gm21 zm73 mp61
$gb_fold=            $ARGV[8]; # number of found background sequences per one foreground sequence, (default value 5)
$gb_at=              $ARGV[9]; # deviation of the A/T nucleotide content of a background sequence from that for a foreground sequence, (default value 0.01)
$gb_limit=           $ARGV[10]; # total average number of attempts Na to get background sequences from genome per one foreground sequence (default value 10000)
$gb_done=            $ARGV[11]; # the fraction of completely processed input sequences allowing to stop calculations (default value 0.99)

$bedext = ".bed", $faext = ".fa", $backext = "_gb";
$gb_ext1 = ".outm", $gb_ext2 = ".outd", $gb_ext3 = ".outm_one", $gb_ext4 = ".outd_one", $gb_ext5 = ".outlog";
$bederr = "bed_errors.txt";

$chipseq_file_old = $path_bed . $chipseq_file;
$chipseq_file_old = $chipseq_file_old . $bed_or_fasta;
$chipseq_file_new = $path_out . $chipseq_file;
$chipseq_file_new = $chipseq_file_new . $bed_or_fasta;

if ( -d "$path_out"){
    print "Directory already exist.\n";
}
else{
   mkdir($path_out)
   or die("Can't create directory \"$path_out\": $!\n");
}

$cmd= "cp $chipseq_file_old $chipseq_file_new";
print "$cmd\n";
system $cmd;

if($bed_or_fasta eq $bedext){
$cmd= "$path_exe/longext_many.exe ${path_in} ${path_out}${chipseq_file}${bedext} ${path_out}${chipseq_file}${faext} 0 0 3000 ${genome} ${path_out}${bederr}";
print "$cmd\n";
system $cmd;
}

else{
$faext = $bed_or_fasta;
}

$cmd= "$path_exe/background_genome_mono.exe ${path_in} ${path_out}${chipseq_file}${faext} ${path_out}${chipseq_file}${backext} ${gb_fold} ${gb_at} ${gb_limit} ${genome} ${$len_back} ${gb_done} ${path_out}${chipseq_file}${gb_ext1} ${path_out}${chipseq_file}${gb_ext2} ${path_out}${chipseq_file}${gb_ext3} ${path_out}${chipseq_file}${gb_ext4} ${path_out}${chipseq_file}${gb_ext5}";
print "$cmd\n";
system $cmd;

# puts("Sintax: 1 path_genome 2file in_fa, 3file out_fa 4int height 5double mono prec 6int back_iter 7char genome (hg38 mm10 rn6 zf11 dm6 ce235 sc64 sch294 at10 gm21 zm73 mp61)");
# puts("8double stop_fraction 9int sequence_length (the same OR (>0 && <3000) 10,11,12,13file_out (mono-, di-) x (forground_vs_background, statistics) 14file_out log");
