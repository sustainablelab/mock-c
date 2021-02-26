#include <unity.h>
#include <stdbool.h>
#include <Mock.h>
#include "test_Mock.h"
#include "test_ReturnValues.h"
#include "test_RecordedArg.h"

void (*setUp)(void);
void (*tearDown)(void);
Mock_s *mock;

bool Yep=true, Nope=false;

void DevelopingMock(bool run_test)
{
    if (run_test)
    {
        /* =====[ New functionality I added 2019 October ]===== */
        setUp       = SetUp_AssertCall;
        tearDown    = TearDown_AssertCall;
        printf("\n# Test AssertCall\n");
        RUN_TEST(AssertCall_returns_false_if_call_number_exceeds_call_list);
        RUN_TEST(AssertCall_returns_false_if_call_n_does_not_match_name);
        RUN_TEST(AssertCall_returns_true_if_call_n_matches_name);
        // use same setUp/tearDown for AssertArg tests
        printf("\n# Test AssertArg\n");
        RUN_TEST(AssertArg_returns_false_if_call_number_exceeds_call_list);
        RUN_TEST(AssertArg_returns_false_if_arg_number_exceeds_arg_list);
        RUN_TEST(AssertArg_returns_true_if_arg_1_in_call_1_matches_uint8_arg_value);
        RUN_TEST(AssertArg_returns_true_if_arg_2_in_call_1_matches_uint8_arg_value);
        RUN_TEST(AssertArg_returns_true_if_arg_1_in_call_2_matches_uint8_arg_value);
        RUN_TEST(AssertArg_returns_true_if_arg_2_in_call_2_matches_uint8_arg_value);
        /* // use same setUp/tearDown for NumberOfActualCalls tests */
        printf("\n# Test NumberOfActualCalls\n");
        RUN_TEST(NumberOfActualCalls_returns_number_of_actual_calls_recorded_in_mock);

        setUp       = SetUp_libMock;
        tearDown    = TearDown_libMock;

        printf("\n# Test RanAsHoped\n");
        RUN_TEST(RanAsHoped_returns_true_if_call_lists_match);
        RUN_TEST(RanAsHoped_returns_false_if_more_expected_calls_than_actual_calls);
        RUN_TEST(RanAsHoped_returns_false_if_more_actual_calls_than_expected_calls);
        RUN_TEST(RanAsHoped_returns_false_if_call_names_do_not_match);
        RUN_TEST(RanAsHoped_returns_false_if_a_call_expected_more_inputs);
        RUN_TEST(RanAsHoped_returns_false_if_a_call_expected_less_inputs);
        RUN_TEST(RanAsHoped_returns_false_if_a_call_has_the_wrong_input_value);

        printf("\n# Test WhyDidItFail\n");
        // TODO(sustainablelab): I think Mock.WhyDidItFail is
        // replaced with Mock.ListAllCalls. Delete these tests if
        // WhyDidItFail is not used. And add tests for
        // ListAllCalls.
        RUN_TEST(WhyDidItFail_reports_unexpected_calls);
        RUN_TEST(WhyDidItFail_reports_when_calls_are_out_of_order);
        RUN_TEST(WhyDidItFail_reports_first_unexpected_call_after_last_expected_call);
        RUN_TEST(WhyDidItFail_reports_first_missed_call_after_last_actual_call);
    }
}

void DevelopingRecordedCall(bool run_test)
{
    if (run_test)
    {
    }
}

void DevelopingRecordedArg (bool run_test)
{
    if (run_test)
    {

        setUp = SetUp_RecordedArg; tearDown = TearDown_RecordedArg;
        printf("\n# Test Methods in struct SetupRecord_uint8_t\n");
        RUN_TEST(SetupRecord_uint8_t_points_pArg_at_a_uint8_t);
        RUN_TEST(Destroy_for_SetupRecord_uint8_t_frees_a_uint8_t);
        RUN_TEST(Print_for_SetupRecord_uint8_t_prints_a_uint8_t_to_a_string);
        RUN_TEST(Match_for_SetupRecord_uint8_t_checks_if_uint8_t_values_match);
        printf("\n# Test Methods in struct SetupRecord_uint16_t\n");
        RUN_TEST(SetupRecord_uint16_t_points_pArg_at_a_uint16_t);
        RUN_TEST(Destroy_for_SetupRecord_uint16_t_frees_a_uint16_t);
        RUN_TEST(Print_for_SetupRecord_uint16_t_prints_a_uint16_t_to_a_string);
        RUN_TEST(Match_for_SetupRecord_uint16_t_checks_if_uint16_t_values_match);
        printf("\n# Test Methods in struct SetupRecord_GString\n");
        RUN_TEST(SetupRecord_GString_points_pArg_at_a_GString);
        RUN_TEST(Destroy_for_SetupRecord_GString_frees_a_GString);
        RUN_TEST(Print_for_SetupRecord_GString_prints_a_GString_to_a_string);
        RUN_TEST(Match_for_SetupRecord_GString_checks_if_GString_values_match);
        printf("\n# Test Methods in struct SetupRecord_p_uint8_t\n");
        RUN_TEST(SetupRecord_p_uint8_t_points_pArg_at_a_pointer_to_an_uint8_t);
        RUN_TEST(Destroy_for_SetupRecord_p_uint8_t_frees_a_pointer_to_an_uint8_t);
        RUN_TEST(Print_for_SetupRecord_p_uint8_t_derefs_and_prints_value_to_a_string);
        RUN_TEST(Match_for_SetupRecord_p_uint8_t_derefs_and_checks_if_values_match);
        printf("\n# Test Methods in struct SetupRecord_p_GString\n");
        RUN_TEST(SetupRecord_p_GString_points_pArg_at_a_pointer_to_a_GString);
        RUN_TEST(Destroy_for_SetupRecord_p_GString_frees_a_pointer_to_a_GString);
        RUN_TEST(Print_for_SetupRecord_p_GString_derefs_and_prints_value_to_a_string);
        RUN_TEST(Match_for_SetupRecord_p_GString_derefs_and_checks_if_values_match);
    }
}

void DevelopingReturnValues(bool run_test)
{ 
    if (run_test)
    {
        setUp = SetUp_ReturnValues; tearDown = TearDown_ReturnValues;
        printf("\n# Test ReturnValues\n");
        RUN_TEST(StubReturnsFalse_returns_false);
        RUN_TEST(StubReturnsTrue_returns_true);
        RUN_TEST(StubReturns_uint8_t_returns_the_input_uint8_t);
    }
}

int main(void)
{
    /* TODO(sustainablelab): Write more tests */
    UNITY_BEGIN();
    DevelopingMock          (Yep); // <---- WRITE TESTS FOR ListAllCalls
    DevelopingRecordedArg   (Yep);
    DevelopingRecordedCall  (Yep); // <--- WRITE THESE TESTS
    DevelopingReturnValues  (Yep);  // <---- WRITE TESTS FOR OTHER RETURN TYPES
    return UNITY_END();
}
