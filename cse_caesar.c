#include "cse_caesar.h"
#include "strgPtr.h"
/* DO NOT use <string.h> or <ctype.h> */
//Brandon Moy 
//116187802

//Encrypts plaintext into cipher text
int encryptCaesar(const char *plaintext, char *ciphertext, int key) {
    //Check for Null
    if (plaintext == NULL || ciphertext == NULL){
        return -2;
    }

    //Check we have enough capacity
    int capacity = strgLen(ciphertext);
    int capacityNeeded = strgLen(plaintext) + 7;
    if (capacity < capacityNeeded){
        return -1;
    }

    
    //encrypt logic
    int i = 0;
    int count = 0;
    while (plaintext[i] != '\0'){
        if (plaintext[i]>='A' && plaintext[i]<='Z'){
            int charNum = plaintext[i] - 'A';
            //Included the + 26) %26 logic to account for negative key inputs
            charNum = ((charNum + (key + i)) % 26 +26) % 26;
            ciphertext[i] = 'A' + charNum;
            count++;
        }
        else if (plaintext[i] >= 'a' && plaintext[i] <= 'z'){
            int charNum = plaintext[i] - 'a';
            charNum = ((charNum + (key + i)) % 26 +26) % 26;
            ciphertext[i] = 'a' + charNum;
            count++;
        }
        else if (plaintext[i] >= '0' && plaintext[i] <= '9'){
            int charNum = plaintext[i] - '0';
            charNum = ((charNum + (key + 2*i)) % 10 +10) % 10;
            ciphertext[i] = '0' + charNum;
            count++;
        }
        else{
            ciphertext[i] = plaintext[i];
        }
        i++;
    }

    //add EOM
    strgCopy("__EOM__", &ciphertext[i], 8);

    return count;


}

//Decrypts ciphertext into plaintext
int decryptCaesar(const char *ciphertext, char *plaintext, int key) {
    //Check for null
    if (ciphertext == NULL || plaintext == NULL){
        return -2;
    }
    //Check if plaintext has len 0
    int length = strgLen(plaintext);
    if (length == 0){
        return 0;
    }

    //Check our cipher text has __EOM__
    int i = 0;
    int eom_index = -1;
    while (ciphertext[i] != '\0'){
        if (ciphertext[i] == '_' &&
            ciphertext[i+1] == '_' &&
            ciphertext[i+2] == 'E' &&
            ciphertext[i+3] == 'O' &&
            ciphertext[i+4] == 'M' &&
            ciphertext[i+5] == '_' &&
            ciphertext[i+6] == '_'){
            eom_index = i;
            break;
        }

        i++;
    }
    if (eom_index == -1){
        return -1;
    }

    //Decrypt logic
    i = 0;
    int count = 0;
    while (i < eom_index && i < length-1){
        if (ciphertext[i]>='A' && ciphertext[i]<='Z'){
            int charNum = ciphertext[i] - 'A';
            //Included the + 26) %26 logic to account for negative key inputs
            charNum = ((charNum - (key + i)) % 26 +26) % 26;
            plaintext[i] = 'A' + charNum;
            count++;
        }
        else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z'){
            int charNum = ciphertext[i] - 'a';
            charNum = ((charNum - (key + i)) % 26 +26) % 26;
            plaintext[i] = 'a' + charNum;
            count++;
        }
        else if (ciphertext[i] >= '0' && ciphertext[i] <= '9'){
            int charNum = ciphertext[i] - '0';
            charNum = ((charNum - (key + 2*i)) % 10 +10) % 10;
            plaintext[i] = '0' + charNum;
            count++;
        }
        else{
            plaintext[i] = ciphertext[i];
        }
        i++;
    }

    plaintext[i] = '\0';
    return count;

}


