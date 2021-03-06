#ifndef _TEST_RECORDEDARG_H
#define _TEST_RECORDEDARG_H

void SetUp_RecordedArg(void);
void TearDown_RecordedArg(void);

void SetupRecord_uint8_t_points_pArg_at_a_uint8_t(void);
void Destroy_for_SetupRecord_uint8_t_frees_a_uint8_t(void);
void Print_for_SetupRecord_uint8_t_prints_a_uint8_t_to_a_string(void);
void Match_for_SetupRecord_uint8_t_checks_if_uint8_t_values_match(void);

void SetupRecord_uint16_t_points_pArg_at_a_uint16_t(void);
void Destroy_for_SetupRecord_uint16_t_frees_a_uint16_t(void);
void Print_for_SetupRecord_uint16_t_prints_a_uint16_t_to_a_string(void);
void Match_for_SetupRecord_uint16_t_checks_if_uint16_t_values_match(void);

void SetupRecord_GString_points_pArg_at_a_GString(void);
void Destroy_for_SetupRecord_GString_frees_a_GString(void);
void Print_for_SetupRecord_GString_prints_a_GString_to_a_string(void);
void Match_for_SetupRecord_GString_checks_if_GString_values_match(void);

void SetupRecord_p_uint8_t_points_pArg_at_a_pointer_to_an_uint8_t(void);
void Destroy_for_SetupRecord_p_uint8_t_frees_a_pointer_to_an_uint8_t(void);
void Print_for_SetupRecord_p_uint8_t_derefs_and_prints_value_to_a_string(void);
void Match_for_SetupRecord_p_uint8_t_derefs_and_checks_if_values_match(void);

void SetupRecord_p_GString_points_pArg_at_a_pointer_to_a_GString(void);
void Destroy_for_SetupRecord_p_GString_frees_a_pointer_to_a_GString(void);
void Print_for_SetupRecord_p_GString_derefs_and_prints_value_to_a_string(void);
void Match_for_SetupRecord_p_GString_derefs_and_checks_if_values_match(void);

#endif // _TEST_RECORDEDARG_H
