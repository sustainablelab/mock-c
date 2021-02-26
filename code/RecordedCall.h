#ifndef _RECORDEDCALL_H
#define _RECORDEDCALL_H

#include <glib.h>         // GString, GList

//=====[ mock-c RecordedCall datatype ]=====
typedef struct RecordedCall RecordedCall;
struct RecordedCall {
    char const * name;
    GList *inputs;    // The GList must be initialized to NULL.
};
RecordedCall * RecordedCall_new(char const *name);
void RecordedCall_destroy(RecordedCall *self);

#endif // _RECORDEDCALL_H
