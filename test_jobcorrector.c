#include <stdio.h>
#include "JobCorrector.h"

int main(void) {
    int d = calculateDistance("kitten", "sitting");
    printf("Distance(\"kitten\", \"sitting\") = %d (expected 3)\n", d);

    int d2 = edit_distance("flaw", "lawn");
    printf("edit_distance(\"flaw\", \"lawn\") = %d (expected 2)\n", d2);

    const char* jobs[] = {"schedule", "scheduler", "compile", "scedule"};
    const char* suggestion = suggestCorrection("scedule", jobs, 4);
    printf("suggestCorrection(\"scedule\") => %s\n", suggestion);

    const char* jobs2[] = {"alpha", "beta", "gamma"};
    suggestion = suggestCorrection("zzzzz", jobs2, 3);
    printf("suggestCorrection(\"zzzzz\") => %s (expected No close match found)\n", suggestion);

    return 0;
}
