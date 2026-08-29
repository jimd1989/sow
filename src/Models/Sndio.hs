module Models.Sndio (SioHdl(..), startAudio) where

import Prelude ((.), ($), (==), (++), Eq, IO, Show, fromIntegral, pure)
import Control.Monad (when)
import Control.Monad.IO.Class (MonadIO, liftIO)
import Control.Monad.Except (MonadError, throwError)
import Data.Bits (shift)
import Data.Int (Int)
import Data.String (String)
import Foreign.C.String (CString, withCString)
import Foreign.C.Types (CBool(..), CInt(..), CUInt(..))
import Foreign.Marshal.Alloc (alloca)
import Foreign.Ptr (Ptr, nullPtr)
import Foreign.Storable (Storable(..), peekByteOff, pokeByteOff)
import System.IO.Error (ioError, userError)
import Models.Config (Config(..))

foreign import ccall "sio_open" sio_open
  ∷ CString → CUInt → CBool → IO (Ptr CSioHdl)

foreign import ccall "sio_initpar" sio_initpar ∷ (Ptr CSioPar) → IO ()

foreign import ccall "sio_setpar" sio_setpar 
  ∷ (Ptr CSioHdl) → (Ptr CSioPar) → IO CInt

foreign import ccall "sio_getpar" sio_getpar 
  ∷ (Ptr CSioHdl) → (Ptr CSioPar) → IO CInt

foreign import ccall "sio_start" sio_start ∷ (Ptr CSioHdl) → IO CInt

data CSioHdl

data SioMode = SioPlay | SioRec | SioPlayRec

cSioMode ∷ SioMode → CUInt
cSioMode SioPlay    = 1
cSioMode SioRec     = 2
cSioMode SioPlayRec = 3

sioOpen ∷ (MonadIO m, MonadError String m) ⇒ String → SioMode → m (Ptr CSioHdl)
sioOpen device mode = do
  let n = cSioMode mode
  sio   ← liftIO $ withCString device $ \ω → sio_open ω n 1
  when (sio == nullPtr) $ throwError $ "error opening sndio " ++ device
  pure sio

data CSioPar = CSioPar {
  bits     ∷ CUInt,      
  bps      ∷ CUInt,       
  sig      ∷ CUInt,       
  le       ∷ CUInt,        
  msb      ∷ CUInt,       
  rchan    ∷ CUInt,     
  pchan    ∷ CUInt,     
  rate     ∷ CUInt,      
  appbufsz ∷ CUInt,  
  bufsz    ∷ CUInt,     
  round    ∷ CUInt,     
  xrun     ∷ CUInt
} deriving (Show, Eq)

instance Storable CSioPar where
  sizeOf    _   = 48
  alignment _   = 8 -- not portable
  peek ω        = do
    bits     ← peekByteOff ω 0 
    bps      ← peekByteOff ω 4
    sig      ← peekByteOff ω 8       
    le       ← peekByteOff ω 12        
    msb      ← peekByteOff ω 16       
    rchan    ← peekByteOff ω 20     
    pchan    ← peekByteOff ω 24    
    rate     ← peekByteOff ω 28      
    appbufsz ← peekByteOff ω 32  
    bufsz    ← peekByteOff ω 36     
    round    ← peekByteOff ω 40     
    xrun     ← peekByteOff ω 44
    pure $ CSioPar bits bps sig le msb rchan pchan 
                   rate appbufsz bufsz round xrun
  poke ω (CSioPar bits bps sig le msb rchan pchan
          rate appbufsz bufsz round xrun) = do
    pokeByteOff ω 0  bits
    pokeByteOff ω 4  bps
    pokeByteOff ω 8  sig
    pokeByteOff ω 12 le
    pokeByteOff ω 16 msb
    pokeByteOff ω 20 rchan
    pokeByteOff ω 24 pchan
    pokeByteOff ω 28 rate
    pokeByteOff ω 32 appbufsz
    pokeByteOff ω 36 bufsz
    pokeByteOff ω 40 round
    pokeByteOff ω 44 xrun

fillSioPar ∷ Config → Ptr CSioPar → IO ()
fillSioPar ω par = do
  α      ← peek par
  let αα = α { bits     = fromIntegral $ bitDepth ω, 
               rate     = fromIntegral $ sampleRateHz ω,
               pchan    = fromIntegral $ playChannels ω,
               rchan    = fromIntegral $ recChannels ω,
               appbufsz = 1 }
  poke par αα

data SioHdl = SioHdl {
  bytes      ∷ Int,
  recChan    ∷ Int,
  playChan   ∷ Int,
  sampleRate ∷ Int,
  bufferSize ∷ Int,
  handle     ∷ Ptr CSioHdl
} deriving (Show, Eq)

sioHdl ∷ CSioPar → Ptr CSioHdl → SioHdl
sioHdl ω ptr = SioHdl b (f rchan ω) (f pchan ω) (f rate ω) (f appbufsz ω) ptr
  where b   = fromIntegral $ shift (bits ω) (-3)
        f g = fromIntegral . g

ensureNotZero ∷ CInt → String → IO ()
ensureNotZero n err = when (n == 0) $ ioError (userError err)

sioSetPar ∷ MonadIO m ⇒ Config → Ptr CSioHdl → m SioHdl
sioSetPar ω sio = liftIO $ alloca $ \par → do
  sio_initpar par
  fillSioPar ω par
  respCode ← sio_setpar sio par
  ensureNotZero respCode "could not set sndio parameters"
  getCode ← sio_getpar sio par
  ensureNotZero getCode "could not get sndio parameters"
  reified ← peek par
  pure $ sioHdl reified sio

sioStart ∷ MonadIO m ⇒ Ptr CSioHdl → m ()
sioStart ptr = liftIO $ do
  respCode ← sio_start ptr
  ensureNotZero respCode "could not start sndio playback"

startAudio ∷ (MonadIO m, MonadError String m) ⇒ Config → m SioHdl
startAudio ω = do
  ptr ← sioOpen (device ω) SioPlay
  hdl ← sioSetPar ω ptr
  sioStart ptr
  -- should make an audio buffer
  pure hdl
