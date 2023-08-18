module EhPar where

    ehPar :: Int -> Bool

    ehPar a
        | mod a 2 == 0 = True
        | otherwise = False