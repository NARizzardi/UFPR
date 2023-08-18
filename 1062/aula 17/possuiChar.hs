module PossuiChar where

    contains :: String -> Char -> Bool

    contains [] ch = False
    contains (h:t) ch
        | h == ch = True
        | otherwise = contains t ch
        