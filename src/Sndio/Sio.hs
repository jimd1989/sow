module Sndio.Sio (Sio(..), sio) where

import Prelude (($), (==), (++), IO, Show(..), pure, putStrLn)
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
import Helpers (try')
import Models.Config (Config(..))
import Sndio.Ffi (sio_open, sio_initpar, sio_setpar, sio_getpar, sio_start, 
                  sio_stop) 
import Sndio.SioHdl (SioHdl)
import Sndio.SioMode (SioMode(..), toCUInt)
import Sndio.SioPar (SioPar(..), sioPar)

-- Sio represents a running sndio audio handle
data Sio m = Sio {
  name   ∷ String,
  mode   ∷ SioMode,
  params ∷ SioPar,
  handle ∷ Ptr SioHdl,
  stop   ∷ m ()
}

instance Show (Sio m) where
  show ω = "{" ++
           "name = "   ++ (show $ name ω)   ++ ", " ++
           "mode = "   ++ (show $ mode ω)   ++ ", " ++
           "params = " ++ (show $ params ω) ++ ", " ++ 
           "handle = " ++ (show $ handle ω) ++ 
           "}"

notNull ∷ Ptr a → String → IO ()
notNull ω err = when (ω == nullPtr) $ ioError (userError err)

notZero ∷ CInt → String → IO ()
notZero n err = when (n == 0) $ ioError (userError err)

sioOpen ∷ String → SioMode → IO (Ptr SioHdl)
sioOpen device mode = do
  let n  = toCUInt mode
  sioHdl ← liftIO $ withCString device $ \ω → sio_open ω n 1
  liftIO $ notNull sioHdl $ "error opening sndio " ++ device
  pure sioHdl

sioSetPar ∷ Ptr SioHdl → IO SioPar
sioSetPar hdl = alloca $ \parPtr → do
  sio_initpar parPtr
  poke parPtr sioPar
  ok1 ← sio_setpar hdl parPtr
  notZero ok1 "could not set sndio parameters"
  ok2 ← sio_getpar hdl parPtr
  notZero ok2 "could not get sndio parameters"
  peek parPtr

sioStart ∷ Ptr SioHdl → IO ()
sioStart hdl = do
  ok ← sio_start hdl
  notZero ok "could not start sndio playback"

sioStop ∷ Ptr SioHdl → String → IO ()
sioStop hdl deviceName = do
  ok ← sio_stop hdl
  notZero ok "could not stop sndio playback"
  putStrLn $ ("sndio " ++ deviceName ++ " stopped")

sio ∷ (MonadIO m, MonadError String m) ⇒ Config → m (Sio m)
sio ω = do
  let deviceName = device ω
  let sioMode    = SioPlay
  hdl ← try' $ sioOpen deviceName sioMode
  par ← try' $ sioSetPar hdl
  try'   $ sioStart hdl
  liftIO $ putStrLn ("sndio " ++ deviceName ++ " playing")
  pure $ Sio deviceName sioMode par hdl (try' $ sioStop hdl deviceName)
