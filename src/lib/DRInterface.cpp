#include "lib/DRInterface.h"

#ifdef _WIN32
HMODULE   DRInterface::mDLL = 0;
#else
void* DRInterface::mDLL = NULL;
#endif

DRInterface* (*getInstance)(void) = NULL;
void (*releaseInstance)(DRInterface*) = NULL;

DRInterface::DRInterface()
{

}

DRInterface::~DRInterface()
{

}

void DRInterface::close()
{
    if(mDLL)
    {
#ifdef _WIN32
        FreeLibrary(mDLL);
#else
        dlclose(mDLL);
#endif
        mDLL = 0;
        releaseInstance = NULL;
        getInstance = NULL;
    }
}

DRInterface* DRInterface::Instance(const char* dllName)
{
 //try to load from dll
    if(!mDLL)
    {
        if(loadDll(dllName))
        {
            LOG_ERROR("keine dll", NULL);
            //LOG_WARNING("keine dll");
            //return new DRInterface();
        }
    }

    if(!getInstance) loadDll(dllName);
    if(getInstance)
    {
        return getInstance();
    }
    else
    {
        LOG_ERROR("function didn't exist in dll", NULL);
        //return new DRInterface();
    }

//    return NULL;
}

DRReturn DRInterface::loadDll(const char* dllname)
{
    //try to load from dll
    if(!mDLL)
    {
#ifdef _WIN32
        mDLL = LoadLibraryA(dllname);
#else
        mDLL = dlopen(dllname, RTLD_LAZY);
#endif
    }
    if(mDLL)
    {
#ifdef _WIN32
        if(!getInstance)
            getInstance = (DRInterface* (*)())(GetProcAddress(mDLL, "getInstance"));
        if(!releaseInstance)
            releaseInstance = (void (*)(DRInterface*))(GetProcAddress(mDLL, "releaseInstance"));
#else
        if(!getInstance)
            getInstance = (DRInterface* (*)())(dlsym(mDLL, "getInstance"));
        if(!releaseInstance)
            releaseInstance = (void (*)(DRInterface*))(dlsym(mDLL, "releaseInstance"));
#endif
    }
    else
    {
#ifndef _WIN32
        UniLib::EngineLog.writeToLog("Fehler bei dll (%s) Load: %s", dllname, dlerror());
#else
		UniLib::EngineLog.writeToLog("Fehler bei dll (%s) Load, error nr: %d (%s)", dllname, GetLastError(), someErrorCodes(GetLastError()));
#endif
        LOG_ERROR("Fehler bei dll load", DR_ERROR);
    }
    return DR_OK;
}

const char* DRInterface::someErrorCodes(int errorCode)
{
	switch(errorCode) {
	case 14001: return "The application has failed to start because its side-by-side configuration is incorrect. Please see the application event log or use the command-line sxstrace.exe tool for more detail.";
	default: return "";
	};
}

void DRInterface::releaseMem(DRInterface* data, const char* dllname)
{
    if(!data) LOG_ERROR_VOID("data, ZERO-POINTER");

    if(!mDLL)
    {
        if(!loadDll(dllname))
        {
            LOG_WARNING("keine dll");
            DR_SAVE_DELETE(data);
        }
    }

    if(!releaseInstance) loadDll(dllname);
    if(releaseInstance)
    {
        releaseInstance(data);
    }
    else
    {
        LOG_WARNING("function didn't exist in dll");
        DR_SAVE_DELETE(data);
    }

}
