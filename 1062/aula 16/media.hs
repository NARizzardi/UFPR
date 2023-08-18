module Media where
    calculaMedia :: Double -> Double -> Double -> String

    calculaMedia p1 p2 p3
        | mediaFinal >= 7 = "Aprovado"
        | otherwise = "Reprovado"
          where 
            mediaFinal = (p1 + p2 + p3) / 3