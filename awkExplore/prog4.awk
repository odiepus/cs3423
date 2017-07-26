BEGIN{
    s = 0
    t = 0
    u = 0
    v = 0
    w = 0
    }

    /Ascend-Data-Rate/ {
        if ($3 <= 14400)
        {
            {s += 1}
        }
        else if ($3 > 14401 && $3 <= 19200)
        {
            {t += 1}
        }
        else if ($3 > 19201 && $3 <= 28800)
        {
            {u += 1}
        }
        else if ($3 > 28801 && $3 <= 36600)
        {
            {v += 1}
        }
        else if ($3 > 36600)
        {
            {w += 1}
        }
    }


END{ 
print "0-14400\t\t"s
print "14401-19200\t"t
print "19201-28800\t"u
print "28801-36600\t"v
print "above 36600\t"w
}
