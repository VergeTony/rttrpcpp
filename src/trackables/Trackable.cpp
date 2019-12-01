#include <rttrpcpp/trackables/Trackable.h>
#include <rttrpcpp/core/Logging.h>

using namespace RTTrPCpp;

TrackableGeneric::TrackableGeneric(std::string name) :
    m_moduleCount(0),
    m_name(name)
{

}

uint16_t TrackableGeneric::getSize() const
{
    return TRACKABLE_COMMON_HEADER_SIZE + m_name.size();
}

void TrackableGeneric::addModule(std::shared_ptr<ModuleGeneric> module)
{
    m_modules.push_front(module);
    m_moduleCount++;
}

const std::forward_list<std::shared_ptr<ModuleGeneric>> &TrackableGeneric::getModules() const
{
    return m_modules;
}

size_t TrackableGeneric::toBytes(uint8_t * const buf)
{
    m_size = Serializable::htons(getSize());
    uint8_t type = getType();
    uint8_t nameSize = m_name.size();

    memcpy(&buf[0], &type, sizeof(uint8_t));
    memcpy(&buf[1], &m_size, sizeof(uint16_t));
    memcpy(&buf[3], &nameSize, sizeof(uint8_t));
    memcpy(&buf[4], reinterpret_cast<const uint8_t*>(m_name.c_str()), nameSize);

    return sizeof(uint8_t) + sizeof(uint16_t) + sizeof(uint8_t) + nameSize;
}

size_t TrackableGeneric::fromBytes(uint8_t * const buf)
{
    uint8_t type = buf[0];
    assert(type == getType());

    memcpy(&m_size, &buf[1], sizeof(uint16_t));
    m_size = Serializable::ntohs(m_size);

    uint8_t nameSize;
    memcpy(&nameSize, &buf[3], sizeof(uint8_t));

    m_name = std::string(reinterpret_cast<const char*>(&buf[4]), nameSize);

    log_debug("Trackable Header:");
    log_debug("  Type:      0x%02X", type);
    log_debug("  Size:      %u", m_size);
    log_debug("  NameSize:  %u", nameSize);
    log_debug("  Name:      %s", m_name.c_str());

    return sizeof(uint8_t) + sizeof(uint16_t) + sizeof(uint8_t) + nameSize;
}

bool TrackableGeneric::operator==(const TrackableGeneric &other) const
{
    return getType() == other.getType()
        && m_moduleCount == other.m_moduleCount
        && getSize() == other.getSize()
        && m_name == other.m_name;
}
