/*
 * PROJECT:     ReactOS SM Helper Library
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Utility functions built around the client SM API
 * COPYRIGHT:   Copyright 2005 Emanuele Aliberti <ea@reactos.com>
 *              Copyright 2022 Hermès Bélusca-Maïto <hermes.belusca-maito@reactos.org>
 */

#include "precomp.h"

#define WIN32_NO_STATUS
#define _INC_WINDOWS
#define COM_NO_WINDOWS_H
#include <windef.h>
#include <winreg.h>

#define NTOS_MODE_USER
#include <ndk/cmfuncs.h>

#include <sm/helper.h>

#define NDEBUG
#include <debug.h>

#if DBG
BOOLEAN SmpDebug = TRUE;
#else
BOOLEAN SmpDebug = FALSE;
#endif

/**
 * @brief
 * This function is used to make the SM start an environment
 * subsystem server process.
 *
 * @param[in]   SmApiPort
 * Port handle returned by SmConnectToSm().
 *
 * @param[in]   Program
 * Name of the subsystem (to be used by the SM to lookup
 * the image name from the registry).
 * Valid names are: DEBUG, WINDOWS, POSIX, OS2, and VMS.
 *
 * @return
 * Success status as handed by the SM reply; otherwise a failure
 * status code.
 *
 * @remark
 * Adapted from SMSS' SmpExecuteInitialCommand() and SmpExecuteImage().
 **/
NTSTATUS
NTAPI
SmExecuteProgram(
    _In_ HANDLE SmApiPort,
    _In_ PUNICODE_STRING Program /*,
    _Out_opt_ PRTL_USER_PROCESS_INFORMATION ProcessInformation*/)
{
    // ULONG MuSessionId;

    NTSTATUS Status;
    RTL_USER_PROCESS_INFORMATION ProcessInfo;
    PRTL_USER_PROCESS_PARAMETERS ProcessParameters;

    PUNICODE_STRING FileName = Program; // FIXME!
    PUNICODE_STRING Directory = NULL; // FIXME!
    PUNICODE_STRING CommandLine = NULL; // FIXME!

    PVOID SmpDefaultEnvironment = NtCurrentPeb()->ProcessParameters->Environment;
    // UNICODE_STRING SmpDefaultLibPath;

    DPRINT("SMLIB: %s(%p, '%wZ') called\n",
           __FUNCTION__, SmApiPort, Program);

    /* Parameters validation */
    if (!SmApiPort)
        return STATUS_INVALID_PARAMETER_1;
    if (!Program)
        return STATUS_INVALID_PARAMETER_2;

    /* Create parameters for the target process, using the current environment */
    Status = RtlCreateProcessParameters(&ProcessParameters,
                                        FileName,
                                        /* SmpDefaultLibPath.Length ?
                                        &SmpDefaultLibPath : */ NULL,
                                        Directory,
                                        CommandLine,
                                        SmpDefaultEnvironment,
                                        NULL,
                                        NULL,
                                        NULL,
                                        0);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("SMLIB: RtlCreateProcessParameters failed for %wZ - Status == %lx\n",
                FileName, Status);
        return Status;
    }

    /* Set the size field as required */
    ProcessInfo.Size = sizeof(ProcessInfo);

    /* Otherwise inherit the flag that was passed to SMSS itself */
    ProcessParameters->DebugFlags = SmpDebug;

    /* And always force NX for anything that SMSS launches */
    ProcessParameters->Flags |= RTL_USER_PROCESS_PARAMETERS_NX;

    /* Now create the process in suspended state */
    Status = RtlCreateUserProcess(FileName,
                                  OBJ_CASE_INSENSITIVE,
                                  ProcessParameters,
                                  NULL,
                                  NULL,
                                  NULL,
                                  FALSE,
                                  NULL,
                                  NULL,
                                  &ProcessInfo);
    RtlDestroyProcessParameters(ProcessParameters);
    if (!NT_SUCCESS(Status))
    {
        /* If we couldn't create it, fail back to the caller */
        DPRINT1("SMLIB: Failed load of %wZ - Status  == %lx\n",
                FileName, Status);
        return Status;
    }

    // /* Now duplicate the handle to this process */
    // Status = NtDuplicateObject(NtCurrentProcess(),
                               // ProcessInfo.ProcessHandle,
                               // NtCurrentProcess(),
                               // InitialCommandProcess,
                               // PROCESS_ALL_ACCESS,
                               // 0,
                               // 0);
    // if (!NT_SUCCESS(Status))
    // {
        // /* Kill it utterly if duplication failed */
        // DPRINT1("SMLIB: DupObject Failed. Status == %lx\n", Status);
        // NtTerminateProcess(ProcessInfo.ProcessHandle, Status);
        // NtResumeThread(ProcessInfo.ThreadHandle, NULL);
        // NtClose(ProcessInfo.ThreadHandle);
        // NtClose(ProcessInfo.ProcessHandle);
        // return Status;
    // }

    /* Call SM and wait for a reply */
    Status = SmExecPgm(SmApiPort, &ProcessInfo, TRUE);

    NtClose(ProcessInfo.ThreadHandle);
    NtClose(ProcessInfo.ProcessHandle);

    // if (ProcessInformation)
        // *ProcessInformation = ProcessInfo;

    DPRINT("SMLIB: %s returned (Status=0x%08lx)\n", __FUNCTION__, Status);
    return Status;
}

