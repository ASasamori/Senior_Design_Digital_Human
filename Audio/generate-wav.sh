# This creates a .wav file in the specified location
# TODO: Change the name of the file to be dynamic everytime captured
cd  ~/YobeSDK-Release-GrandE-0.6.2-Linux/samples
arecord -D plughw:2,0 -f S16_LE -r 16000 -c 2 -t wav -d 10 ~/YobeSDK-Release-GrandE-0.6.2-Linux/samples/audio_files/IDListener/raw_output.wav

# We run on the pi 

# .wav file; API function to normalize .wav; 

# build ... broadside/endfire
cmake --build ~/YobeSDK-Release-GrandE-0.6.2-Linux/samples/build # New pi or if changing the C++ file

# Build file and have to run from the samples directory
# TODO: Change the file name to be dynamic
./build/IDListener_demo ./audio_files/IDListener/[file_location].wav broadside target-speaker "student-pc" ./build