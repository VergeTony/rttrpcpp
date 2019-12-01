#include <limits>
#include <cassert>

#include <rttrpcpp/modules/ModuleFactory.h>
#include <rttrpcpp/trackables/TrackableDefault.h>
#include <rttrpcpp/core/Logging.h>

using namespace RTTrPCpp;

uint16_t TrackableDefault::getSize() const
{
    size_t moduleSize = 0;

    for (auto &module : m_modules)
    {
        moduleSize += module->getSize();
    }

    return TrackableGeneric::getSize() + moduleSize;
}

size_t TrackableDefault::toBytes(uint8_t * const buf)
{
    auto size = TrackableGeneric::toBytes(buf);

    memcpy(&buf[size], &m_moduleCount, sizeof(uint8_t));
    size += sizeof(uint8_t);

    for (auto &module : m_modules)
    {
        size += module->toBytes(&buf[size]);
    }

    return size;
}

size_t TrackableDefault::fromBytes(uint8_t * const buf)
{
    size_t ret = TrackableGeneric::fromBytes(buf);

    memcpy(&m_moduleCount, &buf[ret], sizeof(uint8_t));
    ret += sizeof(uint8_t);

    log_debug("  Modules:   %u", m_moduleCount);

    ModuleFactory factory;

    for (uint8_t i = 0; i < m_moduleCount; i++)
    {
        m_modules.push_front(factory.generateFromBytes(&buf[ret]));
        ret += m_modules.front()->getSize();
    }

    assert(m_size = ret);

    return ret;
}