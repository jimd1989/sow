module Ffi (ffiAdd) where

import Prelude (Int, fromIntegral)
import Data.Function (on)
import Foreign.C.Types (CInt(..))

foreign import ccall "c_example" c_example ∷ CInt → CInt → CInt

ffiAdd ∷ Int → Int → CInt
ffiAdd = on c_example fromIntegral
