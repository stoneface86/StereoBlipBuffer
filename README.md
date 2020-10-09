# StereoBlipBuffer
A couple modifications to blargg's Blip_Buffer library for stereo buffers

Synthesizing stereo sound using the original library requires two Blip_Buffer and
two Blip_Synth objects, one for each terminal. With this modication you only need one
of each, as Blip_Buffer now contains a sample buffer with interleaved samples.
Ie, instead of:

```cpp
Blip_Buffer left;
Blip_Buffer right;
Blip_Synth<blip_good_quality,20> left_synth;
Blip_Synth<blip_good_quality,20> right_synth;
```

You can just do:

```cpp
Blip_buffer buf;
Blip_Synth<blip_good_quality,20> synth;
```

This makes emulating audio from systems with stereo output much easier, and
also reduces memory usage compared to the original library.

## Usage

Use the library the same as you would before, except you can now pass a terminal argument
to Blip_Synth::update to specify the left or right terminal

```cpp
synth.update(time, 100, blip_term_left); // updates amplitude for the left terminal at time = 100
synth.update(time, 100, blip_term_right); // updates amplitude for the right terminal at time = 100
// ...
```

You can now read samples directly into a stereo buffer. Instead of this:

```cpp
Blip_Buffer left, right;

// synth update ...

auto samples = new blip_sample_t[count * 2];
left.read_samples(samples, count, 1);
right.read_samples(samples + 1, count, 1);
```

Do this:

```cpp
Blip_Buffer buf;

// synth update ...

auto samples = new blip_sample_t[count * 2];
buf.read_samples(samples, count);
```

## Changes

Here is a list of changes I made to the original library:
 * All code is put into the blargg namespace
 * `Blip_Buffer::buffer_` is now a stereo buffer (twice the size of `buffer_size_`)
 * `Blip_Synth::offset_resampled` writes samples in interleaved format
 * `Blip_Buffer::read_samples` writes samples to a stereo buffer
 * `Blip_Buffer::read_samples` no longer takes a stereo argument
 * `Blip_Synth_::last_amp` member replaced with `last_amp_left` and `last_amp_right` members
 * Blip_Synth update and offset methods now take a terminal argument (0 for left, 1 for right),
   default is left.
 * add `blip_term_t` typedef for specifying the terminal

# Credits

The original Blip_Buffer library was written by Shay Green (blargg). You can
acquire it here https://www.slack.net/~ant/libs/audio.html#Blip_Buffer