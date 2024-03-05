/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/
#include  "ControlTask.h"
#include  "MainTask.h"
#include "ActuatorTask.h"
#include "WeldRecipe.h"
#include "SocketReceiver.h"

using namespace std;


ActuatorTask::ActuatorTask() {
	socketInterface = ACT_CommunicationInterface::getinstance();
	message.msgID = 0;
}

/**************************************************************************//**
* \brief  - sends messages to the actuator client via a socket connection
* 			
*
* \param  - Message& 	message 
* \param  - UINT32 		buffLen
*
* \return  - int bytesSent
*
******************************************************************************/
int ActuatorTask::SendMessageToClient(Message& message, UINT32 msgLen)
{
	Client_Message sendBuffer;
	char outBuf[MAX_SIZE_OF_MSG_LENGTH]	= {0x00};
	UINT32 iLen = 0;
	UINT32 bufLen= 0;
	int bytesSent = ERROR;

	SocketReceiver* pSocketReceiver;
	
	memset(sendBuffer.Buffer,0x00,sizeof(sendBuffer.Buffer));
	
	sendBuffer.msgID 	= message.msgID;
	sendBuffer.msgLen 	= msgLen;
	
	if(sendBuffer.msgLen < (MAX_SIZE_OF_MSG_LENGTH - sizeof(sendBuffer.msgID) - sizeof(sendBuffer.msgLen)))
	{
		memcpy(sendBuffer.Buffer,message.Buffer,sendBuffer.msgLen);
		iLen = sizeof(sendBuffer.msgID)+sizeof(sendBuffer.msgLen)+sendBuffer.msgLen;
		
		sendBuffer.crc32 =  pSocketReceiver->MessageCRCCal(sendBuffer);
		
		bufLen += (sizeof(sendBuffer.msgID)+sizeof(sendBuffer.msgLen));
		memcpy(outBuf, &sendBuffer, bufLen);
		
		memcpy(outBuf+bufLen, sendBuffer.Buffer, sendBuffer.msgLen);
		bufLen += sendBuffer.msgLen;
		
		memcpy(outBuf+bufLen, &sendBuffer.crc32, sizeof(sendBuffer.crc32));
		bufLen += sizeof(sendBuffer.crc32);
		
		bytesSent = socketInterface->Send (reinterpret_cast<char*>(outBuf),bufLen);

		if (bufLen != bytesSent)
			LOGERR((char *)"ActuatorTask : SendMessageToClient, ReqLen: %d bytesSent: %d",bufLen, bytesSent, 0);
	}
	else
	{
		LOGERR((char *)"ActuatorTask : SendMessageToClient, Invalid message limit : %d",sendBuffer.msgLen, 0, 0);
	}
	
	return bytesSent;
}


/**************************************************************************//**
* \brief  - Prints the current AC recipe
* 			
*
* \param  - WeldRecipeAC& weldRecipeAC
*
* \return  - None
*
******************************************************************************/
void ActuatorTask::PrintRecipe	(WeldRecipeAC& weldRecipeAC)
{
#ifdef ACTUATOR_DBG
	printf("---------AC WELD RECIPE BEFORE SENT-----------\n");
	printf("WeldForce			: %d\n",weldRecipeAC.WeldForce);
	printf("ForceRampTime		: %d\n",weldRecipeAC.ForceRampTime);
	printf("HoldMode			: %d\n",weldRecipeAC.HoldMode);
	printf("TotalCollapseTarget	: %d\n",weldRecipeAC.TotalCollapseTarget);
	printf("HoldForce			: %d\n",weldRecipeAC.HoldForce);
	printf("HoldForceRampTime	: %d\n",weldRecipeAC.HoldForceRampTime);
	printf("ExpectedPartContactPosition : %d\n",weldRecipeAC.ExpectedPartContactPosition);
	printf("ReadyPosition		: %d\n",weldRecipeAC.ReadyPosition);
	printf("DownAcceleration	: %d\n",weldRecipeAC.DownAcceleration);
	printf("DownMaxVelocity		: %d\n",weldRecipeAC.DownMaxVelocity);
	printf("DownDeceleration	: %d\n",weldRecipeAC.DownDeceleration);
	printf("ReturnAcceleration	: %d\n",weldRecipeAC.ReturnAcceleration);
	printf("ReturnMaxVelocity	: %d\n",weldRecipeAC.ReturnMaxVelocity);
	printf("ReturnDeceleration	: %d\n",weldRecipeAC.ReturnDeceleration);
	printf("EPCOffset			: %d\n",weldRecipeAC.ExpectedPartContactOffset);
	printf("PCWMinus			: %d\n",weldRecipeAC.PartContactWindowMinus);
	printf("PCWPlus				: %d\n",weldRecipeAC.PartContactWindowPlus);
	printf("NumForceSteps 		: 	%d\n",weldRecipeAC.NumForceSteps);
	printf("ReadyPositionToggle	: 	%d\n",weldRecipeAC.ReadyPositionToggle);
	printf("WeldForceControl	: 	%d\n",weldRecipeAC.WeldForceControl);
	
	for(int idx = 0; idx < weldRecipeAC.NumForceSteps; idx++)
	{
		printf("ForceStepForce[%d]	: %d\n",idx,weldRecipeAC.ForceStepForce[idx]);
		printf("ForceStepRampTime[%d] 	: %d\n",idx,weldRecipeAC.ForceStepRampTime[idx]);
	}
#endif
}
