/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/
#ifndef ACTUATORTASK_H_
#define ACTUATORTASK_H_

#include "Common.h"
#include "CommonProperty.h"
#include "SCTask.h"   
#include "CommunicationInterface.h"
#include "CommunicationInterface_ACT.h"
#include "WeldRecipe.h"

#define ACT_REQUEST_MSG_PAYLOAD_SIZE 20
#define SER_VER_NO_BUFF_SIZE         24
#define SER_VER_NO_HDR_SIZE          4
#define SER_VER_NO_SERIAL_SIZE       (SER_VER_NO_BUFF_SIZE-SER_VER_NO_HDR_SIZE)

class ActuatorTask : public SCTask
{
    
public:
	ActuatorTask();
	~ActuatorTask() {CP = NULL;}
	
	virtual void			ProcessTaskMessage		() {};
	
protected:
	
	int		SendMessageToClient	(Message& message, UINT32 msgLen);
	void	PrintRecipe			(WeldRecipeAC& weldRecipeAC);	
	char 						recvMsgBuffer[MAX_SIZE_OF_MSG_LENGTH];
	Message 					message;
	CommunicationInterface *	socketInterface;
};


// actuator process task extension
class ActuatorTaskProcess : public ActuatorTask
{
public:
	ActuatorTaskProcess();
	~ActuatorTaskProcess();
	
	void		ProcessTaskMessage				();
	void		ACTPdoUploadRequest 			();
	void 		CheckActTxPdo 					();	
	static 		void * Actuator_Process_Task 	(void *);

private:
	void 		ACTPdoDownloadRequest	();
	bool		bACTTxPdo;
	int			ind_ACTTxPdo;
};



//actuator system task extension
class ActuatorTaskSystem : public ActuatorTask
{
public:
	ActuatorTaskSystem();
	~ActuatorTaskSystem();
	
	void			ProcessTaskMessage			();
	void 			ACTSerVerNoRequest			();
	static 			void* Actuator_System_Task 	(void *);

private:
	bool			GetAcWeldRecipe		(char *pRecipe);
	WeldRecipeAC 			weldRecipeAC;

};


#endif /* ACTUATORTASK_H_ */
