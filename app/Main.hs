module Main (main) where

import Prelude (($), IO, putStrLn)
import Control.Monad.Except (runExceptT)
import Control.Monad.Reader (runReaderT)
import Data.Either(Either(..))
import Ffi (startAudio)
import Models.Config (config)

main ∷ IO ()
main = do
  let appConfig = config
  result        ← runExceptT $ runReaderT (startAudio 16) appConfig
  case result of
    (Right _) → putStrLn "ok"
    (Left  ω) → putStrLn ω
