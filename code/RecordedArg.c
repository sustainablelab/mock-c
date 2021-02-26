#include "RecordedArg.h"
#include <stdlib.h>     // malloc, free
#include <stdbool.h>    // bool, true, false

RecordedArg * RecordedArg_new(SetupRecordedArg SetupRecord)
{
    RecordedArg *out = (RecordedArg *)malloc(sizeof(RecordedArg));
    SetupRecord(out);
    return out;
}
void RecordedArg_destroy(RecordedArg *self)
{   // Deallocate this recorded arg.
    self->Destroy(self);        // Deallocate the memory `pArg` points to.
                                // `Destroy` is assigned to a function specific
                                // to the datatype of this recorded arg.
    free(self);                 // Deallocate the RecordedArg struct itself.
}

//=====[ RecordedArg: type-specific functions assigned by SetupRecord ]=====
// The `RecordedArg` struct has *four* elements
    // - pointer to the heap-mem that stores the argument value
    // - Free function to dealloacte heap-mem
    // - Print function to print the value in heap-mem
    // - Match function to check if the args in two RecordedArg structs match
    // - CheckArg function to check for equality to the arg value in a RecordedArg struct
static FreeArg              Destroy_uint8;
static FreeArg              Destroy_uint16;
static FreeArg              Destroy_uint32;
static FreeArg              Destroy_GString;
static FreeArg              Destroy_p_uint8;
static FreeArg              Destroy_p_GString;
static PrintArgToString     Print_uint8;
static PrintArgToString     Print_uint16;
static PrintArgToString     Print_uint32;
static PrintArgToString     Print_GString;
static PrintArgToString     Print_p_uint8;
static PrintArgToString     Print_p_GString;
static DoArgsMatch          Match_uint8;
static DoArgsMatch          Match_uint16;
static DoArgsMatch          Match_uint32;
static DoArgsMatch          Match_GString;
static DoArgsMatch          Match_p_uint8;
static DoArgsMatch          Match_p_GString;
static CheckArg_t           CheckArg_uint8;
static CheckArg_t           CheckArg_uint16;
static CheckArg_t           CheckArg_uint32;
static CheckArg_t           CheckArg_GString;
static CheckArg_t           CheckArg_p_uint8;
static CheckArg_t           CheckArg_p_GString;
static CheckValArgPointsTo_t           CheckValArgPointsTo_p_uint8;
/* static CheckValArgPointsTo_t           CheckValArgPointsTo_p_GString; */

//=====[ RecordedArg: Define SetupRecord for different arg datatypes ]=====
// The *four* elements of a RecordedArg struct are defined by the
// `SetupRecordedArg_arg_t` functions.
void SetupRecord_uint8_t(RecordedArg *self)
{
    self->pArg = malloc(sizeof(uint8_t));   // Get heap-mem.
    self->Destroy  = Destroy_uint8;         // How to deallocate.
    self->Print    = Print_uint8;           // How to print.
    self->Match    = Match_uint8;           // How to check if args match.
    self->CheckArg = CheckArg_uint8;        // How to check if arg equals a value.
}
void SetupRecord_uint16_t(RecordedArg *self)
{
    self->pArg = malloc(sizeof(uint16_t));  // Get heap-mem.
    self->Destroy = Destroy_uint16;         // How to deallocate.
    self->Print   = Print_uint16;           // How to print.
    self->Match   = Match_uint16;           // How to check if args match.
    self->CheckArg = CheckArg_uint16;        // How to check if arg equals a value.
}
void SetupRecord_uint32_t(RecordedArg *self)
{
    self->pArg = malloc(sizeof(uint32_t));  // Get heap-mem.
    self->Destroy = Destroy_uint32;         // How to deallocate.
    self->Print   = Print_uint32;           // How to print.
    self->Match   = Match_uint32;           // How to check if args match.
    self->CheckArg = CheckArg_uint32;        // How to check if arg equals a value.
}
void SetupRecord_GString(RecordedArg *self)
{
    self->pArg = malloc(sizeof(GString));   // Get heap-mem.
    self->Destroy = Destroy_GString;        // How to deallocate.
    self->Print   = Print_GString;          // How to print.
    self->Match   = Match_GString;          // How to check if args match.
    self->CheckArg = CheckArg_GString;      // How to check if arg equals a value.
}
void SetupRecord_p_uint8_t(RecordedArg *self)
{
    self->pArg = malloc(sizeof(uint8_t *));   // Get heap-mem.
    self->Destroy = Destroy_p_uint8;          // How to deallocate.
    self->Print   = Print_p_uint8;            // How to print.
    self->Match   = Match_p_uint8;            // How to check if args match.
    self->CheckArg = CheckArg_p_uint8;      // How to check if arg equals a value.
    self->CheckValArgPointsTo = CheckValArgPointsTo_p_uint8;      // How to check if arg equals a value.
}
void SetupRecord_p_GString(RecordedArg *self)
{
    self->pArg = malloc(sizeof(GString *));   // Get heap-mem.
    self->Destroy = Destroy_p_GString;        // How to deallocate.
    self->Print   = Print_p_GString;          // How to print.
    self->Match   = Match_p_GString;          // How to check if args match.
    self->CheckArg = CheckArg_p_GString;      // How to check if arg equals a value.
    /* self->CheckValArgPointsTo = CheckValArgPointsTo_p_GString;      // How to check if arg equals a value. */
}

