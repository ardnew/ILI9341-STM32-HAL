/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usbpd_dpm_user.c
  * @author  MCD Application Team
  * @brief   USBPD DPM user code
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

#define USBPD_DPM_USER_C
/* Includes ------------------------------------------------------------------*/
#include "usbpd_core.h"
#include "usbpd_pdo_defs.h"
#include "usbpd_dpm_core.h"
#include "usbpd_dpm_conf.h"
#include "usbpd_dpm_user.h"
#include "usbpd_vdm_user.h"
#if defined(_TRACE)
#include "usbpd_trace.h"
#include "stdio.h"
#endif /* _TRACE */
#include "usbpd_pwr_if.h"
#include "string.h"
#include "cmsis_os.h"
#include "usbpd_pwr_user.h"

/** @addtogroup STM32_USBPD_APPLICATION
  * @{
  */

/** @addtogroup STM32_USBPD_APPLICATION_DPM_USER
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN Private_Typedef */

/* USER CODE END Private_Typedef */

/* Private define ------------------------------------------------------------*/
/** @defgroup USBPD_USER_PRIVATE_DEFINES USBPD USER Private Defines
  * @{
  */
#if (osCMSIS < 0x20000U)
void                USBPD_DPM_UserExecute(void const *argument);
#else
void                USBPD_DPM_UserExecute(void *argument);
#endif /* osCMSIS < 0x20000U */
/* USER CODE BEGIN Private_Define */

/* USER CODE END Private_Define */

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/** @defgroup USBPD_USER_PRIVATE_MACROS USBPD USER Private Macros
  * @{
  */
#if defined(_TRACE)
#define DPM_USER_DEBUG_TRACE_SIZE       40u
#define DPM_USER_DEBUG_TRACE(_PORT_, ...)  do {                                          \
      char _str[DPM_USER_DEBUG_TRACE_SIZE];                                                                    \
      uint8_t _size = snprintf(_str, DPM_USER_DEBUG_TRACE_SIZE, __VA_ARGS__);                                  \
      if (_size < DPM_USER_DEBUG_TRACE_SIZE)                                                                   \
        USBPD_TRACE_Add(USBPD_TRACE_DEBUG, (uint8_t)(_PORT_), 0, (uint8_t*)_str, strlen(_str));  \
      else                                                                              \
        USBPD_TRACE_Add(USBPD_TRACE_DEBUG, (uint8_t)(_PORT_), 0, (uint8_t*)_str, DPM_USER_DEBUG_TRACE_SIZE);   \
 } while(0)
#else
#define DPM_USER_DEBUG_TRACE(_PORT_, ...)
#endif /* _TRACE */
/* USER CODE BEGIN Private_Macro */

/* USER CODE END Private_Macro */
/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/** @defgroup USBPD_USER_PRIVATE_VARIABLES USBPD USER Private Variables
  * @{
  */
/* USER CODE BEGIN Private_Variables */
extern USBPD_ParamsTypeDef DPM_Params[USBPD_PORT_COUNT];
/* USER CODE END Private_Variables */
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup USBPD_USER_PRIVATE_FUNCTIONS USBPD USER Private Functions
  * @{
  */
/* USER CODE BEGIN USBPD_USER_PRIVATE_FUNCTIONS_Prototypes */
static int32_t DPM_FindVoltageIndex(
    uint32_t PortNum,
    USBPD_SNKPowerRequest_TypeDef* PtrRequestedPower
);
static void DPM_SNK_GetSelectedPDO(
    uint8_t PortNum,
    uint8_t IndexSrcPDO,
    uint16_t RequestedVoltage,
    USBPD_SNKRDO_TypeDef* Rdo,
    USBPD_CORE_PDO_Type_TypeDef *PtrPowerObject
);
/* USER CODE END USBPD_USER_PRIVATE_FUNCTIONS_Prototypes */
/**
  * @}
  */

/* Exported functions ------- ------------------------------------------------*/
/** @defgroup USBPD_USER_EXPORTED_FUNCTIONS USBPD USER Exported Functions
  * @{
  */
/* USER CODE BEGIN USBPD_USER_EXPORTED_FUNCTIONS */

/* USER CODE END USBPD_USER_EXPORTED_FUNCTIONS */

/** @defgroup USBPD_USER_EXPORTED_FUNCTIONS_GROUP1 USBPD USER Exported Functions called by DPM CORE
  * @{
  */
/* USER CODE BEGIN USBPD_USER_EXPORTED_FUNCTIONS_GROUP1 */

/* USER CODE END USBPD_USER_EXPORTED_FUNCTIONS_GROUP1 */

/**
  * @brief  Initialize DPM (port power role, PWR_IF, CAD and PE Init procedures)
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_UserInit(void)
{
/* USER CODE BEGIN USBPD_DPM_UserInit */
  USBPD_PWR_IF_Init();

  return USBPD_OK;
/* USER CODE END USBPD_DPM_UserInit */
}

/**
  * @brief  User delay implementation which is OS dependant
  * @param  Time time in ms
  * @retval None
  */
void USBPD_DPM_WaitForTime(uint32_t Time)
{
/* USER CODE BEGIN USBPD_DPM_WaitForTime */
  osDelay(Time);
/* USER CODE END USBPD_DPM_WaitForTime */
}

/**
  * @brief  User processing time, it is recommended to avoid blocking task for long time
  * @param  argument  DPM User event
  * @retval None
  */
#if (osCMSIS < 0x20000U)
void USBPD_DPM_UserExecute(void const *argument)
#else
void USBPD_DPM_UserExecute(void *argument)
#endif /* osCMSIS < 0x20000U */
{
/* USER CODE BEGIN USBPD_DPM_UserExecute */

/* USER CODE END USBPD_DPM_UserExecute */
}

/**
  * @brief  UserCableDetection reporting events on a specified port from CAD layer.
  * @param  PortNum The handle of the port
  * @param  State CAD state
  * @retval None
  */
void USBPD_DPM_UserCableDetection(uint8_t PortNum, USBPD_CAD_EVENT State)
{
  switch(State)
  {
  case USBPD_CAD_EVENT_ATTEMC:
    DPM_Ports[PortNum].DPM_IsConnected = 1;
    break;

  case USBPD_CAD_EVENT_ATTACHED:
   /* Format and send a notification to GUI if enabled */
    DPM_Ports[PortNum].DPM_IsConnected = 1;
    break;

  case USBPD_CAD_EVENT_DETACHED:
  case USBPD_CAD_EVENT_EMC:
  default:
    //LED_OFF(LED2_WHITE);

    /* reset all values received from port partner */
    memset(&DPM_Ports[PortNum], 0, sizeof(DPM_Ports[PortNum]));
    break;

  }
/* USER CODE BEGIN USBPD_DPM_UserCableDetection */
/* USER CODE END USBPD_DPM_UserCableDetection */
}

