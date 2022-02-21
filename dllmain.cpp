#include <Windows.h>
#include <detours.h>

#include <cstring>
#include <cstdio>

#include "loader.h"

namespace pkodev
{
    namespace address
    {
        // Game.exe 0 (1222073761)
        namespace GAME_13X_0
        {
            // void	CAniClock::Render(int x, int y)
            const unsigned int CAniClock__Render = 0x004ED500;

            // CGuiFont
            const unsigned int CGuiFont = 0x0066A730;

            // void CGuiFont::BRender(unsigned int nIndex, const char* str, int x, int y, DWORD color, DWORD shadow)
            const unsigned int CGuiFont__BRender = 0x0046FF70;

            // void CSkillCommand::Render(int x, int y)
            const unsigned int CSkillCommand__Render = 0x0048F200;
        }

        // Game.exe 1 (1243412597)
        namespace GAME_13X_1
        {
            // void	CAniClock::Render(int x, int y)
            const unsigned int CAniClock__Render = 0x004ED610;

            // CGuiFont
            const unsigned int CGuiFont = 0x0066A730;

            // void CGuiFont::BRender(unsigned int nIndex, const char* str, int x, int y, DWORD color, DWORD shadow)
            const unsigned int CGuiFont__BRender = 0x0046FFB0;

            // void CSkillCommand::Render(int x, int y)
            const unsigned int CSkillCommand__Render = 0x0048F310;
        }

        // Game.exe 2 (1252912474)
        namespace GAME_13X_2
        {
            // void	CAniClock::Render(int x, int y)
            const unsigned int CAniClock__Render = 0x004ED6E0;

            // CGuiFont
            const unsigned int CGuiFont = 0x0066A730;

            // void CGuiFont::BRender(unsigned int nIndex, const char* str, int x, int y, DWORD color, DWORD shadow)
            const unsigned int CGuiFont__BRender = 0x00470050;

            // void CSkillCommand::Render(int x, int y)
            const unsigned int CSkillCommand__Render = 0x0048F3B0;
        }

        // Game.exe 3 (1244511158)
        namespace GAME_13X_3
        {
            // void	CAniClock::Render(int x, int y)
            const unsigned int CAniClock__Render = 0x004ED6D0;

            // CGuiFont
            const unsigned int CGuiFont = 0x0066A730;

            // void CGuiFont::BRender(unsigned int nIndex, const char* str, int x, int y, DWORD color, DWORD shadow)
            const unsigned int CGuiFont__BRender = 0x00470040;

            // void CSkillCommand::Render(int x, int y)
            const unsigned int CSkillCommand__Render = 0x0048F3A0;
        }

        // Game.exe 4 (1585009030)
        namespace GAME_13X_4
        {
            // void	CAniClock::Render(int x, int y)
            const unsigned int CAniClock__Render = 0x004ED8F0;

            // CGuiFont
            const unsigned int CGuiFont = 0x0066A748;

            // void CGuiFont::BRender(unsigned int nIndex, const char* str, int x, int y, DWORD color, DWORD shadow)
            const unsigned int CGuiFont__BRender = 0x00470150;

            // void CSkillCommand::Render(int x, int y)
            const unsigned int CSkillCommand__Render = 0x0048F5B0;
        }

        // Game.exe 5 (1207214236)
        namespace GAME_13X_5
        {
            // void	CAniClock::Render(int x, int y)
            const unsigned int CAniClock__Render = 0x004ED330;

            // CGuiFont
            const unsigned int CGuiFont = 0x0066A738;

            // void CGuiFont::BRender(unsigned int nIndex, const char* str, int x, int y, DWORD color, DWORD shadow)
            const unsigned int CGuiFont__BRender = 0x0046FC40;

            // void CSkillCommand::Render(int x, int y)
            const unsigned int CSkillCommand__Render = 0x0048F000;
        }
    }

    namespace pointer
    {
        // void	CAniClock::Render(int x, int y)
        typedef void(__thiscall* CAniClock__Render__Ptr)(void *, int, int);
        CAniClock__Render__Ptr CAniClock__Render = (CAniClock__Render__Ptr)(void*)(address::MOD_EXE_VERSION::CAniClock__Render);

        // void CGuiFont::BRender(unsigned int nIndex, const char* str, int x, int y, DWORD color, DWORD shadow)
        typedef void(__thiscall* CGuiFont_BRender_Ptr)(void*, const char*, int, int, int, int);
        CGuiFont_BRender_Ptr CGuiFont_BRender = (CGuiFont_BRender_Ptr)(void*)(address::MOD_EXE_VERSION::CGuiFont__BRender);

        // void CSkillCommand::Render(int x, int y)
        typedef void(__thiscall* CSkillCommand__Render__Ptr)(void*, int, int);
        CSkillCommand__Render__Ptr CSkillCommand__Render = (CSkillCommand__Render__Ptr)(void*)(address::MOD_EXE_VERSION::CSkillCommand__Render);
    }

    namespace hook
    {
        // void	CAniClock::Render(int x, int y)
        void __fastcall CAniClock__Render(void* This, void* NotUsed, int x, int y);
        
