#include <criterion/criterion.h>
#include "../strgPtr.h"

Test(strgLen, basic) {
    cr_expect_eq(strgLen("Stony Brooks"), 12);     // Typical
    cr_expect_eq(strgLen("Volelyball"), 10); 
    cr_expect_eq(strgLen("abg"), 3); 
    cr_expect_eq(strgLen(""), 0);                // Empty
    cr_expect_eq(strgLen(NULL), -1);             // NULL (Critical)
    cr_expect_eq(strgLen(" "), 1);               // Single space
    cr_expect_eq(strgLen("676767"), 6);           // Digits
    cr_expect_eq(strgLen("!@#$!!!"), 7);            // Symbols
    cr_expect_eq(strgLen("A"), 1);               // Single char
    cr_expect_eq(strgLen("LongLongLongLongLongLong"), 24); 
    cr_expect_eq(strgLen("\n\t"), 2);            // Escape characters
    cr_expect_eq(strgLen("Ending null\0hidden"), 11); // Internal null (stops early)
}

Test(strgCopy, truncation) {
    char d[20];
    
    // 1. Basic copy
    strgCopy("Hello", d, 20);
    cr_expect_str_eq(d, "Hello");

    // 2. Truncation (Your case)
    char d2[5];
    strgCopy("Computer Science", d2, 5);
    cr_expect_str_eq(d2, "Comp");

    // 3. Size 1 (Only room for null)
    char d3[1];
    strgCopy("Space", d3, 1);
    cr_expect_str_eq(d3, "");

    // 4. NULL Source/Dest
    strgCopy(NULL, d, 5); // Should not crash
    strgCopy("Hello", NULL, 5); // Should not crash

    // 5. Size 0
    strgCopy("Hello", d, 0); // Should not crash/change d

    // 6. Source is empty
    strgCopy("", d, 10);
    cr_expect_str_eq(d, "");

    // 7. Copy exactly size-1 characters
    char d4[4];
    strgCopy("ABG", d4, 4);
    cr_expect_str_eq(d4, "ABG");

    // 8. Large size, small source
    char d5[50];
    strgCopy("Small", d5, 50);
    cr_expect_str_eq(d5, "Small");

    // 9. Numeric source
    strgCopy("676767", d, 10);
    cr_expect_str_eq(d, "676767");

    // 10. Source with symbols
    strgCopy("!@#!", d, 10);
    cr_expect_str_eq(d, "!@#!");
}

Test(strgChangeCase, adjacency) {
    char s1[] = "stony Brook"; strgChangeCase(s1);
    cr_expect_str_eq(s1, "STONY bROOK"); // Typical

    char s2[] = "6a7"; strgChangeCase(s2);
    cr_expect_str_eq(s2, "6a7"); // Neighboring digits (No change)

    char s3[] = "a7b"; strgChangeCase(s3);
    cr_expect_str_eq(s3, "a7b"); // Neighboring digits (No change)

    char s4[] = "!a!"; strgChangeCase(s4);
    cr_expect_str_eq(s4, "!A!"); // Non-digit neighbors (Change)

    char s5[] = "ABC"; strgChangeCase(s5);
    cr_expect_str_eq(s5, "abc"); // All upper -> lower

    char s6[] = "abc"; strgChangeCase(s6);
    cr_expect_str_eq(s6, "ABC"); // All lower -> upper

    char s7[] = "A676"; strgChangeCase(s7);
    cr_expect_str_eq(s7, "A676"); // Digit on right only

    char s8[] = "676z"; strgChangeCase(s8);
    cr_expect_str_eq(s8, "676z"); // Digit on left only

    char s9[] = ""; strgChangeCase(s9);
    cr_expect_str_eq(s9, ""); // Empty string

    char s10[] = "brandonmoy"; strgChangeCase(s10);
    cr_expect_str_eq(s10, "BRANDONMOY"); 
    char s11[] = "katelyN"; strgChangeCase(s11);
    cr_expect_str_eq(s11, "KATELYn"); 
    strgChangeCase(NULL); // NULL check (Should not crash)
}

