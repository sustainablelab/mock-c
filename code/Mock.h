#ifndef _MOCK_H
#define _MOCK_H

#include "RecordedCall.h"   // RecordedCall
#include "RecordedArg.h"  // RecordedArg
#include <stdbool.h>        // bool, true, false

//=====[ mock-c Mock datatype ]=====
typedef struct Mock_s Mock_s;
extern Mock_s *mock;    // memory allocated in the test runner
Mock_s * Mock_new(void);
void Mock_destroy(Mock_s *self);
void RecordExpectedCall(Mock_s *self, RecordedCall *func_call);
void RecordActualCall(Mock_s *self, RecordedCall *func_call);
void RecordArg(RecordedCall *self, RecordedArg *input_arg);
void PrintAllCalls(Mock_s *self);  // Example
// copied from old mock-c
bool RanAsHoped(Mock_s *self);
char const * WhyDidItFail(Mock_s *self);
/* =====[ New functionality I added 2018 August ]===== */
char const * ListAllCalls(Mock_s *self);  // alternate to WhyDidItFail()
/* =====[ New functionality I added 2019 October ]===== */
/* bool AssertCall(Mock_s *mock, uint8_t call_number, char * call_name); */
bool AssertCall(Mock_s *mock, uint16_t call_number, char const * call_name);
bool AssertArg(
    Mock_s *mock,
    uint16_t call_number,
    uint8_t arg_number,
    void *p_assert_val
    );
bool AssertArgPointsToValue(
    Mock_s *self,
    uint8_t call_n,
    uint8_t arg_k,
    void *p_assert_val
    );
uint16_t NumberOfActualCalls(Mock_s *mock);

#endif // _MOCK_H
