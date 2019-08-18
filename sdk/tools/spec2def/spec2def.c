#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>

#define ROSCOMPAT_HOST
#include <roscompat.h>

#ifdef _MSC_VER
#define strcasecmp(_String1, _String2) _stricmp(_String1, _String2)
#define strncasecmp(_String1, _String2, _MaxCount) _strnicmp(_String1, _String2, _MaxCount)
#endif

#define ARRAYSIZE(a) (sizeof(a) / sizeof((a)[0]))

typedef struct _STRING
{
    const char *buf;
    int len;
} STRING, *PSTRING;

typedef struct
{
    STRING strName;
    STRING strTarget;
    int nCallingConvention;
    int nOrdinal;
    int nStackBytes;
    int nArgCount;
    int anArgs[30];
    unsigned int uFlags;
    int nNumber;
    unsigned uVersionMask;
    int bVersionIncluded;
} EXPORT;

#if 0 // Debug helper function
void
PrintExport(EXPORT *pexp)
{
    fprintf(stderr, "strName='%.*s'\n", pexp->strName.len, pexp->strName.buf);
    fprintf(stderr, "strName='%.*s'\n", pexp->strTarget.len, pexp->strTarget.buf);
    fprintf(stderr, "nCallingConvention=%u\n", pexp->nCallingConvention);
    fprintf(stderr, "nOrdinal=%u\n", pexp->nOrdinal);
    fprintf(stderr, "nStackBytes=%u\n", pexp->nStackBytes);
    fprintf(stderr, "nArgCount=%u\n", pexp->nArgCount);
    fprintf(stderr, "uFlags=0x%x\n", pexp->uFlags);
    fprintf(stderr, "nNumber=%u\n", pexp->nNumber);
    fprintf(stderr, "nStartVersion=%u\n", pexp->nStartVersion);
    fprintf(stderr, "nEndVersion=%u\n", pexp->nEndVersion);
    fprintf(stderr, "bVersionIncluded=%u\n", pexp->bVersionIncluded);
}
#endif

enum _ARCH
{
    ARCH_X86,
    ARCH_AMD64,
    ARCH_IA64,
    ARCH_ARM,
    ARCH_ARM64,
    ARCH_PPC
};

typedef int (*PFNOUTLINE)(FILE *, EXPORT *);
int gbMSComp = 0;
int gbImportLib = 0;
int gbNotPrivateNoWarn = 0;
int gbTracing = 0;
int giArch = ARCH_X86;
int gbNoRosCompat = 0;
char *pszArchString = "i386";
char *pszArchString2;
char *pszSourceFileName = NULL;
char *pszDllName = NULL;
char *gpszUnderscore = "";
int gbDebug;
unsigned guOsVersion = 0x502;
#define DbgPrint(...) (!gbDebug || fprintf(stderr, __VA_ARGS__))

enum
{
    FL_PRIVATE = 1,
    FL_STUB = 2,
    FL_NONAME = 4,
    FL_ORDINAL = 8,
    FL_NORELAY = 16,
    FL_RET64 = 32,
    FL_REGISTER = 64,
};

enum
{
    CC_STDCALL,
    CC_CDECL,
    CC_FASTCALL,
    CC_THISCALL,
    CC_EXTERN,
    CC_STUB,
};

enum
{
    ARG_LONG,
    ARG_PTR,
    ARG_STR,
    ARG_WSTR,
    ARG_DBL,
    ARG_INT64,
    ARG_INT128,
    ARG_FLOAT
};

unsigned
GetVersionMask(unsigned uStartVersion, unsigned uEndVersion)
{
    unsigned uMask = 0;
    if ((uStartVersion <= 0x400) && (uEndVersion >= 0x400))
        uMask |= (1 << ROSCOMPAT_VERSION_BIT_NT4);
    if ((uStartVersion <= 0x500) && (uEndVersion >= 0x500))
        uMask |= (1 << ROSCOMPAT_VERSION_BIT_WIN2K);
    if ((uStartVersion <= 0x501) && (uEndVersion >= 0x501))
        uMask |= (1 << ROSCOMPAT_VERSION_BIT_WINXP);
    if ((uStartVersion <= 0x502) && (uEndVersion >= 0x502))
        uMask |= (1 << ROSCOMPAT_VERSION_BIT_WS03);
    if ((uStartVersion <= 0x600) && (uEndVersion >= 0x600))
        uMask |= (1 << ROSCOMPAT_VERSION_BIT_VISTA);
    if ((uStartVersion <= 0x601) && (uEndVersion >= 0x601))
        uMask |= (1 << ROSCOMPAT_VERSION_BIT_WIN7);
    if ((uStartVersion <= 0x602) && (uEndVersion >= 0x602))
        uMask |= (1 << ROSCOMPAT_VERSION_BIT_WIN8);
    if ((uStartVersion <= 0x603) && (uEndVersion >= 0x603))
        uMask |= (1 << ROSCOMPAT_VERSION_BIT_WIN81);
    if ((uStartVersion <= 0xA00) && (uEndVersion >= 0xA00))
        uMask |= (1 << ROSCOMPAT_VERSION_BIT_WIN10);
    return uMask;
}

const char* astrCallingConventions[] =
{
    "STDCALL",
    "CDECL",
    "FASTCALL",
    "THISCALL",
    "EXTERN"
};

/*
 * List of OLE exports that should be PRIVATE and not be assigned an ordinal.
 * In case these conditions are not met when linking with MS LINK.EXE, warnings
 * LNK4104 and LNK4222 respectively are emitted.
 */
static const char* astrOlePrivateExports[] =
{
    "DllCanUnloadNow",
    "DllGetClassObject",
    "DllGetClassFactoryFromClassString",
    "DllGetDocumentation",
    "DllInitialize",
    "DllInstall",
    "DllRegisterServer",
    "DllRegisterServerEx",
    "DllRegisterServerExW",
    "DllUnload",
    "DllUnregisterServer",
    "RasCustomDeleteEntryNotify",
    "RasCustomDial",
    "RasCustomDialDlg",
    "RasCustomEntryDlg",
};

static
int
IsSeparator(char chr)
{
    return ((chr <= ',' && chr != '$' && chr != '#') ||
            (chr >= ':' && chr < '?') );
}

int
CompareToken(const char *token, const char *comparand)
{
    while (*comparand)
    {
        if (*token != *comparand) return 0;
        token++;
        comparand++;
    }
    if (IsSeparator(comparand[-1])) return 1;
    if (!IsSeparator(*token)) return 0;
    return 1;
}

const char *
ScanToken(const char *token, char chr)
{
    while (!IsSeparator(*token))
    {
        if (*token == chr) return token;
        token++;
    }
    return 0;
}

const char *
NextLine(const char *pc)
{
    while (*pc != 0)
    {
        if (pc[0] == '\n' && pc[1] == '\r') return pc + 2;
        else if (pc[0] == '\n') return pc + 1;
        pc++;
    }
    return pc;
}

