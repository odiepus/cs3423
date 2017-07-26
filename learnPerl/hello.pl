#!/usr/bin/perl -w

die "kill username\n" if @ARGV != 1;

$user = $ARGV[0];

open(P, "names.txt");

while( <P> )
{
    next unless /^($user.*) $/;
    print $1, "\n" ;
}
