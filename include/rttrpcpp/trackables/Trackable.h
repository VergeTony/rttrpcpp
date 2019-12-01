#pragma once
#include <string>
#include <memory>
#include <forward_list>

#include <rttrpcpp/core/Serializable.h>
#include <rttrpcpp/modules/Module.h>

namespace RTTrPCpp {

class TrackableFactory;

class TrackableGeneric : public ModuleGeneric
{
public:
    TrackableGeneric() = default;
    TrackableGeneric(std::string name);

    virtual uint16_t getSize() const;

    void addModule(std::shared_ptr<ModuleGeneric> module);
    const std::forward_list<std::shared_ptr<ModuleGeneric>> &getModules() const;
    const std::string &getName() const { return m_name; }

    virtual size_t toBytes(uint8_t * const buf) override;
    virtual size_t fromBytes(uint8_t * const buf) override;

    bool operator==(const TrackableGeneric &other) const;

protected:
    uint8_t m_moduleCount;
    std::forward_list<std::shared_ptr<ModuleGeneric>> m_modules;

    /* type = 1, size = 2, namesize = 1, modulecount = 1 */
    static const size_t TRACKABLE_COMMON_HEADER_SIZE = 5;

    std::string m_name;
    uint16_t m_size;
};

template<int TrackableType>
class Trackable : public TrackableGeneric
{
friend TrackableFactory;
public:
    Trackable() = default;
    Trackable(std::string name) : TrackableGeneric(name) {}
    uint8_t getType() const final { return static_cast<uint8_t>(TrackableType); }

private:
    const static uint8_t typeId = TrackableType;
};

} // namespace RTTrPCpp