Test(strgDiff, basic_equality){
    cr_expect_eq(strgDiff("Hellooo", "Hellooo"), -1);     // Identical
    cr_expect_eq(strgDiff(NULL, "Test"), -2);        // NULL
    cr_expect_eq(strgDiff("Test", NULL), -2);
    cr_expect_eq(strgDiff("abc", "acc"), 1);         // Diff at index 1
    cr_expect_eq(strgDiff("abc", "abcd"), 3);        // One is prefix (diff at \0)
    cr_expect_eq(strgDiff("abcd", "abc"), 3);        // Reverse prefix
    cr_expect_eq(strgDiff("Abg", "abg"), 0);             // Case sensitivity
    cr_expect_eq(strgDiff("", ""), -1);              // Both empty
    cr_expect_eq(strgDiff("", "a"), 0);              // One empty
    cr_expect_eq(strgDiff("123", "126"), 2);         // Digits diff
    cr_expect_eq(strgDiff("676767", "676767"), -1); 
    cr_expect_eq(strgDiff("abc", "zbc"), 0);         // Diff at start
}

Test(strgInterleave, priority) {
    char d[20];

    // 1. Same length
    strgInterleave("abcd", "1234", d, 20);
    cr_expect_str_eq(d, "a1b2c3d4");

    // 2. S1 longer
    strgInterleave("abcd", "12", d, 20);
    cr_expect_str_eq(d, "a1b2cd");

    // 3. S2 longer
    strgInterleave("ab", "1234", d, 20);
    cr_expect_str_eq(d, "a1b234");

    // 4. Truncation (Your case)
    char d2[6];
    strgInterleave("abcdefghijklm", "12345676767", d2, 6);
    cr_expect_str_eq(d2, "a1b2c");

    // 5. One empty string
    strgInterleave("", "123", d, 20);
    cr_expect_str_eq(d, "123");

    // 6. Both empty
    strgInterleave("", "", d, 20);
    cr_expect_str_eq(d, "");

    // 7. size = 1
    char d3[1];
    strgInterleave("abg", "6767", d3, 1);
    cr_expect_str_eq(d3, "");

    // 8. size = 0
    strgInterleave("abg", "6767", d, 0); // No change

    // 9. NULL check
    strgInterleave(NULL, "6767", d, 20); // No change

    // 10. Large truncation
    char d4[3];
    strgInterleave("abcdef", "67676767676", d4, 3);
    cr_expect_str_eq(d4, "a6");
}

Test(strgReverseLetters, all_cases) {
    char s1[] = "abcd"; strgReverseLetters(s1);
    cr_expect_str_eq(s1, "dcba"); // Simple reverse

    char s2[] = "a6b7g"; strgReverseLetters(s2);
    cr_expect_str_eq(s2, "g6b7a"); // Digits stay put

    char s3[] = "12345"; strgReverseLetters(s3);
    cr_expect_str_eq(s3, "12345"); // No letters to reverse

    char s4[] = "!a b?"; strgReverseLetters(s4);
    cr_expect_str_eq(s4, "!b a?"); // Symbols and spaces stay put

    char s5[] = "AaBb"; strgReverseLetters(s5);
    cr_expect_str_eq(s5, "bBaA"); // Case matters

    char s6[] = "racecar"; strgReverseLetters(s6);
    cr_expect_str_eq(s6, "racecar"); // Palindrome

    char s7[] = "A"; strgReverseLetters(s7);
    cr_expect_str_eq(s7, "A"); // Single char

    char s8[] = ""; strgReverseLetters(s8);
    cr_expect_str_eq(s8, ""); // Empty string

    char s9[] = "   "; strgReverseLetters(s9);
    cr_expect_str_eq(s9, "   "); // Only spaces

    char s10[] = "gbagbagba"; strgReverseLetters(s10);
    cr_expect_str_eq(s10, "abgabgabg"); // Simple reverse

    strgReverseLetters(NULL); // NULL check
}
