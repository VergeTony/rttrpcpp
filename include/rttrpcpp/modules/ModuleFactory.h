#pragma once
#include <memory>
#include <rttrpcpp/modules/Module.h>

namespace RTTrPCpp {

class ModuleFactory
{
public:
    std::shared_ptr<ModuleGeneric> generateFromBytes(uint8_t * const buf);

    template <class ModuleClass>
    std::shared_ptr<ModuleClass> generate(uint8_t * const buf)
    {
        static_assert(std::is_base_of<ModuleGeneric, ModuleClass>::value);
        return std::make_shared<ModuleClass>(buf);
    }
};

} // namespace RTTrPCpp