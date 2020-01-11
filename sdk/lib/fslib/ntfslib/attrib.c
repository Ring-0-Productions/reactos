/*
 * COPYRIGHT:   See COPYING in the top level directory
 * PROJECT:     ReactOS NTFS FS library
 * FILE:        lib/fslib/ntfslib/attrib.c
 * PURPOSE:     NTFS lib
 * PROGRAMMERS: Pierre Schweitzer, Klachkov Valery
 */

/* INCLUDES ******************************************************************/

#include <ntfslib.h>

#define NDEBUG
#include <debug.h>


/* MACROSES ******************************************************************/

// Get resident attribute data address
#define RESIDENT_DATA(A, T) ((T)((LONG_PTR)A + RA_HEADER_LENGTH))


/* FUNCTIONS *****************************************************************/

static
VOID
SetFileRecordEnd(OUT PFILE_RECORD_HEADER FileRecord,
                 OUT PNTFS_ATTR_RECORD   AttrEnd,
                 IN  ULONG               EndMarker)
{
    // Ensure AttrEnd is aligned on an 8-byte boundary, relative to FileRecord
    ASSERT(((ULONG_PTR)AttrEnd - (ULONG_PTR)FileRecord) % ATTR_RECORD_ALIGNMENT == 0);

    // Mark the end of attributes
    AttrEnd->Type = AttributeEnd;

    // Restore the "file-record-end marker." The value is never checked but this behavior is consistent with Win2k3.
    AttrEnd->Length = EndMarker;

    // Recalculate bytes in use
    FileRecord->BytesInUse = (ULONG_PTR)AttrEnd - (ULONG_PTR)FileRecord + sizeof(ULONG) * 2;
}

VOID
AddStandardInformationAttribute(OUT PFILE_RECORD_HEADER FileRecord,
                                OUT PNTFS_ATTR_RECORD   Attribute)
{
    PSTANDARD_INFORMATION StandardInfo;
    LARGE_INTEGER         SystemTime;

    StandardInfo = RESIDENT_DATA(Attribute, PSTANDARD_INFORMATION);

    Attribute->Type     = AttributeStandardInformation;
    Attribute->Instance = FileRecord->NextAttributeNumber++;

    // Default setup for resident attribute
    Attribute->Length = sizeof(STANDARD_INFORMATION) + RA_HEADER_LENGTH;
    Attribute->Length = ALIGN_UP_BY(Attribute->Length, ATTR_RECORD_ALIGNMENT);

    Attribute->Resident.ValueLength = sizeof(STANDARD_INFORMATION);
    Attribute->Resident.ValueOffset = RA_HEADER_LENGTH;

    // Set dates and times
    KeQuerySystemTime(&SystemTime);
    StandardInfo->CreationTime   = SystemTime.QuadPart;
    StandardInfo->ChangeTime     = SystemTime.QuadPart;
    StandardInfo->LastWriteTime  = SystemTime.QuadPart;
    StandardInfo->LastAccessTime = SystemTime.QuadPart;
    StandardInfo->FileAttribute  = RA_METAFILES_ATTRIBUTES;

    // Move the attribute-end and file-record-end markers to the end of the file record
    Attribute = (PNTFS_ATTR_RECORD)((ULONG_PTR)Attribute + Attribute->Length);
    SetFileRecordEnd(FileRecord, Attribute, Attribute->Length);
}

VOID
AddFileNameAttribute(OUT PFILE_RECORD_HEADER FileRecord,
                     OUT PNTFS_ATTR_RECORD   Attribute,
                     IN  LPCWSTR             FileName,
                     IN  DWORD32             MftRecordNumber)
{
    PFILENAME_ATTRIBUTE FileNameAttribute;
    LARGE_INTEGER       SystemTime;

    DWORD32 FileNameLength = wcslen(FileName);                // Count of chars
    DWORD32 FileNameSize   = FileNameLength * sizeof(WCHAR);  // Count of bytes

    FileNameAttribute = RESIDENT_DATA(Attribute, PFILENAME_ATTRIBUTE);

    Attribute->Type     = AttributeFileName;
    Attribute->Instance = FileRecord->NextAttributeNumber++;

    // Set dates and times
    KeQuerySystemTime(&SystemTime);
    FileNameAttribute->CreationTime   = SystemTime.QuadPart;
    FileNameAttribute->ChangeTime     = SystemTime.QuadPart;
    FileNameAttribute->LastWriteTime  = SystemTime.QuadPart;
    FileNameAttribute->LastAccessTime = SystemTime.QuadPart;

    FileNameAttribute->FileAttributes = (FileRecord->Flags & MFT_RECORD_IS_DIRECTORY)
        ? NTFS_FILE_TYPE_DIRECTORY
        : RA_METAFILES_ATTRIBUTES;
    
    // Set reference to parent directory
    FileNameAttribute->DirectoryFileReferenceNumber = MftRecordNumber;
    FileNameAttribute->DirectoryFileReferenceNumber |= (ULONGLONG)NTFS_FILE_ROOT << 48;

    // Copy file name and save it length
    FileNameAttribute->NameLength = FileNameLength;
    RtlCopyMemory(FileNameAttribute->Name, FileName, FileNameSize);

    // TODO: Check filename for DOS compatibility and set NameType to NTFS_FILE_NAME_WIN32_AND_DOS
    FileNameAttribute->NameType = NTFS_FILE_NAME_POSIX;

    FileRecord->LinkCount++;

    // Setup for resident attribute
    Attribute->Length = RA_HEADER_LENGTH + FIELD_OFFSET(FILENAME_ATTRIBUTE, Name) + FileNameSize;
    Attribute->Length = ALIGN_UP_BY(Attribute->Length, ATTR_RECORD_ALIGNMENT);

    Attribute->Resident.ValueLength = FIELD_OFFSET(FILENAME_ATTRIBUTE, Name) + FileNameSize;
    Attribute->Resident.ValueOffset = RA_HEADER_LENGTH;

    Attribute->Resident.Flags = RA_INDEXED;

    // Move the attribute-end and file-record-end markers to the end of the file record
    Attribute = (PNTFS_ATTR_RECORD)((ULONG_PTR)Attribute + Attribute->Length);
    SetFileRecordEnd(FileRecord, Attribute, Attribute->Length);
}

