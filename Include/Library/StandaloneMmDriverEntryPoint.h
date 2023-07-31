/** @file
  Module entry point library for Standalone MM Drivers.

Copyright (c) 2006 - 2008, Intel Corporation. All rights reserved.<BR>
Copyright (c) 2016 - 2018, ARM Limited. All rights reserved.<BR>
Copyright (c) 2018, Linaro, Limited. All rights reserved.<BR>

SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#ifndef __MODULE_ENTRY_POINT_H__
#define __MODULE_ENTRY_POINT_H__

///
/// Declare the PI Specification Revision that this driver requires to execute
/// correctly.
///
extern CONST UINT32  _gMmRevision;

///
/// Declare the number of unload handler in the image.
///
extern CONST UINT8  _gDriverUnloadImageCount;

/**
  The entry point of PE/COFF Image for a Standalone MM Driver.

  This function is the entry point for a Standalone MM Driver.
  This function must call ProcessLibraryConstructorList() and
  ProcessModuleEntryPointList().
  If the return status from ProcessModuleEntryPointList()
  is an error status, then ProcessLibraryDestructorList() must be called.
  The return value from ProcessModuleEntryPointList() is returned.
  If _gMmRevision is not zero and MmSystemTable->Hdr.Revision is
  less than _gMmRevision, then return EFI_INCOMPATIBLE_VERSION.

  @param  ImageHandle    The image handle of the Standalone MM Driver.
  @param  MmSystemTable  A pointer to the MM System Table.

  @retval  EFI_SUCCESS               The Standalone MM Driver exited normally.
  @retval  EFI_INCOMPATIBLE_VERSION  _gMmRevision is greater than
                                     MmSystemTable->Hdr.Revision.
  @retval  Other                     Return value from
                                     ProcessModuleEntryPointList().

**/
EFI_STATUS
EFIAPI
_ModuleEntryPoint (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_MM_SYSTEM_TABLE  *MmSystemTable
  );

/**
  Auto generated function that calls the library constructors for all of the
  module's dependent libraries.

  This function must be called by _ModuleEntryPoint().
  This function calls the set of library constructors for the set of library
  instances that a module depends on.  This includes library instances that a
  module depends on directly and library instances that a module depends on
  indirectly through other libraries. This function is auto generated by build
  tools and those build tools are responsible for collecting the set of library
  instances, determine which ones have constructors, and calling the library
  constructors in the proper order based upon each of the library instances own
  dependencies.

  @param  ImageHandle    The image handle of the Standalone MM Driver.
  @param  MmSystemTable  A pointer to the MM System Table.

**/
VOID
EFIAPI
ProcessLibraryConstructorList (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_MM_SYSTEM_TABLE  *MmSystemTable
  );

/**
  Auto generated function that calls the library descructors for all of the
  module's dependent libraries.

  This function may be called by _ModuleEntryPoint().
  This function calls the set of library destructors for the set of library
  instances that a module depends on. This includes library instances that a
  module depends on directly and library instances that a module depends on
  indirectly through other libraries.
  This function is auto generated by build tools and those build tools are
  responsible for collecting the set of library instances, determine which ones
  have destructors, and calling the library destructors in the proper order
  based upon each of the library instances own dependencies.

  @param  ImageHandle    The image handle of the Standalone MM Driver.
  @param  MmSystemTable  A pointer to the MM System Table.

**/
VOID
EFIAPI
ProcessLibraryDestructorList (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_MM_SYSTEM_TABLE  *MmSystemTable
  );

/**
  Auto generated function that calls a set of module entry points.

  This function must be called by _ModuleEntryPoint().
  This function calls the set of module entry points.
  This function is auto generated by build tools and those build tools are
  responsible for collecting the module entry points and calling them in a
  specified order.

  @param  ImageHandle    The image handle of the Standalone MM Driver.
  @param  MmSystemTable  A pointer to the MM System Table.

  @retval  EFI_SUCCESS   The Standalone MM Driver executed normally.
  @retval  !EFI_SUCCESS  The Standalone MM Driver failed to execute normally.
**/
EFI_STATUS
EFIAPI
ProcessModuleEntryPointList (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_MM_SYSTEM_TABLE  *MmSystemTable
  );

/**
  Autogenerated function that calls a set of module unload handlers.

  This function must be called from the unload handler registered by _ModuleEntryPoint().
  This function calls the set of module unload handlers.
  This function is autogenerated by build tools and those build tools are responsible
  for collecting the module unload handlers and calling them in a specified order.

  @param  ImageHandle  The image handle of the DXE Driver, DXE Runtime Driver, DXE SMM Driver, or UEFI Driver.

  @retval  EFI_SUCCESS  The unload handlers executed normally.
  @retval  !EFI_SUCCESS The unload handlers failed to execute normally.

**/
EFI_STATUS
EFIAPI
ProcessModuleUnloadList (
  IN EFI_HANDLE  ImageHandle
  );

#endif