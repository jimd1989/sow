module Sndio.SioPar (SioPar(..), sioPar) where

import Prelude (($), Eq(..), Show(..), pure)
import Foreign.C.Types (CUInt(..))
import Foreign.Storable (Storable(..), peekByteOff, pokeByteOff)

data SioPar = SioPar {
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

instance Storable SioPar where
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
    pure $ SioPar bits bps sig le msb rchan pchan 
                   rate appbufsz bufsz round xrun
  poke ω (SioPar bits bps sig le msb rchan pchan
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

sioPar ∷ SioPar
sioPar = SioPar 16 2 1 1 0 2 2 48000 1 1 1 0 
