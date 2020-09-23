# Audio Application Portfolio
## A selection of C++ Audio Applications, using Maximilian and OpenFrameworks

# 3-D Waveform Visualiser

![3-D Waveform ](/images/img_waveform)

This project is a prototype of a 3-D waveform visualiser, made in openFrameworks.
It takes data from a given audio file and pushes it into a 2-D vector in segments relative to the audio buffer size, where the outer vectors holds the segments, and the inner vectors contain the amplitude values.
The RMS of each block are calculated manually, and used to determine the height of the 3-D blocks that constitute the visual waveform. The static waveform of the whole audio file is drawn on setup, using a vector of pointers to a Block class.
Playing the audio file colours the waveform accordingly, so that the current play point is tracked. This was achieved by updating a counter each cycle of the audio loop, and using that number to update the blocks that are coloured.