int
TokenLength(const char *pc)
{
    int length = 0;

    while (!IsSeparator(*pc++)) length++;

    return length;
}

const char *
NextToken(const char *pc)
{
    /* Skip token */
    while (!IsSeparator(*pc)) pc++;

    /* Skip white spaces */
    while (*pc == ' ' || *pc == '\t') pc++;

    /* Check for end of line */
    if (*pc == '\n' || *pc == '\r' || *pc == 0) return 0;

    /* Check for comment */
    if (*pc == '#' || *pc == ';') return 0;

    return pc;
}

void
OutputHeader_stub(FILE *file)
{
    fprintf(file, "/* This file is autogenerated, do not edit. */\n\n"
            "#include <stubs.h>\n");

    if (gbTracing)
    {
        fprintf(file, "#include <wine/debug.h>\n");
        fprintf(file, "#include <inttypes.h>\n");
        fprintf(file, "WINE_DECLARE_DEBUG_CHANNEL(relay);\n");
    }

    /* __int128 is not supported on x86, so use a custom type */
    fprintf(file, "\n"
                  "typedef struct {\n"
                  "    __int64 lower;\n"
                  "    __int64 upper;\n"
                  "} MyInt128;\n");

    fprintf(file, "\n");
}

int
OutputLine_stub(FILE *file, EXPORT *pexp)
{
    int i;
    int bRelay = 0;
    int bInPrototype = 0;

    /* Workaround for forwarded externs. See here for an explanation:
     * https://stackoverflow.com/questions/4060143/forwarding-data-in-a-dll */
    if (gbMSComp &&
        (pexp->nCallingConvention == CC_EXTERN) &&
        (pexp->strTarget.buf != NULL) &&
        (!!ScanToken(pexp->strTarget.buf, '.')))
    {
        fprintf(file, "#pragma comment(linker,\"/export:%s%.*s=%.*s,DATA\")\n\n",
            gpszUnderscore, pexp->strName.len, pexp->strName.buf, pexp->strTarget.len, pexp->strTarget.buf);
        return 0;
    }

    if (pexp->nCallingConvention != CC_STUB &&
        (pexp->uFlags & FL_STUB) == 0)
    {
        /* Only relay trace stdcall C functions */
        if (!gbTracing || (pexp->nCallingConvention != CC_STDCALL)
                || (pexp->uFlags & FL_NORELAY)
                || (pexp->strName.buf[0] == '?'))
        {
            return 0;
        }
        bRelay = 1;
    }

    /* Declare the "real" function */
    if (bRelay)
    {
        fprintf(file, "extern ");
        bInPrototype = 1;
    }

    do
    {
        if (pexp->uFlags & FL_REGISTER)
        {
            /* FIXME: Not sure this is right */
            fprintf(file, "void ");
        }
        else if (pexp->uFlags & FL_RET64)
        {
            fprintf(file, "__int64 ");
        }
        else
        {
            fprintf(file, "int ");
        }

        if ((giArch == ARCH_X86) &&
            pexp->nCallingConvention == CC_STDCALL)
        {
            fprintf(file, "__stdcall ");
        }

        /* Check for C++ */
        if (pexp->strName.buf[0] == '?')
        {
            fprintf(file, "stub_function%d(", pexp->nNumber);
        }
        else
        {
            if (!bRelay || bInPrototype)
                fprintf(file, "%.*s(", pexp->strName.len, pexp->strName.buf);
            else
                fprintf(file, "$relaytrace$%.*s(", pexp->strName.len, pexp->strName.buf);
        }

        for (i = 0; i < pexp->nArgCount; i++)
        {
            if (i != 0) fprintf(file, ", ");
            switch (pexp->anArgs[i])
            {
                case ARG_LONG:   fprintf(file, "long");     break;
                case ARG_PTR:    fprintf(file, "void*");    break;
                case ARG_STR:    fprintf(file, "char*");    break;
                case ARG_WSTR:   fprintf(file, "wchar_t*"); break;
                case ARG_DBL:    fprintf(file, "double");   break;
                case ARG_INT64:  fprintf(file, "__int64");  break;
                /* __int128 is not supported on x86, so use a custom type */
                case ARG_INT128: fprintf(file, "MyInt128"); break;
                case ARG_FLOAT:  fprintf(file, "float");    break;
            }
            fprintf(file, " a%d", i);
        }

        if (bInPrototype)
        {
            fprintf(file, ");\n\n");
        }
    } while (bInPrototype--);

    if (!bRelay)
    {
        fprintf(file, ")\n{\n\tDbgPrint(\"WARNING: calling stub %.*s(",
                pexp->strName.len, pexp->strName.buf);
    }
    else
    {
        fprintf(file, ")\n{\n");
        if (pexp->uFlags & FL_REGISTER)
        {
            /* No return value */
        }
        else if (pexp->uFlags & FL_RET64)
        {
            fprintf(file, "\t__int64 retval;\n");
        }
        else
        {
            fprintf(file, "\tint retval;\n");
        }
        fprintf(file, "\tif (TRACE_ON(relay))\n\t\tDPRINTF(\"%s: %.*s(",
                pszDllName, pexp->strName.len, pexp->strName.buf);
    }

    for (i = 0; i < pexp->nArgCount; i++)
    {
        if (i != 0) fprintf(file, ",");
        switch (pexp->anArgs[i])
        {
            case ARG_LONG:   fprintf(file, "0x%%lx"); break;
            case ARG_PTR:    fprintf(file, "0x%%p");  break;
            case ARG_STR:    fprintf(file, "'%%s'");  break;
            case ARG_WSTR:   fprintf(file, "'%%ws'"); break;
            case ARG_DBL:    fprintf(file, "%%f");    break;
            case ARG_INT64:  fprintf(file, "0x%%\"PRIx64\""); break;
            case ARG_INT128: fprintf(file, "0x%%\"PRIx64\"-0x%%\"PRIx64\""); break;
            case ARG_FLOAT:  fprintf(file, "%%f");    break;
        }
    }
    fprintf(file, ")\\n\"");

    for (i = 0; i < pexp->nArgCount; i++)
    {
        fprintf(file, ", ");
        switch (pexp->anArgs[i])
        {
            case ARG_LONG: case ARG_PTR: case ARG_STR:
            case ARG_WSTR: case ARG_DBL: case ARG_INT64:
                fprintf(file, "a%d", i); break;
            case ARG_INT128:
                fprintf(file, "a%d.lower, a%d.upper", i, i); break;
            case ARG_FLOAT:
                fprintf(file, "a%d", i); break;
        }
    }
    fprintf(file, ");\n");

    if (pexp->nCallingConvention == CC_STUB)
    {
        fprintf(file, "\t__wine_spec_unimplemented_stub(\"%s\", __FUNCTION__);\n", pszDllName);
    }
    else if (bRelay)
    {
        if (pexp->uFlags & FL_REGISTER)
        {
            fprintf(file,"\t");
        }
        else
        {
            fprintf(file, "\tretval = ");
        }
        fprintf(file, "%.*s(", pexp->strName.len, pexp->strName.buf);

        for (i = 0; i < pexp->nArgCount; i++)
        {
            if (i != 0) fprintf(file, ", ");
            fprintf(file, "a%d", i);
        }
        fprintf(file, ");\n");
    }

    if (!bRelay)
        fprintf(file, "\treturn 0;\n}\n\n");
    else if ((pexp->uFlags & FL_REGISTER) == 0)
    {
        if (pexp->uFlags & FL_RET64)
        {
            fprintf(file, "\tif (TRACE_ON(relay))\n\t\tDPRINTF(\"%s: %.*s: retval = 0x%%\"PRIx64\"\\n\", retval);\n",
                    pszDllName, pexp->strName.len, pexp->strName.buf);
        }
        else
        {
            fprintf(file, "\tif (TRACE_ON(relay))\n\t\tDPRINTF(\"%s: %.*s: retval = 0x%%lx\\n\", retval);\n",
                    pszDllName, pexp->strName.len, pexp->strName.buf);
        }
        fprintf(file, "\treturn retval;\n}\n\n");
    }

    return 1;
}

