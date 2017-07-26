BEGIN{FS=','
    $power = 0
    $cost = 0
    $x = 0

~12/20/2012~ {$power += $3
                    $cost += $4
                    push minV[$x], $5
                    push maxV[$x], $6
                    $x++
                }

END{
    mV[] = sort minV[];
    mxV[] = sort maxV[];
    print "Date: 12/20/2012\n";
    print "Power: $power\n";
    print "Cost: $cost\n";
    print "Minimum Volatage: mV[0]\n";
    print "Maximum Voltage: maxV[0]\n";
}
