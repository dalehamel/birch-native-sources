#!/usr/bin/perl -w

open (VERS, "embossversion -full -auto|") || die "Cannot run embossversion";
while (<VERS>) {
    if(/InstallDirectory: +(\S+)/) {
	$installtop = $1;
	$installtop =~ s/\/$//;
    }
    if(/BaseDirectory: +(\S+)/) {
	$distribtop = $1;
	$distribtop =~ s/\/$//;
    }
}
close VERS;

$docdir = "$distribtop/doc/programs/master/emboss/apps";
$docinc = "$docdir/inc";

opendir(INC, $docinc);

while ($file = readdir(INC)) {
    if($file =~ /(^[^.]+)[.]ione$/) {
	$newname = "Short".ucfirst($1);
	system "cp $docinc/$file $newname";
	$newname = "Options".ucfirst($1);
	system "acdtable $1 -verbose 2> x.x";
	system "wikifytable.pl x.x > $newname";
	system "rm x.x";
	$newname = ucfirst($1);
	system "wikifyhtml.pl $docdir/$1.html > $newname.wiki";
    }
    if($file =~ /(^[^.]+)[.]isee$/) {
	$newname = "Seealso".ucfirst($1);
	system "wikifyseealso.pl $docinc/$file > $newname";
    }
    if($file =~ /(^[^.]+)[.]usage$/) {
	$newname = "Example".ucfirst($1);
	system "wikifyusage.pl $docinc/$file > $newname";
    }
    if($file =~ /(^[^.]+)[.]input$/) {
	$newname = "Input".ucfirst($1);
	system "wikifyusage.pl $docinc/$file > $newname";
    }
    if($file =~ /(^[^.]+)[.]output$/) {
	$newname = "Output".ucfirst($1);
	system "wikifyusage.pl $docinc/$file > $newname";
    }
    if($file =~ /(^[^.]+)[.]comment$/) {
	$newname = "Comment".ucfirst($1);
	system "wikifyhtml.pl $docinc/$file > $newname";
    }
    if($file =~ /(^[^.]+)[.]history$/) {
	$newname = "History".ucfirst($1);
	system "wikifyhtml.pl $docinc/$file > $newname";
    }
}
