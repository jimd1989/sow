module Sndio.Ffi (sio_open, sio_initpar, sio_setpar, sio_getpar, sio_start,
                  sio_stop, sio_write) where

import Prelude (IO)
import Data.Word (Word8)
import Foreign.C.String (CString)
import Foreign.C.Types (CBool(..), CInt(..), CUInt(..), CSize(..))
import Foreign.Ptr (Ptr)
import Sndio.SioHdl (SioHdl)
import Sndio.SioPar (SioPar)

foreign import ccall safe "sio_open" sio_open
  ∷ CString → CUInt → CBool → IO (Ptr SioHdl)

foreign import ccall "sio_initpar" sio_initpar ∷ Ptr SioPar → IO ()

foreign import ccall safe "sio_setpar" sio_setpar 
  ∷ Ptr SioHdl → Ptr SioPar → IO CInt

foreign import ccall safe "sio_getpar" sio_getpar 
  ∷ Ptr SioHdl → Ptr SioPar → IO CInt

foreign import ccall safe "sio_start" sio_start ∷ Ptr SioHdl → IO CInt

foreign import ccall safe "sio_stop" sio_stop ∷ Ptr SioHdl → IO CInt

foreign import ccall safe "sio_write" sio_write 
  ∷ Ptr SioHdl → Ptr Word8 → CSize → IO CInt