/**
  * @brief  function used to manage user timer.
  * @param  PortNum Port number
  * @retval None
  */
void USBPD_DPM_UserTimerCounter(uint8_t PortNum)
{
/* USER CODE BEGIN USBPD_DPM_UserTimerCounter */

/* USER CODE END USBPD_DPM_UserTimerCounter */
}

/**
  * @}
  */

/** @defgroup USBPD_USER_EXPORTED_FUNCTIONS_GROUP2 USBPD USER Exported Callbacks functions called by PE
  * @{
  */

/**
  * @brief  Callback function called by PE layer when HardReset message received from PRL
  * @param  PortNum The current port number
  * @param  CurrentRole the current role
  * @param  Status status on hard reset event
  * @retval None
  */
void USBPD_DPM_HardReset(uint8_t PortNum, USBPD_PortPowerRole_TypeDef CurrentRole, USBPD_HR_Status_TypeDef Status)
{
/* USER CODE BEGIN USBPD_DPM_HardReset */
  DPM_USER_DEBUG_TRACE(PortNum, "HELP: update USBPD_DPM_HardReset");
/* USER CODE END USBPD_DPM_HardReset */
}

/**
  * @brief  Request the DPM to setup the new power level.
  * @param  PortNum The current port number
  * @retval USBPD status
  */
USBPD_StatusTypeDef USBPD_DPM_SetupNewPower(uint8_t PortNum)
{
/* USER CODE BEGIN USBPD_DPM_SetupNewPower */
  return USBPD_PWR_IF_SetProfile(PortNum);
/* USER CODE END USBPD_DPM_SetupNewPower */
}

/**
  * @brief  Evaluate the swap request from PE.
  * @param  PortNum The current port number
  * @retval USBPD_ACCEPT, USBPD_WAIT, USBPD_REJECT
  */
USBPD_StatusTypeDef USBPD_DPM_EvaluatePowerRoleSwap(uint8_t PortNum)
{
/* USER CODE BEGIN USBPD_DPM_EvaluatePowerRoleSwap */
  return USBPD_REJECT;
/* USER CODE END USBPD_DPM_EvaluatePowerRoleSwap */
}

/**
  * @brief  Callback function called by PE to inform DPM about PE event.
  * @param  PortNum The current port number
  * @param  EventVal @ref USBPD_NotifyEventValue_TypeDef
  * @retval None
  */
void USBPD_DPM_Notification(uint8_t PortNum, USBPD_NotifyEventValue_TypeDef EventVal)
{
/* USER CODE BEGIN USBPD_DPM_Notification */
  switch(EventVal)
  {
    /***************************************************************************
                              Power Notification
    */
    case USBPD_NOTIFY_POWER_EXPLICIT_CONTRACT:
      /* Power ready means an explicit contract has been establish and Power is available */
      /* Turn On VBUS LED when an explicit contract is established */
      //LED_ON(LED2_WHITE);
      break;
    /*
                              End Power Notification
     ***************************************************************************/
    /***************************************************************************
                               REQUEST ANSWER NOTIFICATION
    */
    case USBPD_NOTIFY_REQUEST_ACCEPTED:
      /* Update DPM_RDOPosition only if current role is SNK */
      if (USBPD_PORTPOWERROLE_SNK == DPM_Params[PortNum].PE_PowerRole)
      {
        USBPD_SNKRDO_TypeDef rdo;
        rdo.d32 = DPM_Ports[PortNum].DPM_RequestDOMsg;
        DPM_Ports[PortNum].DPM_RDOPosition = rdo.GenericRDO.ObjectPosition;
      }
    break;
    /*
                              End REQUEST ANSWER NOTIFICATION
     ***************************************************************************/
    case USBPD_NOTIFY_STATE_SNK_READY:
      {
      }
      break;

    case USBPD_NOTIFY_STATE_SRC_DISABLED:
      {
        /* SINK Port Partner is not PD capable. Legacy cable may have been connected
           In this state, VBUS is set to 5V */
      }
      break;
    default :
      break;
  }
/* USER CODE END USBPD_DPM_Notification */
}

/**
  * @brief  DPM callback to allow PE to retrieve information from DPM/PWR_IF.
  * @param  PortNum Port number
  * @param  DataId  Type of data to be updated in DPM based on @ref USBPD_CORE_DataInfoType_TypeDef
  * @param  Ptr     Pointer on address where DPM data should be written (u8 pointer)
  * @param  Size    Pointer on nb of u8 written by DPM
  * @retval None
  */
void USBPD_DPM_GetDataInfo(uint8_t PortNum, USBPD_CORE_DataInfoType_TypeDef DataId, uint8_t *Ptr, uint32_t *Size)
{
/* USER CODE BEGIN USBPD_DPM_GetDataInfo */
  uint32_t index = 0;

  /* Check type of information targeted by request */
  switch (DataId)
  {
    /* Case Port Source PDO Data information :
    Case Port SINK PDO Data information :
    Call PWR_IF PDO reading request.
    */
    case USBPD_CORE_DATATYPE_SRC_PDO:
    case USBPD_CORE_DATATYPE_SNK_PDO:
      USBPD_PWR_IF_GetPortPDOs(PortNum, DataId, Ptr, Size);
      *Size *= 4;
      break;

    /* Case Port Received Source PDO Data information (from distant port) */
    case USBPD_CORE_DATATYPE_RCV_SRC_PDO:
      for(index = 0; index < DPM_Ports[PortNum].DPM_NumberOfRcvSRCPDO; index++)
        { *(uint32_t*)(Ptr + index) = DPM_Ports[PortNum].DPM_ListOfRcvSRCPDO[index]; }
      *Size = (DPM_Ports[PortNum].DPM_NumberOfRcvSRCPDO * 4);
      break;

    /* Case Port Received Sink PDO Data information (from distant port) */
    case USBPD_CORE_DATATYPE_RCV_SNK_PDO:
      for(index = 0; index < DPM_Ports[PortNum].DPM_NumberOfRcvSNKPDO; index++)
        { *(uint32_t*)(Ptr + index) = DPM_Ports[PortNum].DPM_ListOfRcvSNKPDO[index]; }
      *Size = (DPM_Ports[PortNum].DPM_NumberOfRcvSNKPDO * 4);
      break;

    /* Case Requested voltage value Data information */
    case USBPD_CORE_DATATYPE_REQ_VOLTAGE:
      *Ptr = DPM_Ports[PortNum].DPM_RequestedVoltage;
      *Size = 4;
      break;

    /* Case Request message DO (from Sink to Source) Data information */
    case USBPD_CORE_DATATYPE_REQUEST_DO:
      *Ptr = DPM_Ports[PortNum].DPM_RequestDOMsg;
      *Size = 4;
      break;

    default:
      *Size = 0;
      break;

//  case USBPD_CORE_DATATYPE_SNK_PDO:           /*!< Handling of port Sink PDO, requested by get sink capa*/
//  case USBPD_CORE_EXTENDED_CAPA:              /*!< Source Extended capability message content          */
//  case USBPD_CORE_DATATYPE_REQ_VOLTAGE:       /*!< Get voltage value requested for BIST tests, expect 5V*/
//  case USBPD_CORE_INFO_STATUS:                /*!< Information status message content                  */
//  case USBPD_CORE_MANUFACTURER_INFO:          /*!< Retrieve of Manufacturer info message content       */
//  case USBPD_CORE_BATTERY_STATUS:             /*!< Retrieve of Battery status message content          */
//  case USBPD_CORE_BATTERY_CAPABILITY:         /*!< Retrieve of Battery capability message content      */
  }
/* USER CODE END USBPD_DPM_GetDataInfo */
}

