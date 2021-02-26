#include "test_RecordedArg.h"
#include <RecordedArg.h>
#include <unity.h>
#include <glib.h>       // GString, GList
//=====[ List of tests ]=====
    // [x] SetupRecord_uint8_t defines uint8_t operations for the RecordedArg
        //  [x] SetupRecord_uint8_t points pArg at a uint8_t
        //  [x] Destroy for SetupRecord_uint8_t frees a uint8_t
        //  [x] Print for SetupRecord_uint8_t prints a uint8_t to a string
        //  [x] Match for SetupRecord_uint8_t checks if uint8_t values match
    // [x] SetupRecord_uint16_t defines uint16_t operations for the RecordedArg
        //  [x] SetupRecord_uint16_t points pArg at a uint16_t
        //  [x] Destroy for SetupRecord_uint16_t frees a uint16_t
        //  [x] Print for SetupRecord_uint16_t prints a uint16_t to a string
        //  [x] Match for SetupRecord_uint16_t checks if uint16_t values match
    // [x] SetupRecord_GString defines GString operations for the RecordedArg
        //  [x] SetupRecord_GString points pArg at a GString
        //  [x] Destroy for SetupRecord_GString frees a GString
        //  [x] Print for SetupRecord_GString prints a GString to a string
        //  [x] Match for SetupRecord_GString checks if GString values match
    // [x] SetupRecord_p_uint8_t defines (uint8_t *) operations for the RecordedArg
        //  [x] SetupRecord_p_uint8_t points pArg at a pointer to an uint8_t
        //  [x] Destroy for SetupRecord_p_uint8_t frees a pointer to an uint8_t
        //  [x] Print for SetupRecord_p_uint8_t derefs and prints value to a string
        //  [x] Match for SetupRecord_p_uint8_t derefs and checks if values match
    // [x] SetupRecord_p_GString defines (GString *) operations for the RecordedArg
        //  [x] SetupRecord_p_GString points pArg at a pointer to a GString
        //  [x] Destroy for SetupRecord_p_GString frees a pointer to a GString
        //  [x] Print for SetupRecord_p_GString derefs and prints value to a string
        //  [x] Match for SetupRecord_p_GString derefs and checks if values match

void SetUp_RecordedArg(void){}
void TearDown_RecordedArg(void){}
void SetupRecord_uint8_t_points_pArg_at_a_uint8_t(void)
{
    //=====[ Setup ]=====
    uint8_t b1 = 0xAB;
    RecordedArg *record_of_arg1 = RecordedArg_new(SetupRecord_uint8_t);
    *((uint8_t *)record_of_arg1->pArg) = b1;
    //=====[ Operate and Test ]=====
    TEST_ASSERT_EQUAL_UINT8(b1, *((uint8_t *)record_of_arg1->pArg));
    //=====[ Teardown ]=====
    RecordedArg_destroy(record_of_arg1);
    record_of_arg1 = NULL;
}
void Destroy_for_SetupRecord_uint8_t_frees_a_uint8_t(void)
{
    //=====[ Setup ]=====
    uint8_t b1 = 0xAB;
    RecordedArg *record_of_arg1 = RecordedArg_new(SetupRecord_uint8_t);
    *((uint8_t *)record_of_arg1->pArg) = b1;
    //=====[ Lame test: what else can I do? ]=====
    TEST_ASSERT_NOT_EQUAL(NULL, record_of_arg1->Destroy);
    //=====[ Teardown ]=====
    RecordedArg_destroy(record_of_arg1);
    record_of_arg1 = NULL;
}
void Print_for_SetupRecord_uint8_t_prints_a_uint8_t_to_a_string(void)
{
    //=====[ Setup ]=====
    uint8_t b1 = 0x12;
    GString *expected = g_string_new("(uint8_t)0x12");
    GString *actual = g_string_new(NULL); // Call Print to write to actual.
    RecordedArg *record_of_arg1 = RecordedArg_new(SetupRecord_uint8_t);
    *((uint8_t *)record_of_arg1->pArg) = b1;
    //=====[ Operate ]=====
    record_of_arg1->Print(actual, record_of_arg1);
    //=====[ Test ]=====
    TEST_ASSERT_EQUAL_STRING( expected->str, actual->str);
    //=====[ Teardown ]=====
    g_string_free(expected, true);
    g_string_free(actual, true);
    RecordedArg_destroy(record_of_arg1);
    record_of_arg1 = NULL;
}
void Match_for_SetupRecord_uint8_t_checks_if_uint8_t_values_match(void)
{
    //=====[ Setup ]=====
    RecordedArg *record_of_arg1 = RecordedArg_new(SetupRecord_uint8_t);
    RecordedArg *record_of_arg2 = RecordedArg_new(SetupRecord_uint8_t);
    RecordedArg *record_of_arg3 = RecordedArg_new(SetupRecord_uint8_t);
    uint8_t b3 = 0x03;  // arg1 and arg2
    uint8_t b9 = 0x09;  // arg3
    *((uint8_t *)record_of_arg1->pArg) = b9;
    *((uint8_t *)record_of_arg2->pArg) = b9;
    *((uint8_t *)record_of_arg3->pArg) = b3;
    //=====[ Operate and Test ]=====
    TEST_ASSERT_TRUE (record_of_arg1->Match(record_of_arg1, record_of_arg2));
    TEST_ASSERT_FALSE(record_of_arg1->Match(record_of_arg1, record_of_arg3));
    //=====[ Teardown ]=====
    RecordedArg_destroy(record_of_arg1);
    record_of_arg1 = NULL;
    RecordedArg_destroy(record_of_arg2);
    record_of_arg2 = NULL;
    RecordedArg_destroy(record_of_arg3);
    record_of_arg3 = NULL;
}

