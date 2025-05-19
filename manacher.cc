#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

/**
 * @brief Implements Manacher's algorithm to find all longest palindromic substrings in a given string.
 *        Manacher's algorithm uses a processed string, where special characters '#' are inserted between characters of the original string and at the beginning and end, to handle both even and odd length palindromes uniformly.
 *        A palindromic substring is a substring that reads the same forwards and backward.
 *
 * @param s The input string to find palindromic substrings in.
 * @return A vector of strings, containing all longest palindromic substrings of the input string.
 *         If no palindromic substring exists (e.g., for an empty string), an empty vector is returned.
 *
 * @note Time Complexity: O(N), where N is the length of the input string `s`.
 * @note Space Complexity: O(N), where N is the length of the input string `s`, due to the auxiliary array used for Manacher's algorithm.
 */
vector<string> manacher(string s) {
    string processed_s = "#";
    for (char c : s) {
        processed_s += c;
        processed_s += "#";
    }

    int n = processed_s.length();
    // p[i] stores the radius of the longest palindrome centered at index i in processed_s.
    vector<int> p(n, 0);
    // C is the center of the rightmost palindrome found so far.
    // R is the right boundary of the rightmost palindrome found so far.
    int C = 0, R = 0;
    for (int i = 1; i < n - 1; ++i) {
        int i_mirror = 2 * C - i;
        if (R > i) {
            p[i] = min(R - i, p[i_mirror]);
        }

        // Attempt to expand palindrome centered at i
        while (i - (1 + p[i]) >= 0 && i + (1 + p[i]) < n && processed_s[i - (1 + p[i])] == processed_s[i + (1 + p[i])]) {
            p[i]++;
        }

        // If palindrome centered at i expands past R, adjust center C and right boundary R
        if (i + p[i] > R) {
            C = i;
            R = i + p[i];
        }
    }
    
    int maxLen = 0;
    for (int i = 1; i < n - 1; ++i) {
        if (p[i] > maxLen) {
            maxLen = p[i];
        }
    }
    vector<string> longestPalindromes;
    for (int i = 1; i < n - 1; ++i) {
        if (p[i] == maxLen) {
            int start_index = (i - maxLen) / 2;
            longestPalindromes.push_back(s.substr(start_index, maxLen));
        }
    }
    return longestPalindromes;
}

void test_manacher() {
    // Test case 1: Empty string
    vector<string> result1 = manacher("");
    vector<string> expected1 = {};
    assert(result1 == expected1);

    // Test case 2: Single character string
    vector<string> result2 = manacher("a");
    vector<string> expected2 = {"a"};
    assert(result2 == expected2);

    // Test case 3: Odd length palindrome
    vector<string> result3 = manacher("aba");
    vector<string> expected3 = {"aba"};
    assert(result3 == expected3);

    // Test case 4: String with longest palindrome in the middle
    vector<string> result4 = manacher("cbbd");
    vector<string> expected4 = {"bb"};
    assert(result4 == expected4);

    // Test case 5: Longer string with palindrome
    vector<string> result5 = manacher("bananas");
    vector<string> expected5 = {"anana"};
    assert(result5 == expected5);

    // Test case 6: Even length palindrome
    vector<string> result6 = manacher("abba");
    vector<string> expected6 = {"abba"};
    assert(result6 == expected6);

    // Test case 7: String with multiple longest palindromes "abccba xyzzyx"
    vector<string> result7 = manacher("abccba xyzzyx");
    vector<string> expected7 = {"abccba", "xyzzyx"};
    assert(result7 == expected7);

    // Test case 8: String with a single longest palindrome "levelmadamlevel"
    vector<string> result8 = manacher("levelmadamlevel");
    vector<string> expected8 = {"levelmadamlevel"};
    assert(result8 == expected8);

    // Test case 9: String with multiple longest palindromes "aabbccddeeff"
    vector<string> result9 = manacher("aabbccddeeff");
    vector<string> expected9 = {"aa", "bb", "cc", "dd", "ee", "ff"};
    assert(result9 == expected9);

}

void run_sample_manacher() {
    string input = "google";
    vector<string> result = manacher(input);
    cout << "Longest palindromic substrings of \"" << input << "\": ";
    if (result.empty()) {
        cout << "No palindromes found." << endl;
    } else {
        for (const string& palindrome : result) {
            cout << palindrome << " ";
        }
        cout << endl;
    }
}

int main() {
    test_manacher();
    run_sample_manacher();
    return 0;
}