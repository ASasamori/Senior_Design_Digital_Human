#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <unistd.h>
#include <cstdio>

// WAV header structure (same as your code)
struct WAVHeader {
    char riff[4];
    int32_t chunkSize;
    char wave[4];
    char fmt[4];
    int32_t subchunk1Size;
    int16_t audioFormat;
    int16_t numChannels;
    int32_t sampleRate;
    int32_t byteRate;
    int16_t blockAlign;
    int16_t bitsPerSample;
    char data[4];
    int32_t dataSize;
};

// Function to normalize audio
std::vector<double> normalizeAudio(const std::vector<double>& buffer) {
    if (buffer.empty()) {
        return buffer;
    }

    // Find the maximum absolute value in the buffer
    double max_abs = 0.0;
    for (const double& sample : buffer) {
        max_abs = std::max(max_abs, std::abs(sample));
    }

    // If audio is completely silent or already normalized, return original
    if (max_abs == 0.0 || max_abs == 1.0) {
        return buffer;
    }

    // Calculate normalization factor
    double normalize_factor = 1.0 / max_abs;

    // Apply normalization
    std::vector<double> normalized_buffer(buffer.size());
    for (size_t i = 0; i < buffer.size(); ++i) {
        normalized_buffer[i] = buffer[i] * normalize_factor;
    }

    return normalized_buffer;
}

// Function to process audio in real-time
void processAudioStream() {
    const size_t bufferSize = 1024;  // Adjust this based on expected buffer size
    std::vector<int16_t> raw_samples(bufferSize);  // Buffer to hold raw audio samples
    std::vector<double> normalized_samples(bufferSize);  // Buffer for normalized audio

    while (true) {
        // Read raw audio from stdin (which is piped from pw-record)
        ssize_t bytesRead = read(STDIN_FILENO, raw_samples.data(), raw_samples.size() * sizeof(int16_t));

        if (bytesRead <= 0) {
            std::cerr << "Error reading audio stream or end of stream reached\n";
            break;
        }

        // Convert raw samples (int16_t) to double (normalized between -1 and 1)
        std::vector<double> audio_buffer(raw_samples.size());
        for (size_t i = 0; i < raw_samples.size(); ++i) {
            audio_buffer[i] = raw_samples[i] / 32768.0;  // Convert to double in range [-1.0, 1.0]
        }

        // Apply normalization
        normalized_samples = normalizeAudio(audio_buffer);

        // Process the normalized audio (you can replace this with your actual processing logic)
        // For now, let's just output the peak value for each processed chunk
        double peak_amplitude = 0.0;
        for (const double& sample : normalized_samples) {
            peak_amplitude = std::max(peak_amplitude, std::abs(sample));
        }

        std::cout << "Normalized peak amplitude: " << peak_amplitude << "\n";

        // You can replace the above line with your actual logic to process or store the normalized audio
    }
}

int main() {
    std::cout << "Starting audio processing...\n";

    // Process the audio stream in real-time
    processAudioStream();

    return 0;
}

