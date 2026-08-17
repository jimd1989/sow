module Main (main) where

import Prelude (($), IO, putStrLn, show)
import Ffi (ffiAdd)

main ∷ IO ()
main = putStrLn $ show $ ffiAdd 1 2
