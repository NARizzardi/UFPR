module NMultiplos where

    nmultiplos :: Int -> [Int]

    nmultiplos n = [n*x | x <- [1..10]]
    