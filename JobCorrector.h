#ifndef JOBCORRECTOR_H
#define JOBCORRECTOR_H

#include <stddef.h>

// Returns the edit (Levenshtein) distance between two C strings
int edit_distance(const char* s1, const char* s2);

// C-friendly wrappers (pure C API)
int calculateDistance(const char* s1, const char* s2);

// Returns pointer to the best matching job string from activeJobs or
// the literal "No close match found" when nothing within distance 2.
const char* suggestCorrection(const char* typoQuery, const char* activeJobs[], int totalJobs);

#endif // JOBCORRECTOR_H