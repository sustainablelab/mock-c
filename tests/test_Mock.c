#include "test_Mock.h"
#include "ExampleCalls.h"
#include <unity.h>
#include <Mock.h>

//=====[ List of tests: specifications of RanAsHoped ]=====
    // [x] Pass if call lists are the same length and all values match.
    // RanAsHoped returns true if:
    // [x] call lists are the same length and all values match
    // RanAsHoped returns false if:
    // [x] there are more expected calls than actual calls
    // [x] there are more actual calls than expected calls
    // RanAsHoped returns false if a call has:
    // [x] an expected call name that does not match the actual call name
    // [x] more expected inputs than actual inputs
    // [x] more actual inputs than expected inputs
    // [x] an expected input value that does not match the actual input value
    //
    // WhyDidItFail reports
    // [x] Unexpected calls
    // [x] Calls made out of order
    // [x] first unexpected actual call after exhausting a shorter list of expected calls
    // [x] first missed call after exhausting a shorter list of actual calls
    //

/* =====[ New functionality I added 2019 October ]===== */
// Define what is recorded when the following unit tests fake recording an
// actual call.
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
void SetUp_AssertCall(void){
    mock = Mock_new();
    //
    uint8_t call1_arg1 = 11; uint8_t call1_arg2 = 12;
    uint8_t call2_arg1 = 21; uint8_t call2_arg2 = 22;
    RecordActualCall(mock, Mock_TakesTwoArgs(call1_arg1, call1_arg2));
    RecordActualCall(mock, Mock_TakesTwoArgs(call2_arg1, call2_arg2));
}
void TearDown_AssertCall(void){
    //
    Mock_destroy(mock);
    mock = NULL;
}

void AssertCall_returns_false_if_call_number_exceeds_call_list(void){
    /* =====[ Operate and Test ]===== */
    TEST_ASSERT_FALSE(AssertCall(mock,100,"TakesTwoArgs"));
}
void AssertCall_returns_false_if_call_n_does_not_match_name(void)
{
    /* =====[ Operate and Test ]===== */
    TEST_ASSERT_FALSE(AssertCall(mock,1,"WrongCallName"));
}
void AssertCall_returns_true_if_call_n_matches_name(void)
{
    /* =====[ Operate and Test ]===== */
    TEST_ASSERT_TRUE(AssertCall(mock,1,"TakesTwoArgs"));
}
void AssertArg_returns_false_if_call_number_exceeds_call_list(void)
{
    /* =====[ Operate and Test ]===== */
    uint8_t arg_n = 1; uint8_t assert_val = 11;
    TEST_ASSERT_FALSE(AssertArg(mock, 100, arg_n, &assert_val));
}
void AssertArg_returns_false_if_arg_number_exceeds_arg_list(void)
{
    /* =====[ Operate and Test ]===== */
    uint8_t call_n = 1; uint8_t assert_val = 11;
    TEST_ASSERT_FALSE(AssertArg(mock, call_n, 100, &assert_val));
}
void AssertArg_returns_true_if_arg_1_in_call_1_matches_uint8_arg_value(void)
{
    /* =====[ Operate and Test ]===== */
    uint8_t call_n = 1; uint8_t arg_n = 1; uint8_t assert_val = 11;
    TEST_ASSERT_TRUE(AssertArg(mock, call_n, arg_n, &assert_val));
}
void AssertArg_returns_true_if_arg_2_in_call_1_matches_uint8_arg_value(void)
{
    /* =====[ Operate and Test ]===== */
    uint8_t call_n = 1; uint8_t arg_n = 2; uint8_t assert_val = 12;
    TEST_ASSERT_TRUE(AssertArg(mock, call_n, arg_n, &assert_val));
}
void AssertArg_returns_true_if_arg_1_in_call_2_matches_uint8_arg_value(void)
{
    /* =====[ Operate and Test ]===== */
    uint8_t call_n = 2; uint8_t arg_n = 1; uint8_t assert_val = 21;
    TEST_ASSERT_TRUE(AssertArg(mock, call_n, arg_n, &assert_val));
}
void AssertArg_returns_true_if_arg_2_in_call_2_matches_uint8_arg_value(void)
{
    /* =====[ Operate and Test ]===== */
    uint8_t call_n = 2; uint8_t arg_n = 2; uint8_t assert_val = 22;
    /* printf("\n"); */
    TEST_ASSERT_TRUE(AssertArg(mock, call_n, arg_n, &assert_val));
}
void NumberOfActualCalls_returns_number_of_actual_calls_recorded_in_mock(void)
{
    /* =====[ Operate and Test ]===== */
    TEST_ASSERT_EQUAL_UINT8(2, NumberOfActualCalls(mock));
}

void SetUp_libMock(void){
    mock = Mock_new();
    //
}
void TearDown_libMock(void){
    //
    Mock_destroy(mock);
    mock = NULL;
}

