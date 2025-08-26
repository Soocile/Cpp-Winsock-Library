#include "core/Packet.hpp"
#include <winsock2.h>
#include <string>

namespace Net {

    Packet& Packet::add(const std::string& str)
    {
        size_t strSize = str.size();
        add(strSize); // add the size of the string first
        m_buffer.insert(m_buffer.end(), str.begin(), str.end());
        return *this;
    }

    Packet& Packet::get(std::string& str)
    {
        size_t strSize;
        get(strSize); // firstly read the string size

        // do not accept if the string is bigger than 1 MB to prevent DoS attacks
        constexpr size_t MAX_STR = 1 << 20; // approximately 1 MB
        if (strSize > MAX_STR) {
            throw std::length_error("Packet::get<std::string> - string too large");
        }

        // Control the limitations of buffer size 
        if (m_readOffset + strSize > m_buffer.size()) {
            throw std::out_of_range("Packet::get<std::string> - trying to read beyond buffer size");
        }

        str.assign(m_buffer.data() + m_readOffset, strSize);

        // advance the offset
        m_readOffset += strSize;

        //for chaining
        return *this;
    }

    // Bu fonksiyonu ekliyoruz
    void Packet::clear()
    {
        m_buffer.clear();
        m_readOffset = 0;
    }

    const std::vector<char>& Packet::getBytes() const
    {
        return m_buffer;
    }

    // Bu fonksiyonu da ekliyoruz
    size_t Packet::size() const
    {
        return m_buffer.size();
    }

} // namespace Net