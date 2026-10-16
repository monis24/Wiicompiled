// Guest functions that the shared HLE in runtime/src/hle calls directly by their RMCP01
// (Mario Kart Wii PAL) address. A game other than RMCP01 has no translated function at
// these addresses, so each one stops the runtime with its own log line instead of
// failing the link. Remove an entry once its caller is re-targeted for that game.
#if !defined(WIICOMPILED_GAME_RMCP01)

#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "ppc_runtime.h"
#include "runtime_log.h"

namespace {
[[noreturn]] void HaltMkwGuestCall(uint32_t addr, const char* caller) {
    RT_LOGF(RT_TAG_HLE, "RMCP01-only guest call func_%08X from %s; not available for this game\n",
            addr, caller);
    std::fflush(stderr);
    std::abort();
}
} // namespace

#define MKW_GUEST_CALL_STUB(addr, caller) \
    extern "C" void func_##addr(CpuContext*) { HaltMkwGuestCall(0x##addr, caller); }

MKW_GUEST_CALL_STUB(8012B830, "hle/audio/ax_effects.cpp")
MKW_GUEST_CALL_STUB(801A0620, "hle/os/os_alarm.cpp")
MKW_GUEST_CALL_STUB(801AADE0, "hle/os/os_alarm.cpp")
MKW_GUEST_CALL_STUB(801A1ED8, "hle/os/os_scheduler.cpp")
MKW_GUEST_CALL_STUB(801A961C, "hle/os/os_init.cpp")
MKW_GUEST_CALL_STUB(8055531C, "hle/os/os_init.cpp")
MKW_GUEST_CALL_STUB(801D8D30, "hle/net/network_config.cpp")
MKW_GUEST_CALL_STUB(801D9E94, "hle/net/network_config.cpp")

#endif
