#!/usr/bin/perl -w
#

$regex = shift;
if ($regex eq "-f")
{
    print "111\n\n";
    $regex = shift;
    while (@ARGV != 0)
    {
        print "past while(at argv) \n\n";
        $item = shift;
        if(-f $item && -T $item)
        {
            print "past first file/text checker \n\n";

            chomp $item;

            open(F, "find $item |") or next;

            while ($line = <F>)
            {
                chomp $line;

                print "past first open $line\n\n";

                open(G, $line) or next;
                $stream = <G>;
                chomp $stream;
                print "opened stream on $line $stream\n\n";
                    while(<G>)
                    {
                        print if(/$regex/) ;
                    }
            }
        }
        else
        {
            open(H, "find $item |") or next;
            $x = <H>;
            print "created H $x\n\n";
            if((-f $item && -T $item))
            {
                while(<H>)
                {
                    print if(/$regex/) ;
                }
            }
            else
            {

            }
        }
    }
}
else
{
    while (@ARGV != 0)
    {

    }
}
