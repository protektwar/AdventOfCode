#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <algorithm>
#include <ranges>

/*
High card        1
One Pair           2
Two Pair           2 2
Three of a Kind      3
Full house         2 3
Four of a Kind         4
Five of a kind           5
*/

std::unordered_map<char, int> cards_rank {{'A', 1}, {'K', 2}, {'Q', 3}, {'J', 4}, {'T', 5}, {'9', 6}, {'8', 7}, {'7', 8}, {'6', 9}, {'5', 10}, {'4', 11}, {'3', 12}, {'2', 13}};

bool cmp(std::pair<char, int>& a, 
         std::pair<char, int>& b) 
{ 
    return a.second > b.second; 
}

std::vector<std::pair<char, int>> sort_map(std::unordered_map<char, int>& M) 
{ 
    std::cout << "\nSorting\n";
    std::vector<std::pair<char, int> > A; 
    for (auto& it : M)  
        A.push_back(it); 
    sort(A.begin(), A.end(), cmp); 
/*    for (auto& it : A){
      std::cout << it.first << '-' << it.second << ' ';
      R[it.first] = it.second;
    }
    std::cout << '\n';  
    for (auto& m: R)
      std::cout << m.first << '?' << m.second << ' ';
    std::cout << '\n';*/
    return A;
}  

void insert_ranked(std::string hand, int rank, std::unordered_map<int, std::vector<std::string>> &ranked_hands) 
{
    int bigger = -1;
    bool adding = false;

    if (ranked_hands[rank].size()) {
        for (int i = 0; i < ranked_hands[rank].size(); i++) {
            bigger = -1;
            for (int k = 0; k < 5; k++) {
                
                if (cards_rank[hand.at(k)] > cards_rank[ranked_hands[rank].at(i).at(k)]) {
                    bigger = i;
                    adding = true;
                    break; // Break the inner loop once a larger hand is found
                }
                // If the cards are equal, continue to the next card
                else if (cards_rank[hand.at(k)] < cards_rank[ranked_hands[rank].at(i).at(k)]) {
                    break;
                }
            }

            if (adding) {
                break; // Break the outer loop once a larger hand is found
            }
        }
    }

    if (bigger > -1) {
        ranked_hands[rank].insert(ranked_hands[rank].begin() + bigger, hand);
    } else {
        ranked_hands[rank].push_back(hand);
    }
}

int main(void)
{
    std::ifstream inFile;
    std::string line, cardsStr, gameInfo, pointsStr;
    std::vector<std::unordered_map<char, int>> occurrences;
    std::unordered_map<char, int> occurrence;
    std::vector<std::pair<std::string, int>> hands;
    std::unordered_map<int, std::vector<std::string> > ranked_hands;

    inFile.open("input");
//    inFile.open("test");
    for( std::string line; getline( inFile, line ); ){
      std::stringstream hand(line);
      getline(hand, cardsStr, ' ');
      getline(hand, pointsStr, ' ');
      hands.push_back(std::make_pair(cardsStr, std::stoi(pointsStr)));
    }
    
    for (auto it = hands.begin(); it != hands.end(); ++it){
      int index = it - hands.begin();
      occurrence.clear();
      std::cout << hands.at(index).first << '\n';
      for(auto c : hands.at(index).first){
        occurrence[c] += 1;
      }
/*      occurrence = sort_map(occurrence);
      for (auto &m : occurrence){
        std::cout << '?' << m.first << ' ' << m.second << ' ';
      }
      std::cout << '\n';*/
      occurrences.push_back(occurrence);
    }
    int rank = 0;
    for(int i = 0; i < occurrences.size(); i++){
      std::cout << "Hand: " << hands[i].first << '\n';
      std::vector<int> counter{};
      for (const auto& [_, value] : sort_map(occurrences[i])) {
        counter.push_back(value);
        std::cout << value << ' ';
      }
        std::cout << '\n';
      if (counter.at(0) == 5) {
        std::cout << "Five of a Kind" << '\n';
        insert_ranked(hands[i].first, 7, ranked_hands);
      }
      else if (counter.at(0) == 4) {
        std::cout << "Four of a Kind" << '\n';
        insert_ranked(hands[i].first, 6, ranked_hands);
      }
      else if (counter.at(0) == 3 && counter.at(1) == 1) {
        std::cout << "Three of a Kind" << '\n';
        insert_ranked(hands[i].first, 4, ranked_hands);
      }
      else if (counter.at(0) == 3 && counter.at(1) == 2) {
        std::cout << "Foul House" << '\n';
        insert_ranked(hands[i].first, 5, ranked_hands);
      }
      else if (counter.at(0) == 2 && counter.at(1) == 1) {
        std::cout << "One Pair" << '\n';
        insert_ranked(hands[i].first, 2, ranked_hands);
      }
      else if (counter.at(0) == 2 && counter.at(1) == 2) {
        std::cout << "Two Pair" << '\n';
        insert_ranked(hands[i].first, 3, ranked_hands);
      }
      else if (counter.at(0) == 1) {
        std::cout << "High Card" << '\n';
        insert_ranked(hands[i].first, 1, ranked_hands);
      }
    }
    
    long long int totalWinnings = 0;
    long int rank_ = 1;
    for (int i = 0; i < ranked_hands.size(); i++){
      std::cout << "Rank: " << i << '\n';
      if (ranked_hands[i].size() == 0) continue;
      for (auto ranked_hand: ranked_hands[i]){
        for (auto it = hands.begin(); it != hands.end(); ++it){
          if (hands[it - hands.begin()].first == ranked_hand){
            std::cout << rank_ << " hand " << ranked_hand;
            std::cout << " bid " << hands[it - hands.begin()].second;
            totalWinnings = totalWinnings + (hands[it - hands.begin()].second*rank_);
            std::cout << " totalWinnings " << totalWinnings << '\n';
            rank_ = rank_ + 1;
          }
        } 
      }
    }


    std::cout << "What are the total winnings? "; 
    std::cout << totalWinnings << '\n';
    inFile.close();
}
