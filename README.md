# StereoBlipBuffer
modification to blargg's blip buffer for stereo buffers

Synthesizing stereo sound using the original library requires two Blip_Buffer and
two Blip_Synth objects, one for each terminal. With this modication you only need one
of each, as Blip_Buffer now contains an sample buffer with interleaved samples.


## Changes

Here is a list of changes I made to the original library:
 * All code is put into the blargg namespace
