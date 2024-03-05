/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

***************************************************************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------

This is the module for Control task which periodically executes state machine.

Module name: ControlTask

Filename:    ControlTask.h

-------------------------------------------------------------------------*/

#ifndef INC_CONTROLTASK_H_
#define INC_CONTROLTASK_H_

void ControlTask(void *arg);
void getpdo();

#endif /* INC_CONTROLTASK_H_ */
