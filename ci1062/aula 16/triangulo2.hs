module Triangulo where
    ehTriangulo :: Int -> Int -> Int -> Bool

    ehTriangulo a b c
        | somaAB > c && somaAC > b && somaBC > a = True
        | otherwise = False
          where 
            somaAB = a + b
            somaAC = a + c
            somaBC = b + c
