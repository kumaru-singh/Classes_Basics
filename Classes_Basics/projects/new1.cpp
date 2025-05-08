// Project 9: Multi-Threaded File Compression (std::thread & std::promise)🔹 Concept: Use std::thread and std::promise to implement a multi-threaded file compression system.
// 🔹 Real-World Use Case: Compress large files using parallel threads, reducing execution time compared to sequential compression.
// 🔹 Why Multi-Threading?

// Speeds up compression by dividing a file into chunks and processing them in parallel.
// Demonstrates practical use of std::thread, std::promise, and std::future.
// Useful in file storage, cloud backups, and data transmission applications.


// 📌 Step 1: Install & Set Up zlib for Compression
// Since C++ does not have built-in compression functions, we use zlib for file compression.



// 📌 Step 2: Implement File Chunk Compression
// We divide a file into smaller chunks, compress them concurrently, and merge the results.

// 🖥️ Code: File Compression Function

#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <future>
#include <zlib.h> // Compression library

// Function to compress a chunk of data
std::vector<char> compressChunk(const std::vector<char>& data) {
    uLongf compressedSize = compressBound(data.size());
    std::vector<char> compressedData(compressedSize);

    if (compress(reinterpret_cast<Bytef*>(compressedData.data()), &compressedSize,
                 reinterpret_cast<const Bytef*>(data.data()), data.size()) != Z_OK) {
        throw std::runtime_error("Compression failed");
    }

    compressedData.resize(compressedSize);
    return compressedData;
}


// 📌 Step 3: Read File and Split into Chunks
// We split a large file into chunks and process them in separate threads.

// 🖥️ Code: Read File and Create Tasks

std::vector<std::vector<char>> readFileChunks(const std::string& filename, size_t chunkSize) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) throw std::runtime_error("Could not open file");

    std::vector<std::vector<char>> chunks;
    while (file) {
        std::vector<char> buffer(chunkSize);
        file.read(buffer.data(), chunkSize);
        buffer.resize(file.gcount()); // Resize buffer to actual read size
        if (!buffer.empty()) chunks.push_back(std::move(buffer));
    }

    return chunks;
}


// 📌 Step 4: Multi-Threaded Compression using std::thread and std::promise
// Each chunk is compressed concurrently in a separate thread.



// 🖥️ Code: Multi-Threaded Compression Function

std::vector<std::vector<char>> compressFileMultiThreaded(const std::string& filename, size_t chunkSize) {
    auto chunks = readFileChunks(filename, chunkSize);
    std::vector<std::promise<std::vector<char>>> promises(chunks.size());
    std::vector<std::future<std::vector<char>>> futures;

    // Launch multiple threads for compression
    std::vector<std::thread> threads;
    for (size_t i = 0; i < chunks.size(); ++i) {
        futures.push_back(promises[i].get_future());
        threads.emplace_back([&, i] {
            try {
                auto compressed = compressChunk(chunks[i]);
                promises[i].set_value(std::move(compressed));
            } catch (...) {
                promises[i].set_exception(std::current_exception());
            }
        });
    }

    // Wait for all threads to finish
    for (auto& t : threads) t.join();

    // Retrieve compressed chunks
    std::vector<std::vector<char>> compressedChunks;
    for (auto& future : futures) {
        compressedChunks.push_back(future.get());
    }

    return compressedChunks;
}



// 📌 Step 5: Write Compressed Chunks to a File
// Once the chunks are compressed, we merge and store them in an output file.

// 🖥️ Code: Save Compressed File


void saveCompressedFile(const std::string& outputFilename, const std::vector<std::vector<char>>& compressedChunks) {
    std::ofstream file(outputFilename, std::ios::binary);
    if (!file) throw std::runtime_error("Could not open output file");

    for (const auto& chunk : compressedChunks) {
        file.write(chunk.data(), chunk.size());
    }
}



// 📌 Step 6: Main Function to Test Compression System
// We define the input file, chunk size, and start the compression process.

// 🖥️ Code: Main Function


int main() {
    std::string inputFile = "largefile.txt";
    std::string outputFile = "compressed.zlib";
    size_t chunkSize = 1024 * 1024; // 1 MB per chunk

    try {
        std::cout << "Starting multi-threaded file compression...\n";
        auto compressedChunks = compressFileMultiThreaded(inputFile, chunkSize);
        saveCompressedFile(outputFile, compressedChunks);
        std::cout << "Compression completed. Output saved to " << outputFile << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}




// 📌 Step 7: Expected Output

// Starting multi-threaded file compression...
// Compression completed. Output saved to compressed.zlib


// 📌 Enhancements
// 🔹 Multi-Threaded Decompression: Implement parallel decompression.
// 🔹 Compression Ratio Display: Show the percentage of size reduction.
// 🔹 GUI Interface: Implement a Qt-based frontend for file selection.




// ✅ Why is this project valuable?
// Demonstrates practical use of std::thread, std::promise, and std::future.
// Parallelizes file compression, reducing execution time.
// Real-world application in file storage and data processing systems.
// A strong interview topic showcasing concurrency in C++.new