#!/usr/bin/perl

# Author: MKozuch
# Date: 2017-12-18

use strict;
use warnings;

my $maxRegisterValueInHistory = 0;

sub splitLine{
    my $line = shift(@_);
    return unless $$line and $$line =~ /^([a-z]+)\s(inc|dec)\s(-*[0-9]+)+\sif\s([a-z]+)\s(<|>|==|<=|>=|!=)\s(-*[0-9]+)+/;
    return($1, $2, $3, $4, $5, $6);
}

sub checkCondition{
    my $registersRef    = shift;
    my $operationSymbol = shift;
    my $registerName    = shift;
    my $compareValue    = shift;

    my $registerValue = exists $registersRef->{$registerName} ? $registersRef->{$registerName} : 0;

    my %operationsMap;
    $operationsMap{'>'}  = sub{ return shift(@_) >  shift(@_);};
    $operationsMap{'<'}  = sub{ return shift(@_) <  shift(@_);};
    $operationsMap{'=='} = sub{ return shift(@_) == shift(@_);};
    $operationsMap{'!='} = sub{ return shift(@_) != shift(@_);};
    $operationsMap{'>='} = sub{ return shift(@_) >= shift(@_);};
    $operationsMap{'<='} = sub{ return shift(@_) <= shift(@_);};

    my $op = $operationsMap{$operationSymbol}; 
    return $op->($registerValue, $compareValue);
}

sub modifyRegister{
    my $registersReference = shift;
    my $registerName       = shift;
    my $operationSymbol    = shift;
    my $value              = shift;

    my $registerValue = 0;
    unless(exists $registersReference->{$registerName}){
        $registersReference->{$registerName} = 0;
    }
    else{
        my $registerValue = $registersReference->{$registerName};
    }

    my %operationsMap;
    $operationsMap{'inc'}  = sub{ $_[0] +=  $_[1];};
    $operationsMap{'dec'}  = sub{ $_[0] -=  $_[1];};

    my $op = $operationsMap{$operationSymbol};
    $op->($registersReference->{$registerName}, $value);

    $maxRegisterValueInHistory = $registersReference->{$registerName} > $maxRegisterValueInHistory ?  $registersReference->{$registerName} : $maxRegisterValueInHistory;
}



unless(scalar(@ARGV) == 1 ){
    print("Bad usage\n");
    exit 1
}

my $filename = $ARGV[0];

open(my $file,  "<",  $filename)  or die "Can't open $filename: $!";

my %registers;

 while (<$file>){
    (my $regName, my $regOperation, my $value, my $condRegName, my $condOperation, my $condValue) = splitLine(\$_);

    if(checkCondition(\%registers, $condOperation, $condRegName, $condValue)){
        modifyRegister(\%registers, $regName, $regOperation, $value);
    }
 }

 my $max = 0;
 foreach my $val (values %registers){
     $max = $val if $val > $max;
 }

printf("Greatest register value: %d\n", $max);
printf("Greatest register value in history: %d\n", $maxRegisterValueInHistory);

close $file or die "$filename: $!";