void RanAsHoped_returns_true_if_call_lists_match(void)
{   //  [x] call lists are the same length and all values match
    Expect_TakesNoArg();    // test sets an expectation that a DOF is called
    TakesNoArg_Stubbed();   // simulate the FUT calling the stubbed DOF
    TEST_ASSERT_TRUE_MESSAGE(
        RanAsHoped(mock),           // If this is false,
        WhyDidItFail(mock)          // print this message.
        );
}
void RanAsHoped_returns_false_if_more_expected_calls_than_actual_calls(void)
{   // [x] there are more expected calls than actual calls
    Expect_TakesNoArg();    // test sets an expectation that a DOF is called
    // simulate the FUT missing the call to the stubbed DOF
    TEST_ASSERT_FALSE(RanAsHoped(mock));
}
void RanAsHoped_returns_false_if_more_actual_calls_than_expected_calls(void)
{   // [x] there are more actual calls than expected calls
    SpanishInquisition_Stubbed();  // simulate the FUT making an unexpected call
    TEST_ASSERT_FALSE(RanAsHoped(mock));
}
void RanAsHoped_returns_false_if_call_names_do_not_match(void)
{   // [x] an expected call name that does not match the actual call name
    Expect_TakesNoArg();  // test sets an expectation that TakesNoArg is called
    SpanishInquisition_Stubbed();  // simulate the FUT calling something else
    TEST_ASSERT_FALSE(RanAsHoped(mock));
}
void RanAsHoped_returns_false_if_a_call_expected_more_inputs(void)
{   // [x] more expected inputs than actual inputs
    Expect_TakesTwoArgs(0xa1, 0xa2);  // test sets an expectation this DOF takes two args
    TakesOneArg_StubbedWithCallName_TakesTwoArgs(0xa1);
    TEST_ASSERT_FALSE(RanAsHoped(mock));
}
void RanAsHoped_returns_false_if_a_call_expected_less_inputs(void)
{   // [x] more actual inputs than expected inputs
    Expect_TakesOneArg(0xb1);  // test sets an expectation this DOF takes one arg
    TakesTwoArgs_StubbedWithCallName_TakesOneArg(0xb1, 0xb2);
    TEST_ASSERT_FALSE(RanAsHoped(mock));
}
void RanAsHoped_returns_false_if_a_call_has_the_wrong_input_value(void)
{   // [x] an expected input value that does not match the actual input value
    Expect_TakesOneArg(0xAA);   // test set an expectation this DOF receives 0xAA
    TakesOneArg_Stubbed(0xFF);  // simulate FUT calling DOF with 0xFF instead
    TEST_ASSERT_FALSE(RanAsHoped(mock));
}
void WhyDidItFail_reports_unexpected_calls(void)
{   // [x] Unexpected calls
    Expect_TakesNoArg();           // test expects the FUT to call this DOF
    SpanishInquisition_Stubbed();  // simulate the FUT making an unexpected call
    TEST_ASSERT_FALSE(RanAsHoped(mock));
    TEST_ASSERT_EQUAL_STRING(
        " Call #1: expected 'TakesNoArg',"
        " was 'SpanishInquisition'."
        " ",
        WhyDidItFail(mock)
        );
}
void WhyDidItFail_reports_when_calls_are_out_of_order(void)
{   // [x] Calls made out of order
    Expect_TakesNoArg();
    Expect_TakesOneArg(0x01);
    Expect_TakesTwoArgs(0x02,0x03);
    Expect_TakesOneArg(0xAA);
    TakesNoArg_Stubbed();           // simulate the FUT calling the expected DOF
    TakesTwoArgs_Stubbed(0x02,0x03);// simulate the FUT calling DOF out of order
    TakesOneArg_Stubbed(0x01);      // simulate the FUT calling DOF out of order
    TakesOneArg_Stubbed(0xAA);      // simulate the FUT calling the expected DOF
    TEST_ASSERT_FALSE(RanAsHoped(mock));
    TEST_ASSERT_EQUAL_STRING(
        " Wrong number of args in call #2 'TakesOneArg',"
        " expected 1, was 2."
        " Wrong number of args in call #3 'TakesTwoArgs',"
        " expected 2, was 1."
        " Call #2: expected 'TakesOneArg',"
        " was 'TakesTwoArgs'."
        " Call #2: 'TakesOneArg' expected input '(uint8_t)0x01',"
        " but was '(uint8_t)0x02'."
        " Call #3: expected 'TakesTwoArgs',"
        " was 'TakesOneArg'."
        " Call #3: 'TakesTwoArgs' expected input '(uint8_t)0x02',"
        " but was '(uint8_t)0x01'."
        " ",
        WhyDidItFail(mock)
        );
}
void WhyDidItFail_reports_first_unexpected_call_after_last_expected_call(void)
{   // [x] first unexpected actual call after exhausting a shorter list of expected calls
    Expect_TakesNoArg();            // test expects FUT to call this DOF
    Expect_TakesOneArg(0x01);       // expect this is the last DOF the FUT calls
    TakesNoArg_Stubbed();           // simulate the FUT calling the expected DOF
    TakesOneArg_Stubbed(0x01);      // simulate the FUT calling the expected DOF
    TakesTwoArgs_Stubbed(0x02,0x03);// simulate the FUT calling an unexpected DOF
    TEST_ASSERT_FALSE(RanAsHoped(mock));
    TEST_ASSERT_EQUAL_STRING(
        " Expected 2 calls, received 3 calls."
        " First unexpected call: received #3:'TakesTwoArgs'."
        " ",
        WhyDidItFail(mock)
        );
}
void WhyDidItFail_reports_first_missed_call_after_last_actual_call(void)
{   // [x] first missed call after exhausting a shorter list of actual calls
    Expect_TakesNoArg();            // test expects FUT to call this DOF
    Expect_TakesOneArg(0x01);       // test expects FUT to call this DOF
    Expect_TakesTwoArgs(0x02,0x03); // expect this is the last DOF the FUT calls
    TakesNoArg_Stubbed();           // simulate the FUT calling the expected DOF
    TakesOneArg_Stubbed(0x01);      // simulate this is the last DOF the FUT calls
    TEST_ASSERT_FALSE(RanAsHoped(mock));
    TEST_ASSERT_EQUAL_STRING(
        " Expected 3 calls, received 2 calls."
        " First missed call: expected #3:'TakesTwoArgs'."
        " ",
        WhyDidItFail(mock)
        );
}