void
OutputHeader_asmstub(FILE *file, char *libname)
{
    fprintf(file, "; File generated automatically, do not edit!\n\n");

    if (giArch == ARCH_X86)
    {
        fprintf(file, ".586\n.model flat\n.code\n");
    }
    else if (giArch == ARCH_AMD64)
    {
        fprintf(file, ".code\n");
    }
    else if (giArch == ARCH_ARM || giArch == ARCH_ARM64)
    {
        fprintf(file, "    AREA |.text|,ALIGN=2,CODE,READONLY\n\n");
    }
}

void
Output_stublabel(FILE *fileDest, char* pszSymbolName)
{
    if (giArch == ARCH_ARM || giArch == ARCH_ARM64)
    {
        fprintf(fileDest,
                "\tEXPORT |%s| [FUNC]\n|%s|\n",
                pszSymbolName,
                pszSymbolName);
    }
    else
    {
        fprintf(fileDest,
                "PUBLIC %s\n%s: nop\n",
                pszSymbolName,
                pszSymbolName);
    }
}

int
OutputLine_asmstub(FILE *fileDest, EXPORT *pexp)
{
    char szNameBuffer[128];

    /* Handle autoname */
    if (pexp->strName.len == 1 && pexp->strName.buf[0] == '@')
    {
        sprintf(szNameBuffer, "%s_stub_ordinal%d",
                gpszUnderscore, pexp->nOrdinal);
    }
    else if (giArch != ARCH_X86)
    {
        /* Does the string already have stdcall decoration? */
        const char *pcAt = ScanToken(pexp->strName.buf, '@');
        if (pcAt && (pcAt < (pexp->strName.buf + pexp->strName.len)) &&
            (pexp->strName.buf[0] == '_'))
        {
            /* Skip leading underscore and remove trailing decoration */
            sprintf(szNameBuffer, "_stub_%.*s",
                    (int)(pcAt - pexp->strName.buf - 1),
                    pexp->strName.buf + 1);
        }
        else
        {
            sprintf(szNameBuffer, "_stub_%.*s",
                    pexp->strName.len, pexp->strName.buf);
        }
    }
    else if (pexp->nCallingConvention == CC_STDCALL)
    {
        sprintf(szNameBuffer, "__stub_%.*s@%d",
                pexp->strName.len, pexp->strName.buf, pexp->nStackBytes);
    }
    else if (pexp->nCallingConvention == CC_FASTCALL)
    {
        sprintf(szNameBuffer, "@_stub_%.*s@%d",
                pexp->strName.len, pexp->strName.buf, pexp->nStackBytes);
    }
    else if ((pexp->nCallingConvention == CC_CDECL) ||
             (pexp->nCallingConvention == CC_THISCALL) ||
             (pexp->nCallingConvention == CC_EXTERN) ||
             (pexp->nCallingConvention == CC_STUB))
    {
        sprintf(szNameBuffer, "__stub_%.*s",
                pexp->strName.len, pexp->strName.buf);
    }
    else
    {
        fprintf(stderr, "Invalid calling convention");
        return 0;
    }

    Output_stublabel(fileDest, szNameBuffer);

    return 1;
}

void
OutputHeader_def(FILE *file, char *libname)
{
    fprintf(file,
            "; File generated automatically, do not edit!\n\n"
            "NAME %s\n\n"
            "EXPORTS\n",
            libname);
}

void
PrintName(FILE *fileDest, EXPORT *pexp, PSTRING pstr, int fDeco)
{
    const char *pcName = pstr->buf;
    int nNameLength = pstr->len;
    const char* pcDot, *pcAt;
    char namebuffer[19];

    if ((nNameLength == 1) && (pcName[0] == '@'))
    {
        sprintf(namebuffer, "ordinal%d", pexp->nOrdinal);
        pcName = namebuffer;
        nNameLength = strlen(namebuffer);
    }

    /* Check for non-x86 first */
    if (giArch != ARCH_X86)
    {
        /* Does the string already have stdcall decoration? */
        pcAt = ScanToken(pcName, '@');
        if (pcAt && (pcAt < (pcName + nNameLength)) && (pcName[0] == '_'))
        {
            /* Skip leading underscore and remove trailing decoration */
            pcName++;
            nNameLength = (int)(pcAt - pcName);
        }

        /* Print the undecorated function name */
        fprintf(fileDest, "%.*s", nNameLength, pcName);
    }
    else if (fDeco &&
        ((pexp->nCallingConvention == CC_STDCALL) ||
         (pexp->nCallingConvention == CC_FASTCALL)))
    {
        /* Beware with C++ exports */
        int is_cpp = pcName[0] == '?';

        /* Scan for a dll forwarding dot */
        pcDot = ScanToken(pcName, '.');
        if (pcDot)
        {
            /* First print the dll name, followed by a dot */
            nNameLength = (int)(pcDot - pcName);
            fprintf(fileDest, "%.*s.", nNameLength, pcName);

            /* Now the actual function name */
            pcName = pcDot + 1;
            nNameLength = pexp->strTarget.len - nNameLength - 1;
        }

        /* Does the string already have decoration? */
        pcAt = ScanToken(pcName, '@');
        if (pcAt && (pcAt < (pcName + nNameLength)))
        {
            /* On GCC, we need to remove the leading stdcall underscore, but not for C++ exports */
            if (!gbMSComp && !is_cpp && (pexp->nCallingConvention == CC_STDCALL))
            {
                pcName++;
                nNameLength--;
            }

            /* Print the already decorated function name */
            fprintf(fileDest, "%.*s", nNameLength, pcName);
        }
        else
        {
            /* Print the prefix, but skip it for (GCC && stdcall) */
            if (gbMSComp || (pexp->nCallingConvention != CC_STDCALL))
            {
                fprintf(fileDest, "%c", pexp->nCallingConvention == CC_FASTCALL ? '@' : '_');
            }

            /* Print the name with trailing decoration */
            fprintf(fileDest, "%.*s@%d", nNameLength, pcName, pexp->nStackBytes);
        }
    }
    else
    {
        /* Print the undecorated function name */
        fprintf(fileDest, "%.*s", nNameLength, pcName);
    }
}

