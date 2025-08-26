
#ifndef NET_PACKET_HPP
#define NET_PACKET_HPP

#include "core/PacketHeader.hpp" // Correct file path
#include <vector>
#include <string>
#include <stdexcept> // Required for std::out_of_range

namespace Net {

    class Packet {
    public:
        // Default constructor
        Packet() : m_readOffset(0) {
            m_buffer.reserve(512); // Pre-allocate 512 bytes
        }

        // Copy assignment operator
        Packet& operator=(const Packet& other) {
            if (this != &other) {
                m_buffer = other.m_buffer;
                m_readOffset = other.m_readOffset;
            }
            return *this;
        }

        // Methods for adding data
        template<typename T>
        inline Packet& add(const T& data);
        Packet& add(const std::string& str);

        // Methods for reading data
        template<typename T>
        inline Packet& get(T& data);
        Packet& get(std::string& str);

        // Clears the packet's content
        void clear();

        // Gets packet header and data as a byte array
        const std::vector<char>& getBytes() const;

        // Other necessary function prototypes
        size_t size() const;

    private:
        packetheader m_header; // Correct class name
        std::vector<char> m_buffer;
        size_t m_readOffset;
    };

    // Inline definitions for template functions
    template<typename T>
    inline Packet& Packet::get(T& data) {
        if (m_readOffset + sizeof(T) > m_buffer.size()) {
            throw std::out_of_range("Packet::get<T> - trying to read beyond buffer size");
        }

        memcpy(&data, m_buffer.data() + m_readOffset, sizeof(T));
        m_readOffset += sizeof(T);

        return *this;
    }

    template<typename T>
    inline Packet& Packet::add(const T& data) {
        m_buffer.insert(m_buffer.end(), reinterpret_cast<const char*>(&data), reinterpret_cast<const char*>(&data) + sizeof(T));
        return *this;
    }

} // namespace Net

#endif // NET_PACKET_HPP