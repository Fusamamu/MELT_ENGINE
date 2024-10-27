#include "Core.h"

namespace MELT
{
    std::string GenerateUUID(uintptr_t _id)
    {
        // 1. Get high-resolution time
        auto now = std::chrono::high_resolution_clock::now();
        auto timeSinceEpoch = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();

        // 2. Combine time and object address (id)
        std::stringstream ss;
        ss << std::hex << timeSinceEpoch << _id;

        // 3. Generate a random component
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<uint64_t> distribution(0, 0xFFFFFFFFFFFFFFFF);
        uint64_t randomComponent = distribution(generator);

        // 4. Combine and hash to standardize UUID format
        ss << std::hex << randomComponent;
        std::hash<std::string> hasher;
        auto hashValue = hasher(ss.str());

        // 5. Format as UUID (8-4-4-4-12 format)
        std::stringstream uuid;
        uuid << std::hex << std::setw(8) << std::setfill('0') << ((hashValue >> 96) & 0xFFFFFFFF)
             << '-' << std::setw(4) << ((hashValue >> 80) & 0xFFFF)
             << '-' << std::setw(4) << ((hashValue >> 64) & 0xFFFF)
             << '-' << std::setw(4) << ((hashValue >> 48) & 0xFFFF)
             << '-' << std::setw(12) << (hashValue & 0xFFFFFFFFFFFF);

        return uuid.str();
    }
}