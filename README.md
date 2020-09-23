# Audio Application Portfolio
## A selection of C++ Audio Applications, using Maximilian and OpenFrameworks

### 3-D Waveform Visualiser

![3-D Waveform ](/images/img_waveform.png)

This project is a prototype of a 3-D waveform visualiser, made in openFrameworks.
It takes data from a given audio file and pushes it into a 2-D vector in segments relative to the audio buffer size, where the outer vectors holds the segments, and the inner vectors contain the amplitude values.
The RMS of each block are calculated manually, and used to determine the height of the 3-D blocks that constitute the visual waveform. The static waveform of the whole audio file is drawn on setup, using a vector of pointers to a Block class.
Playing the audio file colours the waveform accordingly, so that the current play point is tracked. This was achieved by updating a counter each cycle of the audio loop, and using that number to update the blocks that are coloured.

### Command Line FM Soundscape

![Command Line FM ](/images/img_commandLineFM2.png)


This is a soundscape piece demonstrating FM synthesis in C++, using the Maximilian library. It attempts to explore the rich depths of sounds achievable through FM synthesis, possible with a very limited amount of code.
It consists of very simple components:

- a carrier sine wave, and two modulators (a sine wave and a phasor)
- a counter/clock
- a low-pass filter (to curb some of the high frequency content)

A carrier wave (which in this case is a sine wave) is being modulated by another sine wave, whose frequency is determined by a harmonicity ratio of the carrier.
The amplitude of this first modulating wave is driven by a low-frequency phasor – this gives a a slow-paced tour through some of the sounds that can be achieved through FM synthesis.
The amplitude of this phasor is a fixed value.

