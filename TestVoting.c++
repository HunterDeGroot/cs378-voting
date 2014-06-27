/*
Google Test Libraries:
    % ls -al /usr/include/gtest/
    ...
    gtest.h
    ...

    % locate libgtest.a
    /usr/lib/libgtest.a

    % locate libpthread.a
    /usr/lib/x86_64-linux-gnu/libpthread.a
    /usr/lib32/libpthread.a

    % locate libgtest_main.a
    /usr/lib/libgtest_main.a

To compile the test:
    % g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Voting.c++ TestVoting.c++ -o TestVoting -lgtest -lgtest_main -lpthread

To run the test:
    % valgrind TestVoting

To obtain coverage of the test:
    % gcov-4.7 -b Voting.c++ TestVoting.c++
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <utility>  // make_pair, pair

#include "gtest/gtest.h"

#include "Voting.h"

// -----------
// TestVoting
// -----------

// ----
// check_tie
// ----

TEST(Voting, check_tie1) {
    int standings[20] = {};
    standings[1] = 1;
    standings[2] = 1;
    bool b = voting_check_tie(standings);
    ASSERT_EQ( b, true);}

TEST(Voting, check_tie2) {
    int standings[20] = {};
    standings[0] = 1;
    standings[19] = 1;
    bool b = voting_check_tie(standings);
    ASSERT_EQ( b, true);}

TEST(Voting, check_tie3) {
    int standings[20] = {};
    standings[1] = 2;
    standings[2] = 1;
    bool b = voting_check_tie(standings);
    ASSERT_EQ( b, false);}

TEST(Voting, check_tie4) {
    int standings[20] = {};
    standings[0] = 1;
    standings[19] = 2;
    bool b = voting_check_tie(standings);
    ASSERT_EQ( b, false);}

TEST(Voting, check_tie5) {
    int standings[20] = {};
    standings[1] = 12;
    standings[2] = 69;
    bool b = voting_check_tie(standings);
    ASSERT_EQ( b, false);}

TEST(Voting, check_tie6) {
    int standings[20] = {};
    standings[1] = 2;
    standings[2] = 2;
    bool b = voting_check_tie(standings);
    ASSERT_EQ( b, true);}

TEST(Voting, check_tie7) {
    int standings[20] = {};
    standings[0] = 69;
    standings[19] = 69;
    bool b = voting_check_tie(standings);
    ASSERT_EQ( b, true);}

TEST(Voting, check_tie8) {
    int standings[20] = {};
    standings[1] = 81;
    standings[2] = 20;
    bool b = voting_check_tie(standings);
    ASSERT_EQ( b, false);}

TEST(Voting, check_tie9) {
    int standings[20] = {};
    standings[0] = 11;
    standings[19] = 2;
    bool b = voting_check_tie(standings);
    ASSERT_EQ( b, false);}

TEST(Voting, check_tie10) {
    int standings[20] = {};
    standings[1] = 12;
    standings[19] = 69;
    bool b = voting_check_tie(standings);
    ASSERT_EQ( b, false);}

TEST(Voting, check_tie11) {
    int standings[20] = {};
    standings[1] = 1;
    standings[2] = 1;
    bool b = voting_check_tie(standings);
    ASSERT_EQ( b, true);}

TEST(Voting, check_tie12) {
    int standings[20] = {};
    standings[0] = 1;
    standings[19] = 1;
    bool b = voting_check_tie(standings);
    ASSERT_EQ( b, true);}

TEST(Voting, check_tie13) {
    int standings[20] = {};
    standings[1] = 2;
    standings[3] = 1;
    bool b = voting_check_tie(standings);
    ASSERT_EQ( b, false);}

TEST(Voting, check_tie14) {
    int standings[20] = {};
    standings[0] = 8;
    standings[19] = 2;
    bool b = voting_check_tie(standings);
    ASSERT_EQ( b, false);}

TEST(Voting, check_tie15) {
    int standings[20] = {};
    standings[1] = 112;
    standings[2] = 69;
    bool b = voting_check_tie(standings);
    ASSERT_EQ( b, false);}

// ----
// no_winner
// ----

TEST(Voting, no_winner1) {
    int standings[20] = {};
    standings[1] = 1;
    standings[2] = 1;
    bool b = voting_no_winner(standings);
    ASSERT_EQ( b, true);}

TEST(Voting, no_winner2) {
    int standings[20] = {};
    standings[0] = 2;
    standings[19] = 1;
    bool b = voting_no_winner(standings);
    ASSERT_EQ( b, false);}

TEST(Voting, no_winner3) {
    int standings[20] = {};
    standings[1] = 2;
    standings[2] = 1;
    bool b = voting_no_winner(standings);
    ASSERT_EQ( b, false);}

TEST(Voting, no_winner4) {
    int standings[20] = {};
    standings[0] = 1;
    standings[19] = 2;
    bool b = voting_no_winner(standings);
    ASSERT_EQ( b, false);}

TEST(Voting, no_winner5) {
    int standings[20] = {};
    standings[1] = 12;
    standings[2] = 69;
    bool b = voting_no_winner(standings);
    ASSERT_EQ( b, false);}

TEST(Voting, no_winner6) {
    int standings[20] = {};
    standings[1] = 20;
    standings[2] = 20;
    standings[3] = 35;
    bool b = (standings);
    ASSERT_EQ( b, true);}