//=====[ RecordedArg: Define Destroy for different arg datatypes ]=====
static void Destroy_uint8(RecordedArg *self)
{
    free((uint8_t *)self->pArg);
}
static void Destroy_uint16(RecordedArg *self)
{
    free((uint16_t *)self->pArg);
}
static void Destroy_uint32(RecordedArg *self)
{
    free((uint32_t *)self->pArg);
}
static void Destroy_GString(RecordedArg *self)
{
    g_string_free((GString *)self->pArg, true);
}
static void Destroy_p_uint8(RecordedArg *self)
{
    free((uint8_t **)self->pArg);
}
static void Destroy_p_GString(RecordedArg *self)
{
    free((GString **)self->pArg);
}

//=====[ RecordedArg: Define Print for different arg datatypes ]=====
static void Print_uint8(GString *string, RecordedArg *self)
{   // Caller provides a temporary string to store the result in.
    g_string_printf(string, "(uint8_t)%#04x", *(uint8_t *)self->pArg);
}
static void Print_uint16(GString *string, RecordedArg *self)
{
    g_string_printf(string, "(uint16_t)%#06x", *(uint16_t *)self->pArg);
    //g_string_printf(string, "%d", *(uint16_t *)self->pArg);
}
static void Print_uint32(GString *string, RecordedArg *self)
{
    g_string_printf(string, "(uint32_t)%#06x", *(uint32_t *)self->pArg);
    //g_string_printf(string, "%d", *(uint32_t *)self->pArg);
}
static void Print_GString(GString *string, RecordedArg *self)
{
    g_string_printf(string, "(GString)%s", ((GString *)self->pArg)->str);
}
static void Print_p_uint8(GString *string, RecordedArg *self)
{   // Caller provides a temporary string to store the result in.
    // TODO: print address or dereferenced value?
    // This prints the dereferenced value instead of the address.
    // This may not be what I want to print, but for now it's fine.
    // I'm just trying to get code to compile and tests to pass.
    // If I really do need the address, come back and fix later.
    g_string_printf(string, "(uint8_t)%#04x", **(uint8_t **)self->pArg);
    // 2019-11-01 there is something very wrong with this print.
    // I am only getting values 0000 and 0x01, regardles off the actual value
    // pointed to by the argument.
}
static void Print_p_GString(GString *string, RecordedArg *self)
{
    g_string_printf(string, "(GString *)%s", (*((GString **)self->pArg))->str);
}

