#define FEE_30_SMALLSECTOR_IMPLEMENTATION_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Fee_30_SmallSector.h"


/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
 
#if (   (FEE_30_SMALLSECTOR_CFG_MAJOR_VERSION != (2u)) \
     || (FEE_30_SMALLSECTOR_CFG_MINOR_VERSION != (0u)))
# error "Version numbers of Fee_30_SmallSector_Cfg.c and Fee_30_SmallSector_Cfg.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

#define FEE_30_SMALLSECTOR_START_SEC_CONST_8BIT
#include "MemMap.h"    /* PRQA S 5087 */  /* MD_MSR_MemMap */

CONST(uint8, FEE_30_SMALLSECTOR_PRIVATE_CONST) Fee_30_SmallSector_DatasetSelectionBits = (4u);

#define FEE_30_SMALLSECTOR_STOP_SEC_CONST_8BIT
#include "MemMap.h"   /* PRQA S 5087 */  /* MD_MSR_MemMap */

#define FEE_30_SMALLSECTOR_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */

/* PRQA S 686 PARTITIONLIST */ /* MD_FEE_30_SMALLSECTOR_ArraySize */
CONST(Fee_30_SmallSector_PartitionConfigType, FEE_30_SMALLSECTOR_PRIVATE_CONST) Fee_30_SmallSector_PartitionConfigList[FEE_30_SMALLSECTOR_NUMBER_OF_PARTITIONS] = 
{
   /*  FEEPARTITIONCONFIGURATION  */ {
     /*  Partition Start Address  */ 0x00000000uL, 
     /*  Partition Address Alignment  */ 0x0040u, 
     /*  Partition Write Alignment  */ 0x0004u, 
     /*  Partition Read Alignment  */ 0x0001u, 
     /*  FLS Device Index  */ 0x0000u, 
     /*  FLS API Reference  */ &Fee_30_SmallSector_FlsApi0, 
     /*  FLS Erase Value  */ 0xFFu, 
     /*  FLS Blank Check API Enabled  */ TRUE, 
    {
       /*  FeeBlockConfiguration  */ 0x0010u, 
       /*  FeeBlockDescriptor  */ 0x0040u, 
       /*  FeeBlockDescriptor_001  */ 0x0050u, 
       /*  FeeBlockDescriptor_002  */ 0x0060u, 
       /*  FeeBlockDescriptor_008  */ 0x00C0u, 
       /*  FeeBlockDescriptor_009  */ 0x00F0u, 
       /*  FeeBlockDescriptor_010  */ 0x0100u, 
       /*  FeeBlockDescriptor_011  */ 0x0110u, 
       /*  FeeBlockDescriptor_012  */ 0x0120u, 
       /*  FeeBlockDescriptor_013  */ 0x0130u, 
       /*  FeeBlockDescriptor_014  */ 0x0140u, 
       /*  FeeBlockDescriptor_015  */ 0x0150u, 
       /*  FeeBlockDescriptor_016  */ 0x0160u, 
       /*  FeeBlockDescriptor_017  */ 0x0170u, 
       /*  FeeBlockDescriptor_018  */ 0x0180u, 
       /*  FeeBlockDescriptor_007  */ 0x00B0u, 
       /*  FeeBlockDescriptor_006  */ 0x00A0u, 
       /*  FeeBlockDescriptor_005  */ 0x0090u, 
       /*  FeeBlockDescriptor_004  */ 0x0080u, 
       /*  FeeBlockDescriptor_003  */ 0x0070u, 
       /*  FeeBlockConfiguration_001  */ 0x0020u, 
       /*  FeeBlockConfiguration_002  */ 0x0030u, 
       /*  FeeDemStatusDataBlock  */ 0x00D0u, 
       /*  FeeDemAdminDataBlock  */ 0x00E0u
    }
  }
};
/* PRQA L: PARTITIONLIST */

