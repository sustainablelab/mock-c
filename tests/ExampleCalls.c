// Calls for testing mock-c corner cases.
#include "ExampleCalls.h"
#include <Mock.h>
#include <RecordedCall.h>

static RecordedCall * Mock_TakesNoArg(void)
{
    char const *call_name = "TakesNoArg";
    RecordedCall *record_of_call = RecordedCall_new(call_name);
    return record_of_call;
}
void Expect_TakesNoArg(void) {
    RecordExpectedCall(mock, Mock_TakesNoArg());
}
void TakesNoArg_Stubbed(void) {
    RecordActualCall(mock, Mock_TakesNoArg());
}
void SpanishInquisition_Stubbed(void) {
    RecordedCall *record_of_call = RecordedCall_new("SpanishInquisition");
    RecordActualCall(mock, record_of_call);
}

static RecordedCall * Mock_TakesOneArg(uint8_t b1)
{
    char const *call_name = "TakesOneArg";
    RecordedCall *record_of_call = RecordedCall_new(call_name);
    RecordedArg *record_of_arg1 = RecordedArg_new(SetupRecord_uint8_t);
    *((uint8_t *)record_of_arg1->pArg) = b1;
    RecordArg(record_of_call, record_of_arg1);
    return record_of_call;
}
void Expect_TakesOneArg(uint8_t b1) {
    RecordExpectedCall(mock, Mock_TakesOneArg(b1));
}
void TakesOneArg_Stubbed(uint8_t b1) {
    RecordActualCall(mock, Mock_TakesOneArg(b1));
}
void TakesTwoArgs_StubbedWithCallName_TakesOneArg(uint8_t b1, uint8_t b2) {
    RecordedCall *record_of_call = RecordedCall_new("TakesOneArg");
    RecordedArg *record_of_arg1 = RecordedArg_new(SetupRecord_uint8_t);
    *((uint8_t *)record_of_arg1->pArg) = b1;
    RecordedArg *record_of_arg2 = RecordedArg_new(SetupRecord_uint8_t);
    *((uint8_t *)record_of_arg2->pArg) = b2;
    RecordArg(record_of_call, record_of_arg1);
    RecordArg(record_of_call, record_of_arg2);
    RecordActualCall(mock, record_of_call);
}

static RecordedCall * Mock_TakesTwoArgs(uint8_t b1, uint8_t b2)
{
    char const *call_name = "TakesTwoArgs";
    RecordedCall *record_of_call = RecordedCall_new(call_name);
    RecordedArg *record_of_arg1 = RecordedArg_new(SetupRecord_uint8_t);
    *((uint8_t *)record_of_arg1->pArg) = b1;
    RecordedArg *record_of_arg2 = RecordedArg_new(SetupRecord_uint8_t);
    *((uint8_t *)record_of_arg2->pArg) = b2;
    RecordArg(record_of_call, record_of_arg1);
    RecordArg(record_of_call, record_of_arg2);
    return record_of_call;
}
void Expect_TakesTwoArgs(uint8_t b1, uint8_t b2) {
    RecordExpectedCall(mock, Mock_TakesTwoArgs(b1, b2));
}
void TakesTwoArgs_Stubbed(uint8_t b1, uint8_t b2) {
    RecordActualCall(mock, Mock_TakesTwoArgs(b1, b2));
}
void TakesOneArg_StubbedWithCallName_TakesTwoArgs(uint8_t b1) {
    RecordedCall *record_of_call = RecordedCall_new("TakesTwoArgs");
    RecordedArg *record_of_arg1 = RecordedArg_new(SetupRecord_uint8_t);
    *((uint8_t *)record_of_arg1->pArg) = b1;
    RecordArg(record_of_call, record_of_arg1);
    RecordActualCall(mock, record_of_call);
}
