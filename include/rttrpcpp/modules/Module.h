#pragma once
#include <cassert>
#include <cstring>

#include <rttrpcpp/core/Serializable.h>

namespace RTTrPCpp {

class ModuleGeneric : public Serializable
{
public:
    virtual uint8_t getType() const = 0;
    virtual uint16_t getSize() const = 0;

    virtual size_t toBytes(uint8_t * const buf) override;
    virtual size_t fromBytes(uint8_t * const buf) override;
};

template<int ModuleType>
class Module : public ModuleGeneric
{
public:
    const static uint8_t typeId = ModuleType;
    uint8_t getType() const final { return static_cast<uint8_t>(ModuleType); }
};

} // namespace RTTrPCpp
