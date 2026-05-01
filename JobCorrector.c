#include "JobCorrector.h"
#include <string.h>
#include <limits.h>

static int min3(int a, int b, int c) {
    int m = a;
    if (b < m) m = b;
    if (c < m) m = c;
    return m;
}

// Classic DP Algorithm: Levenshtein (Edit) Distance
int edit_distance(const char* s1, const char* s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int dp[50][50];
    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min3(
                    dp[i][j - 1],    // Insert
                    dp[i - 1][j],    // Remove
                    dp[i - 1][j - 1] // Replace
                );
            }
        }
    }
    return dp[len1][len2];
}

// Simple wrapper delegating to the C edit_distance implementation
int calculateDistance(const char* s1, const char* s2) {
    return edit_distance(s1, s2);
}

// Suggest correction (returns pointer to existing job string or a literal)
const char* suggestCorrection(const char* typoQuery, const char* activeJobs[], int totalJobs) {
    int minDistance = INT_MAX;
    const char* bestMatch = NULL;

    for (int i = 0; i < totalJobs; i++) {
        const char* candidate = activeJobs[i];
        if (!candidate) continue;
        int dist = edit_distance(typoQuery, candidate);
        if (dist < minDistance) {
            minDistance = dist;
            bestMatch = candidate;
        }
    }

    if (bestMatch != NULL && minDistance <= 2) {
        return bestMatch;
    }
    return "No close match found";
}
