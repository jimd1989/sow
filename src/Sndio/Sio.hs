module Sndio.Sio (Sio(..), sio) where

import Prelude (($), (==), (++), IO, Show, pure)
import Control.Monad (when)
import Control.Monad.IO.Class (MonadIO, liftIO)
import Control.Monad.Except (MonadError)
import Data.String (String)
import Foreign.C.String (withCString)
import Foreign.C.Types (CInt)
import Foreign.Marshal.Alloc (alloca)
import Foreign.Ptr (Ptr, nullPtr)
import Foreign.Storable (Storable(..)) 
import System.IO.Error (ioError, userError)
import Models.Config (Config(..))
import Sndio.Ffi (sio_open, sio_initpar, sio_setpar, sio_getpar, sio_start) 
import Sndio.SioHdl (SioHdl)
import Sndio.SioMode (SioMode(..), toCUInt)
import Sndio.SioPar (SioPar(..), sioPar)

-- Sio represents a running sndio audio handle
data Sio = Sio {
  params ∷ SioPar,
  handle ∷ Ptr SioHdl
} deriving (Show)

notNull ∷ Ptr a → String → IO ()
notNull ω err = when (ω == nullPtr) $ ioError (userError err)

notZero ∷ CInt → String → IO ()
notZero n err = when (n == 0) $ ioError (userError err)

sioOpen ∷ MonadIO m ⇒ String → SioMode → m (Ptr SioHdl)
sioOpen device mode = do
  let n  = toCUInt mode
  sioHdl ← liftIO $ withCString device $ \ω → sio_open ω n 1
  liftIO $ notNull sioHdl $ "error opening sndio " ++ device
  pure sioHdl

sioSetPar ∷ MonadIO m ⇒ Ptr SioHdl → m Sio
sioSetPar hdl = liftIO $ alloca $ \parPtr → do
  sio_initpar parPtr
  poke parPtr sioPar
  ok1 ← sio_setpar hdl parPtr
  notZero ok1 "could not set sndio parameters"
  ok2 ← sio_getpar hdl parPtr
  notZero ok2 "could not get sndio parameters"
  par ← peek parPtr
  pure $ Sio par hdl

sioStart ∷ MonadIO m ⇒ Ptr SioHdl → m ()
sioStart hdl = liftIO $ do
  ok ← sio_start hdl
  notZero ok "could not start sndio playback"

sio ∷ (MonadIO m, MonadError String m) ⇒ Config → m Sio
sio ω = do
  ptr ← sioOpen (device ω) SioPlay
  hdl ← sioSetPar ptr
  sioStart ptr
  pure hdl
