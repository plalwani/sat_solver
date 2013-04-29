#! /usr/bin/perl

# Script to loop over all benchmarks and consolidate the runtime of each benchmark in a csv
# all benchmarks should be saved in benchmarks folder in current directory

use strict;
use warnings;
use Cwd;

print"\nThis script will loop over all cnf files stored in ./benchmarks/";
print"\nAll results will be saved in Results.csv and output files will be dumped in tar files(benchmark folder)";
print "\nPress any key to continue:";
<>;

print "\ngetting the list of benchmarks now\n";

system("make clean");
system("make");

# Consolidated file to store all results
my $consol_file = getcwd() . "/Results.csv";
open(FILE, ">",$consol_file) or die $!;
print FILE "Benchmark,Status,Basic DPLL(hh:mm:ss),DPLL with Conflict learning(hh:mm:ss),DPLL with Watch_Var(hh:mm:ss),DPLL with Watch_Var & Conflict learning(hh:mm:ss)\n";

my $cmd;
my @benchmarks = `ls benchmarks/*.cnf`;	# Get a list of benchmarks in benchmarks folder
foreach(@benchmarks)
{
	# Get the benchmark name
	chomp($_);
	my @bench = split "/" , $_;

	print FILE "$bench[1]";	# print benchmark name to file

	# Basic DPLL
	print "\nRunning benchmark " . $bench[1] . " with basic DPLL: \n";
	run_sat_solver($_,0,0);
	print_status($bench[1],"00");
	print_time($bench[1],"00");
	
	# DPLL with watch Variables
	print "\nRunning benchmark " . $bench[1] . " with conflict driven learning: \n";
	run_sat_solver($_,0,1);
	print_time($bench[1],"01");

	# DPLL with Conflict Clauses
	print "\nRunning benchmark " . $bench[1] . " with watched variables: \n";
	run_sat_solver($_,1,0);
	print_time($bench[1],"10");

	# DPLL with Watch Variables and Conflict Clauses
	print "\nRunning benchmark " . $bench[1] . " with watched variables and conflict driven learning: \n";
	run_sat_solver($_,1,1);
	print_time($bench[1],"11");

	print FILE "\n";
}

close(FILE);
# zip all output files
system("tar --remove-files -cf ./benchmarks/output_files.tar ./benchmarks/*.out");
# zip all time files
system("tar --remove-files -cf ./benchmarks/time_files.tar ./benchmarks/*.time");


# Read the time from time file
sub print_time
{
	my $tm_file = "./benchmarks/" . $_[0] . "_" . "$_[1]" . ".time";
	open(FL, "<", $tm_file) or die $!;
	my @tmp = <FL>;
	close(FL);
	chomp($tmp[0]);
	print FILE ",$tmp[0]";
}


#Find if the benchmark is SAT or UNSAT
sub print_status
{
	my $out_file = "./benchmarks/" . $_[0] . "_" . "$_[1]" . ".out";
	open(FL, "<", $out_file) or die $!;
	my @tmp = <FL>;
	close(FL);
	
	my $flag = 0;
	foreach(@tmp)
	{
		if($_ =~ /is SAT/)
		{
			print FILE ",SAT";
			$flag = 1;
			last;
		}
	}

	if($flag ==0)
	{
		print FILE ",UNSAT";
	}
}


#Run the sat solver with specified toggle
sub run_sat_solver
{
	my $cmd = "/usr/bin/time -f \"%E\" -o $_[0]" . "_" . "$_[1]" . "$_[2]" . ".time ./myrun $_[0] $_[0]" . "_" . "$_[1]" . "$_[2]" . ".out" . " $_[1] $_[2]";
	system($cmd);
}
