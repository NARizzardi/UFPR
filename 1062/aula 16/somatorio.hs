module Somatorio where
    somatorio :: Int -> Int

    somatorio 0 = 0
    somatorio y = y + somatorio (y-1)