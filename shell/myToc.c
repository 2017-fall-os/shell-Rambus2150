////reserved for my toc
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>

#include "myToc.h"

#define BUFLEN 2000

//better refined token counter

char **myToc(char *str, char delim) {
    char tmpBuf[BUFLEN];

    int tokenN = 0;
    int tokensCounted = 0;

    char finalChar = delim;

    char *strP;
    char *strEnd;

    char *tmpP;
    char *tmpEnd;

    char **tokens;
    char **tokensP;
    char **tokensEnd;

    // set string pointers;
    for (strEnd = str; *strEnd; strEnd++) {
        ;
    }

    tokenN = numTokens(str, delim);
    // create tokens array
    tokens = (char **)calloc((tokenN + 1), sizeof(char *));
    tokensEnd = tokens + tokenN;
    tokens[tokenN] = 0;

    // insert tokens into array
    for (tokensP = tokens; tokensP < tokensEnd; tokensP ++) {
        for (strP = str; strP != strEnd; strP++) {
            if (*strP == delim && finalChar == delim) {
                // multiple demimeters
                finalChar = *strP;

            } else if (*strP != delim && finalChar != delim) {
                // middle of a token
                *tmpP = *strP;
                tmpP ++;
                finalChar = *strP;

            } else if (*strP != delim && finalChar == delim) {
                // beginning of a token
                tmpP = tmpBuf;  // reset
                *tmpP = *strP;
                tmpP ++;
                finalChar = *strP;

            } else if (*strP == delim && finalChar != delim) {
                // end of a token
                *tmpP = 0;
                *tokensP = myCopy(tmpBuf);
                tokensP ++;
                finalChar = *strP;
            }
        }
        *tmpP = 0;
        *tokensP = myCopy(tmpBuf);
        tokensP ++;
    }
    return tokens;
}
int numTokens(char *str, char delim) {
    char *strP;     // string pointer
    char *strEnd;   // pointer to the end of the string

    char finalChar = delim;  // the last character read

    int token = 0;  // the number of tokens found

    // Find end of string
    for (strEnd = str; *strEnd; strEnd++){
        ;
    }

    for (strP = str; strP != strEnd; strP ++) {
        if (*strP == delim && finalChar == delim) {
            // multiple demimeters
            finalChar = *strP;

        } else if (*strP != delim && finalChar != delim) {
            // middle of a token
            finalChar = *strP;

        } else if (*strP != delim && finalChar == delim) {
            // beginning of a token
            finalChar = *strP;
            token ++;

        } else if (*strP == delim && finalChar != delim) {
            // end of a token
            finalChar = *strP;
        }
    }
    return token;
}


char *myCopy(char *str) {
    char *strP;
    char *strEnd;
    char *copy;
    char *copyP;

    int length;

    for (strEnd = str; *strEnd; strEnd++){
        ;
    }

    length = strEnd - str + 1;
    copy = copyP = (char *)malloc(length);
    for(strP = str; *strP; strP++) {
        *copyP = *strP;
        copyP++;
    }
    copyP = 0;
    return copy;
}
