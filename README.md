----------------------------------------------------------------------------------------------------
CSE 220 - Homework 4
Brandon Moy 
116187802
----------------------------------------------------------------------------------------------------

C Programming assignment focused on string manipulation and pointers. 


I tested both Part 1 and Part 2 using Criterion

Part 1: String Manipulation
strgLen - Tested strgLen with all kinds of inputs including normal strings. Also tested important edge cases like empty string and null pointers
strgCopy - tested strgCopy with normal inputs and cases where the destination was smaller than the source. Handled empty and null
strChangeCase - Tested the digit adjacency rule with digits on the left and right. Included symbols
strDiff - Tested identical strings, prefix strings, and case sensitive cases. Made sure edge cases were tested
strInterleave - Tested the logic with strings of equal length, mismatched cases, and empty cases. Tested when the size paramter was small
strReverseLetters - Verified that digits stayed in place and normal cases reversed

Part 2: Ceasar Cipher
EncrypCeaser - Tested cases wehre the __EOM__ does not fit and confirmed normal inputs to return only values changed
DecryptCeaser - Verified the cases stop when it reaches __EOM__ so tried inner __EOM__ messages and tested the logic with short buffer. Also tested edge cases for Null empty and missing __EOM__ 