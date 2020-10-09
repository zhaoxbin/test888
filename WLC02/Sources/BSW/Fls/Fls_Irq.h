/*============================================================================*/
/* Project      = AUTOSAR Renesas X1x MCAL Components                         */
/* Module       = Fls_Irq.h                                                   */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* Copyright(c) 2015 - 2018 Renesas Electronics Corporation                   */
/*============================================================================*/
/* Purpose:                                                                   */
/* Provision for prototypes of Interrupt Service Routines.                    */
/*============================================================================*/
/*                                                                            */
/* Unless otherwise agreed upon in writing between your company and           */
/* Renesas Electronics Corporation the following shall apply!                 */
/*                                                                            */
/* Warranty Disclaimer                                                        */
/*                                                                            */
/* There is no warranty of any kind whatsoever granted by Renesas. Any        */
/* warranty is expressly disclaimed and excluded by Renesas, either expressed */
/* or implied, including but not limited to those for non-infringement of     */
/* intellectual property, merchantability and/or fitness for the particular   */
/* purpose.                                                                   */
/*                                                                            */
/* Renesas shall not have any obligation to maintain, service or provide bug  */
/* fixes for the supplied Product(s) and/or the Application.                  */
/*                                                                            */
/* Each User is solely responsible for determining the appropriateness of     */
/* using the Product(s) and assumes all risks associated with its exercise    */
/* of rights under this Agreement, including, but not limited to the risks    */
/* and costs of program errors, compliance with applicable laws, damage to    */
/* or loss of data, programs or equipment, and unavailability or              */
/* interruption of operations.                                                */
/*                                                                            */
/* Limitation of Liability                                                    */
/*                                                                            */
/* In no event shall Renesas be liable to the User for any incidental,        */
/* consequential, indirect, or punitive damage (including but not limited     */
/* to lost profits) regardless of whether such liability is based on breach   */
/* of contract, tort, strict liability, breach of warranties, failure of      */
/* essential purpose or otherwise and even if advised of the possibility of   */
/* such damages. Renesas shall not be liable for any services or products     */
/* provided by third party vendors, developers or consultants identified or   */
/* referred to the User by Renesas in connection with the Product(s) and/or   */
/* the Application.                                                           */
/*                                                                            */
/*============================================================================*/
/* Environment:                                                               */
/*              Devices:        X1x                                           */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * V1.0.0:  08-Oct-2015  : Initial Version
 *
 * V1.1.0:  28-Sep-2016  :  #ARDAABD-843
 *                          1. Removed support for
 *                             FLS_AR_HIGHER_VERSION / FLS_AR_LOWER_VERSION
 * V2.0.0:  11-Nov-2016  : #ARDAABD-732 - Added interrupt mapping for DMA ISRs
 * V2.0.1:  02-Oct-2017  : #ARDAABD-2489 Support is added for DMA interrupts of
 *                         F1KM-S4 devices.
 * V2.0.2:  17-Apr-2018  : Following changes were made:
 *                         1. As per merging activity, #ARDAABD-3466
 *                            below changes were made (Ref:ARDAABD-3257):
 *                          a. Support is added for DMA interrupts of
 *                             F1KH devices.
 *                          b. Copyright information is updated.
 */
/******************************************************************************/
#ifndef FLS_IRQ_H
#define FLS_IRQ_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Fls_Ram.h"
#include "Fls_Types.h"
/* Included for interrupt category definitions */
#include "Os.h"
/*******************************************************************************
**                      Version Information                                  **
*******************************************************************************/
/* AUTOSAR Release version information */
#define FLS_IRQ_AR_RELEASE_MAJOR_VERSION        FLS_AR_RELEASE_MAJOR_VERSION
#define FLS_IRQ_AR_RELEASE_MINOR_VERSION        FLS_AR_RELEASE_MINOR_VERSION
#define FLS_IRQ_AR_RELEASE_REVISION_VERSION     FLS_AR_RELEASE_REVISION_VERSION


/* File version information */
#define FLS_IRQ_SW_MAJOR_VERSION                FLS_SW_MAJOR_VERSION
#define FLS_IRQ_SW_MINOR_VERSION                FLS_SW_MINOR_VERSION

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/


#endif  /* FLS_IRQ_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
