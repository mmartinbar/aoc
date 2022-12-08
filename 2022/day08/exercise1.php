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

// Fill visibility array
$visible = array();
$numVisibleTrees = 0;
for ($i = 0; $i < $size; $i++) {
    for ($j = 0; $j < $size; $j++) {
        if ($i == 0 || $i == ($size - 1) || $j == 0 || $j == ($size - 1)) {
            $visible[$i][$j] = 1;
            $numVisibleTrees++;
        } else {
            $visible[$i][$j] = 0;
        }
    }
}

for ($i = 0; $i < $size; $i++) {
    $max_height_l = 0;
    $max_height_t = 0;
    for ($j = 0; $j < $size; $j++) {
            // left
            if ($heights[$i][$j] > $max_height_l) {
                $max_height_l = $heights[$i][$j];

                if ($visible[$i][$j] == 0) {
                    $visible[$i][$j] = 1;
                    $numVisibleTrees++;      
                }
            }

            // top
            if ($heights[$j][$i] > $max_height_t) {
                $max_height_t = $heights[$j][$i];

                if ($visible[$j][$i] == 0) {
                    $visible[$j][$i] = 1;
                    $numVisibleTrees++;      
                }
            }
    }

    $max_height_r = 0;
    $max_height_d = 0;
    for ($j = ($size - 1); $j >= 0; $j--) {
            // right
            if ($heights[$i][$j] > $max_height_r) {
                $max_height_r = $heights[$i][$j];

                if ($visible[$i][$j] == 0) {
                    $visible[$i][$j] = 1;
                    $numVisibleTrees++;      
                }
            }

            // down
            if ($heights[$j][$i] > $max_height_d) {
                $max_height_d = $heights[$j][$i];

                if ($visible[$j][$i] == 0) {
                    $visible[$j][$i] = 1;
                    $numVisibleTrees++;      
                }
            }
    }
}

//print_r($heights);
//print_r($visible);
echo "num visible trees $numVisibleTrees\n";

fclose($handle);

?>
