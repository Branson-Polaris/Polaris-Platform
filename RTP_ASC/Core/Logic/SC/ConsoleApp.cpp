/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 ---------------------------- MODULE DESCRIPTION ----------------------------   
 	 It contains the Console App related implementation
***************************************************************************/

#include "ConsoleApp.h"
#include "DSPTask.h"
#include <sstream>
#include "MainTask.h"
#include "version_common.h"
#include "SC.h"
#include "SystemType.h"

/**************************************************************************//**
* \brief   - Initialize the member data with default values.
*
* \param   - None.
*
* \return  - None.
*
*****************************************************************************/
ConsoleApp::ConsoleApp()
{
	CP = CommonProperty::getInstance();
}


/**************************************************************************//**
* \brief   - Capture the user input to display in console terminal.
*
* \param   - None
*
* \return  - IRet - Returns captured integer value.
*
*****************************************************************************/
INT32 ConsoleApp::ConsoleRead(CA_ENTRY_TYPE entryType)
{
	char chInput;
	char temp[10] = {0x00};
	INT32 iRet 	 = 0;
	INT32 Digit  = 0;
	bool bIsNegativeNumber = false;

	while(cin.get(chInput))
	{
		if(chInput =='\n')
		{
			break;
		}
		else
		{
			if (entryType == CA_CHAR)
			{
				temp[0] = chInput;
				iRet = temp[0]; 
				break;
			}
			else
			{
				if(chInput == '-')
				{
					bIsNegativeNumber = true;
				}
				else
				{
					temp[0] = chInput;
					Digit = atoi(temp);
					iRet  = (iRet*10)+Digit;
				}
			}
		}				
	}
	cout << endl;
	if(bIsNegativeNumber)
	{
		iRet = -iRet;
	}
	return iRet;	
}


/**************************************************************************//**
* \brief   - Load the weld recipe with latest saved recipe
*
* \param   - None.
*
* \return  - None.
*
*****************************************************************************/
void ConsoleApp::SetWeldRecipe()
{	
	SetScWeldRecipe();
	SetPcWeldRecipe();
	SetAcWeldRecipe();
}

/**************************************************************************//**
* \brief   - Set the SC weld recipe with latest saved recipe on power up.
*
* \param   - None.
*
* \return  - None.
*
*****************************************************************************/
void ConsoleApp::SetScWeldRecipe()
{
	ParamDescriptor::MODEVALUE modeValue;
	auto &refScWeldRecipe = ScWeldRecipe::GetInstance();
	/* Default or latest modified recipe from consoleApp - Which is stored into WeldRecipe.txt or UpdateWeldRecipe.txt file in SD card */
	Console_WeldRecipe.SCData.WeldMode				= refScWeldRecipe.GetWeldMode();
	
	modeValue = {Console_WeldRecipe.SCData.WeldMode.Get(), refScWeldRecipe.GetModeValue()};
	Console_WeldRecipe.SCData.ModeValue				= modeValue;
	Console_WeldRecipe.SCData.HoldTime				= refScWeldRecipe.GetHoldTime();
	Console_WeldRecipe.SCData.AmplitudeStep[0]		= refScWeldRecipe.InitialAmplitude()/10;
}

/**************************************************************************//**
* \brief   - Set the PC weld recipe with latest saved recipe on power up.
*
* \param   - None.
*
* \return  - None.
*
*****************************************************************************/
void ConsoleApp::SetPcWeldRecipe()
{
	auto &refPcWeldRecipe = PcWeldRecipe::GetInstance();
	Console_WeldRecipe.PCData.StartFrequency	= refPcWeldRecipe.GetDigitalTuneWithOffsets();
	Console_WeldRecipe.PCData.DigitalTune		= refPcWeldRecipe.GetDigitalTune();
}

/**************************************************************************//**
* \brief   - Set the AC weld recipe with latest saved recipe on power up.
*
* \param   - None.
*
* \return  - None.
*
*****************************************************************************/
void ConsoleApp::SetAcWeldRecipe()
{
	Console_WeldRecipe.ACData.WeldForce	= AcWeldRecipe::GetInstance().GetWeldForce();
}

