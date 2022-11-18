#include "SubStringSearch/SubStringSearch.h"
#include <vector>

using namespace std;

int RabinKarpSearch(string text, string target)
{
    size_t textLength   = text.length();
    size_t targetLength = target.length();
    auto h = hash<string>();

    if (textLength < targetLength)
        return -1;

    size_t findHash = h(target);

    for (int i = 0; i <= textLength - targetLength; ++i) {
        if (h(text.substr(i, targetLength)) == findHash)
            return i;
    }

    return -1;
}

int KnuthMorrisPrattSearch(string text, string target)
{
    size_t textLength   = text.length();
    size_t targetLength = target.length();

    if (textLength < targetLength)
        return -1;

    vector<int> prefixes(targetLength);
    prefixes[0] = 0;

    for (int k = 0, i = 1; i < targetLength; ++i)
    {
        while ((k > 0) && (target[i] != target[k]))
            k = prefixes[k - 1];

        if (target[i] == target[k])
            k++;

        prefixes[i] = k;
    }

    for (int k = 0, i = 0; i < textLength; ++i)
    {
        while ((k > 0) && (target[k] != text[i]))
            k = prefixes[k - 1];

        if (target[k] == text[i])
            k++;

        if (k == targetLength)
            return i - targetLength + 1;

    }

    return -1;
}


bool CompareStringsBackward(
        const string& text,
        int from,
        const string& target,
        int *divergencePoint)
{
    const int targetSize = target.length();

    for (int i = 0; i < targetSize; ++i) {
        if (text[from - i] != target[targetSize - i - 1]) {
            *divergencePoint = from - i;
            return false;
        }
    }

    return true;
}

int FindAdvance(const string &target, char pattern) {
    int targetSize = target.length();

    for (int i = 0; i < targetSize; ++i)
        if (target[targetSize - i - 1] == pattern)
            return i;

    return targetSize;
}

int BoyerMooreSearch(string text, string target) {
    int targetLength = target.length();
    int textLength   = text.length();
    int position     = targetLength - 1;

    if (textLength < targetLength)
        return -1;

    while (position >= 0 && position < textLength) {
        if (CompareStringsBackward(text, position, target, &position))
            return position - targetLength + 1;

        int advance = FindAdvance(target, text[position]);
        position += advance;
    }

    return -1;
}