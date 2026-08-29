module Sndio.SioMode (SioMode(..), toCUInt) where

import Foreign.C.Types (CUInt(..))

data SioMode = SioPlay | SioRec | SioPlayRec

toCUInt ∷ SioMode → CUInt
toCUInt SioPlay    = 1
toCUInt SioRec     = 2
toCUInt SioPlayRec = 3
