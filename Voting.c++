// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream> // to parse each ballot
#include <string>
#include "Voting.h"

using namespace std;

// -------------
// print_cands
// -------------

void print_cands(candidate* candidates, int* standings, int number_of_candidates){
	
	int count;
	for(count = 0; count < number_of_candidates; ++count){
		
		cout << candidates[count].name << endl;
		int i;
		for(i = 0; i < candidates[count].num_of_ballots; ++i){
			int x;
			for(x = 0; x < number_of_candidates; ++x)
				cout << candidates[count].ballots[i][x] << " ";
			cout << endl;
		}
		cout << endl;}

	for(count = 0; count < number_of_candidates; ++count)
		cout << count << ": " << standings[count] << endl;

	}

// -------------
// Voting_get_winner
// -------------

void voiting_get_winner(candidate* candidates, int* standings, int number_of_candidates, std::ostream& w){

	print_cands(candidates,standings,number_of_candidates);
}

// -------------
// Voting_setup
// -------------

void voting_setup (candidate* candidates, int* standings, std::istream& r, std::ostream& w) {

	int number_of_candidates = 0;
	r >> number_of_candidates;

	// skip to first line of names
	int count;
	string name;
	getline(r,name);
	for(count = 0; count < number_of_candidates; ++count){
		getline(r, name);
		candidates[count].name = name;
	}
	
	// fill candidate array with info based on first
	string ballot;
	int cand_num = 0;
	while( getline(r,ballot)){
		istringstream is(ballot);
		string vote;

		// The first vote determines who the ballot gets initialized to
		is >> vote;

		// stop if you've reached the end of the election
		if(vote.compare("") == 0) {
			voiting_get_winner(candidates,standings,number_of_candidates,w);
			return;}

		// turn the first vote into an int and set that as the candidate
		cand_num = atoi(vote.c_str());

		// next available index is the size
		int next = candidates[cand_num-1].num_of_ballots;

		candidates[cand_num-1].ballots[next][0] = cand_num;
		++candidates[cand_num-1].num_of_ballots;
		++standings[cand_num-1];

		for(count = 1; count < number_of_candidates; ++count){
			is >> vote;
			// fill the rest of the ballot in the next available spot in that candidates ballots
			candidates[cand_num-1].ballots[next][count] = atoi(vote.c_str());
		}
	}
	voiting_get_winner(candidates,standings,number_of_candidates,w);
}	

// -------------
// Voting_resolve
// -------------

void voting_resolve (std::istream& r, std::ostream& w) {
	
	// check to see how many elections 
	// there are and resolve each of them
	int number_of_elections;
	r >> number_of_elections;
	
	int i;
	for(i = 0; i < number_of_elections; ++i) {
		// gather the candidates names in an array
		candidate candidates[20] = {};
		int standings[20] = {};
		voting_setup(candidates,standings,r,w);}}
	