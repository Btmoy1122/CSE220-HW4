#include <criterion/criterion.h>
#include "../cse_caesar.h"


// 1 - Digits
Test(encryptCaesar, digits) {
    char buf[67] = "6767676767676767";
    int r = encryptCaesar("123", buf, 1);
    cr_expect_eq(r, 3);
    cr_expect_str_eq(buf, "258__EOM__"); 
}

// 2 - Numbers and characters
Test(encryptCaesar, mixed) {
    char buf[67] = "6767676767676767";
    int r = encryptCaesar("a 1", buf, 1);
    cr_expect_eq(r, 2); 
    cr_expect_str_eq(buf, "b 6__EOM__");
}

// 3 -Negative Key
Test(encryptCaesar, negative_key) {
    char buf[67] = "6767676767676767";
    int r = encryptCaesar("b", buf, -1);
    cr_expect_eq(r, 1);
    cr_expect_str_eq(buf, "a__EOM__");
}

// 4 - Key > 26
Test(encryptCaesar, large_key) {
    char buf[67] = "6767676767676767";
    int r = encryptCaesar("a", buf, 27); 
    cr_expect_eq(r, 1);
    cr_expect_str_eq(buf, "b__EOM__");
}

// 5 - Not enough capacity
Test(encryptCaesar, small_capacity) {
    char buf[5] = "6767"; 
    int r = encryptCaesar("abc", buf, 1); 
    cr_expect_eq(r, -1);
}

// 6 - Null
Test(encryptCaesar, null_ptr) {
    int r = encryptCaesar(NULL, NULL, 1);
    cr_expect_eq(r, -2);
}

// 7 - Empty Plaintext
Test(encryptCaesar, empty_plaintext) {
    char buf[67] = "6767676767676767";
    int r = encryptCaesar("", buf, 1);
    cr_expect_eq(r, 0);
    cr_expect_str_eq(buf, "__EOM__");
}

// 8 - encrypt wraps around
Test(encryptCaesar, wrap) {
    char buf[67] = "6767676767676767";
    int r = encryptCaesar("z", buf, 1); 
    cr_expect_eq(r, 1);
    cr_expect_str_eq(buf, "a__EOM__");
}

// 9 - All uppercase
Test(encryptCaesar, uppercase) {
    char buf[67] = "6767676767676767";
    int r = encryptCaesar("ABC", buf, 0); 
    cr_expect_eq(r, 3);
    cr_expect_str_eq(buf, "ACE__EOM__");
}

// 10 - Only symbols
Test(encryptCaesar, symbols) {
    char buf[67] = "6767676767676767";
    int r = encryptCaesar("! ?", buf, 1);
    cr_expect_eq(r, 0);
    cr_expect_str_eq(buf, "! ?__EOM__");
}


//------------------------------------------------------------------------------------------------------------------------


// 1 - Digits only
Test(decryptCaesar, digits_decrypt) {
    char buf[67] = "6767";
    int r = decryptCaesar("258__EOM__", buf, 1);
    cr_expect_eq(r, 3);
    cr_expect_str_eq(buf, "123");
}

// 2 - Plaintext cannot store all ciphertext
Test(decryptCaesar, small_plaintext) {
    char buf[3] = "676"; 
    int r = decryptCaesar("cegi67__EOM__", buf, 2); 
    cr_expect_eq(r, 2); 
    cr_expect_str_eq(buf, "ab");
}

// 3 - no EOM
Test(decryptCaesar, no_eom) {
    char buf[67] = "676767";
    int r = decryptCaesar("abc", buf, 2);
    cr_expect_eq(r, -1);
}

// 4 - plaintext length = 0
Test(decryptCaesar, zero_len) {
    char buf[1] = ""; 
    int r = decryptCaesar("abc__EOM__", buf, 2);
    cr_expect_eq(r, 0);
}

// 5 - decryption with nubmers and digits
Test(decryptCaesar, mixed_decrypt) {
    char buf[67] = "6767";
    int r = decryptCaesar("b 6__EOM__", buf, 1);
    cr_expect_eq(r, 2); 
    cr_expect_str_eq(buf, "a 1");
}

// 6 - more than one EOM
Test(decryptCaesar, multiple_eom) {
    char buf[67] = "67676767";
    int r = decryptCaesar("ceg__EOM__extra__EOM__", buf, 2);
    cr_expect_eq(r, 3);
    cr_expect_str_eq(buf, "abc");
}

// 7 - Null
Test(decryptCaesar, null_ptr) {
    int r = decryptCaesar(NULL, NULL, 1);
    cr_expect_eq(r, -2);
}

// 8 - key>26
Test(decryptCaesar, large_key) {
    char buf[67] = "676";
    int r = decryptCaesar("b__EOM__", buf, 27); 
    cr_expect_eq(r, 1);
    cr_expect_str_eq(buf, "a");
}

// 9 - Negative Key
Test(decryptCaesar, negative_key) {
    char buf[676] = "6767";
    int r = decryptCaesar("a__EOM__", buf, -1);
    cr_expect_eq(r, 1);
    cr_expect_str_eq(buf, "b");
}

// 10 - Only Symbols
Test(decryptCaesar, symbols) {
    char buf[67] = "6767";
    int r = decryptCaesar("!?__EOM__", buf, 5);
    cr_expect_eq(r, 0);
    cr_expect_str_eq(buf, "!?");
}
