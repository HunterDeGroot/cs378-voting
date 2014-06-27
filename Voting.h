using namespace std;

struct candidate{
	int eliminated = 0;
	int ballots[1000][20] = {};
	int num_of_ballots = 0;
	string name;};

// -------------
// Voting_print_winner
// -------------

void voting_print_winner(int*,candidate*);

// -------------
// print_cands
// -------------

// print current state of the candidates ballots
void voting_print_cands(candidate*, int*, int);

// -------------
// Voting_get_loser
// -------------

// return the index of the canidate with lowest non-zero number of ballots 
void voting_get_losers(int*, int*&);

// -------------
// Voting_distribute_losing_ballots
// -------------

// take loser's ballots and add them to the next significant candidate
candidate* voting_distribute_losing_ballots(candidate*&,int,int*,int,int*&);

// -------------
// Voting_check_tie
// -------------

// if there is a true tie return true
bool voting_check_tie(int*);

// -------------
// Voting_no_winner
// -------------

// if there is no current winner return true
bool voting_no_winner(int*);

// -------------
// Voting_get_winner
// -------------

// resolve each election
void voting_get_winner(candidate*, int*, int, std::ostream&);

// -------------
// Voting_election
// -------------

// aranges all candidates in an array with their corresponding ballots
void voting_setup (candidate*, int*, std::istream&, std::ostream&);

// -------------
// Voting_reslove
// -------------

// figure out who won the elections from iostream
void voting_resolve (std::istream&, std::ostream&);