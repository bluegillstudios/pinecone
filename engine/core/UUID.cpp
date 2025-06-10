#include "UUID.h"
#include <random>

namespace Pinecone {

    static std::random_device rd;
    static std::mt19937_64 generator(rd());
    static std::uniform_int_distribution<uint64_t> distribution;

    UUID::UUID()
        : m_ID(distribution(generator)) {}

    UUID::UUID(uint64_t id)
        : m_ID(id) {}

}
