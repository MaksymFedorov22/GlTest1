#include <iostream>
#include <filesystem>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>
#include "gltestlib1.h"

namespace fs = std::filesystem;
std::atomic<bool> found(false);
std::atomic<int> nThreads(0);

void search_directory2(const fs::path &directory_path, const std::string &file_name)
{
    try
    {
        for (const auto &entry : fs::recursive_directory_iterator(directory_path))
        {
            if (found)
                return;
            if (entry.is_regular_file() && entry.path().filename() == file_name)
            {
                std::cout << entry.path().string() << '\n';
                found = true;
                return;
            }
        }
    }
    catch (...)
    {
    }
}
void search_directory(const fs::path &directory_path, const std::string &file_name)
{
    nThreads++;
    search_directory2(directory_path, file_name);
    nThreads--;
}

void gltest1(std::string strpath, std::string strfilename)
{
    fs::path p{strpath};
    std::string filename{strfilename};
    std::vector<std::thread> threads;
    for (const auto &entry : fs::directory_iterator(p))
    {
        if (entry.is_directory())
        {
            // std::cout << "Threads: " << nThreads << std::endl;
            while (nThreads > 7)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
            threads.emplace_back(search_directory, entry.path(), filename);
        }
        // ADD FILE FINDER ON C:
        if (entry.is_regular_file() && entry.path().filename() == strfilename)
        {
            std::cout << entry.path().string() << '\n';
            found = true;
            break;
        }
    }

    for (auto &thread : threads)
    {
        thread.join();
    }

    if (!found)
        std::cout << "File not found" << std::endl;
}
