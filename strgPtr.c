#include "strgPtr.h"
/* DO NOT use <string.h> or <ctype.h> */

int strgLen(const char *s) {
    if (s == NULL){
        return -1;
    }

    int i = 0;
    while (s[i]!='\0'){
        i++;
    }
    return i;
    
}

void strgCopy(const char *source, char *destination, size_t size) {
    if (source == NULL || destination == NULL || size == 0){
        return;
    }

    size_t i = 0;
    while (source[i] != '\0' && i<size-1){
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
    
}

void strgChangeCase(char *s) {
    if (s == NULL){
        return;
    }

    int i = 0;
    while (s[i] != '\0'){
        if ( (s[i]>='A' && s[i] <= 'Z') || (s[i]>='a' && s[i] <= 'z') ){
        
            int isLeftDigit = (i>0 && s[i-1]>='0' && s[i-1]<='9');
            int isRightDigit = (s[i+1]!='\0' && s[i+1] >='0' && s[i+1]<='9');

            if (!isLeftDigit && !isRightDigit){
                if (s[i]>='A' && s[i]<='Z'){
                    s[i] += 32;
                }
                else if (s[i]>='a' && s[i] <='z'){
                    s[i] -= 32;
                }
            }
        }
        i++;
    }
}

int strgDiff(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL){
        return -2;
    }

    size_t i = 0;
    while (s1[i]!='\0' && s2[i]!='\0'){
        if (s1[i] != s2[i]){
            return (int)i;
        }
        i++;
    }
    if (s1[i] == '\0' && s2[i] == '\0'){
        return -1;
    }
    return (int)i;
}

void strgInterleave(const char *s1, const char *s2, char *d, size_t size) {
    if (s1 == NULL || s2 == NULL || d == NULL || size == 0){
        return;
    }

    size_t i = 0;
    size_t numChars = 0;
    while (s1[i] != '\0' && s2[i]!= '\0'){
        if (numChars == size-1){
            d[numChars] = '\0';
            return;
        }
        d[numChars++] = s1[i];
        
        if (numChars == size-1){
            d[numChars] = '\0';
            return;
        }
        d[numChars++] = s2[i];
        i++;
    }

    if (s1[i] == '\0'){
        while (s2[i]!='\0'){
            d[numChars++] = s2[i++];
            if (numChars == size-1){
                d[numChars] = '\0';
                return;
            }
        }
    }

    else if (s2[i] == '\0'){
        while (s1[i]!='\0'){
            d[numChars++] = s1[i++];
            if (numChars == size-1){
                d[numChars] = '\0';
                return;
            }
        }
    }
    d[numChars] = '\0';
}

void strgReverseLetters(char *s) {
    if (s == NULL){
        return;
    }

    int length = strgLen(s);
    if (length <=1){
        return;
    }

    size_t left = 0;
    size_t right = (size_t)length-1;

    while (left<right){
        while (left<right && !((s[left]>='A' && s[left]<='Z') || (s[left]>='a' && s[left]<='z')) ){
            left++; 
        }
        while (left<right && !((s[right]>='A' && s[right]<='Z') || (s[right]>='a' && s[right]<='z')) ){
            right--;
        }

        if (left<right){
            char temp = s[left];
            s[left] = s[right];
            s[right] = temp;
            left++;
            right--;
        }
    }
}
