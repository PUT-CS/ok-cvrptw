use feature "say";
use strict;

my @TEMPS = ();
for (my $i=100000; $i<=1000000; $i += 100000) {
    push @TEMPS, $i;
}

my @COOLING_RATES = ();
for (my $i=0.91; $i<=0.99; $i += 0.01) {
    push @COOLING_RATES, $i;
}

my @MAX_NEIGHBORS = ();
for (my $i=10; $i<=100; $i+=10) {
    push @MAX_NEIGHBORS, $i;
}

my @LETTERS = ("R", "C", "RC");
my @NUM = ("102", "103", "104", "202", "203", "204");

my $best_temp;
my $best_rate;
my $best_neighbors;

my $lowest_sum = 10000000;

for (my $i=0; $i<$#TEMPS; $i++) {
    my $temp = $TEMPS[$i];
    say "Current Temperature: ". $temp;
    
    print "Best Temperature: " . $best_temp . "\n";
    print "Best Rate: " . $best_rate . "\n";
    print "Best Neighbor Num: " . $best_neighbors . "\n";

    for (my $j=0; $j<$#COOLING_RATES; $j++) {
        my $rate = $COOLING_RATES[$j];
        say "Current Cooling Rate: " . $rate;
        for (my $k=0; $k<$#MAX_NEIGHBORS; $k++) {
            my $neighbors = $MAX_NEIGHBORS[$k];
            say "Current Neighbor Num: " . $neighbors;
            my $SUM = 0.0;

            #perform all the tests
            for (my $l = 0; $l<@LETTERS; $l++) {
                my $letter = $LETTERS[$l];
                for (my $m = 0; $m<@NUM; $m++) {
                    my $num = $NUM[$m];
                    my $filename = $letter . $num;
                    #say "./cvrptw data/$filename.txt $temp 5 $rate $neighbors";
                    my $output = `./cvrptw data/$filename.txt $temp 5 $rate $neighbors`;
                    my $value_str = `echo '$output' | head -n 1 | awk '{print \$2}'`;
#                    print $value_str;
                    $SUM = $SUM + $value_str;
                }
            }
            say "Lowest sum: " . $lowest_sum . "\n";
            say "Sum: " . $SUM . "\n";
            if ($SUM < $lowest_sum) {
                $lowest_sum = $SUM;
                $best_temp = $temp;
                $best_rate = $rate;
                $best_neighbors = $neighbors;
            }
        }
    }
}

print "Best Temperature: " . $best_temp . "\n";
print "Best Rate: " . $best_rate . "\n";
print "Best Neighbor Num: " . $best_neighbors . "\n";

die "Finished Tuning";

