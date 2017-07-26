#!/usr/bin/perl -w

while(<>)
{
    chomp;
    @f = split /:/, ;
    print "@f[0]\t\t@f[4]\n";
}
