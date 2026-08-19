module Main (main) where

import Prelude (($), IO, putStrLn)
import Control.Monad.Except (runExceptT)
import Control.Monad.Reader (runReaderT)
import Data.Either(Either(..))
import Sndio (startAudio)
import Models.Config (Config(..), config)

main ∷ IO ()
main = do
  let appConfig = config
  result ← runExceptT $ runReaderT
           (startAudio $ device appConfig) appConfig
  case result of
    (Right _) → putStrLn "ok"
    (Left  ω) → putStrLn ω
