#include "Mock.h"
#include <stdlib.h>     // malloc, free
#include <stdio.h>      // printf

struct Mock_s {
    GString *fail_msg;
    GList *expected_calls;    // The GList must be initialized to NULL.
    GList *actual_calls;    // The GList must be initialized to NULL.
};
Mock_s * Mock_new(void)
{   // Initialize all pointer members!
    Mock_s *out = (Mock_s *)malloc(sizeof(Mock_s));
    out->fail_msg = g_string_new(
        "No failures recorded. This message should never print."
        );
    out->expected_calls = NULL;
    out->actual_calls   = NULL;
    return out;
}
void Mock_destroy(Mock_s *self)
{   // Deallocate this mock struct.
    g_list_free_full(           // Deallocate each GList struct and free the
        self->expected_calls,   // RecordedCall that each data member points to.
        (GDestroyNotify)RecordedCall_destroy);
    g_list_free_full(
        self->actual_calls,
        (GDestroyNotify)RecordedCall_destroy);
    g_string_free(              // Deallocate the GString struct 
        self->fail_msg, true);  // and the message string it points to.
    free(self);  // Tabled: I cannot tell if this is deallocating the Mock_s.
}
void RecordExpectedCall(Mock_s *self, RecordedCall *func_call)
{   // Record a function call in the list of expected calls.
    self->expected_calls = g_list_append(
        self->expected_calls,
        (RecordedCall *)func_call
        );
}
void RecordActualCall(Mock_s *self, RecordedCall *func_call)
{   // Record a function call in the list of actual calls.
    self->actual_calls = g_list_append(
        self->actual_calls,
        (RecordedCall *)func_call
        );
}
void RecordArg(RecordedCall *self, RecordedArg *input_arg)
{
    self->inputs = g_list_append(
        self->inputs,
        (RecordedArg *)input_arg
        );
}

