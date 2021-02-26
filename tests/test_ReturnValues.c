#include "test_ReturnValues.h"
#include <unity.h>
#include <ReturnValues.h>
void SetUp_ReturnValues(void){}
void TearDown_ReturnValues(void){}
void StubReturnsFalse_returns_false(void)
{
    TEST_ASSERT_FALSE(StubReturnsFalse());
}
void StubReturnsTrue_returns_true(void)
{
    TEST_ASSERT_TRUE(StubReturnsTrue());
}
//TODO: this function is useless because I cannot pass the input in my test
//example:
//uint8_t (*FtReadData_Returns)(void) = StubReturns_uint8_t(0x00);
//The function pointer input argument (void) does not match the assignment.
//Use my globals hack instead.
void StubReturns_uint8_t_returns_the_input_uint8_t(void)
{
    TEST_ASSERT_EQUAL_HEX8(0x23, StubReturns_uint8_t(0x23));
}
