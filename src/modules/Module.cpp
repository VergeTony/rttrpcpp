#include <rttrpcpp/modules/Module.h>
#include <rttrpcpp/core/Logging.h>

using namespace RTTrPCpp;

size_t ModuleGeneric::toBytes(uint8_t * const buf)
{
    uint8_t type = getType();
    uint16_t size = Serializable::htons(getSize());

    memcpy(&buf[0], &type, sizeof(uint8_t));
    memcpy(&buf[1], &size, sizeof(uint16_t));

    return sizeof(uint8_t) + sizeof(uint16_t);
}

size_t ModuleGeneric::fromBytes(uint8_t * const buf)
{
    uint8_t type = buf[0];
    assert(type == getType());

    uint16_t size;
    memcpy(&size, &buf[1], sizeof(uint16_t));
    size = Serializable::ntohs(size);
    assert(static_cast<size_t>(size) == getSize());

    log_debug("Module Header:");
    log_debug("  Type:      0x%02X", type);
    log_debug("  Size:      %u", size);

    return sizeof(uint8_t) + sizeof(uint16_t);
}