/* =====[ New functionality I added 2018 August ]===== */
char const * ListAllCalls(Mock_s *self)
{
    // Alternate to `WhyDidItFail`.
    /* GList *expected_calls   = self->expected_calls; */
    /* GList *actual_calls     = self->actual_calls; */
    /* uint8_t num_expected_calls = g_list_length(expected_calls); */
    /* uint8_t num_actual_calls   = g_list_length(actual_calls); */
    GList *expected_calls   = self->expected_calls;
    GList *actual_calls     = self->actual_calls;
    g_string_append_printf( self->fail_msg,
        "**Calls expected**:"
        );
    while (expected_calls != NULL) {
        RecordedCall *this_call = (RecordedCall *)expected_calls->data;
        g_string_append_printf( self->fail_msg, " `%s()`", this_call->name);
        expected_calls  = expected_calls->next;
    }
    g_string_append_printf( self->fail_msg,
        "**Calls made**:"
        );
    while (actual_calls != NULL) {
        RecordedCall *this_call = (RecordedCall *)actual_calls->data;
        g_string_append_printf( self->fail_msg, " `%s()`", this_call->name);
        actual_calls  = actual_calls->next;
    }
    return self->fail_msg->str;
}
/* =====[ New functionality I added 2019 October ]===== */
/* bool AssertCall( */
/*     Mock_s *self, */
/*     uint8_t n, */
/*     char * name */
/*     ) */
bool SilentAssertCall(
    Mock_s *self,
    uint16_t n,
    char const * name
    )
{
    bool call_n_matches_name = false;
    // Walk the list of calls to get to the nth call.
    uint16_t this_call_num = 0;
    GList *actual_calls = self->actual_calls;
    while( (actual_calls != NULL) && (++this_call_num < n)){
        actual_calls  = actual_calls->next;
    }
    if (actual_calls != NULL)
    {
        RecordedCall *nth_call = (RecordedCall *)actual_calls->data;
        if (0 == g_strcmp0(name, nth_call->name))
        {
            call_n_matches_name = true;
        }
    }
    return call_n_matches_name;
}
bool AssertCall(
    Mock_s *self,
    uint16_t n,
    char const * name
    )
{
    /* printf("\nChecking if call %d is named %s.\n",n,name); */
    printf("Call %d is named %s? ",n,name);
    /* Return true if call `n` is named `name`. */
    /* Return false otherwise. */
    bool call_n_matches_name = false;
    /* First call is n=1. */
    /* uint8_t this_call_num = 0; // iterate call number starting with call 1 */
    uint16_t this_call_num = 0; // iterate call number starting with call 1
    /* Work with the list of *actual* calls in the `mock` struct. */
    GList *actual_calls = self->actual_calls;
    while( (actual_calls != NULL) && (++this_call_num < n)){
        actual_calls  = actual_calls->next;
    }
    if (actual_calls == NULL)
    {
        printf("Error: less than %d calls.\n", n);
    }
    else
    {
        printf("... ");
        RecordedCall *nth_call = (RecordedCall *)actual_calls->data;
        /* printf("- Call %d is %s.\n", this_call_num, nth_call->name); */
        // I found an instance where the simple `==` does not work.
        // I'm not sure what's different about this instance.
        /* printf("- Result of `==`?: %d\n", (nth_call->name == name)); */
        /* if (nth_call->name == name) call_n_matches_name = true; */
        // So use `g_strcmp0` instead. That works for this corner case.
        /* printf("- If they match, g_strcmp0 returns 0: %d\n", g_strcmp0(name, nth_call->name)); */
        if (0 == g_strcmp0(name, nth_call->name))
        {
            call_n_matches_name = true;
            printf("Yes, call %d is %s.\n", this_call_num, nth_call->name);
        }
        else
        {
            printf("No, call %d is %s.\n", this_call_num, nth_call->name);
        }
    }
        return call_n_matches_name;
}
bool AssertArg(
    Mock_s *self,
    uint16_t call_n,
    uint8_t arg_k,
    void *p_assert_val
    )
{
    // Return true if nth call, kth arg matches value pointed to by `p_assert_val`.
    // Return false otherwise.
    // ~Client passes definition of `match_arg`.~
    // CheckArg is a built-in method for a RecordedArg struct.
    // This determines the data type pointed to by input `p_assert_val`.
    /* printf("\nChecking value of arg %d in call %d.\n",arg_k,call_n); */
    printf("Value passed to call %d, arg %d? ",call_n,arg_k);
    bool arg_k_matches_value = false;
    /* First call is n=1. */
    uint8_t this_call_num = 0; // iterate call number starting with call 1
    /* Work with the list of *actual* calls in the `mock` struct. */
    GList *actual_calls = self->actual_calls;
    while( (actual_calls != NULL) && (++this_call_num < call_n)){
        actual_calls  = actual_calls->next;
    }
    if (actual_calls == NULL)
    {
        printf("Error: less than %d calls.\n", call_n);
    }
    else
    {
        RecordedCall *nth_call = (RecordedCall *)actual_calls->data;
        GList *inputs = nth_call->inputs;
        // Walk the inputs to get to the kth arg.
        /* First arg is k=1. */
        uint8_t this_arg_num = 0; // iterate arg number starting with arg 1
        while( (inputs != NULL) && (++this_arg_num < arg_k)){
            inputs  = inputs->next;
        }
        if (inputs == NULL)
        {
            printf("Error: call %d has less than %d args.\n", this_call_num, arg_k);
        }
        else
        {
            RecordedArg *kth_arg = (RecordedArg *)inputs->data;
            // TODO: how do I print the expected arg type and arg value?
            // Return true/false if expected and actual args have:
            // - matching types
            // - matching values
            arg_k_matches_value = kth_arg->CheckArg(kth_arg, p_assert_val);
            // print message: call number, arg number, arg value
            GString *printed_arg = g_string_new(" ");
            kth_arg->Print(printed_arg, kth_arg); // print value to GString
            /* printf("Call %d, ", this_call_num); */
            /* printf("arg %d, ", this_arg_num); */
            /* printf("has value %s.\n", printed_arg->str); */
            printf("%s.\n", printed_arg->str);
        }
    }
    return arg_k_matches_value;
}
// TODO: eliminate this
// AssertArgPointsToValue is bullshit.
// It stores the pointer but does not store the values pointed to.
// The values pointed to are only in memory while the FUT is on the stack frame.
// After the FUT returns, the values pointed to are unprotected.
// Sometimes they are untouched and dereferencing the pointer works.
// Sometimes not, and dereferencing the pointer returns unexpected values,
// thought it never results in a seg fault.
// AssertArgPointsToValue is only valid to use in the case where the arg points
// to a global. It is invalid to use if the arg points to a variable local to
// the FUT.
bool AssertArgPointsToValue(
    Mock_s *self,
    uint8_t call_n,
    uint8_t arg_k,
    void *pp_assert_val
    )
{
    // Return true if nth call, kth arg points to a value equal to the value
    // pointed to by `p_assert_val`. Return false otherwise.
    // Note `pp_assert_val` is a pointer *to a pointer* to a value. It gets
    // dereferenced *twice*. Example: check if kth arg points to value 0x01:
    // uint8_t argv=0x01; uint8_t *pargv=&argv;
    // Then pass `&pargv` as the argument for pp_assert_val.
    // ---- START SECTION: IDENTICAL TO AssertArg()
    // CheckArg is a built-in method for a RecordedArg struct.
    // This determines the data type pointed to by input `pp_assert_val`.
    /* printf("\nChecking value of arg %d in call %d.\n",arg_k,call_n); */
    printf("Value at address passed to call %d, arg %d? ",call_n,arg_k);
    bool arg_k_matches_value = false;
    /* First call is n=1. */
    uint8_t this_call_num = 0; // iterate call number starting with call 1
    /* Work with the list of *actual* calls in the `mock` struct. */
    GList *actual_calls = self->actual_calls;
    while( (actual_calls != NULL) && (++this_call_num < call_n)){
        actual_calls  = actual_calls->next;
    }
    if (actual_calls == NULL)
    {
        printf("Error: less than %d calls.\n", call_n);
    }
    else
    {
        RecordedCall *nth_call = (RecordedCall *)actual_calls->data;
        GList *inputs = nth_call->inputs;
        // Walk the inputs to get to the kth arg.
        /* First arg is k=1. */
        uint8_t this_arg_num = 0; // iterate arg number starting with arg 1
        while( (inputs != NULL) && (++this_arg_num < arg_k)){
            inputs  = inputs->next;
        }
        if (inputs == NULL)
        {
            printf("Error: call %d has less than %d args.\n", this_call_num, arg_k);
        }
        else
        {
            RecordedArg *kth_arg = (RecordedArg *)inputs->data;
            // TODO: how do I print the expected arg type and arg value?
            // Return true/false if expected and actual args have:
            // - matching types
            // - matching values
            // ---- END SECTION: IDENTICAL TO AssertArg()
            // The change from AssertArg:
                // Replace CheckArg with CheckValArgPointsTo
                // This dereferences the kth_arg and does an additional dereference to the pp_assert_val so that the values are compared, not the pointers.
            arg_k_matches_value = kth_arg->CheckValArgPointsTo(kth_arg, pp_assert_val);
            // ---- THE REST IS IDENTICAL TO AssertArg()
            // print message: call number, arg number, arg value
            GString *printed_arg = g_string_new(" ");
            kth_arg->Print(printed_arg, kth_arg); // print value to GString
            /* printf("Call %d, ", this_call_num); */
            /* printf("arg %d, ", this_arg_num); */
            /* printf("has value %s.\n", printed_arg->str); */
            printf("%s.\n", printed_arg->str);
        }
    }
    return arg_k_matches_value;
}
uint16_t NumberOfActualCalls(Mock_s *self)
{
    // Return the number of actual calls recorded in the `Mock_s`.
    GList *actual_calls = self->actual_calls;
    uint16_t num_actual_calls = g_list_length(actual_calls);
    return num_actual_calls;
}
//=====[ Examples using Mock to implement mock-c functionalty ]=====
static void PrintAllInputs(GList *inputs)
{
    GString *printed_arg = g_string_new(
        "Error: `RecordedArg->Print` should have overwritten this message."
        );
    while (inputs != NULL)
    {
        RecordedArg *this_arg = (RecordedArg *)inputs->data;
        (this_arg->Print(printed_arg, this_arg));   // print to the GString
        printf(", %s", printed_arg->str);           // print to stdout
        //printf(", %s", ((AnyType_s *)inputs->data)->printed->str);
        inputs = inputs->next;
    }
    printf("\n");
    g_string_free(printed_arg, true);
}
void PrintAllCalls(Mock_s *self)  // Example
{
    GList *expected_calls   = self->expected_calls;
    GList *actual_calls     = self->actual_calls;
    uint8_t num_expected_calls = g_list_length(expected_calls);
    uint8_t num_actual_calls   = g_list_length(actual_calls);
    //while (expected_calls != NULL && actual_calls != NULL)
    printf("\n- Expected %d calls:\n", num_expected_calls);
    while (expected_calls != NULL) {
        RecordedCall *this_call = (RecordedCall *)expected_calls->data;
        printf("    - \"%s\"", this_call->name);
        PrintAllInputs(this_call->inputs);
        expected_calls  = expected_calls->next;
    }
    printf("- Received %d calls:\n", num_actual_calls);
    while (actual_calls != NULL) {
        RecordedCall *this_call = (RecordedCall *)actual_calls->data;
        printf( "    - \"%s\"", this_call->name);
        PrintAllInputs(this_call->inputs);
        actual_calls  = actual_calls->next;
    }
}

