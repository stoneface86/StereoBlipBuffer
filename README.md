# StereoBlipBuffer
modification to blargg's blip buffer for stereo buffers

Synthesizing stereo sound using the original library requires two Blip_Buffer and
two Blip_Synth objects, one for each terminal. With this modication you only need one
of each, as Blip_Buffer now contains an sample buffer with interleaved samples.


## Usage

Use the library the same as you would before, except you can now pass a terminal argument
to Blip_Synth::update to specify the left or right terminal

```cpp
synth.update(time, 100, blip_term_left);
synth.update(time, 100, blip_term_right);
// ...
```

You can now read samples directly into a stereo buffer. Instead of this:

```cpp
Blip_Buffer left, right;

// synth update ...

auto samples = new blip_sample_t[count];
left.read_samples(samples, count, 1);
right.read_samples(samples + 1, count, 1);
```

Do this:

```cpp
Blip_Buffer buf;

// synth update ...

auto samples = new blip_sample_t[count];
buf.read_samples(samples, count);
```

## Changes

Here is a list of changes I made to the original library:
 * All code is put into the blargg namespace
 * Blip_Buffer::buffer_ is now a stereo buffer (twice the size of buffer_size_)
 * Blip_Synth::offset_resampled writes samples in interleaved format
 * Blip_Buffer::read_samples writes samples to a stereo buffer
 * Blip_Buffer::read_samples no longer takes a stereo argument
 * Blip_Synth_::last_amp member replaced with last_amp_left and last_amp_right members
 * Blip_Synth update and offset methods now take a terminal argument (0 for left, 1 for right),
   default is left.
 * add blip_term_t typedef for specifying the terminal
