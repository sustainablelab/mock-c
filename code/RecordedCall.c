#include "RecordedCall.h"
#include "RecordedArg.h"  // RecordedArg
#include <stdlib.h>     // malloc, free

RecordedCall * RecordedCall_new(char const *name)
{
    RecordedCall *out = (RecordedCall *)malloc(sizeof(RecordedCall));
    out->name = name;
    out->inputs = NULL;
    return out;
}
void RecordedCall_destroy(RecordedCall *self)
{   // Deallocate this recorded call.
    g_list_free_full(           // Deallocate each GList struct and free the
        self->inputs,           // RecordedArg that each data member points to.
        (GDestroyNotify)RecordedArg_destroy
        );
    free(self);                 // Deallocate the RecordedCall struct itself.
}