/**************************************************************************//**
* \brief   - Provides available functionality options to user.
*
* \param   - None
*
* \return  - None.
*
*****************************************************************************/
void ConsoleApp::ProcessUserOptions()
{
	INT32 iTimeout		= 0;
	char *pMsgStr 		= NULL;
	UINT32 iEvents		= 0;
	bool bValid			= true;
	ParamDescriptor::MODEVALUE modeValue;
	SystemFrequency objSystemFrequency;
	char chInput;
	//Takes user input Initially and display the user menu options.
	cin.get(chInput);					
	LOG("%s", KCYN);
	LOG("\n***** Select Operation *****\n");
	LOG(" 1.  Info\n");
	LOG(" 2.  Reset Alarms\n");
	LOG(" 3.  Weld Mode\n");
	LOG(" 4.  Weld Value\n");
	LOG(" 5.  Weld Amplitude\n");
	LOG(" 6.  Digital Tune\n");
	LOG(" 7.  Weld Hold\n");
	LOG(" 8.  Weld Amplitude Ramp Time\n");
	LOG(" 9.  Amplitude P\n");
	LOG(" 10. Amplitude I\n");
	LOG(" 11. Amplitude D\n");
	LOG(" 12. Phase P\n");
	LOG(" 13. Phase I\n");
	LOG(" 14. Phase D\n");
	LOG(" 15. Last Weld DSP Data\n");
	LOG(" 16. Perform Seek\n");
	LOG(" 17. End Of Weld Store Flag\n");
	LOG(" 18. Set System Frequency\n");
	LOG(" 19. Set System Type\n");
	LOG("\nEnter Selection: __>");
	LOG("%s", KNRM);

	auto &refPcWeldRecipe = PcWeldRecipe::GetInstance();
	auto &refScWeldRecipe = ScWeldRecipe::GetInstance();
	iChoice = ConsoleRead();
		
	switch(iChoice)
	{
		case CA_FW_INFO:
			// previously attained versions
			FWVersion::PrintVersion(FW_VERSION_SC);
			FWVersion::PrintVersion(FW_VERSION_AC);
			FWVersion::PrintVersion(FW_VERSION_PC);
			LOG("\n");
			LOG("System Type :%s\n", GetSystemTypeName().c_str());
			LOG("System Frequency :%d KHZ\n", objSystemFrequency.GetSystemFrequency());
			LOG("WELD MODE   :%d\n", refScWeldRecipe.GetWeldMode());
			LOG("WELD VALUE  :%d\n", refScWeldRecipe.GetModeValue());
			LOG("WELD STATE  :%d\n", SC::stateMachine->GetSCState());
			LOG("WELD AMP    :%d\n", refScWeldRecipe.InitialAmplitude()/10);				
			LOG("WELD FREQ   :%d\n", refPcWeldRecipe.GetDigitalTuneWithOffsets()/10);
			LOG("WELD HOLD   :%d\n", refScWeldRecipe.GetHoldTime());
			LOG("WELD AMP RAMP_TIME :%d\n", refPcWeldRecipe.GetWeldRampTime());
			LOG("AMPLITUDE P :%d\n", refPcWeldRecipe.GetAmplitudePGain());
			LOG("AMPLITUDE I :%d\n", refPcWeldRecipe.GetAmplitudeIGain());
			LOG("AMPLITUDE D :%d\n", refPcWeldRecipe.GetAmplitudeDGain());
			LOG("PHASE P :%d\n", refPcWeldRecipe.GetPhasePGain());
			LOG("PHASE I :%d\n", refPcWeldRecipe.GetPhaseIGain());
			LOG("PHASE D :%d\n", refPcWeldRecipe.GetPhaseDGain());
			if (SC::stateMachine->GetSCState() != SC_ALARM) CP->bConsoleScrollLock = false;
			break;
		
		case CA_RESET_ALARM:
			// let SC leave alarm state
			if (SC::stateMachine->GetSCState() == SC_ALARM)
			{
				message.msgID = TO_CTRL_TASK_RESET_ALARM_CMD;
				//Send request to control task to reset an alarm
				if(mq_timedsend(CP->GetMsgQId(CommonProperty::cTaskName[CTRL_T]), reinterpret_cast<char*>(&message), sizeof (message), 0, &NO_TIMEOUT) != ERROR)	
					LOG("\nCA_RESET_ALARM: success to send from  console\n");
				else
					LOGERR((char *)"\nCA_RESET_ALARM: Failure to send from console\n",0,0,0);
			}
			else
			{
				LOG(" Enter Reset Required: (y/n)__>");
				iChoice = ConsoleRead(CA_CHAR);
				if (iChoice == 'y')
					CP->bConsoleRestReq = true;
				else if (iChoice == 'n')
					CP->bConsoleRestReq = false;
			}
			break;
	
		case CA_WELD_MODE:
			LOG(" Enter WELD MODE: __>");
			iChoice = ConsoleRead();
			
			if (iChoice != 0)
			{
				// limit to time mode for now
				iChoice =  _CHECKMIN(iChoice,1);
				iChoice =  _CHECKMAX(iChoice,1);
				
				Console_WeldRecipe.SCData.WeldMode = iChoice;
				refScWeldRecipe.SetWeldRecipe(Console_WeldRecipe.SCData);
				LOG("\nWELD MODE: %d\n", refScWeldRecipe.GetWeldMode());				
			}
			break;
	
		case CA_WELD_VALUE:
			
			if (refScWeldRecipe.GetWeldMode() == TIMEMODE)
				LOG(" Enter WELD TIME (ms): __>");
			else if (refScWeldRecipe.GetWeldMode() == ENERGYMODE)
				LOG(" Enter WELD ENERGY (j): __>");
			else if (refScWeldRecipe.GetWeldMode() == PEAKPOWERMODE)
				LOG(" Enter WELD PEAK POWER (w): __>");
			else
				bValid = false;
	
			if (bValid)
			{
				iChoice = ConsoleRead();
				if (iChoice != 0)
				{
					iChoice =  _CHECKMIN(iChoice,10000);
					iChoice =  _CHECKMAX(iChoice,10);
					modeValue.mode = Console_WeldRecipe.SCData.WeldMode.Get();
					modeValue.value = iChoice;
					Console_WeldRecipe.SCData.ModeValue = modeValue;
					refScWeldRecipe.SetWeldRecipe(Console_WeldRecipe.SCData);
					LOG("\nWELD VALUE: %d\n", refScWeldRecipe.GetModeValue()); 
				}
			}
			break;
			
		case CA_WELD_AMP:
			
			LOG(" Enter WELD AMPLITUDE (%): __>");
			iChoice = ConsoleRead();
			
			if (iChoice != 0)
			{
				// normally thru HMI setup
				iChoice =  _CHECKMIN(iChoice,WELDAMPLITUDE_DEFAULT);
				iChoice =  _CHECKMAX(iChoice,PC_MIN_WeldAmplitude);
				
				Console_WeldRecipe.SCData.AmplitudeStep[0] = iChoice;
				refScWeldRecipe.SetWeldRecipe(Console_WeldRecipe.SCData);
				LOG("\nWELD AMPLITUDE: %d\n", refScWeldRecipe.InitialAmplitude()/10);				
			}
			break;
		case CA_DIGITAL_TUNE:
			
			LOG(" Enter DIGITAL TUNE (Hz): __>");
			iChoice = ConsoleRead();
			
			if (iChoice != 0)
			{
				// normally thru HMI setup
				FREQUENCY enSystemFrequency = objSystemFrequency.GetSystemFrequency();
				INT32 MaxLimit = F20KHZMAXABS;
				INT32 MinLimit = F20KHZMINABS;
				bool bErrorOccured = false;
				switch(enSystemFrequency)
				{
					case FREQ_20KHZ:
					{
						MaxLimit = F20KHZMAXABS;
						MinLimit = F20KHZMINABS;
					}
					break;
					
					case FREQ_30KHZ:
					{
						MaxLimit = F30KHZMAXABS;
						MinLimit = F30KHZMINABS;
					}
					break;
					
					case FREQ_40KHZ:
					{
						MaxLimit = F40KHZMAXABS;
						MinLimit = F40KHZMINABS;
					}
					break;
					
					default:
					{
						bErrorOccured = true;
					}
					break;				
				}
				
				if(bErrorOccured == false)
				{
					iChoice =  _CHECKMIN(iChoice,MaxLimit/DIGITAL_TUNE_IN_TENS_OF_HZ);
					iChoice =  _CHECKMAX(iChoice,MinLimit/DIGITAL_TUNE_IN_TENS_OF_HZ);
					
					Console_WeldRecipe.PCData.DigitalTune = iChoice * DIGITAL_TUNE_IN_TENS_OF_HZ;
					refPcWeldRecipe.SetDigitalTune(iChoice * DIGITAL_TUNE_IN_TENS_OF_HZ);
					//When a new digital tune value gets set, the memory offset should be set to 0.
					refPcWeldRecipe.SetMemoryOffset(0);
				}
				else
				{
					LOG("\nUnknown System Frequency detected: %d\n", enSystemFrequency);
				}
				
				LOG("\nDIGITAL TUNE: %d\n", refPcWeldRecipe.GetDigitalTune()/10);		
			}
			break;
			
		case CA_WELD_HOLD:
			
			LOG(" Enter HOLD TIME: (ms) __>");
			iChoice = ConsoleRead();
			
			if (iChoice != 0)
			{
				// normally thru HMI setup
				iChoice =  _CHECKMIN(iChoice,10000);
				iChoice =  _CHECKMAX(iChoice,10);
				
				Console_WeldRecipe.SCData.HoldTime = iChoice;
				refScWeldRecipe.SetWeldRecipe(Console_WeldRecipe.SCData);
				LOG("\nWELD HOLD: %d\n", refScWeldRecipe.GetHoldTime());
			}
			break;
			
		case CA_AMPLITUDE_RAMP_TIME:
			LOG(" Enter Weld Amplitude Ramp Time: (ms) __>");
			iChoice = ConsoleRead();
			
			if (iChoice != 0)
			{
				// normally thru HMI setup
				iChoice =  _CHECKMIN(iChoice,PC_MAX_WeldRampTime);
				iChoice =  _CHECKMAX(iChoice,PC_MIN_WeldRampTime);
				Console_WeldRecipe.PCData.WeldRampTime = iChoice;
				refPcWeldRecipe.SetWeldRecipe(Console_WeldRecipe.PCData);
				LOG("\nWeld Amplitude Ramp Time: %d\n", refPcWeldRecipe.GetWeldRampTime());				
			}
			break;
			
		case CA_AMPLITUDE_P:
			LOG(" Enter Amplitude P Value: __>");
			iChoice = ConsoleRead();
			Console_WeldRecipe.PCData.AmpProportionalGain = iChoice;
			refPcWeldRecipe.SetWeldRecipe(Console_WeldRecipe.PCData);
			LOG("\nAmplitude P Value: %d\n", refPcWeldRecipe.GetAmplitudePGain());				
			break;
					
		case CA_AMPLITUDE_I:
			LOG(" Enter Amplitude I Value: __>");
			iChoice = ConsoleRead();
			Console_WeldRecipe.PCData.AmpIntegralGain = iChoice;
			refPcWeldRecipe.SetWeldRecipe(Console_WeldRecipe.PCData);
			LOG("\nAmplitude I Value: %d\n", refPcWeldRecipe.GetAmplitudeIGain());				
			break;
			
		case CA_AMPLITUDE_D:
			LOG(" Enter Amplitude D Value: __>");
			iChoice = ConsoleRead();
			Console_WeldRecipe.PCData.AmpDerivativeGain = iChoice;
			refPcWeldRecipe.SetWeldRecipe(Console_WeldRecipe.PCData);
			LOG("\nAmplitude D Value: %d\n", refPcWeldRecipe.GetAmplitudeDGain());				
			break;
							
		case CA_PHASE_P:
			LOG(" Enter Phase P Value: __>");
			iChoice = ConsoleRead();
			Console_WeldRecipe.PCData.PhaseProportionalGain = iChoice;
			refPcWeldRecipe.SetWeldRecipe(Console_WeldRecipe.PCData);
			LOG("\nPhase P Value: %d\n", refPcWeldRecipe.GetPhasePGain());				
			break;
							
		case CA_PHASE_I:
			LOG(" Enter Phase I Value: __>");
			iChoice = ConsoleRead();
			Console_WeldRecipe.PCData.PhaseIntegralGain = iChoice;
			refPcWeldRecipe.SetWeldRecipe(Console_WeldRecipe.PCData);
			LOG("\nPhase I Value: %d\n",refPcWeldRecipe.GetPhaseIGain());				
			break;
			
		case CA_PHASE_D:
			LOG(" Enter Phase D Value: __>");
			iChoice = ConsoleRead();
			Console_WeldRecipe.PCData.PhaseDerivativeGain = iChoice;
			refPcWeldRecipe.SetWeldRecipe(Console_WeldRecipe.PCData);
			LOG("\nPhase D Value: %d\n", refPcWeldRecipe.GetPhaseDGain());				
			break;
			
		case CA_LAST_WELD_DSP_DATA:
			if(CP->m_vLastWeldDSPData.size() == 0)
			{
				std::cout << "No DSP Data available for last weld" << std::endl;
			}
			else
			{
				std::cout << "DspAmplitude,DspPhase,DspFrequency,DspCurrent,DspStatus" << std::endl;
				for (int nIndex = 0; nIndex < CP->m_vLastWeldDSPData.size(); nIndex++)
				{
					std::cout << CP->m_vLastWeldDSPData[nIndex].Entry0 << ',';
					std::cout << CP->m_vLastWeldDSPData[nIndex].Entry1/1000.0 << ',';
					std::cout << CP->m_vLastWeldDSPData[nIndex].Entry2 << ',';
					std::cout << CP->m_vLastWeldDSPData[nIndex].Entry3 << ',';
					std::cout << CP->m_vLastWeldDSPData[nIndex].Entry4  << '\n';
				}
			}
			break;

		case CA_PERFORM_SEEK:
		{
			//Perform Seek operation while entering through console menu
			Message SeekMessage = {0};
			SeekMessage.msgID = TO_CTRL_TASK_SEEK_CMD;	
			
			//Send request to control task to perform seek operation through console
			if(mq_timedsend(CP->GetMsgQId(CommonProperty::cTaskName[CTRL_T]), reinterpret_cast<char*>(&SeekMessage), sizeof (SeekMessage), 0, &NO_TIMEOUT) == ERROR)
				LOGERR((char *)"\nCA_PERFORM_SEEK: Failure to send SeekMessage from console\n",0,0,0);	
		}
		break;
			
		case CA_END_OF_WELD_STORE:
		{
			LOG(" Disable/Enable End Of Weld Store Flag: (0 - Disable, 1 - Enable) __>");
			iChoice = ConsoleRead();
			
			if(iChoice != 0 && iChoice != 1)
			{
				std::cout << "Enter Valid Choice" << std::endl;
			}
			else
			{
				Console_WeldRecipe.PCData.bEndOfWeldStore = iChoice;
				refPcWeldRecipe.SetEndOfWeldStore(iChoice);	
			}
			
			LOG("\nEnd Of Weld Store Flag Value: %d\n", refPcWeldRecipe.GetEndOfWeldStore());
		}
		break;
		
		case CA_SET_SYSTEM_FREQUENCY:
		{
			LOG(" Set System Frequency: ( Press 20 for 20KHZ, Press 30 for 30KHZ, Press 40 for 40KHZ ) __>");
			iChoice = ConsoleRead();
			
			if(iChoice != FREQ_20KHZ && iChoice != FREQ_30KHZ && iChoice != FREQ_40KHZ)
			{
				std::cout << "Enter Valid Choice" << std::endl;
			}
			else
			{
				objSystemFrequency.SetSystemFrequency((FREQUENCY)iChoice);
			}
			std::cout << "\nSystem Frequency Is: " << objSystemFrequency.GetSystemFrequency() << "KHZ\n" << std::endl;
		}
		break;
		
		case CA_SET_SYSTEM_TYPE:
		{
			LOG(" Set System Type: ( Press 1 for ACE Pro, Press 2 for ACE Pro Power Supply Only Mode) __>");
			iChoice = ConsoleRead();
			
			if ( SetSystemType((SYSTEM_TYPE)iChoice) == true )
			{
				std::cout << "System Type changed! Please Reboot the device for changes to take effect!" << std::endl;
			}
			else
			{
				std::cout << "Failure to set/store the System Type" << std::endl;
			}
		}
		break;
			
		default:
			if (iChoice == 0)
				CP->bConsoleScrollLock = true;
			break;
	}
	LOG("%s", KNRM);
}

