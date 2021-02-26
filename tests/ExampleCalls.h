#ifndef _EXAMPLECALLS_H
#define _EXAMPLECALLS_H
// Calls for testing mock-c corner cases.

#include <stdint.h>  // uint8_t

void Expect_TakesNoArg(void);
void TakesNoArg_Stubbed(void);
void SpanishInquisition_Stubbed(void);

void Expect_TakesOneArg(uint8_t b1);
void TakesOneArg_Stubbed(uint8_t b1);
void TakesTwoArgs_StubbedWithCallName_TakesOneArg(uint8_t b1, uint8_t b2);

void Expect_TakesTwoArgs(uint8_t b1, uint8_t b2);
void TakesTwoArgs_Stubbed(uint8_t b1, uint8_t b2);
void TakesOneArg_StubbedWithCallName_TakesTwoArgs(uint8_t b1);

#endif // _EXAMPLECALLS_H