/**
  * @brief  DPM callback to allow PE to update information in DPM/PWR_IF.
  * @param  PortNum Port number
  * @param  DataId  Type of data to be updated in DPM based on @ref USBPD_CORE_DataInfoType_TypeDef
  * @param  Ptr     Pointer on the data
  * @param  Size    Nb of bytes to be updated in DPM
  * @retval None
  */
void USBPD_DPM_SetDataInfo(uint8_t PortNum, USBPD_CORE_DataInfoType_TypeDef DataId, uint8_t *Ptr, uint32_t Size)
{
/* USER CODE BEGIN USBPD_DPM_SetDataInfo */

  uint32_t index;

  // Check type of information targeted by request
  switch (DataId)
  {
    // Case requested DO position Data information :
    case USBPD_CORE_DATATYPE_RDO_POSITION:
      if (Size == 4)
      {
        DPM_Ports[PortNum].DPM_RDOPosition = *Ptr;
        DPM_Ports[PortNum].DPM_RDOPositionPrevious = *Ptr;
      }
      break;

    // Case requested Voltage Data information :
    case USBPD_CORE_DATATYPE_REQ_VOLTAGE:
      if (Size == 4)
        { DPM_Ports[PortNum].DPM_RequestedVoltage = *Ptr; }
      break;

    // Case Received Source PDO values Data information :
    case USBPD_CORE_DATATYPE_RCV_SRC_PDO:
      if (Size <= (USBPD_MAX_NB_PDO * 4))
      {
        DPM_Ports[PortNum].DPM_NumberOfRcvSRCPDO = (Size / 4);
        /* Copy PDO data in DPM Handle field */
        for (index = 0; index < (Size / 4); index++)
          { DPM_Ports[PortNum].DPM_ListOfRcvSRCPDO[index] = LE32(Ptr + index); }
      }
      break;

    // Case Received Sink PDO values Data information :
    case USBPD_CORE_DATATYPE_RCV_SNK_PDO:
      if (Size <= (USBPD_MAX_NB_PDO * 4))
      {
        DPM_Ports[PortNum].DPM_NumberOfRcvSNKPDO = (Size / 4);
        /* Copy PDO data in DPM Handle field */
        for (index = 0; index < (Size / 4); index++)
          { DPM_Ports[PortNum].DPM_ListOfRcvSNKPDO[index] = LE32(Ptr + index); }
      }
      break;

    // Case Received Request PDO Data information :
    case USBPD_CORE_DATATYPE_RCV_REQ_PDO:
      if (Size == 4)
        { DPM_Ports[PortNum].DPM_RcvRequestDOMsg = *Ptr; }
      break;

    // Case Request message DO (from Sink to Source) Data information :
    case USBPD_CORE_DATATYPE_REQUEST_DO:
      if (Size == 4)
        { DPM_Ports[PortNum].DPM_RcvRequestDOMsg = *Ptr; }
      break;

    // In case of unexpected data type (Set request could not be fulfilled) :
    default :
      break;

//  case USBPD_CORE_DATATYPE_RDO_POSITION:      /*!< Reset the PDO position selected by the sink only */
//  case USBPD_CORE_DATATYPE_RCV_SRC_PDO:       /*!< Storage of Received Source PDO values        */
//  case USBPD_CORE_DATATYPE_RCV_SNK_PDO:       /*!< Storage of Received Sink PDO values          */
//  case USBPD_CORE_EXTENDED_CAPA:              /*!< Source Extended capability message content   */
//  case USBPD_CORE_PPS_STATUS:                 /*!< PPS Status message content                   */
//  case USBPD_CORE_INFO_STATUS:                /*!< Information status message content           */
//  case USBPD_CORE_ALERT:                      /*!< Storing of received Alert message content    */
//  case USBPD_CORE_GET_MANUFACTURER_INFO:      /*!< Storing of received Get Manufacturer info message content */
//  case USBPD_CORE_GET_BATTERY_STATUS:         /*!< Storing of received Get Battery status message content    */
//  case USBPD_CORE_GET_BATTERY_CAPABILITY:     /*!< Storing of received Get Battery capability message content*/
//  case USBPD_CORE_SNK_EXTENDED_CAPA:          /*!< Storing of Sink Extended capability message content       */
  }

/* USER CODE END USBPD_DPM_SetDataInfo */

}

/**
  * @brief  Evaluate received Request Message from Sink port
  * @param  PortNum Port number
  * @param  PtrPowerObject  Pointer on the power data object
  * @retval USBPD status : USBPD_ACCEPT, USBPD_REJECT, USBPD_WAIT, USBPD_GOTOMIN
  */
USBPD_StatusTypeDef USBPD_DPM_EvaluateRequest(uint8_t PortNum, USBPD_CORE_PDO_Type_TypeDef *PtrPowerObject)
{
/* USER CODE BEGIN USBPD_DPM_EvaluateRequest */
  DPM_USER_DEBUG_TRACE(PortNum, "HELP: update USBPD_DPM_EvaluateRequest");
  return USBPD_REJECT;
/* USER CODE END USBPD_DPM_EvaluateRequest */
}

