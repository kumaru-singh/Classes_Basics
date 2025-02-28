// Project 8: Concurrent Web Scraper (std::async & std::future)
// 🔹 Concept: Use std::async and std::future to fetch multiple web pages concurrently.
// 🔹 Real-World Use Case: A web scraping tool that extracts data from multiple URLs in parallel, improving speed compared to sequential requests.
// 🔹 Why Asynchronous Execution?

// Reduces waiting time by fetching multiple pages simultaneously.
// Demonstrates the power of concurrent execution using std::async.
// Common use case in data analysis, automation, and competitive programming.
// 📌 Step 1: Install & Set Up cURL for HTTP Requests
// Since C++ does not have a built-in HTTP client, we use cURL for web requests.

// 1️⃣ Linux/macOS: Install cURL library:

// 📌 Step 2: Implement HTTP GET Request Function
// We define a function to fetch the HTML content of a URL using cURL.

// 🖥️ Code: HTTP GET Request Function


#include <iostream>
#include <future>
#include <vector>
#include <string>
#include <curl/curl.h>

// Callback function to store fetched data
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

// Function to fetch HTML content of a URL
std::string fetchURL(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string htmlData;

    curl = curl_easy_init();  // Initialize cURL
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &htmlData);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Follow redirects

        res = curl_easy_perform(curl); // Execute request
        if (res != CURLE_OK) {
            std::cerr << "cURL Error: " << curl_easy_strerror(res) << "\n";
        }
        curl_easy_cleanup(curl);
    }

    return htmlData;
}



// 📌 Step 3: Fetch Multiple URLs Concurrently using std::async
// We use std::async to execute HTTP requests in parallel instead of sequentially.

// 🖥️ Code: Concurrent Web Scraper


void scrapeWebsites(const std::vector<std::string>& urls) {
    std::vector<std::future<std::string>> futures;

    // Launch multiple asynchronous tasks
    for (const auto& url : urls) {
        futures.push_back(std::async(std::launch::async, fetchURL, url));
    }

    // Collect results
    for (size_t i = 0; i < urls.size(); ++i) {
        std::string htmlContent = futures[i].get();
        std::cout << "Fetched " << urls[i] << " (" << htmlContent.size() << " bytes)\n";
    }
}



// 📌 Step 4: Main Function to Run the Scraper
// We define a set of URLs and scrape them concurrently.

// 🖥️ Code: Main Function

int main() {
    std::vector<std::string> websites = {
        "https://www.example.com",
        "https://www.wikipedia.org",
        "https://www.github.com"
    };

    std::cout << "Starting concurrent web scraping...\n";
    scrapeWebsites(websites);

    return 0;
}


📌 Step 5: Expected Output

// Starting concurrent web scraping...
// Fetched https://www.example.com (12500 bytes)
// Fetched https://www.wikipedia.org (40500 bytes)
// Fetched https://www.github.com (32000 bytes)



// 📌 Enhancements
// 🔹 Save Web Pages to File: Store fetched HTML content in text files.
// 🔹 Extract Specific Data: Parse titles, headings, or links using Regex.
// 🔹 Use a GUI: Display fetched content using Qt or React frontend.


// ✅ Why is this project valuable?
// Demonstrates real-world use of std::async & std::future.
// Parallel processing speeds up web data retrieval.
// Highly relevant in data collection, web scraping, and automation.
// Impresses interviewers with advanced C++ concurrency concepts.