void SetupRecord_uint16_t_points_pArg_at_a_uint16_t(void)
{
    //=====[ Setup ]=====
    uint16_t b1 = 0xAB;
    RecordedArg *record_of_arg1 = RecordedArg_new(SetupRecord_uint16_t);
    *((uint16_t *)record_of_arg1->pArg) = b1;
    //=====[ Operate and Test ]=====
    TEST_ASSERT_EQUAL_UINT8(b1, *((uint16_t *)record_of_arg1->pArg));
    //=====[ Teardown ]=====
    RecordedArg_destroy(record_of_arg1);
    record_of_arg1 = NULL;
}
void Destroy_for_SetupRecord_uint16_t_frees_a_uint16_t(void)
{
    //=====[ Setup ]=====
    uint16_t b1 = 0xAB;
    RecordedArg *record_of_arg1 = RecordedArg_new(SetupRecord_uint16_t);
    *((uint16_t *)record_of_arg1->pArg) = b1;
    //=====[ Lame test: what else can I do? ]=====
    TEST_ASSERT_NOT_EQUAL(NULL, record_of_arg1->Destroy);
    //=====[ Teardown ]=====
    RecordedArg_destroy(record_of_arg1);
    record_of_arg1 = NULL;
}
void Print_for_SetupRecord_uint16_t_prints_a_uint16_t_to_a_string(void)
{
    //=====[ Setup ]=====
    uint16_t b1 = 0x1234;
    GString *expected = g_string_new("(uint16_t)0x1234");
    GString *actual = g_string_new(NULL); // Call Print to write to actual.
    RecordedArg *record_of_arg1 = RecordedArg_new(SetupRecord_uint16_t);
    *((uint16_t *)record_of_arg1->pArg) = b1;
    //=====[ Operate ]=====
    record_of_arg1->Print(actual, record_of_arg1);
    //=====[ Test ]=====
    TEST_ASSERT_EQUAL_STRING( expected->str, actual->str);
    //=====[ Teardown ]=====
    g_string_free(expected, true);
    g_string_free(actual, true);
    RecordedArg_destroy(record_of_arg1);
    record_of_arg1 = NULL;
}
void Match_for_SetupRecord_uint16_t_checks_if_uint16_t_values_match(void)
{
    //=====[ Setup ]=====
    RecordedArg *record_of_arg1 = RecordedArg_new(SetupRecord_uint16_t);
    RecordedArg *record_of_arg2 = RecordedArg_new(SetupRecord_uint16_t);
    RecordedArg *record_of_arg3 = RecordedArg_new(SetupRecord_uint16_t);
    uint16_t b3 = 0x03;  // arg1 and arg2
    uint16_t b9 = 0x09;  // arg3
    *((uint16_t *)record_of_arg1->pArg) = b9;
    *((uint16_t *)record_of_arg2->pArg) = b9;
    *((uint16_t *)record_of_arg3->pArg) = b3;
    //=====[ Operate and Test ]=====
    TEST_ASSERT_TRUE (record_of_arg1->Match(record_of_arg1, record_of_arg2));
    TEST_ASSERT_FALSE(record_of_arg1->Match(record_of_arg1, record_of_arg3));
    //=====[ Teardown ]=====
    RecordedArg_destroy(record_of_arg1);
    record_of_arg1 = NULL;
    RecordedArg_destroy(record_of_arg2);
    record_of_arg2 = NULL;
    RecordedArg_destroy(record_of_arg3);
    record_of_arg3 = NULL;
}

