#include <criterion/criterion.h>
#include "../strgPtr.h"
//Brandon Moy 
//116187802

//Strglen test Cases
Test(strgLen, typical_string) {
    cr_expect_eq(strgLen("Stony Brooks"), 12);
}

Test(strgLen, empty_string) {
    cr_expect_eq(strgLen(""), 0);
}

Test(strgLen, null_pointer) {
    cr_expect_eq(strgLen(NULL), -1);
}

Test(strgLen, single_space) {
    cr_expect_eq(strgLen(" "), 1);
}

Test(strgLen, digits_only) {
    cr_expect_eq(strgLen("676767"), 6);
}

Test(strgLen, symbols_only) {
    cr_expect_eq(strgLen("!@#$!!!"), 7);
}

Test(strgLen, single_character) {
    cr_expect_eq(strgLen("A"), 1);
}

Test(strgLen, long_string) {
    cr_expect_eq(strgLen("LongLongLongLongLongLong"), 24);
}

Test(strgLen, escape_characters) {
    cr_expect_eq(strgLen("\n\t"), 2);
}

Test(strgLen, internal_null_terminator) {
    cr_expect_eq(strgLen("Ending null\0hidden"), 11);
}



//strCopy test cases
Test(strgCopy, basic_copy) {
    char d[20];
    strgCopy("Hello", d, 20);
    cr_expect_str_eq(d, "Hello");
}

Test(strgCopy, truncation_at_capacity) {
    char d[5];
    strgCopy("Computer Science", d, 5);
    cr_expect_str_eq(d, "Comp");
}

Test(strgCopy, size_one_buffer) {
    char d[1];
    strgCopy("Space", d, 1);
    cr_expect_str_eq(d, ""); 
}

Test(strgCopy, null_source_safety) {
    char d[10] = "Original";
    strgCopy(NULL, d, 10);
    cr_expect_str_eq(d, "Original");
}

Test(strgCopy, null_destination_safety) {
    strgCopy("Hello", NULL, 5);
}

Test(strgCopy, size_zero_check) {
    char d[10] = "Original";
    strgCopy("Hello", d, 0);
    cr_expect_str_eq(d, "Original"); 
}

Test(strgCopy, source_is_empty) {
    char d[10];
    strgCopy("", d, 10);
    cr_expect_str_eq(d, "");
}

Test(strgCopy, exact_fit) {
    char d[4];
    strgCopy("ABG", d, 4);
    cr_expect_str_eq(d, "ABG");
}

Test(strgCopy, large_buffer_small_source) {
    char d[50];
    strgCopy("Small", d, 50);
    cr_expect_str_eq(d, "Small");
}

Test(strgCopy, symbols_copy) {
    char d[10];
    strgCopy("!@#!", d, 10);
    cr_expect_str_eq(d, "!@#!");
}


//strChangeCase test cases
Test(strgChangeCase, typical_mixed_case) {
    char s[] = "stony Brook";
    strgChangeCase(s);
    cr_expect_str_eq(s, "STONY bROOK");
}

Test(strgChangeCase, surrounded_by_digits) {
    char s[] = "6a7";
    strgChangeCase(s);
    cr_expect_str_eq(s, "6a7"); 
}

Test(strgChangeCase, digit_between_letters) {
    char s[] = "a7b";
    strgChangeCase(s);
    cr_expect_str_eq(s, "a7b"); 
}

Test(strgChangeCase, symbol_neighbors) {
    char s[] = "!a!";
    strgChangeCase(s);
    cr_expect_str_eq(s, "!A!"); 
}

Test(strgChangeCase, all_uppercase) {
    char s[] = "ABC";
    strgChangeCase(s);
    cr_expect_str_eq(s, "abc");
}

Test(strgChangeCase, all_lowercase) {
    char s[] = "abc";
    strgChangeCase(s);
    cr_expect_str_eq(s, "ABC");
}

Test(strgChangeCase, digit_on_right_only) {
    char s[] = "A676";
    strgChangeCase(s);
    cr_expect_str_eq(s, "A676"); 
}

Test(strgChangeCase, digit_on_left_only) {
    char s[] = "676z";
    strgChangeCase(s);
    cr_expect_str_eq(s, "676z"); 
}
Test(strgChangeCase, empty_string) {
    char s[] = "";
    strgChangeCase(s);
    cr_expect_str_eq(s, "");
}

Test(strgChangeCase, full_name_flip) {
    char s[] = "brandonmoy";
    strgChangeCase(s);
    cr_expect_str_eq(s, "BRANDONMOY");
}

Test(strgChangeCase, internal_uppercase) {
    char s[] = "katelyN";
    strgChangeCase(s);
    cr_expect_str_eq(s, "KATELYn");
}

Test(strgChangeCase, null_safety) {
    strgChangeCase(NULL); 
}


//strDiff testcaases
Test(strgDiff, identical_strings) {
    cr_expect_eq(strgDiff("Hellooo", "Hellooo"), -1);
}

