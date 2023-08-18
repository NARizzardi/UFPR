module Comprimento where
tam :: [Int] -> Int

tam [] = 0
tam (head:tail) = 1 + tam tail