/**************************************************************************//**
* \brief   - Get the task life time status.
*
* \param   - None
*
* \return  - bool.
*
*****************************************************************************/
bool ConsoleApp::bIsTaskRunStatus()
{
	return CP->bTaskRun;
}


/**************************************************************************//**
* \brief   - Cleans the memory related to ConsoleApp class.
*
* \param   - None.
*
* \return  - None.
*
*****************************************************************************/
ConsoleApp::~ConsoleApp()
{
	CP = NULL;
}

/**************************************************************************//**
* \brief   - Takes user input and displaying the user menu options.
* 			Fired initially from the control task and then rests unless an
* 			console event is sent. It can also be disabled.
* 			
* \param   - None.
*
* \return  - None.
*
*****************************************************************************/
void* ConsoleApp::ConsoleApp_Task(void *)
{	
	CommonProperty::getInstance()->SetTaskId(CommonProperty::cTaskName[CONSOLE_T], taskIdSelf());

	ConsoleApp *pConsole = new ConsoleApp();
	pConsole->PullActiveRecipeFromCP ();

	while(pConsole->bIsTaskRunStatus())
	{
		pConsole->ProcessUserOptions();
	}
	
	delete pConsole;
	pConsole = NULL;
	LOG("CONSOLE_T: ----------------Console Task Terminated----------------",0,0,0);
	taskDelete(taskIdSelf());
	return nullptr;
}


/**************************************************************************//**
* \brief   - Assigns default weld recipe values into console weld structures
* 			 from the CP (common part)
*
* \param   - None 
*
* \return  - None
*
******************************************************************************/
void ConsoleApp::PullActiveRecipeFromCP()
{
	// set local recipe to CP 
	SetWeldRecipe();
}

