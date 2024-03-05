/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
  		It handles process/system data from/to the SM and incoming messages.
***************************************************************************/

#ifndef POWERSUPPLYTASK_H_
#define POWERSUPPLYTASK_H_

#include "SCTask.h"

class PowerSupplyTask: public SCTask 
{
public:
	PowerSupplyTask											();
	virtual					~PowerSupplyTask				();
	void 					ProcessTaskMessage				(Message& message) override;
	
	virtual void			PDOUploadRequest 				() = 0;
	virtual void 			PDODownloadRequest				() = 0;
	
	static const unsigned int GetCoreState					();
	static void				SetCoreState					(unsigned int coreState);
	static 		void*		PowerSupply_Task				(void *);
	static PowerSupplyTask* GetInstance						();

	virtual 	void 		TurnOffSonics					() = 0;
	virtual 	void 		UpdateSeekParameters			() = 0;
	virtual 	void 		TurnOnSonics					() = 0;
	virtual 	void 		UpdateWeldParameters			() = 0;
	virtual 	void 		CaptureDSPData					() = 0;
	virtual 	UINT32 		GetTxFrequency					() = 0;
	virtual 	void 		SetRxStartFrequency				(UINT32) = 0;
	virtual 	void		UpdateRxMasterEvent				(UINT32) = 0;
private:
	static unsigned int CoreState;	
	static constexpr unsigned int SONICS_ON = 1;
};

#endif /* POWERSUPPLYTASK_H_ */