/**
 * @brief
 * Reads from the registry key
 * \Registry\SYSTEM\CurrentControlSet\Control\Session Manager\SubSystems
 * the value specified by Name.
 *
 * @param[in]   Name
 * Name of the program to run, that is a value's name in
 * the SM registry key "SubSystems".
 *
 * @param[out]   Data
 * What the registry gave back for Name.
 *
 * @param[in,out]   DataLength
 * How much Data the registry returns.
 *
 * @param[out]   DataType
 * Optional pointer to a variable that receives the type of data
 * stored in the specified value.
 *
 * @param[in]   Environment
 * Optional environment to be used to possibly expand Data before
 * returning it back; if set to NULL, no expansion will be performed.
 **/
NTSTATUS
NTAPI
SmLookupSubsystem(
    _In_ PWSTR Name,
    _Out_ PWSTR Data,
    _Inout_ PULONG DataLength,
    _Out_opt_ PULONG DataType,
    _In_opt_ PVOID Environment)
{
    NTSTATUS Status;
    UNICODE_STRING usKeyName;
    OBJECT_ATTRIBUTES Oa;
    HANDLE hKey = NULL;

    UNICODE_STRING usValueName;
    PWCHAR KeyValueInformation = NULL;
    ULONG  KeyValueInformationLength = 1024;
    ULONG  ResultLength = 0;
    PKEY_VALUE_PARTIAL_INFORMATION kvpi;

    DPRINT("SMLIB: %s(Name='%S') called\n", __FUNCTION__, Name);

    /*
     * Prepare the key name to scan and
     * related object attributes.
     */
    RtlInitUnicodeString(&usKeyName,
        L"\\Registry\\Machine\\SYSTEM\\CurrentControlSet\\Control\\Session Manager\\SubSystems");

    InitializeObjectAttributes(&Oa,
                               &usKeyName,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);
    /*
     * Open the key. This MUST NOT fail, if the
     * request is for a legitimate subsystem.
     */
    Status = NtOpenKey(&hKey,
                       MAXIMUM_ALLOWED,
                       &Oa);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("%s: NtOpenKey failed (Status=0x%08lx)\n", __FUNCTION__, Status);
        return Status;
    }

    KeyValueInformation = RtlAllocateHeap(RtlGetProcessHeap(),
                                          0,
                                          KeyValueInformationLength);
    if (!KeyValueInformation)
    {
        NtClose(hKey);
        return STATUS_NO_MEMORY;
    }

    kvpi = (PKEY_VALUE_PARTIAL_INFORMATION)KeyValueInformation;
    RtlInitUnicodeString(&usValueName, Name);
    Status = NtQueryValueKey(hKey,
                             &usValueName,
                             KeyValuePartialInformation,
                             KeyValueInformation,
                             KeyValueInformationLength,
                             &ResultLength);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("%s: NtQueryValueKey failed (Status=0x%08lx)\n", __FUNCTION__, Status);

        RtlFreeHeap(RtlGetProcessHeap(), 0, KeyValueInformation);
        NtClose(hKey);

        return Status;
    }

    DPRINT("kvpi.TitleIndex = %lu\n", kvpi->TitleIndex);
    DPRINT("kvpi.Type       = %lu\n", kvpi->Type);
    DPRINT("kvpi.DataLength = %lu\n", kvpi->DataLength);

    if (Data && DataLength)
    {
        if (DataType)
            *DataType = kvpi->Type;

        if (Environment && (kvpi->Type == REG_EXPAND_SZ))
        {
            UNICODE_STRING Source;
            UNICODE_STRING Destination;
            PWCHAR DestinationBuffer = NULL;
            ULONG  Length;

            DPRINT("SMLIB: %s: value will be expanded\n", __FUNCTION__);

            Length = 2 * KeyValueInformationLength;
            DestinationBuffer = RtlAllocateHeap(RtlGetProcessHeap(),
                                                0,
                                                Length);
            if (!DestinationBuffer)
            {
                Status = STATUS_NO_MEMORY;
            }
            else
            {
                Source.Length = (USHORT)kvpi->DataLength;
                Source.MaximumLength = Source.Length;
                Source.Buffer = (PWCHAR)&kvpi->Data;

                RtlInitEmptyUnicodeString(&Destination,
                                          DestinationBuffer,
                                          (USHORT)Length);

                Length = 0;
                Status = RtlExpandEnvironmentStrings_U(Environment,
                                                       &Source,
                                                       &Destination,
                                                       &Length);
                if (NT_SUCCESS(Status))
                {
                    *DataLength = min(*DataLength, Destination.Length);
                    RtlCopyMemory(Data, Destination.Buffer, *DataLength);
                }
                RtlFreeHeap(RtlGetProcessHeap(), 0, DestinationBuffer);
            }
        }
        else
        {
            DPRINT("SMLIB: %s: value won't be expanded\n", __FUNCTION__);
            *DataLength = min(*DataLength, kvpi->DataLength);
            RtlCopyMemory(Data, &kvpi->Data, *DataLength);
        }
    }
    else
    {
        DPRINT1("SMLIB: %s: Data or DataLength is NULL!\n", __FUNCTION__);
        Status = STATUS_INVALID_PARAMETER;
    }

    RtlFreeHeap(RtlGetProcessHeap(), 0, KeyValueInformation);
    NtClose(hKey);

    return Status;
}

