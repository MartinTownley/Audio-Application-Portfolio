# Audio Application Portfolio
## A selection of C++ Audio Applications, using Maximilian and OpenFrameworks

### 3-D Waveform Visualiser

![3-D Waveform ](/images/gif_waveform.gif)

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

[Link to audio demo on SoundCloud](https://soundcloud.com/folliclegrid/fm-soundscape-aap-portfolio)


### Karplus-Strong Study

![Karplus-Strong Study ](/images/img_karplus-strong.png)

A simple interactive implementation of the Karplus-Strong theorem. The model can be excited by clicking the mouse – the delay time decreases as the mouse-position goes left to right, increasing the perceived pitch of the sound.
A filter is used to take some of the high end out of the initial noise burst. The frequency cutoff of the filter is scaled to a curve, to give more resolution in the low-end.

[Click here for video demo on Vimeo](https://vimeo.com/460925013)

### The Break-Breaker (Drum Sample Chopper with Effects)

![Break-Breaker ](/images/img_break-breaker.png)

This project demonstrates sample playback techniques and doppler-effect pitch shifting using Maximilian methods. It manipulates drum breaks by dividing the samples into an appropriate amount of start points, and triggering those start points in random sequences (the chopper() and sampleParamsUpadate() functions contain the code for this process). It contains 5 break samples to choose between (and one vocal), or you can edit the code to load your own.
The audio is passed through a “Zinger” effect, which is engaged by holding Q or W. It is essentially a very tight delay line in which a slow phasor is applied to the time of the delay, creating pitch “climbs” and “dives”.
The sample playback speed and delay feedback can be controlled using the GUI.
Each drum break included in the data folder has its own amount of divisions, which is set when the sample is selected.

[Click here for video demo on Vimeo](https://vimeo.com/460927516)


