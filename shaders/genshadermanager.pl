#!/bin/env perl

use strict;

opendir my $dir, "." or die "Cannot open directory: $!";
my @files = readdir $dir;
closedir $dir;

my @shaders;

foreach my $file (@files) {
    if ($file !~ /(.+)\.(\w\w\w)$/) {
        next;
    }
    my $program = $1;
    my $type = $2;
    if ($type !~ /frg|vrt/) {
        next;
    }
    my $name = $program."_".$type;

    push @shaders, [$program,$name,$type];
    print "\n\nstatic const char* ${name} =\n";
    open (my $fh, "<",$file) or die ("Error: Couldn't open $file");
    while (my $line = <$fh>) {
        chomp($line);
        print "\"$line\\n\"\n";
    }
    print ";\n";
    close ($fh);
}

print "\nstatic const int shaderCount = ".($#shaders+1).";\n";

print "\nstatic const char* const programNames[] = {\n";
foreach my $shader (@shaders) {
    print "    \"$$shader[0]\",\n";
}
print "};\n\n";

print "\nstatic const char* const shaderNames[] = {\n";
foreach my $shader (@shaders) {
    print "    \"$$shader[1]\",\n";
}
print "};\n\n";

print "\nstatic const char* const shaderText[] = {\n";
foreach my $shader (@shaders) {
    print "    $$shader[1],\n";
}
print "};\n\n";

print<<EOF
enum ShaderTypeEnum {
    FRAGMENT = 0,
    VERTEX = 1
};
EOF
;

print "\nstatic const ShaderTypeEnum shaderType[] = {\n";
foreach my $shader (@shaders) {
    if ($$shader[2] =~ /frg/) {
        print "    FRAGMENT,\n";
    } elsif ($$shader[2] =~ /vrt/) {
        print "    VERTEX,\n";
    } else {
        die ("Unknown Shader Type ($$shader[2])");
    }
}
print "};\n\n";