/**
 * @brief
 * Ask the SM to collect some data from its internal data
 * structures and send it back.
 *
 * @param[in]   SmApiPort
 * Handle returned by SmConnectApiPort.
 *
 * @param[in]   SmInformationClass
 * An SM information class ID:
 * SM_BASIC_INFORMATION: the number of registered subsystems.
 *
 * @param[in,out]   Data
 * Pointer to storage for the information to request.
 *
 * @param[in]   DataLength
 * Length in bytes of the Data buffer; it must be
 * set and must match the SmInformationClass info size.
 *
 * @param[in,out]   ReturnedDataLength
 * Optional pointer to storage to receive the size of the returned data.
 *
 * @return
 * STATUS_SUCCESS: OK you get what you asked for.
 * STATUS_INFO_LENGTH_MISMATCH: you set DataLength to 0 or to a
 *   value that does not match whet the SmInformationClass
 *   requires.
 * STATUS_INVALID_PARAMETER_2: Invalid information class.
 * A port error.
 *
 * @remark
 * This API is ReactOS-specific and not in NT.
 */
NTSTATUS
NTAPI
SmQueryInformation(
    _In_ HANDLE SmApiPort,
    _In_ SM_INFORMATION_CLASS SmInformationClass,
    _Inout_ PVOID Data,
    _In_ ULONG DataLength,
    _Inout_opt_ PULONG ReturnedDataLength)
{
#if defined(__REACTOS__) && DBG
    NTSTATUS Status;
    SM_API_MSG SmApiMsg;

    if (DataLength == 0)
        return STATUS_INFO_LENGTH_MISMATCH;

    /* Marshal data in the port message */
    switch (SmInformationClass)
    {
        case SmBasicInformation:
            if (DataLength != sizeof(SM_BASIC_INFORMATION))
            {
                return STATUS_INFO_LENGTH_MISMATCH;
            }
            SmApiMsg.u.QueryInfo.SmInformationClass = SmBasicInformation;
            SmApiMsg.u.QueryInfo.DataLength = DataLength;
            SmApiMsg.u.QueryInfo.BasicInformation.SubSystemCount = 0;
            break;

        case SmSubSystemInformation:
            if (DataLength != sizeof(SM_SUBSYSTEM_INFORMATION))
            {
                return STATUS_INFO_LENGTH_MISMATCH;
            }
            SmApiMsg.u.QueryInfo.SmInformationClass = SmSubSystemInformation;
            SmApiMsg.u.QueryInfo.DataLength = DataLength;
            SmApiMsg.u.QueryInfo.SubSystemInformation.SubSystemId =
                ((PSM_SUBSYSTEM_INFORMATION)Data)->SubSystemId;
            break;

        default:
            return STATUS_INVALID_PARAMETER_2;
    }

    /* SM API to invoke */
    SmApiMsg.ApiNumber = SM_API_QUERY_INFORMATION;

    /* NOTE: Repurpose the DataLength variable */
    DataLength = sizeof(SM_QUERYINFO_MSG);

    /* Fill out the Port Message Header */
    // SmApiMsg.h.u2.s2.Type = LPC_NEW_MESSAGE;
    SmApiMsg.h.u2.ZeroInit = 0;
    SmApiMsg.h.u1.s1.TotalLength = (CSHORT)DataLength +
        sizeof(SM_API_MSG) - sizeof(SmApiMsg.u); // FIELD_OFFSET(SM_API_MSG, u) + DataLength;
    SmApiMsg.h.u1.s1.DataLength = (CSHORT)DataLength +
        FIELD_OFFSET(SM_API_MSG, u) - sizeof(SmApiMsg.h); // SmApiMsg.h.u1.s1.TotalLength - sizeof(PORT_MESSAGE);
    // SmApiMsg.h.u1.s1.DataLength = DataLength + 8;

    Status = NtRequestWaitReplyPort(SmApiPort, &SmApiMsg.h, &SmApiMsg.h);
    if (NT_SUCCESS(Status))
    {
        /* Unmarshal data */
        RtlCopyMemory(Data,
                      &SmApiMsg.u.QueryInfo.BasicInformation,
                      SmApiMsg.u.QueryInfo.DataLength);

        /* Use caller provided storage to store data size */
        if (ReturnedDataLength)
            *ReturnedDataLength = SmApiMsg.u.QueryInfo.DataLength;

        return SmApiMsg.ReturnValue;
    }
    DPRINT("SMLIB: %s failed (Status=0x%08lx)\n", __FUNCTION__, Status);
    return Status;
#else
    return STATUS_NOT_IMPLEMENTED;
#endif /* defined(__REACTOS__) && DBG */
}

/* EOF */
