#!/usr/bin/php

<?php

$handle = fopen("input.txt", "r");
if (!$handle) {
    return;
}

// Fill heights array
$heights = array();
$i = 0;
while (($line = fgets($handle)) !== false) {
    $heights[$i++] = str_split(trim($line));
}
$size = count($heights);

// Init scores array
$scores = array();
for ($i = 0; $i < $size; $i++) {
    for ($j = 0; $j < $size; $j++) {
        $scores[$i][$j] = 0;
    }
}

// Compute scores array
$max_score = 0;
for ($i = 0; $i < $size; $i++) {
    for ($j = 0; $j < $size; $j++) {
        $cur_height = $heights[$i][$j];

        // right
        $trees_r = 0;
        for ($k = ($j + 1); $k < $size; $k++) {
            $trees_r++;

            if ($heights[$i][$k] >= $cur_height) {
                break;
            }
        }

        // left
        $trees_l = 0;
        for ($k = ($j - 1); $k >= 0; $k--) {
            $trees_l++;
            
            if ($heights[$i][$k] >= $cur_height) {
                break;
            }
        }

        // top
        $trees_t = 0;
        for ($k = ($i - 1); $k >= 0; $k--) {
            $trees_t++;
            
            if ($heights[$k][$j] >= $cur_height) {
                break;
            }
        }

        // down
        $trees_d = 0;
        for ($k = ($i + 1); $k < $size; $k++) {
            $trees_d++;
            
            if ($heights[$k][$j] >= $cur_height) {
                break;
            }
        }

        // total score
        $scores[$i][$j] = $trees_r * $trees_l * $trees_t * $trees_d;
        if ($scores[$i][$j] >= $max_score) {
            $max_score = $scores[$i][$j];
        }   
    }
}

//print_r($heights);
//print_r($scores);
echo "max score $max_score\n";

fclose($handle);

?>
