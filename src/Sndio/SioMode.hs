module Sndio.SioMode (SioMode(..), toCUInt) where

import Prelude (Show(..))
import Foreign.C.Types (CUInt(..))

data SioMode = SioPlay | SioRec | SioPlayRec

instance Show SioMode where
  show SioPlay    = "play"
  show SioRec     = "record"
  show SioPlayRec = "record and play"

toCUInt ∷ SioMode → CUInt
toCUInt SioPlay    = 1
toCUInt SioRec     = 2
toCUInt SioPlayRec = 3
