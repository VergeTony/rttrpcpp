#pragma once
#include <memory>
#include <forward_list>

#include <rttrpcpp/RTTrPHeader.h>
#include <rttrpcpp/trackables/Trackable.h>

namespace RTTrPCpp {

class RTTrPM : public RTTrPHeader
{
public:
    RTTrPM() = delete;
    RTTrPM(uint32_t packetId) : RTTrPHeader(packetId, RTTrPType::RTTrPM) {}
    RTTrPM(uint8_t * const buf) { fromBytes(buf); }

    /** Gets the total size of the RTTrPM packet when serialized */
    uint16_t getSize() const final;

    /** Adds a trackable module to the RTTrPM Packet */
    void addTrackable(std::shared_ptr<TrackableGeneric> trackable);

    /** Returns all stored trackables */
    const std::forward_list<std::shared_ptr<TrackableGeneric>> &getTrackables() const;

    /** Serializes RTTrPM packet into a buffer.
     * Example use:
     * \code{.cpp}
     * // Build RTTrMP
     * RTTrPM rttrpm(static_cast<uint32_t>(0));
     * rttrpm.addTrackable(trackable);
     *
     * // Create buffer that can fit the size of the RTTrPM packet
     * std::vector<uint8_t> buf(rttrpm.getSize());
     *
     * // Serialize
     * rttrpm.toBytes(&buf[0]);
     * \endcode */
    size_t toBytes(uint8_t * const buf) final;

    /** Deserialize RTTrPM from buffer */
    size_t fromBytes(uint8_t * const buf) final;

protected:
    /** processTrackable() is called as trackables are being deserialized.
     * Override this function at the application level to process modules
     * contained in the trackable */
    virtual void processTrackable(std::shared_ptr<TrackableGeneric> trackable);

private:
    std::forward_list<std::shared_ptr<TrackableGeneric>> m_trackables;
};

} // namespace RTTrPCpp