void
OutputLine_def_MS(FILE *fileDest, EXPORT *pexp)
{
    PrintName(fileDest, pexp, &pexp->strName, 0);

    if (gbImportLib)
    {
        /* Redirect to a stub function, to get the right decoration in the lib */
        fprintf(fileDest, "=_stub_");
        PrintName(fileDest, pexp, &pexp->strName, 0);
    }
    else if (pexp->strTarget.buf)
    {
        if (pexp->strName.buf[0] == '?')
        {
            //fprintf(stderr, "warning: ignoring C++ redirection %.*s -> %.*s\n",
            //        pexp->strName.len, pexp->strName.buf, pexp->strTarget.len, pexp->strTarget.buf);
        }
        else
        {
            fprintf(fileDest, "=");

            /* If the original name was decorated, use decoration in the forwarder as well */
            if ((giArch == ARCH_X86) && ScanToken(pexp->strName.buf, '@') &&
                !ScanToken(pexp->strTarget.buf, '@') &&
                ((pexp->nCallingConvention == CC_STDCALL) ||
                (pexp->nCallingConvention == CC_FASTCALL)) )
            {
                PrintName(fileDest, pexp, &pexp->strTarget, 1);
            }
            else
            {
                /* Write the undecorated redirection name */
                fprintf(fileDest, "%.*s", pexp->strTarget.len, pexp->strTarget.buf);
            }
        }
    }
    else if (((pexp->uFlags & FL_STUB) || (pexp->nCallingConvention == CC_STUB)) &&
             (pexp->strName.buf[0] == '?'))
    {
        /* C++ stubs are forwarded to C stubs */
        fprintf(fileDest, "=stub_function%d", pexp->nNumber);
    }
    else if (gbTracing && ((pexp->uFlags & FL_NORELAY) == 0) && (pexp->nCallingConvention == CC_STDCALL) &&
            (pexp->strName.buf[0] != '?'))
    {
        /* Redirect it to the relay-tracing trampoline */
        fprintf(fileDest, "=$relaytrace$%.*s", pexp->strName.len, pexp->strName.buf);
    }
}

void
OutputLine_def_GCC(FILE *fileDest, EXPORT *pexp)
{
    int bTracing = 0;
    /* Print the function name, with decoration for export libs */
    PrintName(fileDest, pexp, &pexp->strName, gbImportLib);
    DbgPrint("Generating def line for '%.*s'\n", pexp->strName.len, pexp->strName.buf);

    /* Check if this is a forwarded export */
    if (pexp->strTarget.buf)
    {
        int fIsExternal = !!ScanToken(pexp->strTarget.buf, '.');
        DbgPrint("Got redirect '%.*s'\n", pexp->strTarget.len, pexp->strTarget.buf);

        /* print the target name, don't decorate if it is external */
        fprintf(fileDest, "=");
        PrintName(fileDest, pexp, &pexp->strTarget, !fIsExternal);
    }
    else if (((pexp->uFlags & FL_STUB) || (pexp->nCallingConvention == CC_STUB)) &&
             (pexp->strName.buf[0] == '?'))
    {
        /* C++ stubs are forwarded to C stubs */
        fprintf(fileDest, "=stub_function%d", pexp->nNumber);
    }
    else if (gbTracing && ((pexp->uFlags & FL_NORELAY) == 0) &&
             (pexp->nCallingConvention == CC_STDCALL) &&
            (pexp->strName.buf[0] != '?'))
    {
        /* Redirect it to the relay-tracing trampoline */
        char buf[256];
        STRING strTarget;
        fprintf(fileDest, "=");
        sprintf(buf, "$relaytrace$%.*s", pexp->strName.len, pexp->strName.buf);
        strTarget.buf = buf;
        strTarget.len = pexp->strName.len + 12;
        PrintName(fileDest, pexp, &strTarget, 1);
        bTracing = 1;
    }

    /* Special handling for stdcall and fastcall, but not C++ exports*/
    if ((giArch == ARCH_X86) &&
        (pexp->strName.buf[0] != '?') &&
        ((pexp->nCallingConvention == CC_STDCALL) ||
         (pexp->nCallingConvention == CC_FASTCALL)))
    {
        /* Is this the import lib? */
        if (gbImportLib)
        {
            /* Is the name in the spec file decorated? */
            const char* pcDeco = ScanToken(pexp->strName.buf, '@');
            if (pcDeco &&
                (pexp->strName.len > 1) &&
                (pcDeco < pexp->strName.buf + pexp->strName.len))
            {
                /* Write the name including the leading @  */
                fprintf(fileDest, "==%.*s", pexp->strName.len, pexp->strName.buf);
            }
        }
        else if ((!pexp->strTarget.buf) && !(bTracing))
        {
            /* Write a forwarder to the actual decorated symbol */
            fprintf(fileDest, "=");
            PrintName(fileDest, pexp, &pexp->strName, 1);
        }
    }
}

int
OutputLine_def(FILE *fileDest, EXPORT *pexp)
{
    /* Don't add private exports to the import lib */
    if (gbImportLib && (pexp->uFlags & FL_PRIVATE))
    {
        DbgPrint("OutputLine_def: skipping private export '%.*s'...\n", pexp->strName.len, pexp->strName.buf);
        return 1;
    }

    /* For MS linker, forwarded externs are managed via #pragma comment(linker,"/export:_data=org.data,DATA") */
    if (gbMSComp && !gbImportLib && (pexp->nCallingConvention == CC_EXTERN) &&
        (pexp->strTarget.buf != NULL) && !!ScanToken(pexp->strTarget.buf, '.'))
    {
        DbgPrint("OutputLine_def: skipping forwarded extern export '%.*s' ->'%.*s'...\n",
            pexp->strName.len, pexp->strName.buf, pexp->strTarget.len, pexp->strTarget.buf);
        return 1;
    }

    DbgPrint("OutputLine_def: '%.*s'...\n", pexp->strName.len, pexp->strName.buf);
    fprintf(fileDest, " ");

    if (gbMSComp)
        OutputLine_def_MS(fileDest, pexp);
    else
        OutputLine_def_GCC(fileDest, pexp);

    /* On GCC builds we force ordinals */
    if ((pexp->uFlags & FL_ORDINAL) || (!gbMSComp && !gbImportLib))
    {
        fprintf(fileDest, " @%d", pexp->nOrdinal);
    }

    if (pexp->uFlags & FL_NONAME)
    {
        fprintf(fileDest, " NONAME");
    }

    /* Either PRIVATE or DATA */
    if (pexp->uFlags & FL_PRIVATE)
    {
        fprintf(fileDest, " PRIVATE");
    }
    else if (pexp->nCallingConvention == CC_EXTERN)
    {
        fprintf(fileDest, " DATA");
    }

    fprintf(fileDest, "\n");

    return 1;
}

