using namespace std;

struct candidate{
	int eliminated = 0;
	int ballots[1000][20] = {};
	int num_of_ballots = 0;
	string name;};

// -------------
// print_cands
// -------------

void print_cands(candidate*, int*, int);

// -------------
// Voting_get_winner
// -------------

void voiting_get_winner(candidate*, int*, int, std::ostream&);

// -------------
// Voting_election
// -------------

// resolve an election
void voting_setup (candidate*, int*, std::istream&, std::ostream&);

// -------------
// Voting_reslove
// -------------

// figure out who won the elections from iostream
void voting_resolve (std::istream&, std::ostream&);