/* BlockConfigList is sorted by BlockNumbers in ascending order */
CONST(Fee_30_SmallSector_BlockConfigType, FEE_30_SMALLSECTOR_PRIVATE_CONST) Fee_30_SmallSector_BlockConfigList[FEE_30_SMALLSECTOR_NUMBER_OF_BLOCKS] =
{
  {
     /*  Block Start Address  */ 0x00000000uL, 
     /*  Data Length  */ 0x0004u, 
     /*  Number Of Instances  */ 0x01u, 
     /*  Number Of Datasets  */ 0x02u, 
     /*  Immediate Data Block  */ FALSE, 
     /*  Data Verification Enabled  */ FALSE
  }, 
  {
     /*  Block Start Address  */ 0x00000540uL, 
     /*  Data Length  */ 0x000Cu, 
     /*  Number Of Instances  */ 0x01u, 
     /*  Number Of Datasets  */ 0x01u, 
     /*  Immediate Data Block  */ FALSE, 
     /*  Data Verification Enabled  */ FALSE
  }, 
  {
     /*  Block Start Address  */ 0x00000580uL, 
     /*  Data Length  */ 0x000Cu, 
     /*  Number Of Instances  */ 0x01u, 
     /*  Number Of Datasets  */ 0x01u, 
     /*  Immediate Data Block  */ FALSE, 
     /*  Data Verification Enabled  */ FALSE
  }, 
  {
     /*  Block Start Address  */ 0x00000080uL, 
     /*  Data Length  */ 0x000Cu, 
     /*  Number Of Instances  */ 0x01u, 
     /*  Number Of Datasets  */ 0x01u, 
     /*  Immediate Data Block  */ FALSE, 
     /*  Data Verification Enabled  */ FALSE
  }, 
  {
     /*  Block Start Address  */ 0x000000C0uL, 
     /*  Data Length  */ 0x000Cu, 
     /*  Number Of Instances  */ 0x01u, 
     /*  Number Of Datasets  */ 0x01u, 
     /*  Immediate Data Block  */ FALSE, 
     /*  Data Verification Enabled  */ FALSE
  }, 
  {
     /*  Block Start Address  */ 0x00000100uL, 
     /*  Data Length  */ 0x000Cu, 
     /*  Number Of Instances  */ 0x01u, 
     /*  Number Of Datasets  */ 0x01u, 
     /*  Immediate Data Block  */ FALSE, 
     /*  Data Verification Enabled  */ FALSE
  }, 
  {
     /*  Block Start Address  */ 0x00000500uL, 
     /*  Data Length  */ 0x000Cu, 
     /*  Number Of Instances  */ 0x01u, 
     /*  Number Of Datasets  */ 0x01u, 
     /*  Immediate Data Block  */ FALSE, 
     /*  Data Verification Enabled  */ FALSE
  }, 
  {
     /*  Block Start Address  */ 0x000004C0uL, 
     /*  Data Length  */ 0x000Cu, 
     /*  Number Of Instances  */ 0x01u, 
     /*  Number Of Datasets  */ 0x01u, 
     /*  Immediate Data Block  */ FALSE, 
     /*  Data Verification Enabled  */ FALSE
  }, 
  {
     /*  Block Start Address  */ 0x00000480uL, 
     /*  Data Length  */ 0x000Eu, 
     /*  Number Of Instances  */ 0x01u, 
     /*  Number Of Datasets  */ 0x01u, 
     /*  Immediate Data Block  */ FALSE, 
     /*  Data Verification Enabled  */ FALSE
  }, 
  {
     /*  Block Start Address  */ 0x00000440uL, 
     /*  Data Length  */ 0x000Cu, 
     /*  Number Of Instances  */ 0x01u, 
     /*  Number Of Datasets  */ 0x01u, 
     /*  Immediate Data Block  */ FALSE, 
     /*  Data Verification Enabled  */ FALSE
  }, 
  {
     /*  Block Start Address  */ 0x00000400uL, 
     /*  Data Length  */ 0x000Cu, 
     /*  Number Of Instances  */ 0x01u, 
     /*  Number Of Datasets  */ 0x01u, 
     /*  Immediate Data Block  */ FALSE, 
     /*  Data Verification Enabled  */ FALSE
  }, 
  {
     /*  Block Start Address  */ 0x00000140uL, 
     /*  Data Length  */ 0x000Cu, 
     /*  Number Of Instances  */ 0x01u, 
     /*  Number Of Datasets  */ 0x01u, 
     /*  Immediate Data Block  */ FALSE, 
     /*  Data Verification Enabled  */ FALSE
  }, 
  {
     /*  Block Start Address  */ 0x000005C0uL, 
     /*  Data Length  */ 0x000Cu, 
     /*  Number Of Instances  */ 0x01u, 
     /*  Number Of Datasets  */ 0x01u, 
     /*  Immediate Data Block  */ FALSE, 
     /*  Data Verification Enabled  */ FALSE
  }, 
  {
     /*  Block Start Address  */ 0x00000600uL, 
     /*  Data Length  */ 0x000Cu, 
     /*  Number Of Instances  */ 0x01u, 
     /*  Number Of Datasets  */ 0x01u, 
     /*  Immediate Data Block  */ FALSE, 
     /*  Data Verification Enabled  */ FALSE
  }, 
  {
     /*  Block Start Address  */ 0x00000180uL, 
     /*  Data Length  */ 0x000Cu, 
     /*  Number Of Instances  */ 0x01u, 
     /*  Number Of Datasets  */ 0x01u, 
     /*  Immediate Data Block  */ FALSE, 
     /*  Data Verification Enabled  */ FALSE
  }, 
  {
     /*  Block Start Address  */ 0x000001C0uL, 
     /*  Data Length  */ 0x000Cu, 
     /*  Number Of Instances  */ 0x01u, 
     /*  Number Of Datasets  */ 0x01u, 
     /*  Immediate Data Block  */ FALSE, 
     /*  Data Verification Enabled  */ FALSE
  }, 
  {
     /*  Block Start Address  */ 0x00000200uL, 
     /*  Data Length  */ 0x000Cu, 
     /*  Number Of Instances  */ 0x01u, 
     /*  Number Of Datasets  */ 0x01u, 
     /*  Immediate Data Block  */ FALSE, 
     /*  Data Verification Enabled  */ FALSE
  }, 
  {
     /*  Block Start Address  */ 0x00000240uL, 
     /*  Data Length  */ 0x000Cu, 
     /*  Number Of Instances  */ 0x01u, 
     /*  Number Of Datasets  */ 0x01u, 
     /*  Immediate Data Block  */ FALSE, 
     /*  Data Verification Enabled  */ FALSE
  }, 
  {
     /*  Block Start Address  */ 0x00000280uL, 
     /*  Data Length  */ 0x000Cu, 
     /*  Number Of Instances  */ 0x01u, 
     /*  Number Of Datasets  */ 0x01u, 
     /*  Immediate Data Block  */ FALSE, 
     /*  Data Verification Enabled  */ FALSE
  }, 
  {
     /*  Block Start Address  */ 0x000002C0uL, 
     /*  Data Length  */ 0x000Cu, 
     /*  Number Of Instances  */ 0x01u, 
     /*  Number Of Datasets  */ 0x01u, 
     /*  Immediate Data Block  */ FALSE, 
     /*  Data Verification Enabled  */ FALSE
  }, 
  {
     /*  Block Start Address  */ 0x00000300uL, 
     /*  Data Length  */ 0x000Cu, 
     /*  Number Of Instances  */ 0x01u, 
     /*  Number Of Datasets  */ 0x01u, 
     /*  Immediate Data Block  */ FALSE, 
     /*  Data Verification Enabled  */ FALSE
  }, 
  {
     /*  Block Start Address  */ 0x00000340uL, 
     /*  Data Length  */ 0x000Cu, 
     /*  Number Of Instances  */ 0x01u, 
     /*  Number Of Datasets  */ 0x01u, 
     /*  Immediate Data Block  */ FALSE, 
     /*  Data Verification Enabled  */ FALSE
  }, 
  {
     /*  Block Start Address  */ 0x00000380uL, 
     /*  Data Length  */ 0x000Cu, 
     /*  Number Of Instances  */ 0x01u, 
     /*  Number Of Datasets  */ 0x01u, 
     /*  Immediate Data Block  */ FALSE, 
     /*  Data Verification Enabled  */ FALSE
  }, 
  {
     /*  Block Start Address  */ 0x000003C0uL, 
     /*  Data Length  */ 0x000Cu, 
     /*  Number Of Instances  */ 0x01u, 
     /*  Number Of Datasets  */ 0x01u, 
     /*  Immediate Data Block  */ FALSE, 
     /*  Data Verification Enabled  */ FALSE
  }
};
/* FLS API pointer table */
CONST(Fee_30_SmallSector_FlsApiType, FEE_30_SMALLSECTOR_PRIVATE_CONST) Fee_30_SmallSector_FlsApi0 = 
{
   /*  Read Service  */ Fls_Read, 
   /*  Write Service  */ Fls_Write, 
   /*  Compare Service  */ Fls_Compare, 
   /*  Erase Service  */ Fls_Erase, 
   /*  Blank Check Service  */ NULL_PTR,
   /*  Get Status Service  */ Fls_GetStatus, 
   /*  Get Job Result Service  */ Fls_GetJobResult
};
 

