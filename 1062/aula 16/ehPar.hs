module EhPar where

    ehPar :: Int -> Bool

    ehPar a = if mod a 2 == 0
        then True
        else False