/**
  * @brief  Evaluate received Capabilities Message from Source port and prepare the request message
  * @param  PortNum         Port number
  * @param  PtrRequestData  Pointer on selected request data object
  * @param  PtrPowerObjectType  Pointer on the power data object
  * @retval None
  */
void USBPD_DPM_SNK_EvaluateCapabilities(uint8_t PortNum, uint32_t *PtrRequestData, USBPD_CORE_PDO_Type_TypeDef *PtrPowerObjectType)
{
/* USER CODE BEGIN USBPD_DPM_SNK_EvaluateCapabilities */

  USBPD_PDO_TypeDef pdo;
  USBPD_SNKRDO_TypeDef rdo;
  USBPD_HandleTypeDef *pdhandle = &DPM_Ports[PortNum];
  USBPD_USER_SettingsTypeDef *puser =
    (USBPD_USER_SettingsTypeDef *)&DPM_USER_Settings[PortNum];

  pdhandle->DPM_RequestedVoltage = 0;

  /* Find the Pdo index for the requested voltage */
  int32_t pdoindex = DPM_FindVoltageIndex(PortNum, &(puser->DPM_SNKRequestedPower));

  /* Initialize RDO */
  rdo.d32 = 0;

  /* If could not find desired pdo index, then return error */
  if (pdoindex == -1)
  {
    //LED_OFF(LED2_WHITE);

    rdo.FixedVariableRDO.ObjectPosition = 1;
    rdo.FixedVariableRDO.OperatingCurrentIn10mAunits =
      puser->DPM_SNKRequestedPower.MaxOperatingCurrentInmAunits / 10;
    rdo.FixedVariableRDO.MaxOperatingCurrent10mAunits =
      puser->DPM_SNKRequestedPower.MaxOperatingCurrentInmAunits / 10;
    rdo.FixedVariableRDO.CapabilityMismatch = 1;
    DPM_Ports[PortNum].DPM_RequestedCurrent =
      puser->DPM_SNKRequestedPower.MaxOperatingCurrentInmAunits;
    /* USBPD_DPM_EvaluateCapabilities: Mismatch, could not find desired pdo index */

    pdhandle->DPM_RequestDOMsg = rdo.d32;
    *PtrRequestData = rdo.d32;
    return;
  }

  /* Extract power information from Power Data Object */
  pdo.d32 = pdhandle->DPM_ListOfRcvSRCPDO[pdoindex];

  /* Set the Object position */
  USBPD_PDO_TypeDef snkFixedPDO;
  uint32_t size = 0;
  uint32_t mV = 0;
  uint32_t mA = 0;
  uint32_t mW = 0;

  USBPD_PWR_IF_GetPortPDOs(PortNum, USBPD_CORE_DATATYPE_SNK_PDO, (uint8_t *)&snkFixedPDO.d32, &size);
  rdo.GenericRDO.ObjectPosition           = pdoindex + 1;
  rdo.GenericRDO.NoUSBSuspend             = 1;
  rdo.GenericRDO.USBCommunicationsCapable = snkFixedPDO.SNKFixedPDO.USBCommunicationsCapable;

  *PtrPowerObjectType = pdo.GenericPDO.PowerObject;

  switch(pdo.GenericPDO.PowerObject)
  {
  case USBPD_CORE_PDO_TYPE_FIXED:
    {
      USBPD_SRCFixedSupplyPDO_TypeDef fixedpdo = pdo.SRCFixedPDO;
      mV = PWR_DECODE_50MV(fixedpdo.VoltageIn50mVunits);
      mA = PWR_DECODE_10MA(fixedpdo.MaxCurrentIn10mAunits);
      mA = USBPD_MIN(mA, puser->DPM_SNKRequestedPower.MaxOperatingCurrentInmAunits);
      mW = mA * mV; /* mW */
      DPM_Ports[PortNum].DPM_RequestedCurrent = mA;
      rdo.FixedVariableRDO.OperatingCurrentIn10mAunits  = mA / 10;
      rdo.FixedVariableRDO.MaxOperatingCurrent10mAunits = mA / 10;
      if (mW < puser->DPM_SNKRequestedPower.OperatingPowerInmWunits)
      {
        rdo.FixedVariableRDO.MaxOperatingCurrent10mAunits = puser->DPM_SNKRequestedPower.MaxOperatingCurrentInmAunits / 10;
        rdo.FixedVariableRDO.CapabilityMismatch = 1;
        /* USBPD_DPM_EvaluateCapabilities: Mismatch, less power offered than the operating power */
      }
    }
    break;
  case USBPD_CORE_PDO_TYPE_BATTERY:
    {
      USBPD_SRCBatterySupplyPDO_TypeDef batterypdo = pdo.SRCBatteryPDO;
      mV = PWR_DECODE_50MV(batterypdo.MinVoltageIn50mVunits);
      mW = PWR_DECODE_MW(batterypdo.MaxAllowablePowerIn250mWunits);
      mW = USBPD_MIN(mW, puser->DPM_SNKRequestedPower.MaxOperatingPowerInmWunits); /* mW */
      mA = mW / mV; /* mA */
      mA = USBPD_MIN(mA, puser->DPM_SNKRequestedPower.MaxOperatingCurrentInmAunits);
      DPM_Ports[PortNum].DPM_RequestedCurrent       = mA;
      mW = mA * mV; /* mW */
      rdo.BatteryRDO.ObjectPosition                 = pdoindex + 1;
      rdo.BatteryRDO.OperatingPowerIn250mWunits     = mW / 250;
      rdo.BatteryRDO.MaxOperatingPowerIn250mWunits  = mW / 250;
      if (mW < puser->DPM_SNKRequestedPower.OperatingPowerInmWunits)
      {
        rdo.BatteryRDO.CapabilityMismatch = 1;
        /* Mismatch, less power offered than the operating power */
      }
      /* USBPD_DPM_EvaluateCapabilities: Battery Request Data Object %u: %d mW", rdo.d32, mw */
    }
    break;
  case USBPD_CORE_PDO_TYPE_VARIABLE:
    {
      //USBPD_SRCVariableSupplyPDO_TypeDef variablepdo = pdo.SRCVariablePDO;
    }
    break;
  default:
    break;
  }

  pdhandle->DPM_RequestDOMsg = rdo.d32;

  *PtrRequestData = pdhandle->DPM_RequestDOMsg;
  /* Get the requested voltage */
  pdhandle->DPM_RequestedVoltage = mV;

/* USER CODE END USBPD_DPM_SNK_EvaluateCapabilities */
}

/**
  * @brief  Power role swap status update
  * @param  PortNum Port number
  * @param  CurrentRole the current role
  * @param  Status status on power role swap event
  */
