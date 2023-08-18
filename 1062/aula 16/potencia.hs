module Potencia where
    potencia :: Int -> Int -> Int

    potencia x n
        | x <= 0 = 0
        | n < 0 = 0
        | n == 0 = 1
        | n > 0 = x * potencia x (n - 1)