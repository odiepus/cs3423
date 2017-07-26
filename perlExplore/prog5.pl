#!/usr/bin/perl -w

foreach $x (@ARGV)
{
   open(F, "find $x |") or die;
       while (<F>)
       {
            push @list, $_;
       }
}

@l = sort @list;
shift @l;

foreach $y (@l)
{
    print $y;
}
