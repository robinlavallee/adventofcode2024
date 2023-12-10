
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>

void replace(std::string& str,
    const std::string& oldStr,
    const std::string& newStr)
{
    std::string::size_type pos = 0u;
    while ((pos = str.find(oldStr, pos)) != std::string::npos) {
        str.replace(pos, oldStr.length(), newStr);
        pos += newStr.length();
    }
}

struct HandBid {
    std::string hand; // A, K, Q, J, T, 9, 8, 7, 6, 5, 4, 3, 2 (A is highest)
    int bid;

    enum class Type {
        HighCard,
        OnePair,
        TwoPair,
        ThreeOfAKind,
        FullHouse,
        FourOfAKind,
        FiveOfAKind,
    };

    Type getType() const {
        Type type = Type::HighCard;
        std::map<char, int> cardCount;
        for (auto& c : hand) {
            cardCount[c]++;
        }

        for (auto& card : cardCount) {
            if (card.second == 5) {
                type = Type::FiveOfAKind;
            } else if (card.second == 4) {
                type = Type::FourOfAKind;
            } else if (card.second == 3) {
                if (type == Type::OnePair) {
                    type = Type::FullHouse;
                } else {
                    type = Type::ThreeOfAKind;
                }
            } else if (card.second == 2) {
                if (type == Type::ThreeOfAKind) {
                    type = Type::FullHouse;
                } else if (type == Type::OnePair) {
                    type = Type::TwoPair;
                } else {
                    type = Type::OnePair;
                }
            }
        }

        return type;
    }

    bool operator<(const HandBid& other) const {
        // find the type 
        
        Type type = getType();
        Type otherType = other.getType();

        if (type != otherType) {
            return type < otherType;
        }

        char order[] = { '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J','Q', 'K', 'A' };

        // compare card by card, strongest to weakest
        for (int i = 0; i < hand.length(); ++i) {
            if (hand[i] != other.hand[i]) {
                return std::find(std::begin(order), std::end(order), hand[i]) < std::find(std::begin(order), std::end(order), other.hand[i]);
            }
        }

        return false;
    }
};

struct HandBidJoker {
    std::string hand; // A, K, Q, T, 9, 8, 7, 6, 5, 4, 3, 2, J (A is highest)
    int bid;

    enum class Type {
        HighCard,
        OnePair,
        TwoPair,
        ThreeOfAKind,
        FullHouse,
        FourOfAKind,
        FiveOfAKind,
    };

    Type getType() const {
        Type type = Type::HighCard;
        std::map<char, int> cardCount;
        int numJokers = 0;
        for (auto& c : hand) {
            if (c == 'J') {
                numJokers++;
            } else {
                cardCount[c]++;
            }
        }

        for (auto& card : cardCount) {
            if (card.second == 5) {
                type = Type::FiveOfAKind;
            } else if (card.second == 4) {
                type = Type::FourOfAKind;
            } else if (card.second == 3) {
                if (type == Type::OnePair) {
                    type = Type::FullHouse;
                } else {
                    type = Type::ThreeOfAKind;
                }
            } else if (card.second == 2) {
                if (type == Type::ThreeOfAKind) {
                    type = Type::FullHouse;
                } else if (type == Type::OnePair) {
                    type = Type::TwoPair;
                } else {
                    type = Type::OnePair;
                }
            }
        }

        if (numJokers == 1) {
            if (type == Type::HighCard) {
                type = Type::OnePair;
            } else if (type == Type::OnePair) {
                type = Type::TwoPair;
            } else if (type == Type::TwoPair) {
                type = Type::FullHouse;
            } else if (type == Type::ThreeOfAKind) {
                type = Type::FullHouse;
            } else if (type == Type::FourOfAKind) {
                type = Type::FiveOfAKind;
            }
        } else if (numJokers == 2) {
            if (type == Type::HighCard) {
                type = Type::ThreeOfAKind;
            } else if (type == Type::OnePair) {
                type = Type::FullHouse;
            } else if (type == Type::ThreeOfAKind) {
                type = Type::FiveOfAKind;
            }
        } else if (numJokers == 3) {
            if (type == Type::HighCard) {
                type = Type::FourOfAKind;
            } else if (type == Type::OnePair) {
                type = Type::FiveOfAKind;
            }
        } else if (numJokers == 4) {
            type = Type::FiveOfAKind;
        } else if (numJokers == 5) {
            type = Type::FiveOfAKind;
        }

        return type;
    }

    bool operator<(const HandBidJoker& other) const {
        // find the type 
        
        Type type = getType();
        Type otherType = other.getType();

        if (type != otherType) {
            return type < otherType;
        }

        char order[] = { 'J', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'Q', 'K', 'A' };

        // compare card by card, strongest to weakest
        for (int i = 0; i < hand.length(); ++i) {
            if (hand[i] != other.hand[i]) {
                return std::find(std::begin(order), std::end(order), hand[i]) < std::find(std::begin(order), std::end(order), other.hand[i]);
            }
        }

        return false;
    }
};


int first() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {

        std::vector<HandBid> handBids;        
        std::string tp;
        while (getline(newfile, tp)) {
            // line looks like: 32T3K 765 where 32T3K is the hand and 765 is the bid
            // split by space
            HandBid handBid;
            int space = tp.find(" ");
            std::string hand = tp.substr(0, space);
            std::string bid = tp.substr(space + 1);
            handBid.hand = hand;
            handBid.bid = std::stoi(bid);
            handBids.push_back(handBid);
        }

        std::sort(handBids.begin(), handBids.end());

        unsigned long long sum = 0;
        for (size_t i = 0; i < handBids.size(); ++i) {
            sum += handBids[i].bid * (i + 1);
        }

        std::cout << sum << std::endl;

        newfile.close();
    }

    return 0;
}

int second() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {

        std::vector<HandBidJoker> handBids;        
        std::string tp;
        while (getline(newfile, tp)) {
            // line looks like: 32T3K 765 where 32T3K is the hand and 765 is the bid
            // split by space
            HandBidJoker handBid;
            int space = tp.find(" ");
            std::string hand = tp.substr(0, space);
            std::string bid = tp.substr(space + 1);
            handBid.hand = hand;
            handBid.bid = std::stoi(bid);
            handBids.push_back(handBid);
        }

        std::sort(handBids.begin(), handBids.end());

        unsigned long long sum = 0;
        for (size_t i = 0; i < handBids.size(); ++i) {
            sum += handBids[i].bid * (i + 1);
        }

        std::cout << sum << std::endl;

        newfile.close();
    }
    return 0;
}

int main() {
    first();
    second();
}


