#include <criterion/criterion.h>
#include "../strgPtr.h"

Test(strgLen, basic) {
    cr_expect_eq(strgLen("Stony Brook"), 11);
    cr_expect_eq(strgLen(""), 0);
    cr_expect_eq(strgLen(NULL), -1);
}

Test(strgCopy, truncation) {
    char d[5];
    strgCopy("Computer Science", d, 5);
    cr_expect_str_eq(d, "Comp");
}

Test(strgChangeCase, adjacency) {
    char s[] = "Stony Brook";
    strgChangeCase(s);
    cr_expect_str_eq(s, "sTONY bROOK");
}

Test(strgInterleave, priority) {
    char d[6];
    strgInterleave("abcdef", "12", d, 6);
    cr_expect_str_eq(d, "a1b2c");
}
