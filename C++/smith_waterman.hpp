#pragma once

#include <string>
#include <tuple>
#include <vector>
#include "types.hpp"

// return the maximum of three values or zero
inline std::tuple<int, int> _max(int left, int up, int diag);

inline int _score_alignment(char alpha, char beta, int match, int mismatch, int gap);

int smith_waterman(std::string seq1, std::string seq2, int match, int mismatch, int gap, bool just_score);
Blastn::IndexedSequenceMap smith_waterman_filter(Blastn::IndexedSequenceMap data, int minscore, int match, int mismatch, int gap);

void print(Blastn::Matrix m);

void test_smith_waterman();
