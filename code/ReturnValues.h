#ifndef _RETURNVALUES_H
#define _RETURNVALUES_H

#include <stdbool.h>    // bool, true, false
#include <stdint.h>     // uint8_t

// mockist tests assign a DOF_Returns() function pointer to these functions
bool StubReturnsFalse(void);  
bool StubReturnsTrue(void);
uint8_t StubReturns_uint8_t(uint8_t return_value);

#endif // _RETURNVALUES_H