Test(strgDiff, s1_is_null) {
    cr_expect_eq(strgDiff(NULL, "Test"), -2);
}

Test(strgDiff, s2_is_null) {
    cr_expect_eq(strgDiff("Test", NULL), -2);
}

Test(strgDiff, difference_at_index_1) {
    cr_expect_eq(strgDiff("abc", "acc"), 1);
}

Test(strgDiff, s2_is_longer) {
    cr_expect_eq(strgDiff("abc", "abcd"), 3);
}

Test(strgDiff, s1_is_longer) {
    cr_expect_eq(strgDiff("abcd", "abc"), 3);
}

Test(strgDiff, case_sensitivity) {
    cr_expect_eq(strgDiff("Abg", "abg"), 0);
}

Test(strgDiff, both_empty) {
    cr_expect_eq(strgDiff("", ""), -1);
}

Test(strgDiff, s1_empty_s2_not) {
    cr_expect_eq(strgDiff("", "a"), 0);
}

Test(strgDiff, numeric_difference) {
    cr_expect_eq(strgDiff("123", "126"), 2);
}

Test(strgDiff, identical_numeric_strings) {
    cr_expect_eq(strgDiff("676767", "676767"), -1);
}

Test(strgDiff, difference_at_start) {
    cr_expect_eq(strgDiff("abc", "zbc"), 0);
}


//strInterleave test cases
Test(strgInterleave, same_length) {
    char d[20];
    strgInterleave("abcd", "1234", d, 20);
    cr_expect_str_eq(d, "a1b2c3d4");
}

Test(strgInterleave, s1_longer) {
    char d[20];
    strgInterleave("abcd", "12", d, 20);
    cr_expect_str_eq(d, "a1b2cd");
}

Test(strgInterleave, s2_longer) {
    char d[20];
    strgInterleave("ab", "1234", d, 20);
    cr_expect_str_eq(d, "a1b234");
}

Test(strgInterleave, small_buffer_truncation) {
    char d[6];
    strgInterleave("abcdefghijklm", "12345676767", d, 6);
    cr_expect_str_eq(d, "a1b2c"); 
}

Test(strgInterleave, first_string_empty) {
    char d[20];
    strgInterleave("", "123", d, 20);
    cr_expect_str_eq(d, "123");
}

Test(strgInterleave, both_strings_empty) {
    char d[20];
    strgInterleave("", "", d, 20);
    cr_expect_str_eq(d, "");
}

Test(strgInterleave, size_one_buffer) {
    char d[1];
    strgInterleave("abg", "6767", d, 1);
    cr_expect_str_eq(d, "");
}

Test(strgInterleave, size_zero_nop) {
    char d[10] = "Original";
    strgInterleave("abg", "6767", d, 0);
    cr_expect_str_eq(d, "Original"); 
}

Test(strgInterleave, null_pointer_safety) {
    char d[10] = "Original";
    strgInterleave(NULL, "6767", d, 10);
    cr_expect_str_eq(d, "Original"); 
}

Test(strgInterleave, extreme_truncation) {
    char d[3];
    strgInterleave("abcdef", "67676767676", d, 3);
    cr_expect_str_eq(d, "a6");
}


//strReverseLetters test cases
Test(strgReverseLetters, standard_reverse) {
    char s[] = "abcd";
    strgReverseLetters(s);
    cr_expect_str_eq(s, "dcba");
}

Test(strgReverseLetters, mixed_with_digits) {
    char s[] = "a6b7g";
    strgReverseLetters(s);
    cr_expect_str_eq(s, "g6b7a");
}

Test(strgReverseLetters, digits_only_nop) {
    char s[] = "12345";
    strgReverseLetters(s);
    cr_expect_str_eq(s, "12345");
}

Test(strgReverseLetters, symbols_and_spaces) {
    char s[] = "!a b?";
    strgReverseLetters(s);
    cr_expect_str_eq(s, "!b a?");
}

Test(strgReverseLetters, case_sensitivity_check) {
    char s[] = "AaBb";
    strgReverseLetters(s);
    cr_expect_str_eq(s, "bBaA");
}

Test(strgReverseLetters, palindrome_check) {
    char s[] = "racecar";
    strgReverseLetters(s);
    cr_expect_str_eq(s, "racecar");
}

Test(strgReverseLetters, single_char) {
    char s[] = "A";
    strgReverseLetters(s);
    cr_expect_str_eq(s, "A");
}

Test(strgReverseLetters, empty_string) {
    char s[] = "";
    strgReverseLetters(s);
    cr_expect_str_eq(s, "");
}

Test(strgReverseLetters, spaces_only) {
    char s[] = "   ";
    strgReverseLetters(s);
    cr_expect_str_eq(s, "   ");
}

Test(strgReverseLetters, long_pattern_reverse) {
    char s[] = "gbagbagba";
    strgReverseLetters(s);
    cr_expect_str_eq(s, "abgabgabg");
}

Test(strgReverseLetters, null_safety) {
    strgReverseLetters(NULL); 
}