# Capture git directory 
START_DIR=$(dirname "$(pwd)")
# echo "Starting in: $START_DIR"
YOBE_SDK="$HOME/YobeSDK-Release-GrandE-0.6.2-Linux"
echo "This path is $YOBE_SDK "

# Retrieve time stamp (MM_DD_HH_MM)
TIMESTAMP=$(date +"%m_%d_%H_%M")
RAW_OUTPUT="${TIMESTAMP}_output"

# This creates a .wav file in the specified location
cd  ~/YobeSDK-Release-GrandE-0.6.2-Linux/samples
arecord -D plughw:2,0 -f S16_LE -r 16000 -c 2 -t wav -d 20 "$YOBE_SDK/samples/audio_files/IDListener/${RAW_OUTPUT}.wav"
echo "A record has finished"
g++ -o "$START_DIR/Audio/normalize_raw" "$START_DIR/Audio/normalize_wav.cpp" -std=c++11

# echo "g++ has finished"

# Normalizes raw Audio
# Command follows the convention of: Executable, input, output
"$START_DIR/Audio/normalize_raw" "$YOBE_SDK/samples/audio_files/IDListener/${RAW_OUTPUT}.wav" "$YOBE_SDK/samples/audio_files/IDListener/normalize_${TIMESTAMP}.wav"


# build ... broadside/endfire
cmake --build "$YOBE_SDK/samples/build" # New pi or if changing the C++ file

# Build file and have to run from the samples directory
# ./build/IDListener_demo ./audio_files/IDListener/[file_location].wav broadside target-speaker "student-pc" ./build
# Output file will be in the same location, but have _processed.wav extension
./build/IDListener_demo "$YOBE_SDK/samples/audio_files/IDListener/normalize_${TIMESTAMP}.wav" broadside target-speaker "student-pc" ./build
echo "Is this working?"


# TODO: ADD ELIF TO CHECK IF RUNNING BROADSIDE/ENDFIRE
# mv old_filename new_filename
mv "$YOBE_SDK/samples/audio_files/IDListener/normalize_${TIMESTAMP}_broadside_processed.wav" "$YOBE_SDK/samples/audio_files/IDListener/${TIMESTAMP}_processed.wav"
# Hardcoded Broadside for now
"$START_DIR/Audio/normalize_raw" "$YOBE_SDK/samples/audio_files/IDListener/${TIMESTAMP}_processed.wav" "$YOBE_SDK/samples/audio_files/IDListener/normalize_${TIMESTAMP}_broadside_processed.wav"

rm "$START_DIR/Audio/normalize_raw"