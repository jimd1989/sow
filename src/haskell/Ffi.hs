module Ffi (startAudio) where

import Prelude (($), Int, IO, fromIntegral, pure)
import Control.Monad.IO.Class (MonadIO, liftIO)
import Control.Monad.Except (MonadError, throwError)
import Control.Monad.Reader (MonadReader, asks)
import Data.String (String)
import Foreign.C.Types (CInt(..))
import Models.Config (Config)

foreign import ccall "start_audio" start_audio ∷ CInt → IO CInt

startAudio ∷ (MonadError String m, MonadIO m, MonadReader Config m) ⇒ Int → m ()
startAudio handleN = do
  returnCode ← liftIO $ start_audio $ fromIntegral handleN
  case returnCode of
    (-1) → throwError "error opening sndio"
    _    → pure ()
