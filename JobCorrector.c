#include <string.h>
#include <limits.h>

static int min3(int a, int b, int c) {
    int m = a;
    if (b < m) m = b;
    if (c < m) m = c;
    return m;
}

int str_diff_rec(int i, int j, char s1[50], char s2[50], int dp[50][50]){
    // Base cases: if one string is empty, return the length of the other
    if (i == 0) return j;
    if (j == 0) return i;

    if (dp[i][j] != -1) return dp[i][j];

    // i and j are lengths, so the last character is at index i-1 and j-1
    if (s1[i - 1] == s2[j - 1]) {
        return dp[i][j] = str_diff_rec(i - 1, j - 1, s1, s2, dp);
    } else {
        int del = str_diff_rec(i - 1, j,     s1, s2, dp);
        int ins = str_diff_rec(i,     j - 1, s1, s2, dp);
        int rep = str_diff_rec(i - 1, j - 1, s1, s2, dp);

        return dp[i][j] = 1 + min3(del, ins, rep);
    }
}

// DP Algorithm: Levenshtein Distance
int str_diff(char s1[50], char s2[50]) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int dp[50][50];

    // Base case
    for(int j=0; j<=len2; j++) dp[0][j] = j;
    for(int i=0; i<=len1; i++) dp[i][0] = i;

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {

            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                int del = dp[i-1][j];
                int ins = dp[i][j-1];
                int rep = dp[i-1][j-1];

                return dp[i][j] = 1 + min3(del, ins, rep);
            }
        }
    }
    return dp[len1][len2];

//     for(int i=0; i<50; i++){
//         for(int j=0; j<50; j++) dp[i][j] = -1;
//     }
//     return str_diff_rec(len1, len2, s1, s2, dp);
}


// Suggest correction (writes to resultOut)
void suggestCorrection(char typoQuery[50], char activeJobs[][50], int totalJobs, char resultOut[50]) {
    int minDistance = INT_MAX;
    int bestIndex = -1;

    for (int i = 0; i < totalJobs; i++) {
        char* candidate = activeJobs[i];
        if (!candidate || candidate[0] == '\0') continue;
        int dist = str_diff(typoQuery, candidate);
        if (dist < minDistance) {
            minDistance = dist;
            bestIndex = i;
        }
    }

    if (bestIndex != -1 && minDistance <= 2) {
        strcpy(resultOut, activeJobs[bestIndex]);
    } else {
        strcpy(resultOut, "No close match found");
    }
}