void SetupRecord_GString_points_pArg_at_a_GString(void)
{
    //=====[ Setup ]=====
    GString *pGS1 = g_string_new("string 1");
    RecordedArg *record_of_arg1 = RecordedArg_new(SetupRecord_GString);
    record_of_arg1->pArg = (void *)g_string_new(pGS1->str);
    //=====[ Operate and Test ]=====
    TEST_ASSERT_EQUAL_STRING(pGS1->str, ((GString *)record_of_arg1->pArg)->str);
    //=====[ Teardown ]=====
    g_string_free(pGS1, true);
    RecordedArg_destroy(record_of_arg1);
    record_of_arg1 = NULL;
}
void Destroy_for_SetupRecord_GString_frees_a_GString(void)
{
    //=====[ Setup ]=====
    GString *pGS1 = g_string_new("string 1");
    RecordedArg *record_of_arg1 = RecordedArg_new(SetupRecord_GString);
    record_of_arg1->pArg = (void *)g_string_new(pGS1->str);
    //=====[ Lame test: what else can I do? ]=====
    TEST_ASSERT_NOT_EQUAL(NULL, record_of_arg1->Destroy);
    //=====[ Teardown ]=====
    RecordedArg_destroy(record_of_arg1);
    record_of_arg1 = NULL;
}
void Print_for_SetupRecord_GString_prints_a_GString_to_a_string(void)
{
    //=====[ Setup ]=====
    GString *expected = g_string_new("(GString)bob");
    GString *actual = g_string_new(NULL); // Call Print to write to actual.
    RecordedArg *record_of_arg1 = RecordedArg_new(SetupRecord_GString);
    record_of_arg1->pArg = (void *)g_string_new("bob");
    //=====[ Operate ]=====
    record_of_arg1->Print(actual, record_of_arg1);
    //=====[ Test ]=====
    TEST_ASSERT_EQUAL_STRING( expected->str, actual->str);
    //=====[ Teardown ]=====
    g_string_free(expected, true);
    g_string_free(actual, true);
    RecordedArg_destroy(record_of_arg1);
    record_of_arg1 = NULL;
}
void Match_for_SetupRecord_GString_checks_if_GString_values_match(void)
{
    //=====[ Setup ]=====
    RecordedArg *record_of_arg1 = RecordedArg_new(SetupRecord_GString);
    RecordedArg *record_of_arg2 = RecordedArg_new(SetupRecord_GString);
    RecordedArg *record_of_arg3 = RecordedArg_new(SetupRecord_GString);
    GString *str3 = g_string_new("string 3");  // arg1 and arg2
    GString *str9 = g_string_new("string 9");  // arg3
    record_of_arg1->pArg = (void *)g_string_new(str9->str);
    record_of_arg2->pArg = (void *)g_string_new(str9->str);
    record_of_arg3->pArg = (void *)g_string_new(str3->str);
    //=====[ Operate and Test ]=====
    TEST_ASSERT_TRUE (record_of_arg1->Match(record_of_arg1, record_of_arg2));
    TEST_ASSERT_FALSE(record_of_arg1->Match(record_of_arg1, record_of_arg3));
    //=====[ Teardown ]=====
    g_string_free(str3, true);
    g_string_free(str9, true);
    RecordedArg_destroy(record_of_arg1);
    record_of_arg1 = NULL;
    RecordedArg_destroy(record_of_arg2);
    record_of_arg2 = NULL;
    RecordedArg_destroy(record_of_arg3);
    record_of_arg3 = NULL;
}

