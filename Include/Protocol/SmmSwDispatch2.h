/** @file
  SMM Software Dispatch Protocol introduced from PI 1.2 Specification
  Volume 4 System Management Mode Core Interface.

  This protocol provides the parent dispatch service for a given SMI source generator.

  Copyright (c) 2009 - 2018, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#ifndef _SMM_SW_DISPATCH2_H_
#define _SMM_SW_DISPATCH2_H_

//////////////////////////////////////////////////#include <Protocol/MmSwDispatch.h>
//////////////////////////////////////////////////#include <Pi/PiSmmCis.h>

#define EFI_SMM_SW_DISPATCH2_PROTOCOL_GUID  EFI_MM_SW_DISPATCH_PROTOCOL_GUID

///
/// A particular chipset may not support all possible software SMI input values.
/// For example, the ICH supports only values 00h to 0FFh.  The parent only allows a single
/// child registration for each SwSmiInputValue.
///
typedef struct {
  UINTN    SwSmiInputValue;
} EFI_SMM_SW_REGISTER_CONTEXT;

///
/// The DispatchFunction will be called with Context set to the same value as was passed into
/// this function in RegisterContext and with CommBuffer (and CommBufferSize) pointing
/// to an instance of EFI_SMM_SW_CONTEXT indicating the index of the CPU which generated the
/// software SMI.
///
typedef struct {
  ///
  /// The 0-based index of the CPU which generated the software SMI.
  ///
  UINTN    SwSmiCpuIndex;
  ///
  /// This value corresponds directly to the CommandPort parameter used in the call to Trigger().
  ///
  UINT8    CommandPort;
  ///
  /// This value corresponds directly to the DataPort parameter used in the call to Trigger().
  ///
  UINT8    DataPort;
} EFI_SMM_SW_CONTEXT;

typedef struct _EFI_SMM_SW_DISPATCH2_PROTOCOL EFI_SMM_SW_DISPATCH2_PROTOCOL;

/**
  Register a child SMI source dispatch function for the specified software SMI.

  This service registers a function (DispatchFunction) which will be called when the software
  SMI source specified by RegisterContext->SwSmiCpuIndex is detected. On return,
  DispatchHandle contains a unique handle which may be used later to unregister the function
  using UnRegister().

  @param[in]  This                 Pointer to the EFI_SMM_SW_DISPATCH2_PROTOCOL instance.
  @param[in]  DispatchFunction     Function to register for handler when the specified software
                                   SMI is generated.
  @param[in, out] RegisterContext  Pointer to the dispatch function's context.
                                   The caller fills this context in before calling
                                   the register function to indicate to the register
                                   function which Software SMI input value the
                                   dispatch function should be invoked for.
  @param[out] DispatchHandle       Handle generated by the dispatcher to track the
                                   function instance.

  @retval EFI_SUCCESS            The dispatch function has been successfully
                                 registered and the SMI source has been enabled.
  @retval EFI_DEVICE_ERROR       The SW driver was unable to enable the SMI source.
  @retval EFI_INVALID_PARAMETER  RegisterContext is invalid. The SW SMI input value
                                 is not within a valid range or is already in use.
  @retval EFI_OUT_OF_RESOURCES   There is not enough memory (system or SMM) to manage this
                                 child.
  @retval EFI_OUT_OF_RESOURCES   A unique software SMI value could not be assigned
                                 for this dispatch.
**/
typedef
EFI_STATUS
(EFIAPI *EFI_SMM_SW_REGISTER2)(
  IN  CONST EFI_SMM_SW_DISPATCH2_PROTOCOL  *This,
  IN        EFI_SMM_HANDLER_ENTRY_POINT2   DispatchFunction,
  IN  OUT   EFI_SMM_SW_REGISTER_CONTEXT    *RegisterContext,
  OUT       EFI_HANDLE                     *DispatchHandle
  );

/**
  Unregister a child SMI source dispatch function for the specified software SMI.

  This service removes the handler associated with DispatchHandle so that it will no longer be
  called in response to a software SMI.

  @param[in] This                Pointer to the EFI_SMM_SW_DISPATCH2_PROTOCOL instance.
  @param[in] DispatchHandle      Handle of dispatch function to deregister.

  @retval EFI_SUCCESS            The dispatch function has been successfully unregistered.
  @retval EFI_INVALID_PARAMETER  The DispatchHandle was not valid.
**/
typedef
EFI_STATUS
(EFIAPI *EFI_SMM_SW_UNREGISTER2)(
  IN CONST EFI_SMM_SW_DISPATCH2_PROTOCOL  *This,
  IN       EFI_HANDLE                     DispatchHandle
  );

///
/// Interface structure for the SMM Software SMI Dispatch Protocol.
///
/// The EFI_SMM_SW_DISPATCH2_PROTOCOL provides the ability to install child handlers for the
/// given software.  These handlers will respond to software interrupts, and the maximum software
/// interrupt in the EFI_SMM_SW_REGISTER_CONTEXT is denoted by MaximumSwiValue.
///
struct _EFI_SMM_SW_DISPATCH2_PROTOCOL {
  EFI_SMM_SW_REGISTER2      Register;
  EFI_SMM_SW_UNREGISTER2    UnRegister;
  ///
  /// A read-only field that describes the maximum value that can be used in the
  /// EFI_SMM_SW_DISPATCH2_PROTOCOL.Register() service.
  ///
  UINTN                     MaximumSwiValue;
};

extern EFI_GUID  gEfiSmmSwDispatch2ProtocolGuid;

#endif