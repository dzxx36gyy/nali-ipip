while ($line=<>) {
    $line =~ s/((?:[0-2]?[0-9]{1,2}\.){3}[0-2]?[0-9]{1,2})/ipip($1)/eg;
    print $line;
}
sub ipip {
    my $ip=$_[0];

    my $addr;
    $addr=`ipipnali $ip`;

    #optimize output format
    $addr =~ s/\n//g;
    $addr =~ s/ $//g;
    return "$ip \[$addr\]";
}