void SetupRecord_p_uint8_t_points_pArg_at_a_pointer_to_an_uint8_t(void)
{
    //=====[ Setup ]=====
    uint8_t b1 = 0x01;
    uint8_t *b1_address = &b1;
    RecordedArg *record_of_arg1 = RecordedArg_new(SetupRecord_p_uint8_t);
    *((uint8_t **)record_of_arg1->pArg) = b1_address;
    // FAIL: Expected 71 Was 1 : record_of_arg1->pArg = (void *)b1_address;
    //=====[ Operate and Test ]=====
    TEST_ASSERT_EQUAL_PTR(b1_address, *((uint8_t **)record_of_arg1->pArg));
    //=====[ Teardown ]=====
    RecordedArg_destroy(record_of_arg1);
    record_of_arg1 = NULL;
}
void Destroy_for_SetupRecord_p_uint8_t_frees_a_pointer_to_an_uint8_t(void)
{
    //=====[ Setup ]=====
    uint8_t b1 = 0x01;
    uint8_t *b1_address = &b1;
    RecordedArg *record_of_arg1 = RecordedArg_new(SetupRecord_p_uint8_t);
    *((uint8_t **)record_of_arg1->pArg) = b1_address;
    //=====[ Lame test: what else can I do? ]=====
    TEST_ASSERT_NOT_EQUAL(NULL, record_of_arg1->Destroy);
    //=====[ Teardown ]=====
    RecordedArg_destroy(record_of_arg1);
    record_of_arg1 = NULL;
}
void Print_for_SetupRecord_p_uint8_t_derefs_and_prints_value_to_a_string(void)
{
    //=====[ Setup ]=====
    GString *expected = g_string_new("(uint8_t)0x12"); uint8_t b1 = 0x12;
    uint8_t *b1_address = &b1;
    GString *actual = g_string_new(NULL); // Call Print to write to actual.
    RecordedArg *record_of_arg1 = RecordedArg_new(SetupRecord_p_uint8_t);
    *((uint8_t **)record_of_arg1->pArg) = b1_address;
    //=====[ Operate ]=====
    record_of_arg1->Print(actual, record_of_arg1);
    //=====[ Test ]=====
    TEST_ASSERT_EQUAL_STRING( expected->str, actual->str);
    //=====[ Teardown ]=====
    g_string_free(expected, true);
    g_string_free(actual, true);
    RecordedArg_destroy(record_of_arg1);
    record_of_arg1 = NULL;
}
void Match_for_SetupRecord_p_uint8_t_derefs_and_checks_if_values_match(void)
{
    //=====[ Setup ]=====
    RecordedArg *record_of_arg1 = RecordedArg_new(SetupRecord_p_uint8_t);
    RecordedArg *record_of_arg2 = RecordedArg_new(SetupRecord_p_uint8_t);
    RecordedArg *record_of_arg3 = RecordedArg_new(SetupRecord_p_uint8_t);
    uint8_t b3 = 0x03; uint8_t *b3_address = &b3;  // arg1 and arg2
    uint8_t b9 = 0x09; uint8_t *b9_address = &b9;  // arg3
    *((uint8_t **)record_of_arg1->pArg) = b9_address;
    *((uint8_t **)record_of_arg2->pArg) = b9_address;
    *((uint8_t **)record_of_arg3->pArg) = b3_address;
    //=====[ Operate and Test ]=====
    TEST_ASSERT_TRUE (record_of_arg1->Match(record_of_arg1, record_of_arg2));
    TEST_ASSERT_FALSE(record_of_arg1->Match(record_of_arg1, record_of_arg3));
    //=====[ Teardown ]=====
    RecordedArg_destroy(record_of_arg1);
    record_of_arg1 = NULL;
    RecordedArg_destroy(record_of_arg2);
    record_of_arg2 = NULL;
    RecordedArg_destroy(record_of_arg3);
    record_of_arg3 = NULL;
}

