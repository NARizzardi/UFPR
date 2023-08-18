module Potencia where
    potencia :: Int -> Int -> Int

    potencia x 0 = 1
    potencia x n = x * potencia x (n-1)