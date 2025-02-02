/*/*************************************************************************
*                                                                         *
* UniversumLib, collection of classes for generating and go through a     *
* whole universe. It is for my Gameproject Spacecraft					   *
* Copyright (C) 2014, 2015, 2016, 2017 Dario Rekowski.					   *
* Email: dario.rekowski@gmx.de   Web: www.spacecrafting.de                *
*                                                                         *
* This program is free software: you can redistribute it and/or modify    *
* it under the terms of the GNU General Public License as published by    *
* the Free Software Foundation, either version 3 of the License, or       *
* any later version.													   *
*																		   *
* This program is distributed in the hope that it will be useful,	       *
* but WITHOUT ANY WARRANTY; without even the implied warranty of	       *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	       *
* GNU General Public License for more details.							   *
*																		   *
* You should have received a copy of the GNU General Public License	   *
* along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
*                                                                         *
***************************************************************************/

/*!
 *
 * \author: Dario Rekowski
 *
 * \date: 18.10.2015
 *
 * \desc: GPUTask represent one GPU Task which will be running on the gpu
 */

#ifndef __UNIVERSUM_LIB_CONTROLLER_GPU_TASK_H
#define __UNIVERSUM_LIB_CONTROLLER_GPU_TASK_H
#include "Task.h"

namespace UniLib {
	namespace controller {

		class UNIVERSUM_LIB_API GPUTask : public Task 
		{
		public: 
			GPUTask(GPUTaskSpeed taskSpeed = GPU_TASK_FAST);
			GPUTask(size_t childCount, GPUTaskSpeed taskSpeed = GPU_TASK_FAST);
			virtual ~GPUTask();

			virtual bool const isGPUTask() const {return true;}
			virtual const char* getResourceType() const {return "GPUTask";};

			virtual bool isSlowGPUTask() { return mTaskSpeed == GPU_TASK_SLOW; }
			virtual bool isFastGPUTask() { return mTaskSpeed == GPU_TASK_FAST; }
			virtual bool isLoadGPUTask() { return mTaskSpeed == GPU_TASK_LOAD; }
			virtual void scheduleTask(TaskPtr own);
		protected:
			

			GPUTaskSpeed mTaskSpeed;
			
		};

	}
}
#endif