/*/*************************************************************************
 *                                                                         *
 * Engine, Engine-Lib interface class for many things,                     *
 * implementierung in extern libs                               	   *
 * Copyright (C) 2012, 20013, 2014 Dario Rekowski.			   *
 * Email: dario.rekowski@gmx.de   Web: www.spacecrafting.de                *
 *                                                                         *
 * This program is free software: you can redistribute it and/or modify    *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation, either version 3 of the License, or       *
 * any later version.							   *
 *									   *
 * This program is distributed in the hope that it will be useful,	   *
 * but WITHOUT ANY WARRAN TY; without even the implied warranty of	   *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	   *
 * GNU General Public License for more details.				   *
 *									   *
 * You should have received a copy of the GNU General Public License	   *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
 *                                                                         *
 ***************************************************************************/

/*!
    Standard Interface Klasse, parent von allen Interface Klassen,
    welche eine externe dll dynamisch einbinden
*/

#ifndef __DR_UNIVERSUM_LIB_INTERFACE__
#define __DR_UNIVERSUM_LIB_INTERFACE__

#include "UniversumLib.h"

class UNIVERSUM_LIB_API DRInterface
{
public:
    virtual ~DRInterface();

    // Zugrifffunktionen
    static DRInterface* Instance(const char* dllName);

    static void close();

    static void releaseMem(DRInterface* data, const char* dllname);

protected:
    DRInterface();
    static DRReturn loadDll(const char* dllname);
	static const char* someErrorCodes(int errorCode);

#ifdef _WIN32
    static HMODULE mDLL;
#else
    static void* mDLL;
#endif


private:
};
#endif //__DR_UNIVERSUM_LIB_INTERFACE__
