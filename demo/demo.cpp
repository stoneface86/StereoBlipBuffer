
#include "Blip_Buffer.h"
#include "Wave_Writer.h"

#include <memory>

using namespace blargg;

constexpr long SAMPLERATE = 48000;

int main() {

    Blip_Buffer bbuf;
    // 48000 Hz sample rate with 1000 ms buffer (48000 samples)
    bbuf.set_sample_rate(SAMPLERATE, 1000);
    // clock rate = 4194304 Hz (Gameboy)
    bbuf.clock_rate(4194304);
    // Bass filter = 32 Hz
    bbuf.bass_freq(32);

    Blip_Synth<blip_best_quality, 60> synth;
    synth.output(&bbuf);
    // Treble filter -8 dB at 12000 Hz
    synth.treble_eq(blip_eq_t(-8.0, 12000, SAMPLERATE));
    synth.volume(0.5);


    blip_time_t time = 300;

    // 50% duty square wave
    for (int i = 500; --i; ) {
        synth.update(time, 7, blip_term_right);
        time += 1000;
        synth.update(time, 0, blip_term_right);
        time += 1000;
    }

    // 75% duty square wave
    time = 100;
    for (int i = 1000; --i;) {
        synth.update(time, 15, blip_term_left);
        time += 3000;
        synth.update(time, 0, blip_term_left);
        time += 1000;
    }

    


    bbuf.end_frame(time);

    auto sampleCount = bbuf.samples_avail();
    std::unique_ptr<short[]> samples(new short[sampleCount * 2]);
    bbuf.read_samples(samples.get(), sampleCount);

    Wave_Writer wav(SAMPLERATE);
    wav.stereo(1);
    wav.write(samples.get(), sampleCount);

    return 0;
}