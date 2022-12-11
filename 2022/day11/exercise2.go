package main

import (
    "fmt"
    "sort"
)

type NewWorryLevelFunc func(int) int

type NewMonkeyFunc func(int) int

type Monkey struct {
    NumInspectedItems int
    Items []int
    GetNewWorryLevel NewWorryLevelFunc
    GetNewMonkey NewMonkeyFunc
}

func NewMonkey(n int, items []int, newWorryFunc NewWorryLevelFunc, newMonkeyFunc NewMonkeyFunc) (*Monkey) {
    monkey := &Monkey {
        NumInspectedItems: n,
        Items: items,
        GetNewWorryLevel: newWorryFunc,
        GetNewMonkey: newMonkeyFunc,
    }
    return monkey
}

func main() {
    /**
    // short_input
    var numMonkeys = 4
    var monkeys [4]Monkey
    var primeNumbersProduct = 23 * 19 * 13 * 17
    monkeys[0] = *NewMonkey(0,[]int{79,98},func(old int) int { return old * 19 },func(worry int) int { if worry%23 == 0 { return 2 } else { return 3 } })
    monkeys[1] = *NewMonkey(0, []int{54, 65, 75, 74}, func(old int) int { return old + 6 }, func(worry int) int { if (worry%19 == 0) { return 2 } else { return 0 } } )
    monkeys[2] = *NewMonkey(0, []int{79, 60, 97}, func(old int) int { return old * old }, func(worry int) int { if (worry%13 == 0) { return 1 } else { return 3 } } )
    monkeys[3] = *NewMonkey(0, []int{74}, func(old int) int { return old + 3 }, func(worry int) int { if (worry%17 == 0) { return 0 } else { return 1 } } )
    */

    // long_input
    var numMonkeys = 8
    var monkeys [8]Monkey
    var primeNumbersProduct = 2 * 3 * 5 * 7 * 11 * 13 * 17 * 19
    monkeys[0] = *NewMonkey(0,[]int{89,74},func(old int) int { return old * 5 },func(worry int) int { if worry%17 == 0 { return 4 } else { return 7 } })
    monkeys[1] = *NewMonkey(0,[]int{75,69,87,57,84,90,66,50},func(old int) int { return old + 3 },func(worry int) int { if worry%7 == 0 { return 3 } else { return 2 } })
    monkeys[2] = *NewMonkey(0,[]int{55},func(old int) int { return old + 7 },func(worry int) int { if worry%13 == 0 { return 0 } else { return 7 } })
    monkeys[3] = *NewMonkey(0,[]int{69,82,69,56,68},func(old int) int { return old + 5 },func(worry int) int { if worry%2 == 0 { return 0 } else { return 2 } })
    monkeys[4] = *NewMonkey(0,[]int{72,97,50},func(old int) int { return old + 2 },func(worry int) int { if worry%19 == 0 { return 6 } else { return 5 } })
    monkeys[5] = *NewMonkey(0,[]int{90,84,56,92,91,91},func(old int) int { return old * 19 },func(worry int) int { if worry%3 == 0 { return 6 } else { return 1 } })
    monkeys[6] = *NewMonkey(0,[]int{63,93,55,53},func(old int) int { return old * old },func(worry int) int { if worry%5 == 0 { return 3 } else { return 1 } })
    monkeys[7] = *NewMonkey(0,[]int{50,61,52,58,86,68,97},func(old int) int { return old + 4 },func(worry int) int { if worry%11 == 0 { return 5 } else { return 4 } })

    for i := 0; i < 10000; i++ {
        for m := 0; m < numMonkeys; m++ {
            for len(monkeys[m].Items) != 0 {
                var oldWorry = monkeys[m].Items[0]
                monkeys[m].Items = monkeys[m].Items[1:]
                var newWorry = monkeys[m].GetNewWorryLevel(oldWorry)
                var finalWorry = newWorry % primeNumbersProduct
                var newMonkey = monkeys[m].GetNewMonkey(finalWorry)
                monkeys[newMonkey].Items = append(monkeys[newMonkey].Items, finalWorry)
                monkeys[m].NumInspectedItems = monkeys[m].NumInspectedItems + 1;
            }
        }
        if ((i == 0) || (i == 19) || (i % 1000 == 999)) {
            fmt.Printf("Iteration %d\n", i)
            for m := 0; m < numMonkeys; m++ {
                fmt.Printf("Monkey %d inspected items %d times\n", m, monkeys[m].NumInspectedItems)   
            }
            fmt.Println("-----")
        }
    }

    sort.SliceStable(monkeys[:], func (i, j int) bool {
        return monkeys[i].NumInspectedItems > monkeys[j].NumInspectedItems
    })

    fmt.Printf("Value is %d = %d * %d\n", monkeys[0].NumInspectedItems * monkeys[1].NumInspectedItems, monkeys[0].NumInspectedItems, monkeys[1].NumInspectedItems)
}
