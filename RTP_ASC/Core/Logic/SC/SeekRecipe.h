/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 
***************************************************************************/

#ifndef SEEKRECIPE_H_
#define SEEKRECIPE_H_

#include "Common.h"

//500 milliseconds
#define SEEK_TIME_DEFAULT					500
#define SEEK_FREQUENCY_OFFSET_20KDEFAULT	0
#define SEEK_FREQUENCY_OFFSET_30KDEFAULT	0
#define SEEK_FREQUENCY_OFFSET_40KDEFAULT	0
#define SEEK_MEMORY_CLEAR					0

typedef struct structSeekRecipe
{
	structSeekRecipe();
	void SetParametersAsPerSystemFrequency();
	
	INT32  SeekFreqLimitHigh;
	INT32  SeekFreqLimitLow;
	INT32  SeekFreqOffset;
	INT8   SeekMemClearBeforeSeek;
	UINT32 SeekTime;
	UINT32 SeekAmplitudeRampTime;
	UINT32 SeekAmplitude;
	INT32  SeekAmpProportionalGain;
	INT32  SeekAmpIntegralGain;
	INT32  SeekAmpDerivativeGain;
	INT32  SeekPhaseProportionalGain;
	INT32  SeekPhaseIntegralGain;
	INT32  SeekPhaseDerivativeGain;
}structSeekRecipe;

class SeekRecipe
{
public:
	SeekRecipe(const SeekRecipe& srcObj) = delete;
	SeekRecipe& operator=(const SeekRecipe& srcObj) = delete;
	static SeekRecipe& GetInstance();
	void SetParametersAsPerSystemFrequency();
	INT32 GetSeekFreqLimitHigh() const;
	INT32 GetSeekFreqLimitLow() const;
	INT32 GetSeekFreqOffset() const;
	INT8 GetSeekMemClearBeforeSeek() const;
	UINT32 GetSeekTime() const;
	UINT32 GetSeekAmplitudeRampTime() const;
	UINT32 GetSeekAmplitude() const;
	INT32 GetSeekAmpProportionalGain() const;
	INT32 GetSeekAmpIntegralGain() const;
	INT32 GetSeekAmpDerivativeGain() const;
	INT32 GetSeekPhaseProportionalGain() const;
	INT32 GetSeekPhaseIntegralGain() const;
	INT32 GetSeekPhaseDerivativeGain() const;
	void UpdateSeekRecipe(structSeekRecipe& recipe);
	structSeekRecipe&	GetSeekRecipe();
	
private:
	structSeekRecipe	m_Recipe;
	SeekRecipe();
	~SeekRecipe();
};

#endif /* SEEKRECIPE_H_ */