/**** NvM Callback Assignments ****/
CONST(Fee_30_SmallSector_CbkJobEndNotificationType, FEE_30_SMALLSECTOR_PRIVATE_CONST) Fee_30_SmallSector_CbkJobEndNotification = /* PRQA S 1533 */  /* MD_FEE_30_SMALLSECTOR_ExternalDefinition */
    NULL_PTR;
CONST(Fee_30_SmallSector_CbkJobErrorNotificationType, FEE_30_SMALLSECTOR_PRIVATE_CONST) Fee_30_SmallSector_CbkJobErrorNotification = /* PRQA S 1533 */  /* MD_FEE_30_SMALLSECTOR_ExternalDefinition */
    NULL_PTR;

#define FEE_30_SMALLSECTOR_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"	/* PRQA S 5087 */  /* MD_MSR_MemMap */

/* Justification for module-specific MISRA deviations:
 MD_FEE_30_SMALLSECTOR_ArraySize: rule 9.3
      Reason:     Array size of Fee_30_SmallSector_PartitionConfigType.BlockNumberList depends on maximum number of blocks in one partition.             
      Risk:       No risk. Partitions with fewer blocks and thus BlockNumberLists with fewer initializers are implicitly 
                  initialized to zero.
      Prevention: Program flow has been verified by component tests and review.
      
 MD_FEE_30_SMALLSECTOR_ExternalDefinition: rule 8.9
      Reason:     The function pointer is only used inside one translation unit of the static files. The assignment of 
                  this function pointer needs to be done seperately inside the generated file as the related Nvm callback function is configurable.
      Risk:       No risk. 
      Prevention: Program flow has been verified by component tests and review.
*/

/**********************************************************************************************************************
 *  END OF FILE: Fee_30_SmallSector_Cfg.c
 *********************************************************************************************************************/