void USBPD_DPM_PowerRoleSwap(uint8_t PortNum, USBPD_PortPowerRole_TypeDef CurrentRole, USBPD_PRS_Status_TypeDef Status)
{
/* USER CODE BEGIN USBPD_DPM_PowerRoleSwap */
  DPM_USER_DEBUG_TRACE(PortNum, "HELP: update USBPD_DPM_PowerRoleSwap");
/* USER CODE END USBPD_DPM_PowerRoleSwap */
}

/**
  * @brief  Callback to be used by PE to evaluate a Vconn swap
  * @param  PortNum Port number
  * @retval USBPD_ACCEPT, USBPD_REJECT, USBPD_WAIT
  */
USBPD_StatusTypeDef USBPD_DPM_EvaluateVconnSwap(uint8_t PortNum)
{
/* USER CODE BEGIN USBPD_DPM_EvaluateVconnSwap */
  return USBPD_REJECT;
/* USER CODE END USBPD_DPM_EvaluateVconnSwap */
}

/**
  * @brief  Callback to be used by PE to manage VConn
  * @param  PortNum Port number
  * @param  State Enable or Disable VConn on CC lines
  * @retval USBPD_ACCEPT, USBPD_REJECT
  */
USBPD_StatusTypeDef USBPD_DPM_PE_VconnPwr(uint8_t PortNum, USBPD_FunctionalState State)
{
/* USER CODE BEGIN USBPD_DPM_PE_VconnPwr */
  return USBPD_ERROR;
/* USER CODE END USBPD_DPM_PE_VconnPwr */
}

/**
  * @brief  DPM callback to allow PE to forward extended message information.
  * @param  PortNum Port number
  * @param  MsgType Type of message to be handled in DPM
  *         This parameter can be one of the following values:
  *           @arg @ref USBPD_EXT_SECURITY_REQUEST Security Request extended message
  *           @arg @ref USBPD_EXT_SECURITY_RESPONSE Security Response extended message
  * @param  ptrData   Pointer on address Extended Message data could be read (u8 pointer)
  * @param  DataSize  Nb of u8 that compose Extended message
  * @retval None
  */
void USBPD_DPM_ExtendedMessageReceived(uint8_t PortNum, USBPD_ExtendedMsg_TypeDef MsgType, uint8_t *ptrData, uint16_t DataSize)
{
/* USER CODE BEGIN USBPD_DPM_ExtendedMessageReceived */

/* USER CODE END USBPD_DPM_ExtendedMessageReceived */
}

/**
  * @brief  DPM callback used to know user choice about Data Role Swap.
  * @param  PortNum Port number
  * @retval USBPD_REJECT, UBPD_ACCEPT
  */
USBPD_StatusTypeDef USBPD_DPM_EvaluateDataRoleSwap(uint8_t PortNum)
{
/* USER CODE BEGIN USBPD_DPM_EvaluateDataRoleSwap */
  return USBPD_REJECT;
/* USER CODE END USBPD_DPM_EvaluateDataRoleSwap */
}

/**
  * @brief  Callback to be used by PE to check is VBUS is ready or present
  * @param  PortNum Port number
  * @param  Vsafe   Vsafe status based on @ref USBPD_VSAFE_StatusTypeDef
  * @retval USBPD_DISABLE or USBPD_ENABLE
  */
USBPD_FunctionalState USBPD_DPM_IsPowerReady(uint8_t PortNum, USBPD_VSAFE_StatusTypeDef Vsafe)
{
/* USER CODE BEGIN USBPD_DPM_IsPowerReady */
  return ((USBPD_OK == USBPD_PWR_IF_SupplyReady(PortNum, Vsafe)) ? USBPD_ENABLE : USBPD_DISABLE);
/* USER CODE END USBPD_DPM_IsPowerReady */
}

/**
  * @}
  */

/** @defgroup USBPD_USER_EXPORTED_FUNCTIONS_GROUP3 USBPD USER Functions PD messages requests
  * @{
  */

/**
  * @brief  Request the PE to send a hard reset
  * @param  PortNum The current port number
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestHardReset(uint8_t PortNum)
{
  return USBPD_PE_Request_HardReset(PortNum);
}

/**
  * @brief  Request the PE to send a cable reset.
  * @note   Only a DFP Shall generate Cable Reset Signaling. A DFP Shall only generate Cable Reset Signaling within an Explicit Contract.
            The DFP has to be supplying VCONN prior to a Cable Reset
  * @param  PortNum The current port number
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestCableReset(uint8_t PortNum)
{
  return USBPD_PE_Request_CableReset(PortNum);
}

/**
  * @brief  Request the PE to send a GOTOMIN message
  * @param  PortNum The current port number
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestGotoMin(uint8_t PortNum)
{
  return USBPD_PE_Request_CtrlMessage(PortNum, USBPD_CONTROLMSG_GOTOMIN, USBPD_SOPTYPE_SOP);
}

/**
  * @brief  Request the PE to send a PING message
  * @note   In USB-PD stack, only ping management for P3.0 is implemented.
  *         If PD2.0 is used, PING timer needs to be implemented on user side.
  * @param  PortNum The current port number
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestPing(uint8_t PortNum)
{
  return USBPD_PE_Request_CtrlMessage(PortNum, USBPD_CONTROLMSG_PING, USBPD_SOPTYPE_SOP);
}

/**
  * @brief  Request the PE to send a request message.
  * @param  PortNum     The current port number
  * @param  IndexSrcPDO Index on the selected SRC PDO (value between 1 to 7)
  * @param  RequestedVoltage Requested voltage (in MV and use mainly for APDO)
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestMessageRequest(uint8_t PortNum, uint8_t IndexSrcPDO, uint16_t RequestedVoltage)
{
/* USER CODE BEGIN USBPD_DPM_RequestMessageRequest */
  USBPD_StatusTypeDef status = USBPD_ERROR;
  USBPD_SNKRDO_TypeDef rdo;
  USBPD_CORE_PDO_Type_TypeDef pdo_object;

  rdo.d32 = 0;

  DPM_SNK_GetSelectedPDO(PortNum, (IndexSrcPDO - 1), RequestedVoltage, &rdo, &pdo_object);

  status = USBPD_PE_Send_Request(PortNum, rdo.d32, pdo_object);

  return status;
/* USER CODE END USBPD_DPM_RequestMessageRequest */
}