void
Fatalv(
    const char* filename,
    unsigned nLine,
    const char *pcLine,
    const char *pc,
    size_t errorlen,
    const char *format,
    va_list argptr)
{
    unsigned i, errorpos, len;
    const char* pcLineEnd;

    /* Get the length of the line */
    pcLineEnd = strpbrk(pcLine, "\r\n");
    len = (unsigned)(pcLineEnd - pcLine);

    if (pc == NULL)
    {
        pc = pcLine + len - 1;
        errorlen = 1;
    }

    errorpos = (unsigned)(pc - pcLine);

    /* Output the error message */
    fprintf(stderr, "ERROR: (%s:%u:%u): ", filename, nLine, errorpos);
    vfprintf(stderr, format, argptr);
    fprintf(stderr, "\n");

    /* Output the line with the error */
    fprintf(stderr, "> %.*s\n", len, pcLine);

    if (errorlen == 0)
    {
        errorlen = TokenLength(pc);
    }

    for (i = 0; i < errorpos + 2; i++)
    {
        fprintf(stderr, " ");
    }
    for (i = 0; i < errorlen; i++)
    {
        fprintf(stderr, "~");
    }
    fprintf(stderr, "\n");
    exit(-1);
}

void
Fatal(
    const char* filename,
    unsigned nLine,
    const char *pcLine,
    const char *pc,
    size_t errorlen,
    const char *format,
    ...)
{
    va_list argptr;

    va_start(argptr, format);
    Fatalv(filename, nLine, pcLine, pc, errorlen, format, argptr);
    va_end(argptr);
}

