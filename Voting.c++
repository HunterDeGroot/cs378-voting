// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream> // to parse each ballot
#include <string>
#include "Voting.h"
#include "limits.h" // for MAX_INT

using namespace std;

// -------------
// Voting_print_cands
// -------------

void voting_print_cands(candidate* candidates, int* standings, int number_of_candidates){
	
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
// Voting_print_winner
// -------------

void voting_print_winner(int* standings,candidate* candidates) {
	
	int i;
	bool first_print = true;
	if(voting_no_winner(standings) && voting_check_tie){
		for(i = 0; i < 20; ++i){
			if(standings[i] != 0 && first_print){
				cout<<candidates[i].name;
				first_print = false;
			}
			else if(standings[i] && !first_print)
				cout<<endl<<candidates[i].name;
		}
	} else {
		int w_index;
		int greatest = 0;
		for(i = 0; i < 20; ++i){
			if(standings[i] > greatest) {
				w_index = i;
				greatest = standings[i];
			}
		}
		cout << candidates[w_index].name;}}
	
// -------------
// Voting_get_loser
// -------------

void voting_get_losers(int* standings, int*& losers){
	
	int i;
	int loser = INT_MAX;
	for(i = 0; i < 20; ++i){
		if( standings[i] != 0 && standings[i] < loser) {
			loser = standings[i];
		}
	}

	for(i = 0; i < 20; ++i){
		if(loser == standings[i])
			losers[i] = 1;}}

// -------------
// Voting_distribute_losing_ballots
// -------------

candidate* voting_distribute_losing_ballots(candidate*& candidates,int loser, int* losers,int number_of_candidates,int*& standings){

	int i;
	candidate& l = candidates[loser];
	for(i = 0; i < l.num_of_ballots; ++i){

		int count;
		int index_to_distribute;
		int copy_index = 0;
		bool start_copy = false;

		// go through each vote of each ballot of the losing-est
		for(count = 1; count < number_of_candidates; ++count){
			int vote = l.ballots[i][count];
			if(!start_copy){

				// and as soon as the next valid candidate is seen as priority
				if(standings[vote-1] != 0 && losers[vote-1]==0){

					index_to_distribute = vote-1;
					start_copy = true;
					candidate& c = candidates[index_to_distribute];
					c.ballots[c.num_of_ballots][copy_index] = vote;
					++copy_index;
					++c.num_of_ballots;
					++standings[index_to_distribute];
				}
			} else {

				// fill a ballot from the point of the recieving candidate into its ballots
				candidate& c = candidates[index_to_distribute];
				c.ballots[c.num_of_ballots-1][copy_index] = vote;
				++copy_index;
			}
		}
	}

	l.num_of_ballots = 0;
	standings[loser] = 0;
	return candidates;}

// -------------
// Voting_check_tie
// -------------

bool voting_check_tie(int* standings){

	int i;
	int mode = 0;

	for(i = 0; i < 20; ++i){
		if(standings[i] != 0){
			mode = standings[i];
			break;
		}
	}

	int x;
	for(x = 0; x < 20; ++x){
		if(standings[x] != 0 && standings[x] != mode)
			return false;
	}
	return true;}

// -------------
// Voting_no_winner
// -------------

bool voting_no_winner(int* standings){

	int i;
	int sum = 0;
	for(i = 0; i < 20; ++i)
		sum += standings[i];

	for(i = 0; i < 20; ++i)
		if(standings[i] > sum/2)
			return false;

	return true;}

// -------------
// Voting_get_winner
// -------------

void voting_get_winner(candidate* candidates, int* standings, int number_of_candidates, std::ostream& w){

	// keep re-evaluating ballots from losers till tie or winner
	//voting_print_cands(candidates, standings, number_of_candidates);
	int l [20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int* losers = l;

	while(!voting_check_tie(standings) && voting_no_winner(standings)){
		voting_get_losers(standings,losers);
		int i;
		for(i = 0; i < 20; ++i)
			if(losers[i] == 1)
				voting_distribute_losing_ballots(candidates,i,losers,number_of_candidates,standings);
	//	voting_print_cands(candidates, standings, number_of_candidates);

	}
	voting_print_winner(standings, candidates);}

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
			voting_get_winner(candidates, standings, number_of_candidates, w);
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
	voting_get_winner(candidates,standings,number_of_candidates,w);
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
		int standings [20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		voting_setup(candidates,standings,r,w);
		if(i != number_of_elections-1)
			cout << endl << endl;}}
	