//=====[ Extending old mock-c ]=====
static bool Each_call_has_the_correct_number_of_inputs(Mock_s *self);
static void print_first_call_with_wrong_number_of_inputs(Mock_s *self);
static uint8_t NumberOfArgs(RecordedCall *self);
//=====[ Copied from old mock-c ]=====
static bool Call_lists_are_the_same_length(Mock_s *self);
static bool EachCallMatches(Mock_s *self);
static void print_number_of_expected_and_actual_calls(Mock_s *self);
static void print_first_unexpected_call(Mock_s *self);
static void print_first_missed_call(Mock_s *self);
static void print_all_wrong_calls(Mock_s *self);

bool RanAsHoped(Mock_s *self)
{
    // Initialize message
    /* g_string_printf( self->fail_msg, "Why it failed: "); */
    g_string_printf( self->fail_msg, " ");
    
    if (!Call_lists_are_the_same_length(self))
    {
        print_number_of_expected_and_actual_calls(self);
        print_first_unexpected_call(self);
        print_first_missed_call(self);
    }
    if (!Each_call_has_the_correct_number_of_inputs(self))
        print_first_call_with_wrong_number_of_inputs(self);
    if (!EachCallMatches(self))
        print_all_wrong_calls(self);
    return (
        Call_lists_are_the_same_length(self) &&
        Each_call_has_the_correct_number_of_inputs(self) &&
        EachCallMatches(self)
        );
}
char const * WhyDidItFail(Mock_s *self)
{
    return self->fail_msg->str;
}

