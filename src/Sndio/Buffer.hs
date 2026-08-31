module Sndio.Buffer (SioBuffer, sioBuffer, sioWrite) where

import Prelude (($), (*), Int, IO, fromIntegral)
import Data.Vector.Storable.Mutable (IOVector, length, replicate, unsafeWith)
import Data.Word (Word8)
import Foreign.Ptr (Ptr)
import Helpers ((⊙))
import Sndio.Ffi (sio_write)
import Sndio.SioHdl (SioHdl)
import Sndio.SioPar (SioPar(..))

newtype SioBuffer = SioBuffer { getSioBuffer ∷ IOVector Word8 }

sioBuffer ∷ SioPar → IO SioBuffer
sioBuffer ω = SioBuffer ⊙ replicate α 0
  where α = fromIntegral $ (bps ω) * (pchan ω) * (appbufsz ω) 

-- eventually have some kind of float input here, mixdown, etc
sioWrite ∷ Ptr SioHdl → SioBuffer → IO Int
sioWrite hdl ω = fromIntegral ⊙ (unsafeWith buf $ \ptr → sio_write hdl ptr len)
  where buf = getSioBuffer ω
        len = fromIntegral $ length buf
