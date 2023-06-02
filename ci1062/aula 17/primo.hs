module Primo where
    import Comprimento
    
    ehPrimo :: Int -> Bool

    ehPrimo n
        | tam [x | x <- [1..n], mod n x == 0] == 2 = True
        | otherwise = False