        // void CSkillCommand::Render(int x, int y)
        void __fastcall CSkillCommand__Render(void* This, void* NotUsed, int x, int y);
    }

    // A flag that indicates that it is need to render cooldown time
    bool render{ false };
    int x{ 0 };
    int y{ 0 };
}

// Entry point
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    // Nothing to do . . .
    return TRUE;
}

// Get mod information
void GetModInformation(mod_info& info)
{
    strcpy_s(info.name, TOSTRING(MOD_NAME));
    strcpy_s(info.version, TOSTRING(MOD_VERSION));
    strcpy_s(info.author, TOSTRING(MOD_AUTHOR));
    info.exe_version = MOD_EXE_VERSION;
}

// Start the mod
void Start(const char* path)
{
    // Enable hooks
    DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)pkodev::pointer::CAniClock__Render, pkodev::hook::CAniClock__Render);
    DetourAttach(&(PVOID&)pkodev::pointer::CSkillCommand__Render, pkodev::hook::CSkillCommand__Render);
    DetourTransactionCommit();
}

// Stop the mod
void Stop()
{
    // Disable hooks
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourDetach(&(PVOID&)pkodev::pointer::CAniClock__Render, pkodev::hook::CAniClock__Render);
    DetourDetach(&(PVOID&)pkodev::pointer::CSkillCommand__Render, pkodev::hook::CSkillCommand__Render);
    DetourTransactionCommit();
}

// void	CAniClock::Render(int x, int y)
void __fastcall pkodev::hook::CAniClock__Render(void* This, void* NotUsed, int x, int y)
{
    // Call the original function CAniClock::Render(int x, int y)
    pkodev::pointer::CAniClock__Render(This, x, y);

    // Check that we have to render cooldown time
    if (pkodev::render == true)
    {
        // Check coordinates
        if (x != pkodev::x || y != pkodev::y)
        {
            // Do not render the cooldown
            return;
        }

        // Reset the render flag
        pkodev::render = false;

        // Buffer for time label
        static char buf[16]{ 0x00 };

        // Get some data from CAniClock object
        const float _fPlayTime = *reinterpret_cast<float*>(reinterpret_cast<unsigned int>(This) + 0x20);
        const float _fCurTime = *reinterpret_cast<float*>(reinterpret_cast<unsigned int>(This) + 0x24);

        // Calculate time
        const float remaining = max((_fPlayTime - _fCurTime), 0.0f);
        const unsigned int hours = static_cast<unsigned int>(remaining / 3600);
        const unsigned int minutes = static_cast<unsigned int>(remaining / 60);
        const unsigned int seconds = static_cast<unsigned int>(remaining - (minutes * 60));

        // Format the time label
        if (hours > 0) // hours
        {
            _snprintf_s(buf, _TRUNCATE, "%.2d:%.2d", hours, minutes);
        }
        else
        {
            if (minutes > 0) // minutes
            {
                _snprintf_s(buf, _TRUNCATE, "%.2d:%.2d", minutes, seconds);
            }
            else
            {
                if (seconds > 0) // seconds
                {
                    _snprintf_s(buf, _TRUNCATE, "%d", seconds);
                }
                else
                {
                    _snprintf_s(buf, _TRUNCATE, "%.1f", remaining);
                }
            }
        }

        // Render the time label
        pkodev::pointer::CGuiFont_BRender(
            reinterpret_cast<void*>(pkodev::address::MOD_EXE_VERSION::CGuiFont),
            buf,
            x,
            y,
            0xFFFFFFFF,
            0xFF000000
        );
    }
}

// void CSkillCommand::Render(int x, int y)
void __fastcall pkodev::hook::CSkillCommand__Render(void* This, void* NotUsed, int x, int y)
{
    // Get pointer to the CCompent* CCommandObj::_pParent
    void* CCommandObj___pParent = reinterpret_cast<void*>(
        *reinterpret_cast<unsigned int*>(
            reinterpret_cast<unsigned int>(This) + 0x0C
        )
    );

    // Check the pointer
    if (CCommandObj___pParent != nullptr)
    {
        // Get pointer to CForm* CCompent::_frmOwn
        void* CCompent___frmOwn = reinterpret_cast<void*>(
            *reinterpret_cast<unsigned int*>(
                reinterpret_cast<unsigned int>(CCommandObj___pParent) + 0x80
            )
        );

        // Check the pointer
        if (CCompent___frmOwn != nullptr)
        {
            // Get the form name
            const char* form = reinterpret_cast<const char*>(
                reinterpret_cast<unsigned int>(CCompent___frmOwn) + 0x14
            );

            // Check that the form name is frmSkill
            if (std::strcmp(form, "frmSkill") == 0)
            {
                // Render the cooldown time
                pkodev::render = true;
                pkodev::x = x;
                pkodev::y = y;
            }
        }
    }

    // Call the original method void CSkillCommand::Render(int x, int y)
    pkodev::pointer::CSkillCommand__Render(This, x, y);
}