module ListaCubo where
    cubo :: Int -> Int
    listaCubo :: [Int] -> [Int]

    cubo x = x * x * x
    listaCubo [] = []
    listaCubo(h:t) = cubo h : listaCubo t
