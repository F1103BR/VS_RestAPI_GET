#ifndef RESPONSES_H
#define RESPONSES_H

#define MAX_LENGTH 11
#define MAX_NUM_RESPONSES 9

extern const unsigned char responses_ziffer_hex[];
extern char responses_ziffer[MAX_NUM_RESPONSES][MAX_LENGTH];

extern const char *responses_index[];
extern const char *wrongresponses[];

extern const int num_responses_ziffer;
extern const int num_responses_index;
extern const int num_wrong_responses;

void decode_responses_ziffer();

#endif // RESPONSES_H
