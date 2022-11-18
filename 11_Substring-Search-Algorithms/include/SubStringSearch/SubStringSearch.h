#ifndef SUBSTRINGSEARCH_SUBSTRINGSEARCH_H
#define SUBSTRINGSEARCH_SUBSTRINGSEARCH_H

#include <string>

using namespace std;

int RabinKarpSearch(string text, string target);
int KnuthMorrisPrattSearch(string text, string target);
int BoyerMooreSearch(string text, string target);

#endif //SUBSTRINGSEARCH_SUBSTRINGSEARCH_H
