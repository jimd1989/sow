module Models.Config (Config(..), config) where

import Prelude (Int, String)

data Config = Config
  { device       ∷ String,
    bitDepth     ∷ Int,
    sampleRateHz ∷ Int,
    playChannels ∷ Int,
    recChannels  ∷ Int
  }

config ∷ Config
config = Config "default" 16 48000 2 2
