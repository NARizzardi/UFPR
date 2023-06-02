module Triangulo where
    ehTriangulo :: Int -> Int -> Int -> Bool

    ehTriangulo a b c = 
        if (somaAB > c && somaAC > b && somaBC > a)
            then True
            else False
        where
            somaAB = a + b
            somaAC = a + c
            somaBC = b + c

