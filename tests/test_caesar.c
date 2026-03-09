#include <criterion/criterion.h>
#include "../cse_caesar.h"

Test(encryptCaesar, basic) {
    char buf[32] = "xxxxxxxxxxxxxxxxxxxxxxxx";
    int r = encryptCaesar("abc", buf, 2);
    cr_expect_eq(r, 3);
    cr_expect_str_eq(buf, "ceg__EOM__");
}

Test(decryptCaesar, basic) {
    char buf[32] = "xxxxxxxx";
    int r = decryptCaesar("ceg__EOM__", buf, 2);
    cr_expect_eq(r, 3);
    cr_expect_str_eq(buf, "abc");
}
