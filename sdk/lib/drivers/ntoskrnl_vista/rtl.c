
#include <ntdef.h>
#include <ntifs.h>
#include <debug.h> 

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlQueryRegistryValuesEx(
    _In_     ULONG RelativeTo,
    _In_     PCWSTR Path,
    _Inout_ _At_(*(*QueryTable).EntryContext, _Pre_unknown_)
        PRTL_QUERY_REGISTRY_TABLE QueryTable,
    _In_opt_ PVOID Context,
    _In_opt_ PVOID Environment)
{
    UNIMPLEMENTED;
    return RtlQueryRegistryValues(RelativeTo, Path, QueryTable, Context, Environment);
}
