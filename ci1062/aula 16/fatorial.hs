module Fatorial where
    fatorial :: Int -> Int
    
    fatorial a 
        | a == 0 = 1
        | a > 0 = a * fatorial (a-1)