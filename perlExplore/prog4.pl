#!/usr/bin/perl -w
@list;
while (<>)
{
    @f = split /:/, ;
    $string = "$f[0]\t\t$f[4]\n";
    push @list, $string;
}

@sortedList = sort @list;

foreach $x (@sortedList)
{
    print $x;
}
