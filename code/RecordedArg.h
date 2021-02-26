#ifndef _RECORDEDARG_H
#define _RECORDEDARG_H
#include <glib.h>       // GString, GList
#include <stdbool.h>    // bool, true, false

//=====[ mock-c RecordedArg datatype ]=====
// Record arguments in a `RecordedArg` struct. See definition below.
typedef struct RecordedArg RecordedArg;
// Define function type `SetupRecordedArg`.
typedef void (SetupRecordedArg)(RecordedArg *self);
// Declare `SetupRecord_arg_t` functions for every arg type.
SetupRecordedArg     SetupRecord_uint8_t;
SetupRecordedArg     SetupRecord_uint16_t;
SetupRecordedArg     SetupRecord_uint32_t;
SetupRecordedArg     SetupRecord_GString;
SetupRecordedArg     SetupRecord_p_uint8_t;
SetupRecordedArg     SetupRecord_p_GString;
// To fake a function that takes an arg type not listed above,
// add it above, then in `RecordedArg.c`, define `SetupRecord_arg_t` for that
// `arg_t`.
typedef void (FreeArg)(RecordedArg *self);
typedef void (PrintArgToString)(GString *string, RecordedArg *self);
typedef bool (DoArgsMatch)(RecordedArg *arg1, RecordedArg *arg2);
typedef bool (CheckArg_t)(RecordedArg *argk, void const * arg);
typedef bool (CheckValArgPointsTo_t)(RecordedArg *argk, void const * arg);
// `SetupRecord_` functions allocate heap-mem for the arg.
// Heap-mem address is stored in `RecordedArg` struct member `pArg`.
// `SetupRecord_` functions define allocate heap-mem for the arg.
struct RecordedArg
{
    void *pArg;    // ex: *((uint8_t *)record_of_arg->pArg) returns a uint8_t
    // Store functions for working with the value on the heap pArg points to.
    // The function pointers are assigned by a SetupRecordedArg function.
    FreeArg             *Destroy;
    PrintArgToString    *Print;
    // Anything else needed by mock-c goes here.
    DoArgsMatch         *Match;
    CheckArg_t          *CheckArg;
    CheckValArgPointsTo_t          *CheckValArgPointsTo;
};
RecordedArg * RecordedArg_new(SetupRecordedArg SetupRecord);
void RecordedArg_destroy(RecordedArg *self);

#endif // _RECORDEDARG_H
