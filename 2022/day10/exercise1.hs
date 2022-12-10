getXValue :: String -> [Int] 
getXValue s = do
    let wordsInLine = words s
    if wordsInLine!!0 == "noop"
        then [0]
        else [0, read (wordsInLine!!1) :: Int]

sumXValues :: [Int] -> Int -> [Int]
sumXValues acc n = do
    if acc == []
    then [1, 1]
    else (n + (head acc)) : acc

reverseOrder = foldl (flip (:)) []

signalStrength :: [Int] -> Int -> Int
signalStrength values cycle = do
    cycle * values!!(cycle - 1)

main :: IO ()
main = do
    fileContent <- readFile("input.txt")
    let fileLines = lines fileContent
    let xValues = map getXValue fileLines
    let flatXValues = concat xValues
    let values = reverseOrder (foldl sumXValues [] flatXValues)
    let sum = (signalStrength values 20) + (signalStrength values 60) + (signalStrength values 100) + (signalStrength values 140) + (signalStrength values 180) + (signalStrength values 220)
    print sum