EXPORT *
ParseFile(char* pcStart, FILE *fileDest, unsigned *cExports)
{
    EXPORT *pexports;
    const char *pc, *pcLine;
    int cLines, nLine;
    EXPORT exp;
    int included;
    unsigned int i;

    *cExports = 0;

    //fprintf(stderr, "info: line %d, pcStart:'%.30s'\n", nLine, pcStart);

    /* Count the lines */
    for (cLines = 1, pcLine = pcStart; *pcLine; pcLine = NextLine(pcLine), cLines++)
    {
        /* Nothing */
    }

    /* Allocate an array of EXPORT structures */
    pexports = malloc(cLines * sizeof(EXPORT));
    if (pexports == NULL)
    {
        fprintf(stderr, "ERROR: %s: failed to allocate EXPORT array of %u elements\n", pszSourceFileName, cLines);
        return NULL;
    }

    /* Loop all lines */
    nLine = 1;
    exp.nNumber = 0;
    for (pcLine = pcStart; *pcLine; pcLine = NextLine(pcLine), nLine++)
    {
        pc = pcLine;

        exp.strName.buf = NULL;
        exp.strName.len = 0;
        exp.strTarget.buf = NULL;
        exp.strTarget.len = 0;
        exp.nArgCount = 0;
        exp.uFlags = 0;
        exp.nNumber++;
        exp.uVersionMask = 0xFFF;
        exp.bVersionIncluded = 1;

        /* Skip white spaces */
        while (*pc == ' ' || *pc == '\t') pc++;

        /* Check for line break or comment */
        if ((*pc == '\r') || (*pc == '\n') ||
            (*pc == ';') || (*pc == '#'))
        {
            continue;
        }

        /* On EOF we are done */
        if (*pc == 0)
        {
            return pexports;
        }

        /* Now we should get either an ordinal or @ */
        if (*pc == '@')
        {
            exp.nOrdinal = -1;
        }
        else if ((*pc >= '0') && (*pc <= '9'))
        {
            char* end;
            long int number = strtol(pc, &end, 10);
            if ((*end != ' ') && (*end != '\t'))
            {
                Fatal(pszSourceFileName, nLine, pcLine, end, 0, "Unexpected character(s) after ordinal");
            }

            if ((number < 0) || (number > 0xFFFE))
            {
                Fatal(pszSourceFileName, nLine, pcLine, pc, 0, "Invalid value for ordinal");
            }

            exp.nOrdinal = number;

            /* The import lib should contain the ordinal only if -ordinal was specified */
            if (!gbImportLib)
                exp.uFlags |= FL_ORDINAL;
        }
        else
        {
            Fatal(pszSourceFileName, nLine, pcLine, pc, 0, "Expected '@' or ordinal");
        }

        /* Go to next token (type) */
        if (!(pc = NextToken(pc)))
        {
            Fatal(pszSourceFileName, nLine, pcLine, pc, 1, "Unexpected end of line");
        }

        //fprintf(stderr, "info: Token:'%.*s'\n", TokenLength(pc), pc);

        /* Now we should get the type */
        if (CompareToken(pc, "stdcall"))
        {
            exp.nCallingConvention = CC_STDCALL;
        }
        else if (CompareToken(pc, "cdecl") ||
                 CompareToken(pc, "varargs"))
        {
            exp.nCallingConvention = CC_CDECL;
        }
        else if (CompareToken(pc, "fastcall"))
        {
            exp.nCallingConvention = CC_FASTCALL;
        }
        else if (CompareToken(pc, "thiscall"))
        {
            exp.nCallingConvention = CC_THISCALL;
        }
        else if (CompareToken(pc, "extern"))
        {
            exp.nCallingConvention = CC_EXTERN;
        }
        else if (CompareToken(pc, "stub"))
        {
            exp.nCallingConvention = CC_STUB;
        }
        else
        {
            Fatal(pszSourceFileName, nLine, pcLine, pc, 0, "Invalid calling convention");
        }

        /* Go to next token (options or name) */
        if (!(pc = NextToken(pc)))
        {
            Fatal(pszSourceFileName, nLine, pcLine, pc, 1, "Unexpected end of line");
        }

        /* Handle options */
        included = 1;
        while (*pc == '-')
        {
            if (CompareToken(pc, "-arch="))
            {
                /* Default to not included */
                included = 0;
                pc += 5;

                /* Look if we are included */
                do
                {
                    pc++;
                    if (CompareToken(pc, pszArchString) ||
                        CompareToken(pc, pszArchString2))
                    {
                        included = 1;
                    }

                    /* Skip to next arch or end */
                    while (*pc > ',') pc++;
                } while (*pc == ',');
            }
            else if (CompareToken(pc, "-i386"))
            {
                if (giArch != ARCH_X86) included = 0;
            }
            else if (CompareToken(pc, "-version="))
            {
                const char *pcVersionStart = pc + 9;

                /* Default to not included */
                exp.bVersionIncluded = gbNoRosCompat ? 0 : 1;
                exp.uVersionMask = 0;
                pc += 8;

                /* Look if we are included */
                do
                {
                    unsigned version, endversion;

                    /* Optionally skip leading '0x' */
                    pc++;
                    if ((pc[0] == '0') && (pc[1] == 'x')) pc += 2;

                    /* Now get the version number */
                    endversion = version = strtoul(pc, (char**)&pc, 16);

                    /* Check if it's a range */
                    if (pc[0] == '+')
                    {
                        endversion = 0xFFF;
                        pc++;
                    }
                    else if (pc[0] == '-')
                    {
                        /* Optionally skip leading '0x' */
                        pc++;
                        if ((pc[0] == '0') && (pc[1] == 'x')) pc += 2;
                        endversion = strtoul(pc, (char**)&pc, 16);
                    }

                    /* Check for degenerate range */
                    if (version > endversion)
                    {
                        Fatal(pszSourceFileName,
                              nLine,
                              pcLine,
                              pcVersionStart,
                              pc - pcVersionStart,
                              "Invalid version range");
                    }

                    exp.uVersionMask |= GetVersionMask(version, endversion);

                    /* Now compare the range with our version */
                    if ((guOsVersion >= version) &&
                        (guOsVersion <= endversion))
                    {
                        exp.bVersionIncluded = 1;
                    }

                    /* Skip to next arch or end */
                    while (*pc > ',') pc++;

                } while (*pc == ',');
            }
            else if (CompareToken(pc, "-private"))
            {
                exp.uFlags |= FL_PRIVATE;
            }
            else if (CompareToken(pc, "-noname"))
            {
                exp.uFlags |= FL_ORDINAL | FL_NONAME;
            }
            else if (CompareToken(pc, "-ordinal"))
            {
                exp.uFlags |= FL_ORDINAL;
                /* GCC doesn't automatically import by ordinal if an ordinal
                 * is found in the def file. Force it. */
                if (gbImportLib && !gbMSComp)
                    exp.uFlags |= FL_NONAME;
            }
            else if (CompareToken(pc, "-stub"))
            {
                exp.uFlags |= FL_STUB;
            }
            else if (CompareToken(pc, "-norelay"))
            {
                exp.uFlags |= FL_NORELAY;
            }
            else if (CompareToken(pc, "-ret64"))
            {
                exp.uFlags |= FL_RET64;
            }
            else if (CompareToken(pc, "-register"))
            {
                exp.uFlags |= FL_REGISTER;
            }
            else
            {
                fprintf(stdout,
                        "INFO: %s line %d: Ignored option: '%.*s'\n",
                        pszSourceFileName,
                        nLine,
                        TokenLength(pc),
                        pc);
            }

            /* Go to next token */
            pc = NextToken(pc);
        }

        //fprintf(stderr, "info: Name:'%.10s'\n", pc);

        /* If arch didn't match ours, skip this entry */
        if (!included) continue;

        /* Get name */
        exp.strName.buf = pc;
        exp.strName.len = TokenLength(pc);
        //DbgPrint("Got name: '%.*s'\n", exp.strName.len, exp.strName.buf);

        /* Check for autoname */
        if ((exp.strName.len == 1) && (exp.strName.buf[0] == '@'))
        {
            exp.uFlags |= FL_ORDINAL | FL_NONAME;
        }

        /* Handle parameters */
        exp.nStackBytes = 0;
        pc = NextToken(pc);
        /* Extern can't have parameters, and it's optional to provide ones for stubs. All other exports must have them */
        if (!pc && (exp.nCallingConvention != CC_EXTERN && exp.nCallingConvention != CC_STUB))
        {
            Fatal(pszSourceFileName, nLine, pcLine, pc, 1, "Unexpected end of line");
        }

        if (pc && (exp.nCallingConvention != CC_EXTERN))
        {
            /* Verify syntax */
            if (*pc++ != '(')
            {
                Fatal(pszSourceFileName, nLine, pcLine, pc - 1, 0, "Expected '('");
            }

            /* Skip whitespaces */
            while (*pc == ' ' || *pc == '\t') pc++;

            exp.nStackBytes = 0;
            while (*pc >= '0')
            {
                if (CompareToken(pc, "long"))
                {
                    exp.nStackBytes += 4;
                    exp.anArgs[exp.nArgCount] = ARG_LONG;
                }
                else if (CompareToken(pc, "double"))
                {
                    exp.nStackBytes += 8;
                    exp.anArgs[exp.nArgCount] = ARG_DBL;
                }
                else if (CompareToken(pc, "ptr"))
                {
                    exp.nStackBytes += 4; // sizeof(void*) on x86
                    exp.anArgs[exp.nArgCount] = ARG_PTR;
                }
                else if (CompareToken(pc, "str"))
                {
                    exp.nStackBytes += 4; // sizeof(void*) on x86
                    exp.anArgs[exp.nArgCount] = ARG_STR;
                }
                else if (CompareToken(pc, "wstr"))
                {
                    exp.nStackBytes += 4; // sizeof(void*) on x86
                    exp.anArgs[exp.nArgCount] = ARG_WSTR;
                }
                else if (CompareToken(pc, "int64"))
                {
                    exp.nStackBytes += 8;
                    exp.anArgs[exp.nArgCount] = ARG_INT64;
                }
                else if (CompareToken(pc, "int128"))
                {
                    exp.nStackBytes += 16;
                    exp.anArgs[exp.nArgCount] = ARG_INT128;
                }
                else if (CompareToken(pc, "float"))
                {
                    exp.nStackBytes += 4;
                    exp.anArgs[exp.nArgCount] = ARG_FLOAT;
                }
                else
                {
                    Fatal(pszSourceFileName, nLine, pcLine, pc, 0, "Unrecognized type");
                }

                exp.nArgCount++;

                /* Go to next parameter */
                if (!(pc = NextToken(pc)))
                {
                    Fatal(pszSourceFileName, nLine, pcLine, pc, 1, "Unexpected end of line");
                }
            }

            /* Check syntax */
            if (*pc++ != ')')
            {
                Fatal(pszSourceFileName, nLine, pcLine, pc - 1, 0, "Expected ')'");
            }

            /* Go to next token */
            pc = NextToken(pc);
        }

        /* Handle special stub cases */
        if (exp.nCallingConvention == CC_STUB)
        {
            /* If we got parameters, assume STDCALL */
            if (exp.nArgCount != 0)
            {
                exp.nCallingConvention = CC_STDCALL;
                exp.uFlags |= FL_STUB;
            }

            /* Check for c++ mangled name */
            if (exp.strName.buf[0] == '?')
            {
                //printf("Found c++ mangled name...\n");
                //
            }
            else
            {
                /* Check for stdcall name */
                const char *p = ScanToken(exp.strName.buf, '@');
                if (p && (p - exp.strName.buf < exp.strName.len))
                {
                    int i;

                    /* Truncate the name to before the @ */
                    exp.strName.len = (int)(p - exp.strName.buf);
                    if (exp.strName.len < 1)
                    {
                        Fatal(pszSourceFileName, nLine, pcLine, p, 1, "Unexpected @");
                    }
                    exp.nStackBytes = atoi(p + 1);
                    exp.nArgCount =  exp.nStackBytes / 4;
                    exp.nCallingConvention = CC_STDCALL;
                    exp.uFlags |= FL_STUB;
                    for (i = 0; i < exp.nArgCount; i++)
                        exp.anArgs[i] = ARG_LONG;
                }
            }
        }

        /* Check optional redirection */
        if (pc)
        {
            exp.strTarget.buf = pc;
            exp.strTarget.len = TokenLength(pc);

            /* Check syntax (end of line) */
            if (NextToken(pc))
            {
                Fatal(pszSourceFileName, nLine, pcLine, NextToken(pc), 0, "Excess token(s) at end of definition");
            }

            /* Don't relay-trace forwarded functions */
            exp.uFlags |= FL_NORELAY;
        }
        else
        {
            exp.strTarget.buf = NULL;
            exp.strTarget.len = 0;
        }

        /* Check for no-name without ordinal */
        if ((exp.uFlags & FL_ORDINAL) && (exp.nOrdinal == -1))
        {
            Fatal(pszSourceFileName, nLine, pcLine, pc, 0, "Ordinal export without ordinal");
        }

        /*
         * Check for special handling of OLE exports, only when MSVC
         * is not used, since otherwise this is handled by MS LINK.EXE.
         */
        if (!gbMSComp)
        {
            /* Check whether the current export is not PRIVATE, or has an ordinal */
            int bIsNotPrivate = (!gbNotPrivateNoWarn && /*gbImportLib &&*/ !(exp.uFlags & FL_PRIVATE));
            int bHasOrdinal = (exp.uFlags & FL_ORDINAL);

            /* Check whether the current export is an OLE export, in case any of these tests pass */
            if (bIsNotPrivate || bHasOrdinal)
            {
                for (i = 0; i < ARRAYSIZE(astrOlePrivateExports); ++i)
                {
                    if (strlen(astrOlePrivateExports[i]) == exp.strName.len &&
                        strncmp(exp.strName.buf, astrOlePrivateExports[i], exp.strName.len) == 0)
                    {
                        /* The current export is an OLE export: display the corresponding warning */
                        if (bIsNotPrivate)
                        {
                            fprintf(stderr, "WARNING: %s line %d: Exported symbol '%.*s' should be PRIVATE\n",
                                    pszSourceFileName, nLine, exp.strName.len, exp.strName.buf);
                        }
                        if (bHasOrdinal)
                        {
                            fprintf(stderr, "WARNING: %s line %d: exported symbol '%.*s' should not be assigned an ordinal\n",
                                    pszSourceFileName, nLine, exp.strName.len, exp.strName.buf);
                        }
                        break;
                    }
                }
            }
        }

        pexports[*cExports] = exp;
        (*cExports)++;
        gbDebug = 0;
    }

    return pexports;
}