/**
  * @brief  Request the PE to send a GET_SRC_CAPA message
  * @param  PortNum The current port number
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestGetSourceCapability(uint8_t PortNum)
{
  return USBPD_PE_Request_CtrlMessage(PortNum, USBPD_CONTROLMSG_GET_SRC_CAP, USBPD_SOPTYPE_SOP);
}

/**
  * @brief  Request the PE to send a GET_SNK_CAPA message
  * @param  PortNum The current port number
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestGetSinkCapability(uint8_t PortNum)
{
  return USBPD_PE_Request_CtrlMessage(PortNum, USBPD_CONTROLMSG_GET_SNK_CAP, USBPD_SOPTYPE_SOP);
}

/**
  * @brief  Request the PE to perform a Data Role Swap.
  * @param  PortNum The current port number
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestDataRoleSwap(uint8_t PortNum)
{
  return USBPD_PE_Request_CtrlMessage(PortNum, USBPD_CONTROLMSG_DR_SWAP, USBPD_SOPTYPE_SOP);
}

/**
  * @brief  Request the PE to perform a Power Role Swap.
  * @param  PortNum The current port number
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestPowerRoleSwap(uint8_t PortNum)
{
  return USBPD_PE_Request_CtrlMessage(PortNum, USBPD_CONTROLMSG_PR_SWAP, USBPD_SOPTYPE_SOP);
}

/**
  * @brief  Request the PE to perform a VCONN Swap.
  * @param  PortNum The current port number
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestVconnSwap(uint8_t PortNum)
{
  return USBPD_PE_Request_CtrlMessage(PortNum, USBPD_CONTROLMSG_VCONN_SWAP, USBPD_SOPTYPE_SOP);
}

/**
  * @brief  Request the PE to send a soft reset
  * @param  PortNum The current port number
  * @param  SOPType SOP Type based on @ref USBPD_SOPType_TypeDef
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestSoftReset(uint8_t PortNum, USBPD_SOPType_TypeDef SOPType)
{
  return USBPD_PE_Request_CtrlMessage(PortNum, USBPD_CONTROLMSG_SOFT_RESET, SOPType);
}

/**
  * @brief  Request the PE to send a Source Capability message.
  * @param  PortNum The current port number
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestSourceCapability(uint8_t PortNum)
{
  /* PE will directly get the PDO saved in structure @ref PWR_Port_PDO_Storage */
  return USBPD_PE_Request_DataMessage(PortNum, USBPD_DATAMSG_SRC_CAPABILITIES, NULL);
}

/**
  * @brief  Request the PE to send a VDM discovery identity
  * @param  PortNum The current port number
  * @param  SOPType SOP Type
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestVDM_DiscoveryIdentify(uint8_t PortNum, USBPD_SOPType_TypeDef SOPType)
{
  USBPD_StatusTypeDef _status = USBPD_ERROR;
/* USER CODE BEGIN USBPD_DPM_RequestVDM_DiscoveryIdentify */

  if (USBPD_SOPTYPE_SOP == SOPType)
  {
    _status = USBPD_PE_SVDM_RequestIdentity(PortNum, SOPType);
  }

/* USER CODE END USBPD_DPM_RequestVDM_DiscoveryIdentify */
  return _status;
}

/**
  * @brief  Request the PE to send a VDM discovery SVID
  * @param  PortNum The current port number
  * @param  SOPType SOP Type
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestVDM_DiscoverySVID(uint8_t PortNum, USBPD_SOPType_TypeDef SOPType)
{
  return USBPD_PE_SVDM_RequestSVID(PortNum, SOPType);
}

/**
  * @brief  Request the PE to perform a VDM Discovery mode message on one SVID.
  * @param  PortNum The current port number
  * @param  SOPType SOP Type
  * @param  SVID    SVID used for discovery mode message
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestVDM_DiscoveryMode(uint8_t PortNum, USBPD_SOPType_TypeDef SOPType, uint16_t SVID)
{
  return USBPD_PE_SVDM_RequestMode(PortNum, SOPType, SVID);
}

/**
  * @brief  Request the PE to perform a VDM mode enter.
  * @param  PortNum   The current port number
  * @param  SOPType   SOP Type
  * @param  SVID      SVID used for discovery mode message
  * @param  ModeIndex Index of the mode to be entered
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestVDM_EnterMode(uint8_t PortNum, USBPD_SOPType_TypeDef SOPType, uint16_t SVID, uint8_t ModeIndex)
{
  return USBPD_PE_SVDM_RequestModeEnter(PortNum, SOPType, SVID, ModeIndex);
}

/**
  * @brief  Request the PE to perform a VDM mode exit.
  * @param  PortNum   The current port number
  * @param  SOPType   SOP Type
  * @param  SVID      SVID used for discovery mode message
  * @param  ModeIndex Index of the mode to be exit
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestVDM_ExitMode(uint8_t PortNum, USBPD_SOPType_TypeDef SOPType, uint16_t SVID, uint8_t ModeIndex)
{
  return USBPD_PE_SVDM_RequestModeExit(PortNum, SOPType, SVID, ModeIndex);
}

/**
  * @brief  Request the PE to send a Display Port status
  * @param  PortNum   The current port number
  * @param  SOPType   SOP Type
  * @param  SVID      Used SVID
  * @param  pDPStatus Pointer on DP Status data (32 bit)
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestDisplayPortStatus(uint8_t PortNum, USBPD_SOPType_TypeDef SOPType, uint16_t SVID, uint32_t *pDPStatus)
{
/* USER CODE BEGIN USBPD_DPM_RequestDisplayPortStatus */
  /*USBPD_VDM_FillDPStatus(PortNum, (USBPD_DPStatus_TypeDef*)pDPStatus);*/
/* USER CODE END USBPD_DPM_RequestDisplayPortStatus */
  return USBPD_PE_SVDM_RequestSpecific(PortNum, SOPType, SVDM_SPECIFIC_1, SVID);
}
/**
  * @brief  Request the PE to send a Display Port Config
  * @param  PortNum   The current port number
  * @param  SOPType   SOP Type
  * @param  SVID      Used SVID
  * @param  pDPConfig Pointer on DP Config data (32 bit)
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestDisplayPortConfig(uint8_t PortNum, USBPD_SOPType_TypeDef SOPType, uint16_t SVID, uint32_t *pDPConfig)
{
/* USER CODE BEGIN USBPD_DPM_RequestDisplayPortConfig */
  /*USBPD_VDM_FillDPConfig(PortNum, (USBPD_DPConfig_TypeDef*)pDPConfig);*/
/* USER CODE END USBPD_DPM_RequestDisplayPortConfig */
  return USBPD_PE_SVDM_RequestSpecific(PortNum, SOPType, SVDM_SPECIFIC_2, SVID);
}

