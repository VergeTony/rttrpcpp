#include <cassert>
#include <rttrpcpp/core/Logging.h>
#include <rttrpcpp/RTTrPM.h>
#include <rttrpcpp/trackables/TrackableFactory.h>

using namespace RTTrPCpp;

uint16_t RTTrPM::getSize() const
{
    size_t trackableSize = 0;

    for (auto &trackable : m_trackables)
    {
        trackableSize += trackable->getSize();
    }

    return RTTRP_HEADER_SIZE + trackableSize;
}

void RTTrPM::addTrackable(std::shared_ptr<TrackableGeneric> trackable)
{
    m_trackables.push_front(trackable);
    m_moduleCount++;
}

const std::forward_list<std::shared_ptr<TrackableGeneric>> &RTTrPM::getTrackables() const
{
    return m_trackables;
}

void RTTrPM::processTrackable(std::shared_ptr<TrackableGeneric> trackable)
{
    for (auto &module : trackable->getModules())
    {
        log_info("Received module 0x%02X from %s",
            module->getType(),
            trackable->getName().c_str());
    }
}

size_t RTTrPM::toBytes(uint8_t * const buf)
{
    int ret = RTTrPHeader::toBytes(buf);

    for (auto &trackable : m_trackables)
    {
        ret += trackable->toBytes(&buf[ret]);
    }

    return ret;
}

size_t RTTrPM::fromBytes(uint8_t * const buf)
{
    int ret = RTTrPHeader::fromBytes(buf);

    TrackableFactory factory;

    for (uint8_t i = 0; i < m_moduleCount; i++)
    {
        m_trackables.push_front(factory.generateFromBytes(&buf[ret]));
        ret += m_trackables.front()->getSize();
        processTrackable(m_trackables.front());
    }

    assert(m_size == ret);

    return ret;
}