int
ApplyOrdinals(EXPORT* pexports, unsigned cExports)
{
    unsigned short i, j;
    char* used;

    /* Allocate a table to mark used ordinals */
    used = malloc(65536);
    if (used == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for ordinal use table\n");
        return -1;
    }
    memset(used, 0, 65536);

    /* Pass 1: mark the ordinals that are already used */
    for (i = 0; i < cExports; i++)
    {
        if (pexports[i].uFlags & FL_ORDINAL)
        {
            assert(pexports[i].nOrdinal >= 0 && pexports[i].nOrdinal <= 0xFFF);
            if (used[pexports[i].nOrdinal] != 0)
            {
                fprintf(stderr, "Found duplicate ordinal: %u\n", pexports[i].nOrdinal);
                return -1;
            }
            used[pexports[i].nOrdinal] = 1;
        }
    }

    /* Pass 2: apply available ordinals */
    for (i = 0, j = 1; i < cExports; i++)
    {
        if ((pexports[i].uFlags & FL_ORDINAL) == 0 && pexports[i].bVersionIncluded)
        {
            while (used[j] != 0)
            {
                if (j >= 0xFFF)
                {
                    fprintf(stderr, "Ran out of ordinals.");
                    return -1;
                }
                j++;
            }

            pexports[i].nOrdinal = j;
            used[j] = 1;
        }
    }

    free(used);
    return 0;
}

void usage(void)
{
    printf("syntax: spec2def [<options> ...] <spec file>\n"
           "Possible options:\n"
           "  -h --help               print this help screen\n"
           "  -l=<file>               generate an asm lib stub\n"
           "  -d=<file>               generate a def file\n"
           "  -s=<file>               generate a stub file\n"
           "  --ms                    MSVC compatibility\n"
           "  -n=<name>               name of the dll\n"
           "  --implib                generate a def file for an import library\n"
           "  --no-private-warnings   suppress warnings about symbols that should be -private\n"
           "  -a=<arch>               set architecture to <arch> (i386, x86_64, arm)\n"
           "  --with-tracing          generate wine-like \"+relay\" trace trampolines (needs -s)\n"
           "  --noroscompat           don't generate ros-compat information\n");
}

// HACK, because mingw headers
#define MIN(a,b) ((a) <= (b) ? (a) : (b))

int CompareExports(const void* pLeft,const void* pRight)
{
    EXPORT *pexpLeft = (EXPORT*)pLeft;
    EXPORT *pexpRight = (EXPORT*)pRight;
    int result = strncmp(pexpLeft->strName.buf,
                         pexpRight->strName.buf,
                         MIN(pexpLeft->strName.len,
                             pexpRight->strName.len));
    if (result == 0)
    {
        return (pexpLeft->strName.len < pexpRight->strName.len) ? -1 : 1;
    }

    return result;
}

void
Output_RosCompatDescriptor(FILE *file, EXPORT *pexports, unsigned int cExports)
{
    unsigned int i;

    /// HACK: should make a copy
    qsort(pexports, cExports, sizeof(EXPORT), CompareExports);

    fprintf(file, "ULONG __roscompat_export_masks__[] =\n{\n");
    
    for (i = 0; i < cExports; i++)
    {
        if ((pexports[i].uFlags & FL_NONAME) == 0)
        {
            fprintf(file,
                    "    0x%08x, // %.*s\n",
                    pexports[i].uVersionMask,
                    pexports[i].strName.len,
                    pexports[i].strName.buf);
        }
    }

    fprintf(file,
            "    0x0 // dummy \n"
            "};\n"
            "\n"
            "IMAGE_EXPORT_DIRECTORY __roscompat_magic_export_dir__;\n"
            "#if defined(_MSC_VER)\n"
            "#pragma section(\".expvers\")\n"
            "__declspec(allocate(\".expvers\"))\n"
            "#elif defined(__GNUC__)\n"
            "__attribute__ ((section(\".expvers\")))\n"
            "#else\n"
            "#error Your compiler is not supported (fix in spec2def).\n"
            "#endif\n"
            "ROSCOMPAT_DESCRIPTOR __roscompat_descriptor__ = \n"
            "{\n"
            "    __roscompat_export_masks__,\n"
            "    (sizeof(__roscompat_export_masks__) / sizeof(__roscompat_export_masks__[0])) - 1,\n"
            "   &__roscompat_magic_export_dir__\n"
            "};\n");
}

