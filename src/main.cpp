#include <Windows.h>
#include <spdlog/spdlog.h>
#include "F4SE/F4SE.h"

REL::Relocation<std::uintptr_t> kMovTarget{ REL::ID{ 1118991, 2249275 }, REL::Offset{ 0x166, 0x179, 0x17E } };
constexpr size_t kMovLength = 7;

void NopInstruction(uintptr_t address, size_t length)
{
    DWORD oldProtect;
    VirtualProtect(reinterpret_cast<void*>(address), length, PAGE_EXECUTE_READWRITE, &oldProtect);
    memset(reinterpret_cast<void*>(address), 0x90, length); // 0x90 = NOP
    VirtualProtect(reinterpret_cast<void*>(address), length, oldProtect, &oldProtect);
}

F4SE_PLUGIN_LOAD(const F4SE::LoadInterface* a_f4se)
{
    F4SE::Init(a_f4se);

    NopInstruction(kMovTarget.address(), kMovLength);

    spdlog::info("NOPped mov instruction at Fallout4+0x{:X}", kMovTarget.offset());

    return true;
}