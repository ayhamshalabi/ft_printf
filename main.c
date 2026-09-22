#include <stdio.h>
#include <limits.h>

int main(void)
{
    int ret;
    int dummy = 42;

    printf("==================== %%c (CHAR) ====================\n");
    ret = printf("Standard char:       [%c]\n", 'A');
    printf("Return count:        %d\n", ret);

    ret = printf("Null byte char:      [%c]\n", '\0');
    printf("Return count:        %d\n", ret);

    ret = printf("Special whitespace:  [%c] [%c]\n", '\t', '\n');
    printf("Return count:        %d\n\n", ret);

    printf("==================== %%s (STRING) ==================\n");
    ret = printf("Standard string:     [%s]\n", "Hello, World!");
    printf("Return count:        %d\n", ret);

    ret = printf("Empty string:        [%s]\n", "");
    printf("Return count:        %d\n", ret);

    ret = printf("NULL string pointer: [%s]\n", (char *)NULL);
    printf("Return count:        %d\n\n", ret);

    printf("==================== %%d / %%i (SIGNED) =============\n");
    ret = printf("Zero:                [%d] | [%i]\n", 0, 0);
    printf("Return count:        %d\n", ret);

    ret = printf("Standard positive:   [%d] | [%i]\n", 42, 42);
    printf("Return count:        %d\n", ret);

    ret = printf("Standard negative:   [%d] | [%i]\n", -42, -42);
    printf("Return count:        %d\n", ret);

    ret = printf("INT_MAX:             [%d] | [%i]\n", INT_MAX, INT_MAX);
    printf("Return count:        %d\n", ret);

    ret = printf("INT_MIN:             [%d] | [%i]\n", INT_MIN, INT_MIN);
    printf("Return count:        %d\n\n", ret);

    printf("==================== %%u (UNSIGNED) ================\n");
    ret = printf("Zero:                [%u]\n", 0);
    printf("Return count:        %d\n", ret);

    ret = printf("UINT_MAX:            [%u]\n", UINT_MAX);
    printf("Return count:        %d\n", ret);

    ret = printf("Negative cast (-1):  [%u]\n", (unsigned int)-1);
    printf("Return count:        %d\n\n", ret);

    printf("==================== %%x / %%X (HEX) ================\n");
    ret = printf("Zero:                [%x] | [%X]\n", 0, 0);
    printf("Return count:        %d\n", ret);

    ret = printf("Single digit:        [%x] | [%X]\n", 15, 15);
    printf("Return count:        %d\n", ret);

    ret = printf("UINT_MAX:            [%x] | [%X]\n", UINT_MAX, UINT_MAX);
    printf("Return count:        %d\n", ret);

    ret = printf("Arbitrary number:    [%x] | [%X]\n", 305419896, 305419896);
    printf("Return count:        %d\n\n", ret);

    printf("==================== %%p (POINTER) =================\n");
    ret = printf("Stack address:       [%p]\n", (void *)&dummy);
    printf("Return count:        %d\n", ret);

    ret = printf("NULL pointer:        [%p]\n", (void *)NULL);
    printf("Return count:        %d\n", ret);

    ret = printf("Max address (-1):    [%p]\n", (void *)-1);
    printf("Return count:        %d\n\n", ret);

    printf("==================== %%%% (PERCENT) ================\n");
    ret = printf("Single escaped:      [%%]\n");
    printf("Return count:        %d\n", ret);

    ret = printf("Consecutive escapes: [%%%%] [%%%%%%]\n");
    printf("Return count:        %d\n\n", ret);

    printf("==================== MIXED EDGE CASE ===============\n");
    ret = printf("Combined: [%c] [%s] [%d] [%x] [%p] [%%]\n",
                 '\0', "", INT_MIN, 0, NULL);
    printf("Return count:        %d\n", ret);
    
    return 0;
}