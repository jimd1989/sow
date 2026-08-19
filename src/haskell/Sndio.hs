module Sndio (startAudio) where

import Prelude (($), (==), IO, pure)
import Control.Monad.IO.Class (MonadIO, liftIO)
import Control.Monad.Except (MonadError, throwError)
import Control.Monad.Reader (MonadReader, asks)
import Data.Bool (Bool(..))
import Data.String (String)
import Foreign.Ptr (Ptr, nullPtr)
import Foreign.C.String (CString, withCString)
--import Foreign.C.Types (CString(..), Ptr(..))
import Models.Config (Config)

data SioHdl

foreign import ccall "start_audio" start_audio ∷ CString → IO (Ptr SioHdl)

startAudio ∷ (MonadError String m, MonadIO m, MonadReader Config m) ⇒ 
  String → m (Ptr SioHdl)
startAudio device = do
  sioHdl ← liftIO $ withCString device start_audio
  case (sioHdl == nullPtr) of
    True  → throwError "error opening sndio"
    False → pure sioHdl
