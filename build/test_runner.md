
# Test AssertCall
Call 100 is named TakesTwoArgs? Error: less than 100 calls.
test_runner.c:22:AssertCall_returns_false_if_call_number_exceeds_call_list:PASS
Call 1 is named WrongCallName? ... No, call 1 is TakesTwoArgs.
test_runner.c:23:AssertCall_returns_false_if_call_n_does_not_match_name:PASS
Call 1 is named TakesTwoArgs? ... Yes, call 1 is TakesTwoArgs.
test_runner.c:24:AssertCall_returns_true_if_call_n_matches_name:PASS

# Test AssertArg
Value passed to call 100, arg 1? Error: less than 100 calls.
test_runner.c:27:AssertArg_returns_false_if_call_number_exceeds_call_list:PASS
Value passed to call 1, arg 100? Error: call 1 has less than 100 args.
test_runner.c:28:AssertArg_returns_false_if_arg_number_exceeds_arg_list:PASS
Value passed to call 1, arg 1? (uint8_t)0x0b.
test_runner.c:29:AssertArg_returns_true_if_arg_1_in_call_1_matches_uint8_arg_value:PASS
Value passed to call 1, arg 2? (uint8_t)0x0c.
test_runner.c:30:AssertArg_returns_true_if_arg_2_in_call_1_matches_uint8_arg_value:PASS
Value passed to call 2, arg 1? (uint8_t)0x15.
test_runner.c:31:AssertArg_returns_true_if_arg_1_in_call_2_matches_uint8_arg_value:PASS
Value passed to call 2, arg 2? (uint8_t)0x16.
test_runner.c:32:AssertArg_returns_true_if_arg_2_in_call_2_matches_uint8_arg_value:PASS

# Test NumberOfActualCalls
test_runner.c:35:NumberOfActualCalls_returns_number_of_actual_calls_recorded_in_mock:PASS

# Test RanAsHoped
test_runner.c:41:RanAsHoped_returns_true_if_call_lists_match:PASS
test_runner.c:42:RanAsHoped_returns_false_if_more_expected_calls_than_actual_calls:PASS
test_runner.c:43:RanAsHoped_returns_false_if_more_actual_calls_than_expected_calls:PASS
test_runner.c:44:RanAsHoped_returns_false_if_call_names_do_not_match:PASS
test_runner.c:45:RanAsHoped_returns_false_if_a_call_expected_more_inputs:PASS
test_runner.c:46:RanAsHoped_returns_false_if_a_call_expected_less_inputs:PASS
test_runner.c:47:RanAsHoped_returns_false_if_a_call_has_the_wrong_input_value:PASS

# Test WhyDidItFail
test_runner.c:54:WhyDidItFail_reports_unexpected_calls:PASS
test_runner.c:55:WhyDidItFail_reports_when_calls_are_out_of_order:PASS
test_runner.c:56:WhyDidItFail_reports_first_unexpected_call_after_last_expected_call:PASS
test_runner.c:57:WhyDidItFail_reports_first_missed_call_after_last_actual_call:PASS

# Test Methods in struct SetupRecord_uint8_t
test_runner.c:75:SetupRecord_uint8_t_points_pArg_at_a_uint8_t:PASS
test_runner.c:76:Destroy_for_SetupRecord_uint8_t_frees_a_uint8_t:PASS
test_runner.c:77:Print_for_SetupRecord_uint8_t_prints_a_uint8_t_to_a_string:PASS
test_runner.c:78:Match_for_SetupRecord_uint8_t_checks_if_uint8_t_values_match:PASS

# Test Methods in struct SetupRecord_uint16_t
test_runner.c:80:SetupRecord_uint16_t_points_pArg_at_a_uint16_t:PASS
test_runner.c:81:Destroy_for_SetupRecord_uint16_t_frees_a_uint16_t:PASS
test_runner.c:82:Print_for_SetupRecord_uint16_t_prints_a_uint16_t_to_a_string:PASS
test_runner.c:83:Match_for_SetupRecord_uint16_t_checks_if_uint16_t_values_match:PASS

# Test Methods in struct SetupRecord_GString
test_runner.c:85:SetupRecord_GString_points_pArg_at_a_GString:PASS
test_runner.c:86:Destroy_for_SetupRecord_GString_frees_a_GString:PASS
test_runner.c:87:Print_for_SetupRecord_GString_prints_a_GString_to_a_string:PASS
test_runner.c:88:Match_for_SetupRecord_GString_checks_if_GString_values_match:PASS

# Test Methods in struct SetupRecord_p_uint8_t
test_runner.c:90:SetupRecord_p_uint8_t_points_pArg_at_a_pointer_to_an_uint8_t:PASS
test_runner.c:91:Destroy_for_SetupRecord_p_uint8_t_frees_a_pointer_to_an_uint8_t:PASS
test_runner.c:92:Print_for_SetupRecord_p_uint8_t_derefs_and_prints_value_to_a_string:PASS
test_runner.c:93:Match_for_SetupRecord_p_uint8_t_derefs_and_checks_if_values_match:PASS

# Test Methods in struct SetupRecord_p_GString
test_runner.c:95:SetupRecord_p_GString_points_pArg_at_a_pointer_to_a_GString:PASS
test_runner.c:96:Destroy_for_SetupRecord_p_GString_frees_a_pointer_to_a_GString:PASS
test_runner.c:97:Print_for_SetupRecord_p_GString_derefs_and_prints_value_to_a_string:PASS
test_runner.c:98:Match_for_SetupRecord_p_GString_derefs_and_checks_if_values_match:PASS

# Test ReturnValues
test_runner.c:108:StubReturnsFalse_returns_false:PASS
test_runner.c:109:StubReturnsTrue_returns_true:PASS
test_runner.c:110:StubReturns_uint8_t_returns_the_input_uint8_t:PASS

-----------------------
44 Tests 0 Failures 0 Ignored 
OK
