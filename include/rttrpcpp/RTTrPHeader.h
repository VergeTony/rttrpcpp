#pragma once
#include <rttrpcpp/RTTrP.h>
#include <rttrpcpp/core/Serializable.h>

namespace RTTrPCpp {

class RTTrPHeader : public Serializable
{
public:
    RTTrPHeader(uint8_t * const buf) { fromBytes(buf); }

    /** Helper function that only deserializes required bits to extract type */
    static RTTrPType getTypeFromBytes(uint8_t * const buf);

    RTTrPType getRTTrPType() const { return m_version; }
    virtual uint16_t getSize() const { return RTTRP_HEADER_SIZE; };

    virtual size_t toBytes(uint8_t * const buf) override;
    virtual size_t fromBytes(uint8_t * const buf) override;

    bool operator==(const RTTrPHeader &other) const;

protected:
    RTTrPHeader() = default;
    RTTrPHeader(uint32_t packetId, RTTrPType type);
    uint8_t m_moduleCount;
    uint16_t m_size;

private:
    RTTrPType m_version;
    uint32_t m_packetId;
    PacketFormat m_packetFormat;
    uint32_t m_context;
};

} // namespace RTTrPCpp
