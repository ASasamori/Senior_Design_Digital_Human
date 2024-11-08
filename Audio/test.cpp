#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

// WAV header structure
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

std::vector<double> adjustGain(const std::vector<double>& buffer, double gain_factor) {
    if (buffer.empty() || gain_factor <= 0.0) {
        return buffer;
    }

    std::vector<double> adjusted_buffer(buffer.size());
    for (size_t i = 0; i < buffer.size(); ++i) {
        // Apply gain and clip to prevent overflow
        adjusted_buffer[i] = std::max(-1.0, std::min(1.0, buffer[i] * gain_factor));
    }

    return adjusted_buffer;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <input_wav> <output_wav> <gain_factor>\n";
        return 1;
    }

    std::string input_file = argv[1];
    std::string output_file = argv[2];
    double gain_factor = std::stod(argv[3]);

    // Open input file
    std::ifstream inFile(input_file, std::ios::binary);
    if (!inFile) {
        std::cerr << "Cannot open input file: " << input_file << "\n";
        return 1;
    }

    // Read WAV header
    WAVHeader header;
    inFile.read(reinterpret_cast<char*>(&header), sizeof(WAVHeader));

    // Verify that it's a valid WAV file
    if (strncmp(header.riff, "RIFF", 4) != 0 || strncmp(header.wave, "WAVE", 4) != 0) {
        std::cerr << "Invalid WAV file\n";
        return 1;
    }

    // Read audio data
    std::vector<int16_t> raw_samples((header.dataSize) / sizeof(int16_t));
    inFile.read(reinterpret_cast<char*>(raw_samples.data()), header.dataSize);
    inFile.close();

    // Convert to doubles (normalized between -1 and 1)
    std::vector<double> samples(raw_samples.size());
    for (size_t i = 0; i < raw_samples.size(); ++i) {
        samples[i] = raw_samples[i] / 32768.0;
    }

    // Apply gain adjustment
    auto adjusted_samples = adjustGain(samples, gain_factor);

    // Convert back to int16_t
    for (size_t i = 0; i < adjusted_samples.size(); ++i) {
        raw_samples[i] = static_cast<int16_t>(adjusted_samples[i] * 32768.0);
    }

    // Write output file
    std::ofstream outFile(output_file, std::ios::binary);
    if (!outFile) {
        std::cerr << "Cannot open output file: " << output_file << "\n";
        return 1;
    }

    outFile.write(reinterpret_cast<char*>(&header), sizeof(WAVHeader));
    outFile.write(reinterpret_cast<char*>(raw_samples.data()), header.dataSize);
    outFile.close();

    std::cout << "Successfully processed audio file with gain factor: " << gain_factor << "\n";
    return 0;
}