void SetupRecord_p_GString_points_pArg_at_a_pointer_to_a_GString(void)
{
    //=====[ Setup ]=====
    GString *p_gstring_arg1 = g_string_new("string 1");
    RecordedArg *record_of_arg1 = RecordedArg_new(SetupRecord_p_GString);
    *((GString **)record_of_arg1->pArg) = p_gstring_arg1;
    //=====[ Operate and Test ]=====
    TEST_ASSERT_EQUAL_STRING(
        p_gstring_arg1->str,
        (*((GString **)record_of_arg1->pArg))->str
        );
    //=====[ Teardown ]=====
    g_string_free(p_gstring_arg1, true);
    RecordedArg_destroy(record_of_arg1);
    record_of_arg1 = NULL;
}
void Destroy_for_SetupRecord_p_GString_frees_a_pointer_to_a_GString(void)
{
    //=====[ Setup ]=====
    GString *p_gstring_arg1 = g_string_new("string 1");
    RecordedArg *record_of_arg1 = RecordedArg_new(SetupRecord_p_GString);
    *((GString **)record_of_arg1->pArg) = p_gstring_arg1;
    //=====[ Lame test: what else can I do? ]=====
    TEST_ASSERT_NOT_EQUAL(NULL, record_of_arg1->Destroy);
    //=====[ Teardown ]=====
    RecordedArg_destroy(record_of_arg1);
    record_of_arg1 = NULL;
}
void Print_for_SetupRecord_p_GString_derefs_and_prints_value_to_a_string(void)
{
    //=====[ Setup ]=====
    GString *expected = g_string_new("(GString *)bob");
    GString *actual = g_string_new(NULL); // Call Print to write to actual.
    RecordedArg *record_of_arg1 = RecordedArg_new(SetupRecord_p_GString);
    GString *p_gstring_arg1 = g_string_new("bob");
    *((GString **)record_of_arg1->pArg) = p_gstring_arg1;
    //=====[ Operate ]=====
    record_of_arg1->Print(actual, record_of_arg1);
    //=====[ Test ]=====
    TEST_ASSERT_EQUAL_STRING( expected->str, actual->str);
    //=====[ Teardown ]=====
    g_string_free(expected, true);
    g_string_free(actual, true);
    RecordedArg_destroy(record_of_arg1);
    record_of_arg1 = NULL;
}
void Match_for_SetupRecord_p_GString_derefs_and_checks_if_values_match(void)
{
    //=====[ Setup ]=====
    RecordedArg *record_of_arg1 = RecordedArg_new(SetupRecord_p_GString);
    RecordedArg *record_of_arg2 = RecordedArg_new(SetupRecord_p_GString);
    RecordedArg *record_of_arg3 = RecordedArg_new(SetupRecord_p_GString);
    GString *str9 = g_string_new("string 9");  // arg1 and arg2
    GString *str3 = g_string_new("string 3");  // arg3
    *((GString **)record_of_arg1->pArg) = str9;
    *((GString **)record_of_arg2->pArg) = str9;
    *((GString **)record_of_arg3->pArg) = str3;
    //=====[ Operate and Test ]=====
    TEST_ASSERT_TRUE (record_of_arg1->Match(record_of_arg1, record_of_arg2));
    TEST_ASSERT_FALSE(record_of_arg1->Match(record_of_arg1, record_of_arg3));
    //=====[ Teardown ]=====
    g_string_free(str3, true);
    g_string_free(str9, true);
    RecordedArg_destroy(record_of_arg1);
    record_of_arg1 = NULL;
    RecordedArg_destroy(record_of_arg2);
    record_of_arg2 = NULL;
    RecordedArg_destroy(record_of_arg3);
    record_of_arg3 = NULL;
}
