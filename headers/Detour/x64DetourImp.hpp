//
// Created by steve on 7/4/17.
//

#ifndef POLYHOOK_2_X64DETOURIMPL_HPP
#define POLYHOOK_2_X64DETOURIMPL_HPP

#include "headers/Maybe.hpp"
#include "headers/MemoryAllocation/RangeAllocator.hpp"
#include "headers/IHook.hpp"
#include "headers/Enums.hpp"

#include <memory>  // shared_ptr
#include <vector>

namespace PLH {

class x64DetourImp
{
public:
    //TODO: Make the allocator typedef a template argument to class
    typedef PLH::RangeAllocator<uint8_t, PLH::MemAllocatorUnix> LinuxAllocator;
    typedef std::vector<uint8_t, LinuxAllocator>                DetourBuffer;
    typedef std::vector<std::shared_ptr<PLH::Instruction>>      InstructionVector;

    DetourBuffer makeMemoryBuffer(const uint64_t hint);

    PLH::HookType getType() const;

    PLH::Mode getArchType() const;

    uint8_t minimumPrologueLength() const;

    uint8_t preferredPrologueLength() const;

    JmpType minimumJumpType() const;

    JmpType preferredJumpType() const;

    void setIndirectHolder(const uint64_t holderAddress);

    InstructionVector makeMinimumJump(const uint64_t address, const uint64_t destination) const;

    InstructionVector makePreferredJump(const uint64_t address, const uint64_t destination) const;

private:
    /* Holds the address of the chunk of memory that stores
     * the value of where the indirect jump points too*/
    PLH::Maybe<uint64_t> m_indirectHolder;
};
}
#endif //POLYHOOK_2_X64DETOURIMPL_HPP