int main(int argc, char *argv[])
{
    size_t nFileSize;
    char *pszSource, *pszDefFileName = NULL, *pszStubFileName = NULL, *pszLibStubName = NULL;
    const char* pszVersionOption = "--version=0x";
    char achDllName[40];
    FILE *file;
    unsigned cExports = 0, i;
    EXPORT *pexports;

    if (argc < 2)
    {
        usage();
        return -1;
    }

    /* Read options */
    for (i = 1; i < (unsigned)argc && *argv[i] == '-'; i++)
    {
        if ((strcasecmp(argv[i], "--help") == 0) ||
            (strcasecmp(argv[i], "-h") == 0))
        {
            usage();
            return 0;
        }
        else if (strcasecmp(argv[i], "--noroscompat") == 0)
        {
            gbNoRosCompat = 1;
        }
        else if (argv[i][1] == 'd' && argv[i][2] == '=')
        {
            pszDefFileName = argv[i] + 3;
        }
        else if (argv[i][1] == 'l' && argv[i][2] == '=')
        {
            pszLibStubName = argv[i] + 3;
        }
        else if (argv[i][1] == 's' && argv[i][2] == '=')
        {
            pszStubFileName = argv[i] + 3;
        }
        else if (argv[i][1] == 'n' && argv[i][2] == '=')
        {
            pszDllName = argv[i] + 3;
        }
        else if (strncasecmp(argv[i], pszVersionOption, strlen(pszVersionOption)) == 0)
        {
            guOsVersion = strtoul(argv[i] + strlen(pszVersionOption), NULL, 16);
        }
        else if (strcasecmp(argv[i], "--implib") == 0)
        {
            gbImportLib = 1;
        }
        else if (strcasecmp(argv[i], "--ms") == 0)
        {
            gbMSComp = 1;
        }
        else if (strcasecmp(argv[i], "--no-private-warnings") == 0)
        {
            gbNotPrivateNoWarn = 1;
        }
        else if (strcasecmp(argv[i], "--with-tracing") == 0)
        {
            if (!pszStubFileName)
            {
                fprintf(stderr, "Error: cannot use --with-tracing without -s option.\n");
                return -1;
            }
            gbTracing = 1;
        }
        else if (argv[i][1] == 'a' && argv[i][2] == '=')
        {
            pszArchString = argv[i] + 3;
        }
        else
        {
            fprintf(stderr, "Unrecognized option: %s\n", argv[i]);
            return -1;
        }
    }

    if (strcasecmp(pszArchString, "i386") == 0)
    {
        giArch = ARCH_X86;
        gpszUnderscore = "_";
    }
    else if (strcasecmp(pszArchString, "x86_64") == 0) giArch = ARCH_AMD64;
    else if (strcasecmp(pszArchString, "ia64") == 0) giArch = ARCH_IA64;
    else if (strcasecmp(pszArchString, "arm") == 0) giArch = ARCH_ARM;
    else if (strcasecmp(pszArchString, "arm64") == 0) giArch = ARCH_ARM64;
    else if (strcasecmp(pszArchString, "ppc") == 0) giArch = ARCH_PPC;

    if ((giArch == ARCH_AMD64) || (giArch == ARCH_IA64))
    {
        pszArchString2 = "win64";
    }
    else
        pszArchString2 = "win32";

    /* Set a default dll name */
    if (!pszDllName)
    {
        char *p1, *p2;
        size_t len;

        p1 = strrchr(argv[i], '\\');
        if (!p1) p1 = strrchr(argv[i], '/');
        p2 = p1 = p1 ? p1 + 1 : argv[i];

        /* walk up to '.' */
        while (*p2 != '.' && *p2 != 0) p2++;
        len = p2 - p1;
        if (len >= sizeof(achDllName) - 5)
        {
            fprintf(stderr, "name too long: %s\n", p1);
            return -2;
        }

        strncpy(achDllName, p1, len);
        strncpy(achDllName + len, ".dll", sizeof(achDllName) - len);
        pszDllName = achDllName;
    }

    /* Open input file */
    pszSourceFileName = argv[i];
    file = fopen(pszSourceFileName, "r");
    if (!file)
    {
        fprintf(stderr, "error: could not open file %s\n", pszSourceFileName);
        return -3;
    }

    /* Get file size */
    fseek(file, 0, SEEK_END);
    nFileSize = ftell(file);
    rewind(file);

    /* Allocate memory buffer */
    pszSource = malloc(nFileSize + 1);
    if (!pszSource)
    {
        fclose(file);
        return -4;
    }

    /* Load input file into memory */
    nFileSize = fread(pszSource, 1, nFileSize, file);
    fclose(file);

    /* Zero terminate the source */
    pszSource[nFileSize] = '\0';

    pexports = ParseFile(pszSource, file, &cExports);
    if (pexports == NULL)
    {
        fprintf(stderr, "error: could not parse file!\n");
        return -1;
    }

    if (!gbMSComp)
    {
        if (ApplyOrdinals(pexports, cExports) < 0)
        {
            fprintf(stderr, "error: could not apply ordinals!\n");
            return -1;
        }
    }

    if (pszDefFileName)
    {
        /* Open output file */
        file = fopen(pszDefFileName, "w");
        if (!file)
        {
            fprintf(stderr, "error: could not open output file %s\n", argv[i + 1]);
            return -5;
        }

        OutputHeader_def(file, pszDllName);

        for (i = 0; i < cExports; i++)
        {
            if (pexports[i].bVersionIncluded)
                 OutputLine_def(file, &pexports[i]);
        }

        fclose(file);
    }

    if (pszStubFileName)
    {
        /* Open output file */
        file = fopen(pszStubFileName, "w");
        if (!file)
        {
            fprintf(stderr, "error: could not open output file %s\n", argv[i + 1]);
            return -5;
        }

        OutputHeader_stub(file);

        for (i = 0; i < cExports; i++)
        {
            if (pexports[i].bVersionIncluded)
                OutputLine_stub(file, &pexports[i]);
        }

        if (gbNoRosCompat == 0)
        {
            Output_RosCompatDescriptor(file, pexports, cExports);
        }

        fclose(file);
    }

    if (pszLibStubName)
    {
        /* Open output file */
        file = fopen(pszLibStubName, "w");
        if (!file)
        {
            fprintf(stderr, "error: could not open output file %s\n", argv[i + 1]);
            return -5;
        }

        OutputHeader_asmstub(file, pszDllName);

        for (i = 0; i < cExports; i++)
        {
            if (pexports[i].bVersionIncluded)
                OutputLine_asmstub(file, &pexports[i]);
        }

        fprintf(file, "\n    END\n");
        fclose(file);
    }

    free(pexports);

    return 0;
}
