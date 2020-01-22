/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usbpd_pwr_if.c
  * @author  MCD Application Team
  * @brief   This file contains power interface control functions.
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

#define __USBPD_PWR_IF_C

/* Includes ------------------------------------------------------------------*/
#include "usbpd_pwr_if.h"
#include "usbpd_hw_if.h"
#include "usbpd_pwr_if.h"
#include "usbpd_dpm_core.h"
#include "usbpd_dpm_conf.h"
#include "usbpd_pdo_defs.h"
#include "usbpd_core.h"
#if defined(_TRACE)
#include "usbpd_trace.h"
#endif /* _TRACE */
#include "string.h"
/* USER CODE BEGIN Include */

/* USER CODE END Include */

/** @addtogroup STM32_USBPD_APPLICATION
  * @{
  */

/** @addtogroup STM32_USBPD_APPLICATION_POWER_IF
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/** @addtogroup STM32_USBPD_APPLICATION_POWER_IF_Private_TypeDef
  * @{
  */
/* USER CODE BEGIN Private_Typedef */

/* USER CODE END Private_Typedef */
/**
  * @}
  */

/* Private define ------------------------------------------------------------*/
/** @addtogroup STM32_USBPD_APPLICATION_POWER_IF_Private_Defines
  * @{
  */
/* USER CODE BEGIN Private_Define */

