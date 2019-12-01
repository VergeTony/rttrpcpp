#include <cassert>
#include <rttrpcpp/core/Logging.h>
#include <rttrpcpp/RTTrPHeader.h>

using namespace RTTrPCpp;

RTTrPHeader::RTTrPHeader(uint32_t packetId, RTTrPType type) :
    m_moduleCount(0),
    m_size(0),
    m_version(type),
    m_packetId(packetId),
    m_packetFormat(PacketFormat::Raw),
    m_context(0)
{

}

RTTrPType RTTrPHeader::getTypeFromBytes(uint8_t * const buf)
{
    uint16_t intsig, version;

    /* Only deserialize header that reveals RTTrP type */
    memcpy(&intsig, &buf[0], sizeof(uint16_t));
    memcpy(&version, &buf[4], sizeof(uint16_t));

    intsig = Serializable::ntohs(intsig);

    if (intsig == RTTRP_INTEGER_SIGNATURE_BE)
    {
        return static_cast<RTTrPType>(Serializable::ntohs(version));
    }
    else if (intsig == RTTRP_INTEGER_SIGNATURE_LE)
    {
        return static_cast<RTTrPType>(version);
    }
    else
    {
        return RTTrPType::None;
    }
}

size_t RTTrPHeader::toBytes(uint8_t * const buf)
{
    size_t ret = 0;
    m_size = getSize();
    uint16_t intsig = Serializable::htons(RTTRP_INTEGER_SIGNATURE_BE);
    uint16_t fltsig = Serializable::htons(RTTRP_FLOAT_SIGNATURE_BE);
    uint16_t size = Serializable::htons(m_size);
    uint16_t version = Serializable::htons(static_cast<uint16_t>(m_version));
    uint32_t packetId = Serializable::htonl(static_cast<uint8_t>(m_packetId));
    uint32_t context = Serializable::htonl(m_context);

    memcpy(&buf[ret], &intsig, sizeof(uint16_t));
    ret += sizeof(uint16_t);
    memcpy(&buf[ret], &fltsig, sizeof(uint16_t));
    ret += sizeof(uint16_t);
    memcpy(&buf[ret], &version, sizeof(uint16_t));
    ret += sizeof(uint16_t);
    memcpy(&buf[ret], &packetId, sizeof(uint32_t));
    ret += sizeof(uint32_t);
    memcpy(&buf[ret], &m_packetFormat, sizeof(uint8_t));
    ret += sizeof(uint8_t);
    memcpy(&buf[ret], &size, sizeof(uint16_t));
    ret += sizeof(uint16_t);
    memcpy(&buf[ret], &context, sizeof(uint32_t));
    ret += sizeof(uint32_t);
    memcpy(&buf[ret], &m_moduleCount, sizeof(uint8_t));
    ret += sizeof(uint8_t);

    assert(ret == RTTRP_HEADER_SIZE);

    return ret;
}

size_t RTTrPHeader::fromBytes(uint8_t * const buf)
{
    int ret = 0;
    uint16_t intsig = 0;
    uint16_t fltsig = 0;
    uint16_t version = 0;
    uint16_t size = 0;

    memcpy(&intsig, &buf[ret], sizeof(uint16_t));
    ret += sizeof(uint16_t);
    memcpy(&fltsig, &buf[ret], sizeof(uint16_t));
    ret += sizeof(uint16_t);
    memcpy(&version, &buf[ret], sizeof(uint16_t));
    ret += sizeof(uint16_t);
    memcpy(&m_packetId, &buf[ret], sizeof(uint32_t));
    ret += sizeof(uint32_t);
    memcpy(&m_packetFormat, &buf[ret], sizeof(uint8_t));
    ret += sizeof(uint8_t);
    memcpy(&size, &buf[ret], sizeof(uint16_t));
    ret += sizeof(uint16_t);
    memcpy(&m_context, &buf[ret], sizeof(uint32_t));
    ret += sizeof(uint32_t);
    memcpy(&m_moduleCount, &buf[ret], sizeof(uint8_t));
    ret += sizeof(uint8_t);

    assert(ret == RTTRP_HEADER_SIZE);

    intsig = Serializable::ntohs(intsig);
    fltsig = Serializable::ntohs(fltsig);

    if (intsig == RTTRP_INTEGER_SIGNATURE_BE)
    {
        m_version = static_cast<RTTrPType>(Serializable::ntohs(version));
        m_size = Serializable::ntohs(size);
        m_packetId = Serializable::ntohl(m_packetId);
        m_context = Serializable::ntohl(m_context);
    }

    log_debug(
"**********************************RTTrP Packet Start***************************");
    log_debug("RTTrP Packet Header:");
    log_debug("  IntSig:    0x%04X", intsig);
    log_debug("  FltSig:    0x%04X", fltsig);
    log_debug("  Version:   0x%04X", static_cast<uint16_t>(m_version));
    log_debug("  Pck ID:    %u", m_packetId);
    log_debug("  Pck Fmt:   %u", static_cast<uint8_t>(m_packetFormat));
    log_debug("  Size:      %u", m_size);
    log_debug("  Context:   %u", m_context);
    log_debug("  M Count:   %u", m_moduleCount);

    return ret;
}

bool RTTrPHeader::operator==(const RTTrPHeader &other) const
{
    return m_version == other.m_version
        && m_packetId == other.m_packetId
        && m_packetFormat == other.m_packetFormat
        && m_size == other.m_size
        && m_context == other.m_context
        && m_moduleCount == other.m_moduleCount;
}
