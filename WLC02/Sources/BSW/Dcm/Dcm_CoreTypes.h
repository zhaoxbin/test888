/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                             All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Dcm_CoreTypes.h
 *        \brief  Public data type definition interface of DCM
 *
 *      \details  MICROSAR DCM based on AR 4.0.3
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/
#if !defined(DCM_CORETYPES_H)
# define DCM_CORETYPES_H
/* ----------------------------------------------
 ~&&&   Versions
---------------------------------------------- */

/*! Implementation version */
# define DCM_CORETYPES_MAJOR_VERSION                                 11u
# define DCM_CORETYPES_MINOR_VERSION                                 6u
# define DCM_CORETYPES_PATCH_VERSION                                 0u
/* ----------------------------------------------
 ~&&&   Switches
---------------------------------------------- */
# if (DCM_MEMMGR_SUPPORT_ENABLED == STD_ON)
#  if (DCM_SVC_23_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_2C_02_SUPPORT_ENABLED == STD_ON)
#   define DCM_MEMMGR_MEMOP_READ_ENABLED                             STD_ON
#  else
#   define DCM_MEMMGR_MEMOP_READ_ENABLED                             STD_OFF
#  endif

#  if (DCM_SVC_3D_SUPPORT_ENABLED == STD_ON)
#   define DCM_MEMMGR_MEMOP_WRITE_ENABLED                            STD_ON
#  else
#   define DCM_MEMMGR_MEMOP_WRITE_ENABLED                            STD_OFF
#  endif
# endif /* (DCM_MEMMGR_SUPPORT_ENABLED == STD_ON) */
# if (DCM_DIDMGR_NVM_READ_ENABLED == STD_ON) || \
     (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
#  define DCM_UTI_NVM_READ_ENABLED                                   STD_ON
# else
#  define DCM_UTI_NVM_READ_ENABLED                                   STD_OFF
# endif

# if (DCM_DIDMGR_NVM_WRITE_ENABLED == STD_ON) || \
     (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
#  define DCM_UTI_NVM_WRITE_ENABLED                                  STD_ON
# else
#  define DCM_UTI_NVM_WRITE_ENABLED                                  STD_OFF
# endif
# if (DCM_NET_SUPPRESS_ON_FUNC_REQ_ENABLED == STD_ON)  || \
     (DCM_NET_CONNECTION_WITHOUT_TX_ENABLED == STD_ON)
#  define DCM_NET_CONN_PROPERTIES_ENABLED                            STD_ON
# else
#  define DCM_NET_CONN_PROPERTIES_ENABLED                            STD_OFF
# endif

# if (DCM_NET_PROTOCOL_PRIORITISATION_ENABLED == STD_ON) || \
     (DCM_NET_MONITOR_FOREIGN_N_TA_ENABLED    == STD_ON)
#  define DCM_NET_PROCESSING_CANCELLATION_ENABLED                    STD_ON
# else
#  define DCM_NET_PROCESSING_CANCELLATION_ENABLED                    STD_OFF
# endif

# if (DCM_MODE_COMMCTRL_ENABLED == STD_ON)
#  define DCM_NET_COMMCTRL_ENABLED                                   STD_ON
# else
#  define DCM_NET_COMMCTRL_ENABLED                                   STD_OFF
# endif

# if (DCM_NET_MONITOR_FOREIGN_N_TA_ENABLED == STD_ON)
#  define DCM_NET_CONN_ECU_ADDRESS_ENABLED                           STD_ON
# else
#  define DCM_NET_CONN_ECU_ADDRESS_ENABLED                           STD_OFF
# endif

# if (DCM_MULTI_THREAD_ENABLED == STD_ON)
#  define DCM_NET_PROTOCOL_PARALLELISATION_ENABLED                   STD_ON
# else
#  define DCM_NET_PROTOCOL_PARALLELISATION_ENABLED                   STD_OFF
# endif

# if (DCM_NET_PROTOCOL_PARALLELISATION_ENABLED == STD_ON) && \
     (DCM_NET_MONITOR_FOREIGN_N_TA_ENABLED == STD_ON)
#  error "Parallel service processing not supported in combination with monitoring of requests to other ECUs!"
# endif
# if (DCM_STATE_SESSION_NOTIFICATION_ENABLED == STD_ON) || \
     (DCM_STATE_SECURITY_NOTIFICATION_ENABLED == STD_ON)
#  define DCM_STATE_ANY_NOTIFICATION_ENABLED                         STD_ON
# else
#  define DCM_STATE_ANY_NOTIFICATION_ENABLED                         STD_OFF
# endif

# if (DCM_STATE_SECURITY_ENABLED == STD_ON) && \
     (DCM_SVC_27_SUPPORT_ENABLED == STD_OFF)
#  define DCM_STATE_SECURITY_EXT_SETTER_ENABLED                      STD_ON
# else
#  define DCM_STATE_SECURITY_EXT_SETTER_ENABLED                      STD_OFF
# endif

# if (DCM_STATE_SECURITY_FIXED_BYTES_ENABLED == STD_ON) || \
     (DCM_STATE_SECURITY_EXT_SETTER_ENABLED == STD_ON)
#  define DCM_STATE_SECURITY_LOOKUP_ENABLED                          STD_ON
# else
#  define DCM_STATE_SECURITY_LOOKUP_ENABLED                          STD_OFF
# endif

# if (DCM_SVC_27_SUPPORT_ENABLED == STD_ON) || \
     (DCM_DIDMGR_DYNDID_CLR_ON_STATE_CHG_ENABLED == STD_ON) || \
     (DCM_DIDMGR_PERIODICDID_CLR_ON_STATE_CHG_ENABLED == STD_ON) || \
     ((DCM_DIDMGR_OPTYPE_IO_RETCTRL2ECU_ENABLED == STD_ON) && \
     (DCM_DIDMGR_IODID_EXEC_PRECOND_LIMIT_ENABLED == STD_ON))
#  define DCM_STATE_NOTIFY_SVC_PRO_ENABLED                           STD_ON
# else
#  define DCM_STATE_NOTIFY_SVC_PRO_ENABLED                           STD_OFF
# endif
# if (DCM_DEM_API_430_ENABLED == STD_ON)
#  define DCM_DEM_CLIENTID_ENABLED                                   STD_ON
# else
#  define DCM_DEM_CLIENTID_ENABLED                                   STD_OFF
# endif
# if (DCM_DIAG_OEM_NOTIFICATION_ENABLED == STD_ON) || \
     (DCM_DIAG_SYS_NOTIFICATION_ENABLED == STD_ON)
#  define DCM_DIAG_ANY_NOTIFICATION_ENABLED                          STD_ON
# else
#  define DCM_DIAG_ANY_NOTIFICATION_ENABLED                          STD_OFF
# endif

# if (DCM_DIAG_RCRRP_LIMIT_ENABLED == STD_ON) || \
     (DCM_NET_PROCESSING_CANCELLATION_ENABLED == STD_ON)
#  define DCM_DIAG_CANCEL_OP_ENABLED                                 STD_ON
# else
#  define DCM_DIAG_CANCEL_OP_ENABLED                                 STD_OFF
# endif

# if (DCM_NET_PROTOCOL_PRIORITISATION_ENABLED == STD_ON) && \
     (DCM_SPLIT_TASKS_ENABLED == STD_ON)
#  define DCM_DIAG_GARB_COL_ENABLED                                  STD_ON
# else
#  define DCM_DIAG_GARB_COL_ENABLED                                  STD_OFF
# endif

# if (DCM_NET_PROTOCOL_PRIORITISATION_ENABLED == STD_ON)
#  define DCM_DIAG_TOBJ_QUEUE_ENABLED                                STD_ON
# else
#  define DCM_DIAG_TOBJ_QUEUE_ENABLED                                STD_OFF
# endif

# if (DCM_NET_MULTI_PROTOCOL_ENABLED == STD_ON) || \
     (DCM_NET_MONITOR_FOREIGN_N_TA_ENABLED == STD_ON)
#  define DCM_DIAG_SYNCH_FLAGS_ENABLED                               STD_ON
# else
#  define DCM_DIAG_SYNCH_FLAGS_ENABLED                               STD_OFF
# endif

# if (DCM_DIAG_SYNCH_FLAGS_ENABLED == STD_ON)
#  define DCM_DIAG_PROCESSOR_FLAGS_ENABLED                           STD_ON
# else
#  define DCM_DIAG_PROCESSOR_FLAGS_ENABLED                           STD_OFF
# endif

# if (DCM_DIAG_TOBJ_QUEUE_ENABLED    == STD_ON) || \
     (DCM_DIAG_PROCESSOR_FLAGS_ENABLED == STD_ON)
#  define DCM_DIAG_SYNCH_DATA_SET_ENABLED                            STD_ON
# else
#  define DCM_DIAG_SYNCH_DATA_SET_ENABLED                            STD_OFF
# endif

# if (DCM_MULTI_THREAD_ENABLED == STD_ON) && \
     (DCM_DIAG_SPECIFIC_CAUSE_CODE_ENABLED == STD_ON)
#  error "Parallel service processing not supported in combination with SpecificCauseCode in negative response messages!"
# endif
/*! Decide whether any kind of multiple variant support on diagnostic entities is enabled */
# if (DCM_VARMGR_MULTI_SVC_EXCLUSIVE_ENABLED  == STD_ON) || \
     (DCM_VARMGR_MULTI_SVC_INCLUSIVE_ENABLED  == STD_ON)
#  define DCM_VARMGR_MULTI_SVC_ANY_ENABLED                           STD_ON
# else
#  define DCM_VARMGR_MULTI_SVC_ANY_ENABLED                           STD_OFF
# endif

# if (DCM_VARMGR_MODE_POSTBUILD_LOAD_ENABLED == STD_ON) || \
     (DCM_VARMGR_MODE_POSTBUILD_SELECT_ENABLED == STD_ON)
#  define DCM_VARMGR_MODE_POSTBUILD_ANY_ENABLED                      STD_ON
# else
#  define DCM_VARMGR_MODE_POSTBUILD_ANY_ENABLED                      STD_OFF
# endif
# if (DCM_SVC_10_SUPPORT_ENABLED == STD_ON)                                                                                                          /* COV_DCM_SUPPORT_ALWAYS TX */
#  if (DCM_SVC_10_JMP2BOOT_ENABLED == STD_ON)
#   if (DCM_SVC_10_RST2BOOT_HIS_ENABLED == STD_ON)
    /* never reached code since ECU is reset prior response transmission */
#   else
#    define DCM_SVC_10_RESET_AFTER_RESPONSE                          STD_ON
#   endif
#  endif

#  if defined(DCM_SVC_10_RESET_AFTER_RESPONSE)
/* already exists */
#  else
#   define DCM_SVC_10_RESET_AFTER_RESPONSE                           STD_OFF
#  endif
# endif /* (DCM_SVC_10_SUPPORT_ENABLED == STD_ON) */
/* ----------------------------------------------
 ~&&&   Defines
---------------------------------------------- */
# if (DCM_MEMMGR_SUPPORT_ENABLED == STD_ON)
/*!< Specifies the result of the callout for the memory access */
#  define DCM_MEMMGR_OP_RSLT_OK                                      ((Dcm_MemMgrOpResultType)0x00u) /*!< Memory access was successful */
#  define DCM_MEMMGR_OP_RSLT_PENDING                                 ((Dcm_MemMgrOpResultType)0x01u) /*!< Memory access is not yet finished */
#  define DCM_MEMMGR_OP_RSLT_FAILED                                  ((Dcm_MemMgrOpResultType)0x02u) /*!< Memory access was not successful */
#  define DCM_MEMMGR_OP_RSLT_FORCE_RCRRP                             ((Dcm_MemMgrOpResultType)0x03u) /*!< Memory access is not yet finished, the response pending transmission starts immediately */
/*!< Specifies the result of the Dcm_ReadMemory callout */
#  define DCM_READ_OK                                                DCM_MEMMGR_OP_RSLT_OK           /*!< Read of the memory was successful */
#  define DCM_READ_PENDING                                           DCM_MEMMGR_OP_RSLT_PENDING      /*!< Read of the memory is not yet finished */
#  define DCM_READ_FAILED                                            DCM_MEMMGR_OP_RSLT_FAILED       /*!< Read of the memory was not successful */
#  define DCM_READ_FORCE_RCRRP                                       DCM_MEMMGR_OP_RSLT_FORCE_RCRRP  /*!< Read of the memory is not yet finished, the response pending transmission starts immediately */
/*!< Specifies the result of the Dcm_WriteMemory callout */
#  define DCM_WRITE_OK                                               DCM_MEMMGR_OP_RSLT_OK           /*!< Write to the memory was successful */
#  define DCM_WRITE_PENDING                                          DCM_MEMMGR_OP_RSLT_PENDING      /*!< Write to the memory is not yet finished */
#  define DCM_WRITE_FAILED                                           DCM_MEMMGR_OP_RSLT_FAILED       /*!< Write to the memory was not successful */
#  define DCM_WRITE_FORCE_RCRRP                                      DCM_MEMMGR_OP_RSLT_FORCE_RCRRP  /*!< Write to the memory is not yet finished, the response pending transmission starts immediately */
# endif /* (DCM_MEMMGR_SUPPORT_ENABLED == STD_ON) */
/*! Default definition of a local-inline functions.
 *  Used a re-definable constant to have better debugging support at customer side.
 *  When needed, override this macro in a user configuration file: "#define DCM_LOCAL_INLINE".
 */
# if !defined (DCM_LOCAL_INLINE)                                                                                                                     /* COV_DCM_MACRO_OVERRIDE */
#  define DCM_LOCAL_INLINE                                           LOCAL_INLINE
# endif

/*! Default definition of a global-inline functions.
 *  Used a re-definable constant to have better debugging support at customer side.
 *  When needed, override this macro in a user configuration file: "#define DCM_GLOBAL_INLINE    DCM_LOCAL".
 */
# if !defined (DCM_GLOBAL_INLINE)                                                                                                                    /* COV_DCM_MACRO_OVERRIDE */
#  define DCM_GLOBAL_INLINE                                          LOCAL_INLINE
# endif

/*! Default definition of a static (module's internal and private) functions.
 * Used a re-definable constant to have better debugging support at customer side.
 * When needed, override this macro in a user configuration file: "#define DCM_LOCAL".
 */
# if !defined (DCM_LOCAL)                                                                                                                            /* COV_DCM_MACRO_OVERRIDE */
#  define DCM_LOCAL                                                  static
# endif
/*! Abstract definition of post-build loadable data memory qualifiers */
# if (DCM_VARMGR_MODE_POSTBUILD_LOAD_ENABLED == STD_ON)
/*! The constant (ROM) data is located in the post-build loadable memory area */
#  define DCM_CONST_PBCFG                                            DCM_PBCFG
/*! The variable (RAM) data is located in the post-build loadable memory area */
#  define DCM_RAM_PBCFG                                              DCM_VAR_PBCFG
# else
/*! The constant (ROM) data is located in the non-loadable ROM memory area */
#  define DCM_CONST_PBCFG                                            DCM_CONST
/*! The variable (RAM) data is located in the non-loadable RAM memory area */
#  define DCM_RAM_PBCFG                                              DCM_VAR_NOINIT
# endif

/*! Abstract declaration for PBL/PRE-COMPILE RAM tables */
# if (DCM_VARMGR_MODE_POSTBUILD_LOAD_ENABLED == STD_ON)
#  define DCM_PB_RAM_DATA_DECL(dataType, dataName, dataSize)         /* to be used PB configuration roots */
# else
#  define DCM_PB_RAM_DATA_DECL(dataType, dataName, dataSize)         dataType dataName[dataSize];
# endif
/*! Specifies volatile any data that can be modified within a high-priority task/ISR */
# if (DCM_SPLIT_TASKS_ENABLED == STD_ON)
#  define DCM_VOLATILE_ON_SPLITTASK                                  volatile
# else
#  define DCM_VOLATILE_ON_SPLITTASK                                  /* not used */
# endif
/*! AR DCM generic return codes */
# define DCM_E_OK                                                    ((Std_ReturnType)E_OK)       /*!< Successful operation */
# define DCM_E_NOT_OK                                                ((Std_ReturnType)E_NOT_OK)   /*!< Failed operation with no specific reason (except when NRC is returned in addition) */

# define DCM_E_PROTOCOL_NOT_ALLOWED                                  ((Std_ReturnType)5)          /*!< The protocol change is not allowed by the application (Xxx_StartProtocol()) */

# define DCM_E_ROE_NOT_ACCEPTED                                      ((Std_ReturnType)6)          /*!< An externally triggered RoE STRT is not accepted by DCM (e.g. another request is still in processing) */
# define DCM_E_PERIODICID_NOT_ACCEPTED                               ((Std_ReturnType)7)          /*!< Deprecated: A periodic transmission request is not accepted */

# define DCM_E_REQUEST_NOT_ACCEPTED                                  ((Std_ReturnType)8)          /*!< The new request is not accepted by the application (Xxx_Indication()) */
# define DCM_E_PENDING                                               ((Std_ReturnType)10)         /*!< Invoked callout (operation) needs to be called again */
# define DCM_E_COMPARE_KEY_FAILED                                    ((Std_ReturnType)11)         /*!< The security key is invalid (Xxx_CompareKey()) */

# define DCM_E_FORCE_RCRRP                                           ((Std_ReturnType)12)         /*!< Invoked callout (operation) requests an immediate RCR-RP response transmission and needs to be called again once it is (successfully or not) sent */
/*! Vendor specific return values */
# define DCM_E_PROCESSINGDONE                                        ((Std_ReturnType)40)         /*!< (Sub-)service processor callout finished the processing. DCM core will take over again */
# define DCM_E_LOOP                                                  ((Std_ReturnType)41)         /*!< Invoked repeater-proxy requests an immediate (within the same Dcm_MainFunction() activation) reactivation of the (next) repeater proxy in the chain */
# define DCM_E_BUFFERTOOLOW                                          ((Std_ReturnType)42)         /*!< Invoked callout (operation) detected not enough buffer to accomplish the operation */
/* Deprecated!
#define DCM_E_NOCOMMMODE                                             ((Std_ReturnType)43) */      /*!< Deprecated: Not used any more, but keeps the ordinary value gap filled for backward compatibility */

# define DCM_E_PENDING_LIMITER                                       ((Std_ReturnType)44)         /*!< Similar to DCM_E_PENDING, but used from the DCM's core engine to preserve the old OpStatus value. Shall not be used by any application code */
# define DCM_E_LOOKUP_MATCH_FOUND                                    ((Std_ReturnType)45)         /*!< Used by DCM core engine to signal that a lookup match found, but the result still negative since rejected for other reasons */
# define DCM_E_DATA_READY_PADDING                                    ((Std_ReturnType)46)         /*!< Similar to DCM_E_OK returned by Xxx_UpdatePage() callout signaling that no further data available and shall not be called any more */
# define DCM_E_STOP_REPEATER                                         ((Std_ReturnType)47)         /*!< Stop Repeater Proxy */
/* Override generated DCM version by the MSR one from compiler.h */
# if defined(MSR_PDUR_API_AR_VERSION)
#  define DCM_USED_PDUR_API_AR_VERSION                               MSR_PDUR_API_AR_VERSION
# else
#  define DCM_USED_PDUR_API_AR_VERSION                               DCM_PDUR_API_AR_VERSION
# endif

# if (DCM_USED_PDUR_API_AR_VERSION != 0x412u)
#  error "Not supported DCM/MSR PduR version! No PduR BSWMD file in your MSR project?"
# endif

/*! Specifies size of temporary buffer for SID and sub-function byte as well as NRCs 0x78 and 0x21 in USDT transport object (optional sepcific cause code) */
# if (DCM_DIAG_SPECIFIC_CAUSE_CODE_ENABLED == STD_ON)
#  define DCM_NET_TOBJ_ADDBUFFER_SIZE                                4u
# else
#  define DCM_NET_TOBJ_ADDBUFFER_SIZE                                3u
# endif
/*! ECU power on types for Dcm_GetProgConditions() */
# define DCM_COLD_START                                              ((Dcm_EcuStartModeType)0x00u)  /*!< Normal start */
# define DCM_WARM_START                                              ((Dcm_EcuStartModeType)0x01u)  /*!< Start after FBL programming finished */

/*! Default definition for a panic NRC. It can be overridden via DCM user-configuration file */
# if !defined (DCM_E_PANIC_NRC)                                                                                                                      /* COV_DCM_MACRO_OVERRIDE */
#  define DCM_E_PANIC_NRC                                            DCM_E_GENERALREJECT
# endif
# if (DCM_SVC_28_SUPPORT_ENABLED == STD_ON)
#  define DCM_SVC_28_NETWORK_ALL                                     ((NetworkHandleType)0xFFu)
#  define DCM_SVC_28_NETWORK_CURRENT                                 ((NetworkHandleType)0xFEu)
# endif /* (DCM_SVC_28_SUPPORT_ENABLED == STD_ON) */
/* ----------------------------------------------
 ~&&&   Function-like macros
---------------------------------------------- */
/* Data type templates */

/*! Template of classic stack data structure */
# define Dcm_UtiStackType(baseType, size)                            struct \
                                                                     { \
                                                                     baseType Stack[(size)];        /*!< A stack of elements of a specific type */ \
                                                                     Dcm_UtiStackCntrType StackTop; /*!< Pointer to the current top element of the stack */ \
                                                                     }                                                                               /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Template of simple pair of data */
# define Dcm_UtiPairType(firstType, secondType)                      struct \
                                                                     { \
                                                                     firstType  First;  /*!< The first element of the pair */ \
                                                                     secondType Second; /*!< The second element of the pair */ \
                                                                     }                                                                               /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/* ----------------------------------------------
 ~&&&   Typedefs
---------------------------------------------- */
# if (DCM_MEMMGR_SUPPORT_ENABLED == STD_ON)
typedef uint8 Dcm_MemMgrOpResultType;
typedef Dcm_MemMgrOpResultType Dcm_ReturnReadMemoryType;
typedef Dcm_MemMgrOpResultType Dcm_ReturnWriteMemoryType;
# endif /* (DCM_MEMMGR_SUPPORT_ENABLED == STD_ON) */
/*******************************
 ***  DCM common types
 *******************************/
/*! AR base data type for eventually processed parallel requests (not supported yet) */
typedef uint8                                                   Dcm_IdContextType;
typedef uint8                                                   Dcm_IdThreadType;
/*! Generic ANSI-C bit type for structure data types */
typedef unsigned int                                            Dcm_BitForStructType;
/*! AR base data type for diagnostic message item type */
typedef uint8                                                   Dcm_MsgItemType;
/*! AR base data type for a pointer to a readable and writable diagnostic message buffer located in the pre-compile DCM RAM area */
typedef P2VAR(Dcm_MsgItemType, TYPEDEF, DCM_VAR_NOINIT)         Dcm_MsgType;
/*! Base data type for a pointer to a read-only diagnostic message buffer located in the pre-compile DCM RAM area */
typedef P2CONST(Dcm_MsgItemType, TYPEDEF, DCM_VAR_NOINIT)       Dcm_ReadOnlyMsgType;
/*! Base data type for a non changeable pointer to a readable and writable diagnostic message buffer located in the pre-compile DCM RAM area */
typedef CONSTP2VAR(Dcm_MsgItemType, TYPEDEF, DCM_VAR_NOINIT)    Dcm_ConstMsgType;
/*! Base data type for a non changeable pointer to a readable diagnostic message buffer located in the pre-compile DCM RAM area */
typedef CONSTP2CONST(Dcm_MsgItemType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_ConstReadOnlyMsgType;
/*! Base data type for a non changeable pointer to a readable and writeable diagnostic message buffer located in the post-build loadable DCM RAM area */
typedef CONSTP2VAR(Dcm_MsgItemType, TYPEDEF, DCM_RAM_PBCFG)     Dcm_PbConstMsgType;
/*! Base data type for a pointer to a readable and writable diagnostic message buffer located outside of the DCMs RAM area (i.e. within another BSW or application code) */
typedef P2VAR(Dcm_MsgItemType, TYPEDEF, DCM_APPL_DATA)          Dcm_ApplMsgType;

/*! AR data type for a diagnostic message length */
typedef uint32                                                  Dcm_MsgLenType;

/*! Data type for an abstract pointer to a readable and writable DCM global RAM area of unknown data type */
typedef P2VAR(void, TYPEDEF, DCM_VAR_NOINIT)                    Dcm_GenericDcmRamNoInitPtrType;
/*! Data type for an abstract pointer to a read-only DCM global RAM area of unknown data type */
typedef P2CONST(void, TYPEDEF, DCM_VAR_NOINIT)                  Dcm_GenericDcmConstRamNoInitPtrType;

/*! Base data type for a pointer to a readable and writable 8bit data on the function stack */
typedef P2VAR(uint8, TYPEDEF, AUTOMATIC)                        Dcm_Ptr2LocalU8Type;
/*! Base data type for a pointer to a readable and writable 16bit data on the function stack */
typedef P2VAR(uint16, TYPEDEF, AUTOMATIC)                       Dcm_Ptr2LocalU16Type;
/*! Base data type for a pointer to a readable and writable Dcm_MsgLenType data defined globally */
typedef P2VAR(Dcm_MsgLenType, TYPEDEF, DCM_VAR_NOINIT)          Dcm_MsgLenPtrType;

/*! Base data type for a pointer to a readable and writable 8bit data defined globally */
typedef P2VAR(uint8, TYPEDEF, DCM_VAR_NOINIT)                   Dcm_Uint8VarDataPtrType;
/*! Base data type for a pointer to a readable and writable 16bit data defined globally */
typedef P2VAR(uint16, TYPEDEF, DCM_VAR_NOINIT)                  Dcm_Uint16VarDataPtrType;
/*! Base data type for a pointer to a readable and writable 32bit data defined globally */
typedef P2VAR(uint32, TYPEDEF, DCM_VAR_NOINIT)                  Dcm_Uint32VarDataPtrType;

/*! Base data type for a non changeable pointer to a constant (ROM) 8bit data defined globally */
typedef CONSTP2CONST(uint8, TYPEDEF, DCM_CONST)                 Dcm_Uint8ConstDataConstPtrType;
/*! Base data type for a non changeable pointer to a constant (ROM) 16bit data defined globally */
typedef CONSTP2CONST(uint16, TYPEDEF, DCM_CONST)                Dcm_Uint16ConstDataConstPtrType;
/*! Base data type for a non changeable pointer to a constant (ROM) 32bit data defined globally */
typedef CONSTP2CONST(uint32, TYPEDEF, DCM_CONST)                Dcm_Uint32ConstDataConstPtrType;
/*! Base data type for a non changeable pointer to a constant but calibratable 32bit data defined globally */
typedef CONSTP2CONST(uint32, TYPEDEF, DCM_CAL_PRM)              Dcm_Uint32CalibDataConstPtrType;

/*! Base data type for a pointer to a constant (ROM) 8bit data defined globally */
typedef P2CONST(uint8, TYPEDEF, DCM_CONST)                      Dcm_Uint8ConstDataPtrType;
/*! Base data type for a pointer to a constant (ROM) 16bit data defined globally */
typedef P2CONST(uint16, TYPEDEF, DCM_CONST)                      Dcm_Uint16ConstDataPtrType;
/*! Base data type for a pointer to a constant (ROM) 32bit data defined globally */
typedef P2CONST(uint32, TYPEDEF, DCM_CONST)                     Dcm_Uint32ConstDataPtrType;
/*! Base data type for a pointer to a constant but calibratable 32bit data defined globally */
typedef P2CONST(uint32, TYPEDEF, DCM_CAL_PRM)                   Dcm_Uint32CalibDataPtrType;

/*! Deprecated: An obsolete pre AR4.x DCM specific return data type (now using Std_ReturnType) */
typedef Std_ReturnType                                          Dcm_StatusType;

/*! A definition of a range of uint16 values */
typedef Dcm_UtiPairType(uint16, uint16) Dcm_UtiU16RangeType;
/*! Data type for DET error codes */
typedef uint8 Dcm_DetErrorCodeType;

/*! Data type for DET API IDs */
typedef uint8 Dcm_DetApiIdType;
/*! Data type for critical error detection API IDs */
typedef uint8 Dcm_ExtendedSidType;
/*! Zero based reference to a USDT diagnostic client connection configuration entry (0..31) */
typedef uint8        Dcm_NetConnRefMemType;
typedef uint8_least  Dcm_NetConnRefOptType;

/*! Zero based reference to a diagnostic protocol configuration entry (0..31) */
typedef uint8        Dcm_NetProtRefMemType;
typedef uint8_least  Dcm_NetProtRefOptType;
/*! Base data type for a diagnostic state (e.g. session, security access) identification (0..31) */
typedef uint8       Dcm_StateIndexMemType;
typedef uint8_least Dcm_StateIndexOptType;
typedef uint16 Dcm_TmrTimerCntrMemType;
typedef uint16_least Dcm_TmrTimerCntrOptType;
# if (DCM_OBDUDSIDMGR_SUPPORT_ENABLED == STD_ON)
#  if (DCM_OBDUDSIDMGR_CALIBRATION_ENABLED == STD_ON)
typedef Dcm_Uint32CalibDataPtrType      Dcm_ObdMaskConstDataPtrType;
#  else
typedef Dcm_Uint32ConstDataPtrType      Dcm_ObdMaskConstDataPtrType;
#  endif

typedef uint32 Dcm_ObdIdMgrMaskValueTableType;
# endif /* (DCM_OBDUDSIDMGR_SUPPORT_ENABLED == STD_ON) */
typedef uint8 Dcm_EcuStartModeType;
typedef Dcm_MsgLenType Dcm_DiagBufferIndexType;

/*! Programming condition information */
struct DCM_PROGCONDITIONSTYPE_TAG
{
  uint16  TesterSourceAddr;     /*!< The client ID (source address). Note: AR 4.0.3 specifics the client ID to be a U8 for this API, but the connection configuration has a 16 Bit value! */
  uint8   ProtocolId;           /*!< The protocol ID */
  uint8   Sid;                  /*!< The request SID to be responded to */
  uint8   SubFuncId;            /*!< The sub-function ID to be responded to */
  boolean ReprogrammingRequest; /*!< Specifies whether an ECU preprogramming is needed (TRUE - ECU reprogramming, FALSE - no ECU reprogramming) */
  boolean ApplUpdated;          /*!< Specifies whether the application has been updated (TRUE - application updated, FALSE - no application updated) */
  boolean ResponseRequired;     /*!< Specifies whether a response to the SID and sub-function has to be sent (TRUE) or just the requested diagnostic session shall be entered (FALSE) */
};
typedef struct DCM_PROGCONDITIONSTYPE_TAG Dcm_ProgConditionsType;
typedef P2VAR(Dcm_ProgConditionsType, TYPEDEF, DCM_VAR_NOINIT) Dcm_ProgConditionsPtrType;

/*! Diagnostic application timing (P2) pair */
struct DCM_DIAGP2TIMINGSTYPE_TAG
{
  Dcm_TmrTimerCntrMemType P2;     /*!< The P2 time (in Dcm_MainFunction ticks) */
  Dcm_TmrTimerCntrMemType P2Star; /*!< The P2* time (in Dcm_MainFunction ticks) */
};
typedef struct DCM_DIAGP2TIMINGSTYPE_TAG Dcm_DiagP2TimingsType;

/*! Additional information about a request */
struct DCMMSGADDINFO_TAG
{
  Dcm_BitForStructType reqType               :1; /*!< Specifies the diagnostic request type (0 - physical, 1 - functional) */
  Dcm_BitForStructType suppressPosResponse   :1; /*!< Represents the SPRMIB state at request time and during service processing (e.g. after P2 timeout)( 0 - do not suppress positive response, 1 - do suppress positive response) */
};
typedef struct DCMMSGADDINFO_TAG Dcm_MsgAddInfoType;

/*! Context information of a diagnostic request */
struct DCM_MSGCONTEXT_TAG
{
  Dcm_MsgLenType                reqDataLen;    /*!< Remaining request data length (decremented on each diagnostic service request data evaluation stage) */
  Dcm_MsgLenType                resDataLen;    /*!< Current response data length (incremented on each diagnostic service response data provision stage) */
  Dcm_MsgLenType                resMaxDataLen; /*!< Remaining buffer size for response data (contains the maximum buffer size left after any response data has been added at a given stage) */
  Dcm_MsgLenType                reqBufSize;    /*!< Size of request buffer */
  Dcm_MsgLenType                resBufSize;    /*!< Size of response buffer */
  Dcm_MsgType                   reqData;       /*!< Points to the request data buffer to be evaluated or passed to the application, depending on the request data evaluation stage */
  Dcm_MsgType                   resData;       /*!< Points to the response data buffer to be written or passed to the application to provide data at, depending on the response data provision stage */
  Dcm_DiagBufferIndexType       reqIndex;      /*!< Index to the next request data byte to be evaluated or passed to the application, depending on the request data evaluation stage */
  Dcm_DiagBufferIndexType       resIndex;      /*!< Index to the next response data byte to be written or passed to the application to provide data at, depending on the response data provision stage */
  Dcm_DiagBufferIndexType       resProtHeadLen;/*!< Keeps track of the already provided response protocol header */
  Dcm_MsgAddInfoType            msgAddInfo;    /*!< Additional diagnostic request message information */
  PduIdType                     rxPduId;       /*!< The DcmRxPduId on which the diagnostic request is received */
  Dcm_IdContextType             idContext;     /*!< Specifies the DCM instance for multi-server purposes */
  Dcm_IdThreadType              threadId;      /*!< Specifies the DCM thread-id for parallel service processing */
};

typedef struct DCM_MSGCONTEXT_TAG Dcm_MsgContextType;

typedef P2VAR(Dcm_MsgContextType, TYPEDEF, DCM_VAR_NOINIT) Dcm_MsgContextPtrType;
typedef P2CONST(Dcm_MsgContextType, TYPEDEF, DCM_VAR_NOINIT) Dcm_ReadOnlyMsgContextPtrType;

/*! Generic diagnostic data container descriptor */
struct DCM_DIAGDATACONTEXTTYPE_TAG
{
  Dcm_MsgType     Buffer;    /*!< Points to the beginning of a data buffer */
  Dcm_MsgLenType  Size;      /*!< Specifies the total size of the referenced buffer */
  Dcm_MsgLenType  Usage;     /*!< Keeps track of the used space in the referenced buffer */
  Dcm_MsgLenType  AvailLen;  /*!< Remaining number of bytes that can be written */
};
typedef struct DCM_DIAGDATACONTEXTTYPE_TAG Dcm_DiagDataContextType;
typedef P2VAR(Dcm_DiagDataContextType, TYPEDEF, DCM_VAR_NOINIT) Dcm_DiagDataContextPtrType;
typedef P2CONST(Dcm_DiagDataContextType, TYPEDEF, DCM_VAR_NOINIT) Dcm_DiagDataContextConstPtrType;

/*! Generic pointer to a diagnostic ErrorCode (NRC) in DCM related RAM */
typedef P2VAR(Dcm_NegativeResponseCodeType, TYPEDEF, DCM_VAR_NOINIT) Dcm_NegativeResponseCodePtrType;

# if (DCM_DIAG_STATE_RECOVERY_ENABLED == STD_ON)
/*! Container with all information to be recovered after ECU reset/power down, including verification signature */
struct DCM_RECOVERYINFOTYPE_TAG
{
#  if (DCM_MODE_CTRLDTCSETTING_ENABLED == STD_ON)
#   if (DCM_SVC_85_DTC_GRP_ENABLED == STD_ON)
  uint32                     ControlDTCSettingDTCGroup; /*!< The ControlDTCSetting DTC group to be addressed */
#   endif
  boolean                    ControlDTCSettingDisabled; /*!< The ControlDTCSetting state (TRUE - DTC setting is disabled, FALSE - DTC setting is enabled) */
#  endif
  boolean                    ComMChannelState[DCM_NET_MAX_NUM_COMM_CHANNELS];  /*!< The DCM related ComM channel communication state (TRUE - "DiagActive", FALSE - "DiagInactive") */
#  if (DCM_MODE_COMMCTRL_ENABLED == STD_ON)
  Dcm_CommunicationModeType  CommControlState[DCM_NET_MAX_NUM_ALL_COMM_CHANNELS]; /*!< The ComM channel related communication state (e.g. DCM_ENABLE_RX_TX_NORM etc.) */
#  endif
  Dcm_StateIndexMemType      SessionLevel;              /*!< The diagnostic session as a state index (i.e. 0 - default, 1..N - non-default) */
#  if (DCM_STATE_SECURITY_ENABLED == STD_ON)
  Dcm_StateIndexMemType      SecurityLevel;             /*!< The security access level as a state index (i.e. 0 - locked, 1..N - unlocked level X) */
#  endif
  Dcm_NetConnRefMemType      SessionConnection;         /*!< The diagnostic client connection ID that has initiated the non-default session (if non-default session was active) */
#  if (DCM_NET_MULTI_PROTOCOL_ENABLED == STD_ON)
  Dcm_NetProtRefMemType      ActiveProtocol;            /*!< The protocol handle last activated */
#  endif
  uint32                     Signature;                 /*!< Content verification signature (placed at the end for better reliability of its value) */
};
typedef struct DCM_RECOVERYINFOTYPE_TAG Dcm_RecoveryInfoType;

/*! Generic pointer to a ComM channel state of the recovery info */
typedef P2VAR(boolean, TYPEDEF, DCM_VAR_NOINIT) Dcm_RecoveryInfoComMChannelStatePtrType;
/*! Generic pointer to a communication state of the recovery info */
typedef P2VAR(boolean, TYPEDEF, DCM_VAR_NOINIT) Dcm_RecoveryInfoCommControlStatePtrType;

/*! Recovery context containing the operation state and the recovery information */
struct DCM_RECOVERYCONTEXTTYPE_TAG
{
  Dcm_RecoveryInfoType RecoveryInfo;  /*!< Recovery information */
  Dcm_OpStatusType     OpStatus;      /*!< Current operation status */
};
typedef struct DCM_RECOVERYCONTEXTTYPE_TAG Dcm_RecoveryContextType;
# endif
# if (DCM_SVC_10_SUPPORT_ENABLED == STD_ON)                                                                                                          /* COV_DCM_SUPPORT_ALWAYS TX */
/*! Diagnostic service 0x10 boot loader interaction types */
#  define DCM_SVC10_BOOT_TYPE_NONE                                   (Dcm_Svc10SessionBootType)0 /*!< No bootloader interaction (just session state change) */
#  define DCM_SVC10_BOOT_TYPE_OEM                                    (Dcm_Svc10SessionBootType)1 /*!< Performs jump to the OEM bootloader */
#  define DCM_SVC10_BOOT_TYPE_SYS                                    (Dcm_Svc10SessionBootType)2 /*!< Performs jump to the system supplier bootloader */
typedef uint8 Dcm_Svc10SessionBootType;

/*! Diagnostic service 0x10 positive response P2 timings configuration data */
struct DCM_SVC10P2TIMINGSTYPE_TAG
{
  uint16 P2;      /*!< The P2 time in 1ms resolution */
  uint16 P2Star;  /*!< The P2* time in 10ms resolution */
};
typedef struct DCM_SVC10P2TIMINGSTYPE_TAG Dcm_Svc10P2TimingsType;
# endif /* (DCM_SVC_10_SUPPORT_ENABLED == STD_ON) */
#endif /* !defined(DCM_CORETYPES_H) */
/* ********************************************************************************************************************
 * END OF FILE: Dcm_CoreTypes.h
 * ******************************************************************************************************************** */
