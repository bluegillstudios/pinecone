#pragma once

#include <cstdint>

namespace Pinecone {

    class UUID {
    public:
        UUID();
        UUID(uint64_t id);

        uint64_t Get() const { return m_ID; }

        bool operator==(const UUID& other) const { return m_ID == other.m_ID; }
        bool operator!=(const UUID& other) const { return m_ID != other.m_ID; }

    private:
        uint64_t m_ID;
    };

}
