# StereoBlipBuffer
modification to blargg's blip buffer for stereo buffers

Synthesizing stereo sound using the original library requires two Blip_Buffer and
two Blip_Synth objects, one for each terminal. With this modication you only need one
of each, as Blip_Buffer now contains an sample buffer with interleaved samples.


## Changes

Here is a list of changes I made to the original library:
 * All code is put into the blargg namespace
 * Blip_Buffer::buffer_ is now a stereo buffer (twice the size of buffer_size_)
 * Blip_Synth::offset_resampled writes samples in interleaved format
 * Blip_Buffer::read_samples writes samples to a stereo buffer
 * Blip_Buffer::read_samples no longer takes a stereo argument

