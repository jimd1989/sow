module Main (main) where

import Prelude (($), IO, putStrLn, show)
import Control.Monad.Except (runExceptT)
import Control.Monad.Reader (runReaderT)
import Data.Either(Either(..))
import Models.Config (Config(..), config)
import Models.Sndio (startAudio)

main ∷ IO ()
main = do
  let appConfig = config
  result ← runExceptT $ runReaderT
           (startAudio $ appConfig) appConfig
  case result of
    (Right α) → putStrLn $ show α
    (Left  ω) → putStrLn ω