//=====[ RecordedArg: Define CheckArg for different arg datatypes ]=====
// CheckArg is used in unit tests to assert a specific arg in a specific call
// is equal to some value.
static bool CheckArg_uint8(RecordedArg *argk, void const * arg)
{
    return *((uint8_t *)argk->pArg) == *((uint8_t *)arg);
}
// TODO: used, but not unit tested
static bool CheckArg_uint16(RecordedArg *argk, void const * arg)
{
    return *((uint16_t *)argk->pArg) == *((uint16_t *)arg);
}
// TODO: unit test:
static bool CheckArg_uint32(RecordedArg *argk, void const * arg)
{
    return *((uint32_t *)argk->pArg) == *((uint32_t *)arg);
}
// TODO: unit test:
static bool CheckArg_GString(RecordedArg *argk, void const * arg)
{
    int strings_do_not_match = g_strcmp0(
        ((GString *)argk->pArg)->str,
        ((GString *)arg)->str
        );
    return strings_do_not_match ? false : true;
}
// TODO: unit test:
static bool CheckArg_p_uint8(RecordedArg *argk, void const * arg)
{
    return *((uint8_t **)argk->pArg) == *((uint8_t **)arg);
}
// TODO: unit test:
static bool CheckValArgPointsTo_p_uint8(RecordedArg *argk, void const * arg)
{
    return **((uint8_t **)argk->pArg) == **((uint8_t **)arg);
}
// TODO: unit test:
static bool CheckArg_p_GString(RecordedArg *argk, void const * arg)
{
    // Compare the strings ultimately being pointed to
    int strings_do_not_match = g_strcmp0(
        (*((GString **)argk->pArg))->str,
        (*((GString **)arg))->str
        );
    return strings_do_not_match ? false : true;
}

//=====[ RecordedArg: Define Match for different arg datatypes ]=====
// Match is used in `Mock.c to define RecordedArgsMatch()`:
    // static bool RecordedArgsMatch(RecordedArg *expected_arg, RecordedArg *actual_arg)
    // {
    //     if (expected_arg->Match != actual_arg->Match) return false;
    //     return expected_arg->Match(expected_arg, actual_arg);
    // }
// Compare `pRec_s->Match` to see if args have same datatype.
// Call `pRec_s->Match(pRec1,pRec2)` returns true if args have same value.
static bool Match_uint8(RecordedArg *arg1, RecordedArg *arg2)
{
    return *((uint8_t *)arg1->pArg) == *((uint8_t *)arg2->pArg);
}
static bool Match_uint16(RecordedArg *arg1, RecordedArg *arg2)
{
    return *((uint16_t *)arg1->pArg) == *((uint16_t *)arg2->pArg);
}
static bool Match_uint32(RecordedArg *arg1, RecordedArg *arg2)
{
    return *((uint32_t *)arg1->pArg) == *((uint32_t *)arg2->pArg);
}
static bool Match_GString(RecordedArg *arg1, RecordedArg *arg2)
{
    int strings_do_not_match = g_strcmp0(
        ((GString *)arg1->pArg)->str,
        ((GString *)arg2->pArg)->str
        );
    return strings_do_not_match ? false : true;
}
static bool Match_p_uint8(RecordedArg *arg1, RecordedArg *arg2)
{
    /* TODO: match address or dereferenced value? */
    /* Both pass the test. But I want to compare the address. */
    /* Compare the addresses: */
    return *((uint8_t **)arg1->pArg) == *((uint8_t **)arg2->pArg);
    /* Compare the dereferenced values: */
    //return **((uint8_t **)arg1->pArg) == **((uint8_t **)arg2->pArg);
    /* This does not pass the test. */
    /* It compares the pArgs. The pArgs are different. */
    //return (uint8_t **)arg1->pArg == (uint8_t **)arg2->pArg;
}
static bool Match_p_GString(RecordedArg *arg1, RecordedArg *arg2)
{
    // Compare the strings ultimately being pointed to
    int strings_do_not_match = g_strcmp0(
        (*((GString **)arg1->pArg))->str,
        (*((GString **)arg2->pArg))->str);
    return strings_do_not_match ? false : true;
}
