#!/usr/bin/perl -w

@dirs = <>;
@files = `find @dirs`;

@list = grep("*.pl" && "*.awk", @files);

chop @list;

print join("\n", @list), "\n";