/**
  * @brief  Request the PE to perform a VDM Attention.
  * @param  PortNum The current port number
  * @param  SOPType SOP Type
  * @param  SVID    Used SVID
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestAttention(uint8_t PortNum, USBPD_SOPType_TypeDef SOPType, uint16_t SVID)
{
  return USBPD_PE_SVDM_RequestAttention(PortNum, SOPType, SVID);
}

/**
  * @brief  Request the PE to send an ALERT to port partner
  * @param  PortNum The current port number
  * @param  Alert   Alert based on @ref USBPD_ADO_TypeDef
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestAlert(uint8_t PortNum, USBPD_ADO_TypeDef Alert)
{
  return USBPD_PE_Request_DataMessage(PortNum, USBPD_DATAMSG_ALERT, (uint32_t*)&Alert.d32);
}

/**
  * @brief  Request the PE to get a source capability extended
  * @param  PortNum The current port number
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestGetSourceCapabilityExt(uint8_t PortNum)
{
  return USBPD_PE_Request_CtrlMessage(PortNum, USBPD_CONTROLMSG_GET_SRC_CAPEXT, USBPD_SOPTYPE_SOP);
}

/**
  * @brief  Request the PE to get a sink capability extended
  * @param  PortNum The current port number
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestGetSinkCapabilityExt(uint8_t PortNum)
{
  return USBPD_PE_Request_CtrlMessage(PortNum, USBPD_CONTROLMSG_GET_SNK_CAPEXT, USBPD_SOPTYPE_SOP);
}

/**
  * @brief  Request the PE to get a manufacturer infor
  * @param  PortNum The current port number
  * @param  SOPType SOP Type
  * @param  pManuInfoData Pointer on manufacturer info based on @ref USBPD_GMIDB_TypeDef
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestGetManufacturerInfo(uint8_t PortNum, USBPD_SOPType_TypeDef SOPType, uint8_t* pManuInfoData)
{
  return USBPD_PE_SendExtendedMessage(PortNum, SOPType, USBPD_EXT_GET_MANUFACTURER_INFO, (uint8_t*)pManuInfoData, sizeof(USBPD_GMIDB_TypeDef));
}

/**
  * @brief  Request the PE to request a GET_PPS_STATUS
  * @param  PortNum The current port number
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestGetPPS_Status(uint8_t PortNum)
{
  return USBPD_PE_Request_CtrlMessage(PortNum, USBPD_CONTROLMSG_GET_PPS_STATUS, USBPD_SOPTYPE_SOP);
}

/**
  * @brief  Request the PE to request a GET_STATUS
  * @param  PortNum The current port number
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestGetStatus(uint8_t PortNum)
{
  return USBPD_PE_Request_CtrlMessage(PortNum, USBPD_CONTROLMSG_GET_STATUS, USBPD_SOPTYPE_SOP);
}

/**
  * @brief  Request the PE to perform a Fast Role Swap.
  * @param  PortNum The current port number
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestFastRoleSwap(uint8_t PortNum)
{
  return USBPD_PE_Request_CtrlMessage(PortNum, USBPD_CONTROLMSG_FR_SWAP, USBPD_SOPTYPE_SOP);
}

/**
  * @brief  Request the PE to send a GET_COUNTRY_CODES message
  * @param  PortNum The current port number
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestGetCountryCodes(uint8_t PortNum)
{
  return USBPD_PE_Request_CtrlMessage(PortNum, USBPD_CONTROLMSG_GET_COUNTRY_CODES, USBPD_SOPTYPE_SOP);
}

/**
  * @brief  Request the PE to send a GET_COUNTRY_INFO message
  * @param  PortNum     The current port number
  * @param  CountryCode Country code (1st character and 2nd of the Alpha-2 Country)
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestGetCountryInfo(uint8_t PortNum, uint16_t CountryCode)
{
  return USBPD_PE_Request_DataMessage(PortNum, USBPD_DATAMSG_GET_COUNTRY_INFO, (uint32_t*)&CountryCode);
}

/**
  * @brief  Request the PE to send a GET_BATTERY_CAPA
  * @param  PortNum         The current port number
  * @param  pBatteryCapRef  Pointer on the Battery Capability reference
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestGetBatteryCapability(uint8_t PortNum, uint8_t *pBatteryCapRef)
{
  return USBPD_PE_SendExtendedMessage(PortNum, USBPD_SOPTYPE_SOP, USBPD_EXT_GET_BATTERY_CAP, (uint8_t*)pBatteryCapRef, 1);
}

/**
  * @brief  Request the PE to send a GET_BATTERY_STATUS
  * @param  PortNum           The current port number
  * @param  pBatteryStatusRef Pointer on the Battery Status reference
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestGetBatteryStatus(uint8_t PortNum, uint8_t *pBatteryStatusRef)
{
  return USBPD_PE_SendExtendedMessage(PortNum, USBPD_SOPTYPE_SOP, USBPD_EXT_GET_BATTERY_STATUS, (uint8_t*)pBatteryStatusRef, 1);
}

/**
  * @brief  Request the PE to send a SECURITY_REQUEST
  * @param  PortNum The current port number
  * @retval USBPD Status
  */
USBPD_StatusTypeDef USBPD_DPM_RequestSecurityRequest(uint8_t PortNum)
{
/* USER CODE BEGIN USBPD_DPM_RequestSecurityRequest */
  return USBPD_ERROR;
/* USER CODE END USBPD_DPM_RequestSecurityRequest */
}

/**
  * @}
  */

/** @addtogroup USBPD_USER_PRIVATE_FUNCTIONS
  * @{
  */

/* USER CODE BEGIN USBPD_USER_PRIVATE_FUNCTIONS */

/**
  * @brief  Find PDO index that offers the most amount of power.
  * @param  PortNum Port number
  * @param  PtrRequestedPower  Sink requested power profile structure pointer
  * @retval Index of PDO within source capabilities message (-1 indicating not found)
  */
