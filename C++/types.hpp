#pragma once
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// what is expected
using float32_t = float;
using float64_t = double;

/**
 * @brief The details for what a match has, a word, data indices, query indices.
 */
class Match {
public:
	Match(std::string word, std::vector<int32_t> data_indices, std::vector<int32_t> query_indices);
	std::string word;
	std::vector<int32_t> data_indices;
	std::vector<int32_t> query_indices;
};

class AdjacentPair {
public:
	AdjacentPair(std::string word1, std::string word2, int32_t dindex1, int32_t qindex1, int32_t dindex2, int32_t qindex2);
	std::string word1, word2;
	int32_t length;
	int32_t dindex1, dindex2;
	int32_t qindex1, qindex2;
};

namespace Blastn {
	/**
	 * @brief Used in Smith Waterman for the matrices
	 */
	using Matrix = std::vector<std::vector<int32_t>>;
	void print(Matrix m);
	/**
	 * @brief Map sequence names to their sequence.
	 */
	using SequenceMap = std::unordered_map<std::string, std::string>;
	void print(SequenceMap s);
	/**
	 * @brief Intermediate, map a word to its indices.
	 */
	using IndexedWordMap = std::unordered_map<std::string, std::vector<int32_t>>;
	/**
	 * @brief Map sequence names to all words mapped to a vector or indices where each word appears in its sequence.
	 */
	using IndexedSequenceMap = std::unordered_map<std::string, IndexedWordMap>;
	void print(IndexedSequenceMap s);
	/**
	 * @brief Intermediate, map a word to its Match objects
	 */
	using MatchedMatchesMap = std::unordered_map<std::string, std::vector<Match>>;
	/**
	 * @brief Data name mapped to a query name mapped to a vector of Match objects
	 */
	using MatchedSequenceMap = std::unordered_map<std::string, MatchedMatchesMap>;
	void print(MatchedSequenceMap);
}
