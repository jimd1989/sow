module Models.Config (Config(..), config) where

import Prelude (Int, String)

data Config = Config
  { device ∷ String,
    sampleRate ∷ Int,
    channels ∷ Int
  }

config ∷ Config
config = Config "default" 48000 2 