static int32_t DPM_FindVoltageIndex(uint32_t PortNum, USBPD_SNKPowerRequest_TypeDef *PtrRequestedPower)
{
  uint32_t *ptpdoarray;
  USBPD_PDO_TypeDef  pdo;
  uint32_t mv = 0, voltage = 0, max_voltage = 0, curr_dist = 0, temp_dist = 0;
  uint32_t nbpdo;
  int8_t curr_index = -1, temp_index = -1;

  /* Max voltage is always limited by the board's max request */
  voltage = PtrRequestedPower->OperatingVoltageInmVunits;
  max_voltage = PtrRequestedPower->MaxOperatingVoltageInmVunits;

  /* The requested voltage not supported by this board */
  if (USBPD_IS_VALID_VOLTAGE(voltage, PtrRequestedPower->MaxOperatingVoltageInmVunits, PtrRequestedPower->MinOperatingVoltageInmVunits) != 1)
  {
    /* DPM_FindVoltageIndex: Requested voltage not supported by the board\r */
    return curr_index;
  }

  /* Search PDO index among Source PDO of Port */
  nbpdo = DPM_Ports[PortNum].DPM_NumberOfRcvSRCPDO;
  ptpdoarray = DPM_Ports[PortNum].DPM_ListOfRcvSRCPDO;

  /* search the better PDO in the list of source PDOs */
  for(temp_index = 0; temp_index < nbpdo; temp_index++)
  {
    pdo.d32 = ptpdoarray[temp_index];
    /* get voltage value from PDO */
    mv = pdo.GenericPDO.VoltageIn50mVunits * 50;

    /* check if the source PDO is ok in term of voltage */
    if (mv <= max_voltage)
    {
      /* choose the "better" PDO, in this case only the distance in absolute value from the target voltage */
      temp_dist = mv > voltage ? mv - voltage : voltage - mv;
      if (curr_index == -1 || curr_dist >= temp_dist)
      {
        /* consider the current PDO the better one until this time */
        curr_index = temp_index;
        curr_dist = temp_dist;
      }
    }
  }

  return curr_index;
}

/**
  * @brief  Evaluate received Capabilities Message from Source port and prepare the request message
  * @param  PortNum           Port number
  * @param  IndexSrcPDO       Index on the selected SRC PDO (value between 1 to 7)
  * @param  RequestedVoltage  Requested voltage (in MV and use mainly for APDO)
  * @param  Rdo               Pointer on the RDO
  * @param  PtrPowerObject    Pointer on the selected power object
  * @retval None
  */
void DPM_SNK_GetSelectedPDO(uint8_t PortNum, uint8_t IndexSrcPDO, uint16_t RequestedVoltage, USBPD_SNKRDO_TypeDef* Rdo, USBPD_CORE_PDO_Type_TypeDef *PtrPowerObject)
{
  uint32_t mv = 0, mw = 0, ma = 0;
  USBPD_PDO_TypeDef  pdo;
  USBPD_SNKRDO_TypeDef rdo;
  USBPD_HandleTypeDef *pdhandle = &DPM_Ports[PortNum];
  USBPD_USER_SettingsTypeDef *puser = (USBPD_USER_SettingsTypeDef *)&DPM_USER_Settings[PortNum];

  pdhandle->DPM_RequestedVoltage = 0;

  /* Initialize RDO */
  rdo.d32 = 0;

  /* Extract power information from Power Data Object */
  pdo.d32 = pdhandle->DPM_ListOfRcvSRCPDO[IndexSrcPDO];

  /* Set the Object position */
  rdo.GenericRDO.ObjectPosition = IndexSrcPDO + 1;
  *PtrPowerObject = pdo.GenericPDO.PowerObject;

  switch (pdo.GenericPDO.PowerObject)
  {
    case USBPD_CORE_PDO_TYPE_FIXED:
      {
        USBPD_SRCFixedSupplyPDO_TypeDef fixedpdo = pdo.SRCFixedPDO;
        mv = PWR_DECODE_50MV(fixedpdo.VoltageIn50mVunits);
        ma = PWR_DECODE_10MA(fixedpdo.MaxCurrentIn10mAunits);
        ma = USBPD_MIN(ma, puser->DPM_SNKRequestedPower.MaxOperatingCurrentInmAunits);
        mw = ma * mv; /* mW */
        DPM_Ports[PortNum].DPM_RequestedCurrent = ma;
        rdo.FixedVariableRDO.OperatingCurrentIn10mAunits  = ma / 10;
        rdo.FixedVariableRDO.MaxOperatingCurrent10mAunits = ma / 10;
        if(mw < puser->DPM_SNKRequestedPower.OperatingPowerInmWunits)
        {
          rdo.FixedVariableRDO.MaxOperatingCurrent10mAunits = puser->DPM_SNKRequestedPower.MaxOperatingCurrentInmAunits / 10;
          rdo.FixedVariableRDO.CapabilityMismatch = 1;
          /* USBPD_DPM_EvaluateCapabilities: Mismatch, less power offered than the operating power */
        }
      }
      break;
    case USBPD_CORE_PDO_TYPE_BATTERY:
      {
        USBPD_SRCBatterySupplyPDO_TypeDef batterypdo = pdo.SRCBatteryPDO;
        mv = PWR_DECODE_50MV(batterypdo.MinVoltageIn50mVunits);
        mw = PWR_DECODE_MW(batterypdo.MaxAllowablePowerIn250mWunits);
        mw = USBPD_MIN(mw, puser->DPM_SNKRequestedPower.MaxOperatingPowerInmWunits); /* mW */
        ma = mw / mv; /* mA */
        ma = USBPD_MIN(ma, puser->DPM_SNKRequestedPower.MaxOperatingCurrentInmAunits);
        DPM_Ports[PortNum].DPM_RequestedCurrent       = ma;
        mw = ma * mv; /* mW */
        rdo.BatteryRDO.ObjectPosition                 = IndexSrcPDO + 1;
        rdo.BatteryRDO.OperatingPowerIn250mWunits     = mw / 250;
        rdo.BatteryRDO.MaxOperatingPowerIn250mWunits  = mw / 250;
        if(mw < puser->DPM_SNKRequestedPower.OperatingPowerInmWunits)
        {
          rdo.BatteryRDO.CapabilityMismatch = 1;
          /* Mismatch, less power offered than the operating power */
        }
        /* USBPD_DPM_EvaluateCapabilities: Battery Request Data Object %u: %d mW", rdo.d32, mw */
      }
      break;
    case USBPD_CORE_PDO_TYPE_VARIABLE:
      {
        //USBPD_SRCVariableSupplyPDO_TypeDef variablepdo = pdo.SRCVariablePDO;
      }
      break;
    default:
      break;
  }

  pdhandle->DPM_RequestDOMsg = rdo.d32;
  pdhandle->DPM_RDOPosition = rdo.GenericRDO.ObjectPosition;

  Rdo->d32 = pdhandle->DPM_RequestDOMsg;
  /* Get the requested voltage */
  pdhandle->DPM_RequestedVoltage = mv;
}

/* USER CODE END USBPD_USER_PRIVATE_FUNCTIONS */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
