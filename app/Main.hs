module Main (main) where

import Prelude (($), IO, String, putStrLn, show)
import Control.Monad.IO.Class (MonadIO)
import Control.Monad.Except (MonadError, runExceptT)
import Control.Monad.Reader (runReaderT)
import Data.Either(Either(..))
import Models.Config (Config, config)
import Sndio.Sio (Sio(..), sio)

startAndStop ∷ (MonadIO m, MonadError String m) ⇒ Config → m ()
startAndStop ω = do
  hdl ← sio ω
  stop hdl 

main ∷ IO ()
main = do
  let appConfig = config
  result ← runExceptT $ runReaderT
           (startAndStop $ appConfig) appConfig
  case result of
    (Right α) → putStrLn $ show α
    (Left  ω) → putStrLn ω
