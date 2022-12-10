getXValue :: String -> [Int] 
getXValue s = do
    let wordsInLine = words s
    if wordsInLine!!0 == "noop"
        then [0]
        else [0, read (wordsInLine!!1) :: Int]

sumXValues :: [Int] -> Int -> [Int]
sumXValues acc n = do
    if acc == []
    then [1]
    else (n + (head acc)) : acc

reverseOrder = foldl (flip (:)) []

mapInd :: (a -> Int -> b) -> [a] -> [b]
mapInd f l = zipWith f l [0..]

drawPixel :: Int -> Int -> Char
drawPixel n idx = do
    let col = idx `rem` 40
    if (col >= (n - 1)) && (col <= (n + 1))
    then '#'
    else '.'

splitIntoChunksOfLength :: Int -> String -> [String]
splitIntoChunksOfLength n [] = []
splitIntoChunksOfLength n xs = take n xs : splitIntoChunksOfLength n (drop n xs)

main :: IO ()
main = do
    fileContent <- readFile("input.txt")
    let fileLines = lines fileContent
    let xValues = map getXValue fileLines
    let flatXValues = concat xValues
    let values = 1:(reverseOrder (foldl sumXValues [] flatXValues))
    let pixels = mapInd drawPixel values
    let rows = splitIntoChunksOfLength 40 pixels
    mapM_ print rows