static bool Call_lists_are_the_same_length(Mock_s *self)
{
    return (
        g_list_length(self->expected_calls)
        ==
        g_list_length(self->actual_calls)
        );
}
static bool Each_call_has_the_correct_number_of_inputs(Mock_s *self)
{
    GList *expected_calls   = self->expected_calls;
    GList *actual_calls     = self->actual_calls;
    while (expected_calls != NULL && actual_calls != NULL)
    {
        RecordedCall *this_expected_call = (RecordedCall *)expected_calls->data;
        RecordedCall *this_actual_call   = (RecordedCall *)actual_calls->data;
        if (NumberOfArgs(this_expected_call) != NumberOfArgs(this_actual_call))
            return false;

        expected_calls  = expected_calls->next;
        actual_calls    = actual_calls->next;
    }
    return true;
}
static bool CallNamesMatch(char const *expected_name, char const *actual_name)
{
    int names_do_not_match = g_strcmp0(expected_name, actual_name);
    return names_do_not_match ? false : true;
}

static bool RecordedArgsMatch(RecordedArg *expected_arg, RecordedArg *actual_arg)
{
    //if (match functions are not the same then the types do not even match)
    if (expected_arg->Match != actual_arg->Match) return false;
    //use the match function to return true if they match
    return expected_arg->Match(expected_arg, actual_arg);
}
static bool CallInputsMatch(GList *expected_inputs, GList *actual_inputs)
{
    while (expected_inputs != NULL && actual_inputs != NULL)
    {
        RecordedArg *this_expected_arg = (RecordedArg *)expected_inputs->data;
        RecordedArg *this_actual_arg   = (RecordedArg *)actual_inputs->data;
        if (!RecordedArgsMatch(
            this_expected_arg,
            this_actual_arg)) return false;

        expected_inputs = expected_inputs->next;
        actual_inputs   = actual_inputs->next;
    }
    return true;

}
static bool EachCallMatches(Mock_s *self)
{
    GList *expected_calls   = self->expected_calls;
    GList *actual_calls     = self->actual_calls;
    while (expected_calls != NULL && actual_calls != NULL)
    {
        RecordedCall *this_expected_call = (RecordedCall *)expected_calls->data;
        RecordedCall *this_actual_call   = (RecordedCall *)actual_calls->data;
        if (!CallNamesMatch(
            this_expected_call->name,
            this_actual_call->name)) return false;
        if (!CallInputsMatch(
            this_expected_call->inputs,
            this_actual_call->inputs)) return false;

        expected_calls  = expected_calls->next;
        actual_calls    = actual_calls->next;
    }
    return true;
}
static void print_number_of_expected_and_actual_calls(Mock_s *self)
{
    GList *expected_calls   = self->expected_calls;
    GList *actual_calls     = self->actual_calls;
    uint8_t num_expected_calls = g_list_length(expected_calls);
    uint8_t num_actual_calls   = g_list_length(actual_calls);
    g_string_append_printf( self->fail_msg,
        "Expected %d calls, received %d calls. ",
        num_expected_calls, num_actual_calls
        );
}
static uint8_t NumberOfArgs(RecordedCall *self) {
    return g_list_length(self->inputs);
}
static void print_first_call_with_wrong_number_of_inputs(Mock_s *self)
{
    GList *expected_calls   = self->expected_calls;
    GList *actual_calls     = self->actual_calls;
    int call_number = 1;
    while (expected_calls != NULL && actual_calls != NULL)
    {
        RecordedCall *this_expected_call = (RecordedCall *)expected_calls->data;
        RecordedCall *this_actual_call   = (RecordedCall *)actual_calls->data;
        if (NumberOfArgs(this_expected_call) != NumberOfArgs(this_actual_call))
            g_string_append_printf( self->fail_msg,
                "Wrong number of args in call #%d '%s', expected %d, was %d. ",
                call_number,
                this_expected_call->name,
                NumberOfArgs(this_expected_call),
                NumberOfArgs(this_actual_call)
                );
        call_number++;
        expected_calls  = expected_calls->next;
        actual_calls    = actual_calls->next;
    }
}
static void print_first_unexpected_call(Mock_s *self)
{   // Calls made by the function under test, not expected by the test.
    GList *expected_calls   = self->expected_calls;
    GList *actual_calls     = self->actual_calls;
    uint8_t num_expected_calls = g_list_length(expected_calls);
    uint8_t num_actual_calls   = g_list_length(actual_calls);
    if (num_expected_calls < num_actual_calls)
        g_string_append_printf( self->fail_msg,
            "First unexpected call: received #%d:'%s'. ",
            num_expected_calls + 1,
            ((RecordedCall *)g_list_nth_data(
                actual_calls, num_expected_calls)
                )->name
            );
}
static void print_first_missed_call(Mock_s *self)
{   // Calls expected by the test, not made by the function under test.
    GList *expected_calls   = self->expected_calls;
    GList *actual_calls     = self->actual_calls;
    uint8_t num_expected_calls = g_list_length(expected_calls);
    uint8_t num_actual_calls   = g_list_length(actual_calls);
    if (num_expected_calls > num_actual_calls)
        g_string_append_printf( self->fail_msg,
            "First missed call: expected #%d:'%s'. ",
            num_actual_calls + 1,
            ((RecordedCall *)g_list_nth_data(
                expected_calls, num_actual_calls)
            )->name
            //(gchar *)g_list_nth_data(
            //    expected_calls,
            //    num_actual_calls
            //    )
            );
}
static void PrintExpectedAndActualNames( GString *fail_msg,
    uint8_t call_number, char const *expected_name, char const *actual_name)
{
    g_string_append_printf( fail_msg,
        "Call #%d: expected '%s', was '%s'. ",
        call_number, expected_name, actual_name);
}
static void PrintExpectedAndActualInputs(GString *fail_msg,
    uint8_t call_number, char const *expected_name, GList *expected_inputs, GList *actual_inputs)
{   // loop through the inputs and print the non-matching
    GString *printed_expected_arg = g_string_new(
    "Error: `RecordedArg->Print` should have overwritten this message."
    );
    GString *printed_actual_arg = g_string_new(
    "Error: `RecordedArg->Print` should have overwritten this message."
    );
    while (expected_inputs != NULL && actual_inputs != NULL)
    {
        RecordedArg *this_expected_arg = (RecordedArg *)expected_inputs->data;
        RecordedArg *this_actual_arg   = (RecordedArg *)actual_inputs->data;
        if (!RecordedArgsMatch(
            this_expected_arg,
            this_actual_arg))
        {//print them;
            this_expected_arg->Print(   // print to the GString
                printed_expected_arg, this_expected_arg);
            this_actual_arg->Print(   // print to the GString
                printed_actual_arg, this_actual_arg);
            g_string_append_printf(fail_msg,
                "Call #%d: '%s' expected input '%s', but was '%s'. ",
                call_number, expected_name,
                printed_expected_arg->str,
                printed_actual_arg->str);
        }
        expected_inputs = expected_inputs->next;
        actual_inputs   = actual_inputs->next;
    }
    g_string_free(printed_expected_arg, true);
    g_string_free(printed_actual_arg, true);
}
static void print_all_wrong_calls(Mock_s *self)
{
    uint8_t call_number = 1;
    GList *expected_calls   = self->expected_calls;
    GList *actual_calls     = self->actual_calls;
    while (expected_calls!=NULL && actual_calls!=NULL)
    {
        RecordedCall *this_expected_call = (RecordedCall *)expected_calls->data;
        RecordedCall *this_actual_call   = (RecordedCall *)actual_calls->data;
        if (!CallNamesMatch(
            this_expected_call->name,
            this_actual_call->name)
            ) PrintExpectedAndActualNames(
                self->fail_msg,
                call_number,
                this_expected_call->name,
                this_actual_call->name);
        if (!CallInputsMatch(
            this_expected_call->inputs,
            this_actual_call->inputs)
            ) PrintExpectedAndActualInputs(
                self->fail_msg,
                call_number, this_expected_call->name,
                this_expected_call->inputs,
                this_actual_call->inputs);

        expected_calls = expected_calls->next;
        actual_calls = actual_calls->next;
        call_number++;
    }
}