VOID
AddEmptyDataAttribute(OUT PFILE_RECORD_HEADER FileRecord,
                      OUT PNTFS_ATTR_RECORD   Attribute)
{
    Attribute->Type     = AttributeData;
    Attribute->Instance = FileRecord->NextAttributeNumber++;

    Attribute->Length = RA_HEADER_LENGTH;
    Attribute->Length = ALIGN_UP_BY(Attribute->Length, ATTR_RECORD_ALIGNMENT);

    Attribute->Resident.ValueLength = 0;
    Attribute->Resident.ValueOffset = RA_HEADER_LENGTH;

    // For unnamed $DATA attributes, NameOffset equals header length
    Attribute->NameOffset = RA_HEADER_LENGTH;

    // Move the attribute-end and file-record-end markers to the end of the file record
    Attribute = (PNTFS_ATTR_RECORD)((ULONG_PTR)Attribute + Attribute->Length);
    SetFileRecordEnd(FileRecord, Attribute, Attribute->Length);
}


VOID
AddEmptyVolumeNameAttribute(OUT PFILE_RECORD_HEADER FileRecord,
                            OUT PNTFS_ATTR_RECORD   Attribute)
{
    Attribute->Type     = AttributeVolumeName;
    Attribute->Instance = FileRecord->NextAttributeNumber++;

    Attribute->Length = RA_HEADER_LENGTH;
    Attribute->Length = ALIGN_UP_BY(Attribute->Length, ATTR_RECORD_ALIGNMENT);

    Attribute->Resident.ValueLength = 0;
    Attribute->Resident.ValueOffset = RA_HEADER_LENGTH;

    Attribute->NameOffset = RA_HEADER_LENGTH;

    // Move the attribute-end and file-record-end markers to the end of the file record
    Attribute = (PNTFS_ATTR_RECORD)((ULONG_PTR)Attribute + Attribute->Length);
    SetFileRecordEnd(FileRecord, Attribute, Attribute->Length);
}

VOID
AddVolumeInformationAttribute(OUT PFILE_RECORD_HEADER FileRecord,
                              OUT PNTFS_ATTR_RECORD   Attribute,
                              IN  BYTE                MajorVersion,
                              IN  BYTE                MinorVersion)
{
    PVOLUME_INFORMATION_ATTRIBUTE VolumeInfo;

    Attribute->Type     = AttributeVolumeInformation;
    Attribute->Instance = FileRecord->NextAttributeNumber++;

    VolumeInfo = RESIDENT_DATA(Attribute, PVOLUME_INFORMATION_ATTRIBUTE);

    VolumeInfo->MajorVersion = MajorVersion;
    VolumeInfo->MinorVersion = MinorVersion;
    VolumeInfo->Flags = 0;

    FileRecord->LinkCount++;

    Attribute->Length = RA_HEADER_LENGTH + sizeof(VOLUME_INFORMATION_ATTRIBUTE);
    Attribute->Length = ALIGN_UP_BY(Attribute->Length, ATTR_RECORD_ALIGNMENT);

    Attribute->Resident.ValueLength = sizeof(VOLUME_INFORMATION_ATTRIBUTE);
    Attribute->Resident.ValueOffset = RA_HEADER_LENGTH;
    Attribute->Resident.Flags = RA_INDEXED;

    // Move the attribute-end and file-record-end markers to the end of the file record
    Attribute = (PNTFS_ATTR_RECORD)((ULONG_PTR)Attribute + Attribute->Length);
    SetFileRecordEnd(FileRecord, Attribute, Attribute->Length);
}