/* USER CODE END Private_Define */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @addtogroup STM32_USBPD_APPLICATION_POWER_IF_Private_Macros
  * @{
  */
#if defined(_TRACE)
#define PWR_IF_DEBUG_TRACE(_PORT_, __MESSAGE__)  USBPD_TRACE_Add(USBPD_TRACE_DEBUG,    (_PORT_), 0u,(__MESSAGE__), sizeof(__MESSAGE__) - 1u)
#else
#define PWR_IF_DEBUG_TRACE(_PORT_, __MESSAGE__)
#endif /* _TRACE */
/* USER CODE BEGIN Private_Macro */

/* USER CODE END Private_Macro */
/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/** @addtogroup STM32_USBPD_APPLICATION_POWER_IF_Private_Variables
  * @{
  */
/* USER CODE BEGIN Private_Variables */

/**
  * @brief  USBPD Port PDO Storage array declaration
  */
USBPD_PWR_Port_PDO_Storage_TypeDef PWR_Port_PDO_Storage[USBPD_PORT_COUNT];

/* USER CODE END Private_Variables */
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @addtogroup STM32_USBPD_APPLICATION_POWER_IF_Private_Functions
  * @{
  */
/* USER CODE BEGIN USBPD_USER_PRIVATE_FUNCTIONS_Prototypes */

//
// Functions to initialize Source PDOs
//
uint32_t _PWR_SRCFixedPDO(float MaxCurrent, float Voltage,
                          USBPD_CORE_PDO_PeakCurr_TypeDef PeakCurrent,
                          USBPD_CORE_PDO_DRDataSupport_TypeDef DRDSupport,
                          USBPD_CORE_PDO_USBCommCapable_TypeDef UsbCommCapable,
                          USBPD_CORE_PDO_ExtPowered_TypeDef ExtPower,
                          USBPD_CORE_PDO_USBSuspendSupport_TypeDef UsbSuspendSupport,
                          USBPD_CORE_PDO_DRPowerSupport_TypeDef DRPSupport);
uint32_t _PWR_SRCVariablePDO(float MaxVoltage, float MinVoltage, float MaxCurrent);
uint32_t _PWR_SRCBatteryPDO(float MaxVoltage,float MinVoltage,float MaxPower);

//
// Functions to initialize Sink PDOs
//
uint32_t _PWR_SNKFixedPDO(float OpCurrent, float OpVoltage,
                          USBPD_CORE_PDO_DRDataSupport_TypeDef DRDSupport,
                          USBPD_CORE_PDO_USBCommCapable_TypeDef UsbCommCapable,
                          USBPD_CORE_PDO_ExtPowered_TypeDef ExtPower,
                          USBPD_CORE_PDO_HigherCapability_TypeDef HigherCapab,
                          USBPD_CORE_PDO_DRPowerSupport_TypeDef DRPSupport);
uint32_t _PWR_SNKVariablePDO(float MaxVoltage,float MinVoltage, float MaxCurrent);
uint32_t _PWR_SNKBatteryPDO(float MaxVoltage, float MinVoltage, float MaxPower);

/* USER CODE END USBPD_USER_PRIVATE_FUNCTIONS_Prototypes */
/**
  * @}
  */

/** @addtogroup STM32_USBPD_APPLICATION_POWER_IF_Exported_Functions
  * @{
  */

/**
  * @brief  Initialize structures and variables related to power board profiles
  *         used by Sink and Source, for all available ports.
  * @retval USBPD status
  */
USBPD_StatusTypeDef USBPD_PWR_IF_Init(void)
{
/* USER CODE BEGIN USBPD_PWR_IF_Init */

  // Set links to PDO values and number for Port 0 (defined in PDO arrays in H file).
#if (PORT0_NB_SINKPDO > 0)
  PWR_Port_PDO_Storage[USBPD_PORT_0].SinkPDO.ListOfPDO = (uint32_t *)PORT0_PDO_ListSNK;
  PWR_Port_PDO_Storage[USBPD_PORT_0].SinkPDO.NumberOfPDO = PORT0_NB_SINKPDO;
#endif

  return USBPD_OK;

/* USER CODE END USBPD_PWR_IF_Init */
}

/**
  * @brief  Sets the required power profile, now it works only with Fixed ones
  * @param  PortNum Port number
  * @retval USBPD status
*/
USBPD_StatusTypeDef USBPD_PWR_IF_SetProfile(uint8_t PortNum)
{
/* USER CODE BEGIN USBPD_PWR_IF_SetProfile */
  USBPD_StatusTypeDef _status = USBPD_ERROR;
  return _status;
/* USER CODE END USBPD_PWR_IF_SetProfile */
}

/**
  * @brief  Checks if the power on a specified port is ready
  * @param  PortNum Port number
  * @param  Vsafe   Vsafe status based on @ref USBPD_VSAFE_StatusTypeDef
  * @retval USBPD status
  */
USBPD_StatusTypeDef USBPD_PWR_IF_SupplyReady(uint8_t PortNum, USBPD_VSAFE_StatusTypeDef Vsafe)
{
/* USER CODE BEGIN USBPD_PWR_IF_SupplyReady */

  /* check for valid port */
  if (!USBPD_PORT_IsValid(PortNum))
    { return USBPD_ERROR; }

  if (USBPD_VSAFE_0V == Vsafe)
  {
    /* Vsafe0V */
    return
      HW_IF_PWR_GetVoltage(PortNum) < USBPD_PWR_LOW_VBUS_THRESHOLD
        ? USBPD_OK
        : USBPD_ERROR;
  }
  else
  {
    /* Vsafe5V */
    return
      HW_IF_PWR_GetVoltage(PortNum) > USBPD_PWR_VBUS_THRESHOLD_5V
        ? USBPD_OK
        : USBPD_ERROR;
  }
/* USER CODE END USBPD_PWR_IF_SupplyReady */
}

/**
  * @brief  Enables VBUS power on a specified port
  * @param  PortNum Port number
  * @retval USBPD status
  */
USBPD_StatusTypeDef USBPD_PWR_IF_VBUSEnable(uint8_t PortNum)
{
/* USER CODE BEGIN USBPD_PWR_IF_VBUSEnable */
  return USBPD_ERROR;
/* USER CODE END USBPD_PWR_IF_VBUSEnable */
}

/**
  * @brief  Disbale VBUS/VCONN the power on a specified port
  * @param  PortNum Port number
  * @retval USBPD status
  */
USBPD_StatusTypeDef USBPD_PWR_IF_VBUSDisable(uint8_t PortNum)
{
/* USER CODE BEGIN USBPD_PWR_IF_VBUSDisable */
  return USBPD_ERROR;
/* USER CODE END USBPD_PWR_IF_VBUSDisable */
}

/**
  * @brief  Checks if the power on a specified port is enabled
  * @param  PortNum Port number
  * @retval USBPD_ENABLE or USBPD_DISABLE
  */
USBPD_FunctionalState USBPD_PWR_IF_VBUSIsEnabled(uint8_t PortNum)
{
  /* Get the Status of the port */
  return
    USBPD_PORT_IsValid(PortNum)
      ? (USBPD_FunctionalState)HW_IF_PWR_VBUSIsEnabled(PortNum)
      : USBPD_DISABLE;
}

/**
  * @brief  Reads the voltage and the current on a specified port
  * @param  PortNum Port number
  * @param  pVoltage: The Voltage in mV
  * @param  pCurrent: The Current in mA
  * @retval USBPD_ERROR or USBPD_OK
  */
USBPD_StatusTypeDef USBPD_PWR_IF_ReadVA(uint8_t PortNum, uint16_t *pVoltage, uint16_t *pCurrent)
{
/* USER CODE BEGIN USBPD_PWR_IF_ReadVA */
  /* check for valid port */
  if (!USBPD_PORT_IsValid(PortNum))
  {
    return USBPD_ERROR;
  }

  /* USBPD_OK if at least one pointer is not null, otherwise USBPD_ERROR */
  USBPD_StatusTypeDef ret = USBPD_ERROR;

  /* Get values from HW_IF */
  if (pVoltage != NULL)
  {
    *pVoltage = HW_IF_PWR_GetVoltage(PortNum);
    ret = USBPD_OK;
  }
  if (pCurrent != NULL)
  {
    *pCurrent = HW_IF_PWR_GetCurrent(PortNum);
    ret = USBPD_OK;
  }

  return ret;
/* USER CODE END USBPD_PWR_IF_ReadVA */
}

/**
  * @brief  Enables the VConn on the port.
  * @param  PortNum Port number
  * @param  CC      Specifies the CCx to be selected based on @ref CCxPin_TypeDef structure
  * @retval USBPD status
  */
USBPD_StatusTypeDef USBPD_PWR_IF_Enable_VConn(uint8_t PortNum, CCxPin_TypeDef CC)
{
/* USER CODE BEGIN USBPD_PWR_IF_Enable_VConn */
  return USBPD_ERROR;
/* USER CODE END USBPD_PWR_IF_Enable_VConn */
}

/**
  * @brief  Disable the VConn on the port.
  * @param  PortNum Port number
  * @param  CC      Specifies the CCx to be selected based on @ref CCxPin_TypeDef structure
  * @retval USBPD status
  */
USBPD_StatusTypeDef USBPD_PWR_IF_Disable_VConn(uint8_t PortNum, CCxPin_TypeDef CC)
{
/* USER CODE BEGIN USBPD_PWR_IF_Disable_VConn */
  return USBPD_ERROR;
/* USER CODE END USBPD_PWR_IF_Disable_VConn */
}

/**
  * @brief  Allow PDO data reading from PWR_IF storage.
  * @param  PortNum Port number
  * @param  DataId Type of data to be read from PWR_IF
  *         This parameter can be one of the following values:
  *           @arg @ref USBPD_CORE_DATATYPE_SRC_PDO Source PDO reading requested
  *           @arg @ref USBPD_CORE_DATATYPE_SNK_PDO Sink PDO reading requested
  * @param  Ptr Pointer on address where PDO values should be written (u8 pointer)
  * @param  Size Pointer on nb of u32 written by PWR_IF (nb of PDOs)
  * @retval None
  */
void USBPD_PWR_IF_GetPortPDOs(uint8_t PortNum, USBPD_CORE_DataInfoType_TypeDef DataId, uint8_t *Ptr, uint32_t *Size)
{
    {
      *Size = PORT0_NB_SINKPDO;
      memcpy(Ptr,PORT0_PDO_ListSNK, sizeof(uint32_t) * PORT0_NB_SINKPDO);
    }
/* USER CODE BEGIN USBPD_PWR_IF_GetPortPDOs */

/* USER CODE END USBPD_PWR_IF_GetPortPDOs */
}

/**
  * @brief  Find out SRC PDO pointed out by a position provided in a Request DO (from Sink).
  * @param  PortNum Port number
  * @param  RdoPosition RDO Position in list of provided PDO
  * @param  Pdo Pointer on PDO value pointed out by RDO position (u32 pointer)
  * @retval Status of search
  *         USBPD_OK : Src PDO found for requested DO position (output Pdo parameter is set)
  *         USBPD_FAIL : Position is not compliant with current Src PDO for this port (no corresponding PDO value)
  */
USBPD_StatusTypeDef USBPD_PWR_IF_SearchRequestedPDO(uint8_t PortNum, uint32_t RdoPosition, uint32_t *Pdo)
{
/* USER CODE BEGIN USBPD_PWR_IF_SearchRequestedPDO */
  return USBPD_FAIL;
/* USER CODE END USBPD_PWR_IF_SearchRequestedPDO */
}

/**
  * @brief  the function is called in case of critical issue is detected to switch in safety mode.
  * @retval None
  */
void USBPD_PWR_IF_Alarm()
{
/* USER CODE BEGIN USBPD_PWR_IF_Alarm */

/* USER CODE END USBPD_PWR_IF_Alarm */
}

/**
  * @}
  */

/** @addtogroup STM32_USBPD_APPLICATION_POWER_IF_Private_Functions
  * @{
  */

/* USER CODE BEGIN STM32_USBPD_APPLICATION_POWER_IF_Private_Functions */

/**
  * @brief  Create SRC Fixed PDO object
  * @param  MaxCurrent: Current in A
  * @param  Voltage: voltage in V
  * @param  PeakCurrent: The peak of current
  * @param  DRDSupport: Data Role Swap support indication
  * @param  UsbCommCapable: USB communications capability indication
  * @param  ExtPower: Port externally powered indication
  * @param  UsbSuspendSupport: USB Suspend support indication
  * @param  DRPSupport: Dual Role Power support indication
  * @retval PDO object value (expressed on u32)
  */
uint32_t _PWR_SRCFixedPDO(float MaxCurrent, float Voltage,
                          USBPD_CORE_PDO_PeakCurr_TypeDef PeakCurrent,
                          USBPD_CORE_PDO_DRDataSupport_TypeDef DRDSupport,
                          USBPD_CORE_PDO_USBCommCapable_TypeDef UsbCommCapable,
                          USBPD_CORE_PDO_ExtPowered_TypeDef ExtPower,
                          USBPD_CORE_PDO_USBSuspendSupport_TypeDef UsbSuspendSupport,
                          USBPD_CORE_PDO_DRPowerSupport_TypeDef DRPSupport)
{
  USBPD_PDO_TypeDef pdo;

  pdo.d32 = 0;
  pdo.SRCFixedPDO.MaxCurrentIn10mAunits       = PWR_A_10MA(MaxCurrent);
  pdo.SRCFixedPDO.VoltageIn50mVunits          = PWR_V_50MV(Voltage);
  pdo.SRCFixedPDO.PeakCurrent                 = PeakCurrent;
  pdo.SRCFixedPDO.DataRoleSwap                = DRDSupport;
  pdo.SRCFixedPDO.USBCommunicationsCapable    = UsbCommCapable;
  pdo.SRCFixedPDO.ExternallyPowered           = ExtPower;
  pdo.SRCFixedPDO.USBSuspendSupported         = UsbSuspendSupport;
  pdo.SRCFixedPDO.DualRolePower               = DRPSupport;
  pdo.SRCFixedPDO.FixedSupply                 = USBPD_CORE_PDO_TYPE_FIXED;
  return pdo.d32;
}

/**
  * @brief  Create SRC Variable PDO object
  * @param  MaxVoltage: Max voltage in V
  * @param  MinVoltage: Min voltage in V
  * @param  MaxCurrent: Max current in A
  * @retval PDO object value (expressed on u32)
  */
uint32_t _PWR_SRCVariablePDO(float MaxVoltage, float MinVoltage, float MaxCurrent)
{
  USBPD_PDO_TypeDef pdo;

  pdo.d32 = 0;
  pdo.SRCVariablePDO.MaxCurrentIn10mAunits = PWR_A_10MA(MaxCurrent);
  pdo.SRCVariablePDO.MaxVoltageIn50mVunits = PWR_V_50MV(MaxVoltage);
  pdo.SRCVariablePDO.MinVoltageIn50mVunits = PWR_V_50MV(MinVoltage);
  pdo.SRCVariablePDO.VariableSupply        = USBPD_CORE_PDO_TYPE_VARIABLE;
  return pdo.d32;
}

/**
  * @brief  Create SRC Battery PDO object
  * @param  MaxVoltage: Max voltage in V
  * @param  MinVoltage: Min voltage in V
  * @param  MaxPower: Max allowable power in W
  * @retval PDO object value (expressed on u32)
  */
uint32_t _PWR_SRCBatteryPDO(float MaxVoltage,float MinVoltage,float MaxPower)
{
  USBPD_PDO_TypeDef pdo;

  pdo.d32 = 0;
  pdo.SRCBatteryPDO.MaxAllowablePowerIn250mWunits = PWR_W(MaxPower);
  pdo.SRCBatteryPDO.MinVoltageIn50mVunits         = PWR_V_50MV(MinVoltage);
  pdo.SRCBatteryPDO.MaxVoltageIn50mVunits         = PWR_V_50MV(MaxVoltage);
  pdo.SRCBatteryPDO.Battery                       = USBPD_CORE_PDO_TYPE_BATTERY;
  return pdo.d32;
}

/**
  * @brief  Create SNK Fixed PDO object
  * @param  OpCurrent: Current in A
  * @param  OpVoltage: voltage in V
  * @param  DRDSupport: Data Role Swap support indication
  * @param  UsbCommCapable: USB communications capability indication
  * @param  ExtPower: Port externally powered indication
  * @param  HigherCapab: Sink needs more than vSafe5V to provide full functionality indication
  * @param  DRPSupport: Dual Role Power support indication
  * @retval PDO object value (expressed on u32)
  */
uint32_t _PWR_SNKFixedPDO(float OpCurrent, float OpVoltage,
                          USBPD_CORE_PDO_DRDataSupport_TypeDef DRDSupport,
                          USBPD_CORE_PDO_USBCommCapable_TypeDef UsbCommCapable,
                          USBPD_CORE_PDO_ExtPowered_TypeDef ExtPower,
                          USBPD_CORE_PDO_HigherCapability_TypeDef HigherCapab,
                          USBPD_CORE_PDO_DRPowerSupport_TypeDef DRPSupport)
{
  USBPD_PDO_TypeDef pdo;

  pdo.d32 = 0;
  pdo.SNKFixedPDO.OperationalCurrentIn10mAunits = PWR_A_10MA(OpCurrent);
  pdo.SNKFixedPDO.VoltageIn50mVunits            = PWR_V_50MV(OpVoltage);
  pdo.SNKFixedPDO.DataRoleSwap                  = DRDSupport;
  pdo.SNKFixedPDO.USBCommunicationsCapable      = UsbCommCapable;
  pdo.SNKFixedPDO.ExternallyPowered             = ExtPower;
  pdo.SNKFixedPDO.HigherCapability              = HigherCapab;
  pdo.SNKFixedPDO.DualRolePower                 = DRPSupport;
  pdo.SNKFixedPDO.FixedSupply                   = USBPD_CORE_PDO_TYPE_FIXED;

  return pdo.d32;
}

/**
  * @brief  Create SNK Variable PDO object
  * @param  MaxVoltage: Max voltage in V
  * @param  MinVoltage: Min voltage in V
  * @param  MaxCurrent: Max current in A
  * @retval PDO object value (expressed on u32)
  */
uint32_t _PWR_SNKVariablePDO(float MaxVoltage,float MinVoltage, float MaxCurrent)
{
  USBPD_PDO_TypeDef pdo;

  pdo.d32 = 0;
  pdo.SRCVariablePDO.MaxCurrentIn10mAunits = PWR_A_10MA(MaxCurrent);
  pdo.SRCVariablePDO.MaxVoltageIn50mVunits = PWR_V_50MV(MaxVoltage);
  pdo.SRCVariablePDO.MinVoltageIn50mVunits = PWR_V_50MV(MinVoltage);
  pdo.SRCVariablePDO.VariableSupply        = USBPD_CORE_PDO_TYPE_VARIABLE;
  return pdo.d32;
}

/**
  * @brief  Create SNK Battery PDO object
  * @param  MaxVoltage: Max voltage in V
  * @param  MinVoltage: Min voltage in V
  * @param  MaxPower: Max allowable power in W
  * @retval PDO object value (expressed on u32)
  */
uint32_t _PWR_SNKBatteryPDO(float MaxVoltage, float MinVoltage, float MaxPower)
{
  USBPD_PDO_TypeDef pdo;

  pdo.d32 = 0;
  pdo.SRCBatteryPDO.MaxAllowablePowerIn250mWunits = PWR_W(MaxPower);
  pdo.SRCBatteryPDO.MinVoltageIn50mVunits         = PWR_V_50MV(MinVoltage);
  pdo.SRCBatteryPDO.MaxVoltageIn50mVunits         = PWR_V_50MV(MaxVoltage);
  pdo.SRCBatteryPDO.Battery                       = USBPD_CORE_PDO_TYPE_BATTERY;
  return pdo.d32;
}

/* USER CODE END STM32_USBPD_APPLICATION_POWER_IF_Private_Functions */

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
