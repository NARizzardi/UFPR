module Diversos where
    reajusteSalario :: Float -> Float
    mediaPonderada :: Double -> Double -> Double -> Double -> Double -> Double -> Double
    converteT :: Float -> Float
    idade2032 :: Int -> Int
    tempoEmMin :: Int -> Int -> Int
    somaQuadrados :: Int -> Int -> Int -> Int
    calculaSalario :: Float -> Float
    
    reajusteSalario salarioBase = salarioBase + (salarioBase * 0.25)
    mediaPonderada notaA pesoA notaB pesoB notaC pesoC = ((notaA * pesoA) + (notaB * pesoB) + (notaC * pesoC)) / (pesoA + pesoB + pesoC)
    converteT tCelsius = tCelsius * (9 / 5) + 32
    idade2032 anoNasc = 2032 - anoNasc
    tempoEmMin horas minutos = (horas * 60) + minutos
    somaQuadrados x y z =  (x^2) + (y^2) + (z^2)
    calculaSalario salarioBase = salarioBase + (salarioBase * 0.05) - (salarioBase * 0.07)