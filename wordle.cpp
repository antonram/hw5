// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(std::string guess,  
		const std::string& in,
  	std::string floating,
  	const std::set<std::string>& dict,
		std::set<std::string>& result,
		size_t& dashCount,
		size_t numFilled);

size_t countDashes(const std::string in);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
   std::set<std::string> result;

	//initialize wordle helper. empty string at first
	std::string newFloating = floating;
	size_t dashCount = countDashes(in);
	wordleHelper("", in, newFloating, dict, result, dashCount, 0);

	 return result;

   
}

// Define any helper functions here
void wordleHelper(std::string guess,  
		const std::string& in,
    std::string floating,
    const std::set<std::string>& dict,
		std::set<std::string>& result,
		size_t& dashCount,
		size_t numFilled) 
{

	// if empty, nothing to do
	if(in.size() == 0) {
		return;
	}

	// if guess is complete, either insert the word if it's valid or leave resulting set as is.
	if(guess.size() == in.size()) {
		if((dict.find(guess) != dict.end()) && (floating.size() == 0)) {
			result.insert(guess);
		}
		return;
	}

	// if we know which letter goes in that place, just move on
	if((in[guess.size()] != '-')) {
		wordleHelper(guess + in[guess.size()], in, floating, dict, result, dashCount, numFilled);
		return;
	}

	// if all remaining words are in the floating string.
	if(floating.size() == dashCount - numFilled) {
		for(size_t i = 0; i < floating.size(); i++) {
			std::string newFloating = "";
			// make new string with all chars except the one we are looking at
			for(size_t j = 0; j < floating.size(); j++) {
				if(j != i) {
					newFloating += floating[j];
				}
			}
			wordleHelper(guess + floating[i], in, newFloating, dict, result, dashCount, numFilled+1); 
		}
		return;
	}

	// if none of above were true, then we iterate through all of the alphabet and recurse
	for(char letter = 'a'; letter <= 'z'; letter++) {
		// if letter is in floating list, we must rid of it in next recursion
		if(floating.find(letter) != std::string::npos) {
			std::string newFloating = "";
			int flag = 0;
			for(size_t i = 0; i < floating.size(); i++) {
				if((floating[i] != letter) || (flag == 1)) {
					newFloating += floating[i];
				}
				else {
					flag = 1;
				}
			}
			wordleHelper(guess + letter, in, newFloating, dict, result, dashCount, numFilled+1);
		}
		// if letter not in floating
		else {
			wordleHelper(guess + letter, in, floating, dict, result, dashCount, numFilled+1);
		}
	}
}

size_t countDashes(const std::string in) {
	size_t dashes = 0;
	for(size_t i = 0; i < in.size(); i++) {
		if(in[i] == '-') {
			dashes++;
		}
	}
	return dashes;
}
