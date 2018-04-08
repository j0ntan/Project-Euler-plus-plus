/* In the card game poker, a hand consists of five cards and are ranked, from
 * lowest to highest, in the following way:
 *
 *    * High Card: Highest value card.
 *    * One Pair: Two cards of the same value.
 *    * Two Pairs: Two different pairs.
 *    * Three of a Kind: Three cards of the same value.
 *    * Straight: All cards are consecutive values.
 *    * Flush: All cards of the same suit.
 *    * Full House: Three of a kind and a pair.
 *    * Four of a Kind: Four cards of the same value.
 *    * Straight Flush: All cards are consecutive values of same suit.
 *    * Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.
 *
 * The cards are valued in the order:
 * 2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace.
 *
 * If two players have the same ranked hands then the rank made up of the
 * highest value wins; for example, a pair of eights beats a pair of fives (see
 * example 1 below). But if two ranks tie, for example, both players have a pair
 * of queens, then highest cards in each hand are compared (see example 4
 * below); if the highest cards tie then the next highest cards are compared,
 * and so on.
 *
 * Consider the following five hands dealt to two players:
 * Hand     Player 1        Player 2      Winner
 *  1   5H 5C 6S 7S KD   2C 3S 8S 8D TD  Player 2
 *      Pair of Fives    Pair of Eights
 *
 *  2   5D 8C 9S JS AC   2C 5C 7D 8S QH  Player 1
 *    Highest card Ace  Highest card Queen
 *
 *  3   2D 9C AS AH AC   3D 6D 7D TD QD  Player 2
 *        Three Aces  Flush with Diamonds
 *
 *  4   4D 6S 9H QH QC   3D 6D 7H QD QS  Player 1
 *      Pair of Queens   Pair of Queens
 *    Highest card Nine Highest card Seven
 *
 *  5   2H 2D 4C 4D 4S   3C 3D 3S 9S 9D  Player 1
 *        Full House       Full House
 *    With Three Fours  with Three Threes
 *
 * The file, poker.txt, contains one-thousand random hands dealt to two players.
 * Each line of the file contains ten cards (separated by a single space): the
 * first five are Player 1's cards and the last five are Player 2's cards. You
 * can assume that all hands are valid (no invalid characters or repeated
 * cards), each player's hand is in no specific order, and in each hand there is
 * a clear winner.
 *
 * How many hands does Player 1 win? */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

class Card {
public:
  enum class Rank : unsigned short {
    Two = 0,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace
  };

  enum class Suit : unsigned short { Hearts, Clubs, Diamonds, Spades };

  Card(Rank rank, Suit suit) : _rank(rank), _suit(suit) {}

  bool operator<(const Card &rhs) { return this->_rank < rhs._rank; }

  bool operator>(const Card &rhs) { return this->_rank > rhs._rank; }

  explicit operator Card::Rank() const { return _rank; }

  explicit operator Card::Suit() const { return _suit; }

  explicit operator unsigned short() const {
    return static_cast<unsigned short>(_rank);
  }

  friend std::ostream &operator<<(std::ostream &os, const Card &card) {
    os << '{';
    switch (card._rank) {
    case Card::Rank::Two:
      os << '2';
      break;
    case Card::Rank::Three:
      os << '3';
      break;
    case Card::Rank::Four:
      os << '4';
      break;
    case Card::Rank::Five:
      os << '5';
      break;
    case Card::Rank::Six:
      os << '6';
      break;
    case Card::Rank::Seven:
      os << '7';
      break;
    case Card::Rank::Eight:
      os << '8';
      break;
    case Card::Rank::Nine:
      os << '9';
      break;
    case Card::Rank::Ten:
      os << "10";
      break;
    case Card::Rank::Jack:
      os << "Jack";
      break;
    case Card::Rank::Queen:
      os << "Queen";
      break;
    case Card::Rank::King:
      os << "King";
      break;
    case Card::Rank::Ace:
      os << "Ace";
      break;
    }
    os << ", ";
    switch (card._suit) {
    case Card::Suit::Spades:
      os << "Spades";
      break;
    case Card::Suit::Hearts:
      os << "Hearts";
      break;
    case Card::Suit::Clubs:
      os << "Clubs";
      break;
    case Card::Suit::Diamonds:
      os << "Diamonds";
      break;
    }
    os << '}';
    return os;
  }

private:
  Rank _rank;
  Suit _suit;
};

class Hand {
public:
  enum class Rank : unsigned short {
    HighCard = 0,
    OnePair,
    TwoPairs,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush,
    RoyalFlush
  };

  Hand(Card card1, Card card2, Card card3, Card card4, Card card5)
      : _ranks(
            _readCards(std::vector<Card>{card1, card2, card3, card4, card5})) {}

  bool operator>(const Hand &rhs) const {
    bool greater = false;

    unsigned short i = 0;
    bool found_winner = false;
    while (not found_winner) {
      if (this->_ranks[i].first == rhs._ranks[i].first) {
        if (this->_ranks[i].second != rhs._ranks[i].second) {
          found_winner = true;
          greater = this->_ranks[i].second > rhs._ranks[i].second;
        } else
          ++i;
      } else {
        found_winner = true;
        greater = this->_ranks[i].first > rhs._ranks[i].first;
      }
    }

    return greater;
  }

  friend std::ostream &operator<<(std::ostream &os, const Hand &hand) {
    os << "{{";
    switch (hand._ranks.front().first) {
    case Hand::Rank::RoyalFlush:
      os << "Royal flush";
      break;
    case Hand::Rank::StraightFlush:
      os << "Straight flush";
      break;
    case Hand::Rank::FourOfAKind:
      os << "Four of a kind";
      break;
    case Hand::Rank::FullHouse:
      os << "Full house";
      break;
    case Hand::Rank::Flush:
      os << "Flush";
      break;
    case Hand::Rank::Straight:
      os << "Straight";
      break;
    case Hand::Rank::ThreeOfAKind:
      os << "Three of a kind";
      break;
    case Hand::Rank::TwoPairs:
      os << "Two pairs";
      break;
    case Hand::Rank::OnePair:
      os << "One pair";
      break;
    case Hand::Rank::HighCard:
      os << "High card";
      break;
    }
    os << "}}";

    return os;
  }

private:
  typedef std::pair<Hand::Rank, Card::Rank> rank_pair_t;

  bool _checkAllCardsSameSuit(const std::vector<Card> &cards) const {
    return (static_cast<Card::Suit>(cards[0]) ==
            static_cast<Card::Suit>(cards[1])) and
           (static_cast<Card::Suit>(cards[1]) ==
            static_cast<Card::Suit>(cards[2])) and
           (static_cast<Card::Suit>(cards[2]) ==
            static_cast<Card::Suit>(cards[3])) and
           (static_cast<Card::Suit>(cards[3]) ==
            static_cast<Card::Suit>(cards[4]));
  }

  bool _checkConsecutiveValues(const std::vector<Card> &cards) const {
    return (static_cast<unsigned short>(cards[1]) ==
            static_cast<unsigned short>(cards[0]) + 1) and
           (static_cast<unsigned short>(cards[2]) ==
            static_cast<unsigned short>(cards[1]) + 1) and
           (static_cast<unsigned short>(cards[3]) ==
            static_cast<unsigned short>(cards[2]) + 1) and
           (static_cast<unsigned short>(cards[4]) ==
            static_cast<unsigned short>(cards[3]) + 1);
  }

  std::vector<unsigned short>
  _countCards(const std::vector<Card> &cards) const {
    std::vector<unsigned short> result(13, 0);

    for (auto c : cards)
      result[static_cast<unsigned short>(c)]++;

    return result;
  }

  Card::Rank _rankOfRepeated(const std::vector<unsigned short> &rank_count,
                             const unsigned short &repetitions) {
    const auto repeated_it =
        std::find(rank_count.begin(), rank_count.end(), repetitions);
    const auto rank_val = static_cast<unsigned short>(
        std::distance(rank_count.begin(), repeated_it));
    return static_cast<Card::Rank>(rank_val);
  }

  void _appendRemainingHighCards(std::vector<rank_pair_t> &ranks,
                                 const std::vector<Card> &cards,
                                 const Card::Rank &repeated) {
    for (auto card_it = cards.rbegin(); card_it != cards.rend(); card_it++)
      if (static_cast<Card::Rank>(*card_it) != repeated)
        ranks.emplace_back(rank_pair_t{Hand::Rank::HighCard,
                                       static_cast<Card::Rank>(*card_it)});
  }

  std::vector<rank_pair_t> _singleRankHand(const std::vector<Card> &cards,
                                           const Hand::Rank &rank) {
    return std::vector<rank_pair_t>{
        rank_pair_t{rank, static_cast<Card::Rank>(cards[4])},
        rank_pair_t{rank, static_cast<Card::Rank>(cards[3])},
        rank_pair_t{rank, static_cast<Card::Rank>(cards[2])},
        rank_pair_t{rank, static_cast<Card::Rank>(cards[1])},
        rank_pair_t{rank, static_cast<Card::Rank>(cards[0])}};
  }

  std::vector<rank_pair_t> _readCards(std::vector<Card> cards) {
    std::vector<rank_pair_t> ranks;
    std::sort(cards.begin(), cards.end());

    const bool all_same_suit = _checkAllCardsSameSuit(cards);
    const bool consecutive_values = _checkConsecutiveValues(cards);

    std::vector<unsigned short> ranked_card_count = _countCards(cards);

    const bool has_four_of_a_kind =
        std::find(ranked_card_count.begin(), ranked_card_count.end(), 4) !=
        ranked_card_count.end();
    const bool has_three_of_a_kind =
        std::find(ranked_card_count.begin(), ranked_card_count.end(), 3) !=
        ranked_card_count.end();
    const bool has_a_pair =
        std::find(ranked_card_count.begin(), ranked_card_count.end(), 2) !=
        ranked_card_count.end();
    const bool has_two_pairs =
        has_a_pair and
        std::find(
            std::find(ranked_card_count.begin(), ranked_card_count.end(), 2) +
                1,
            ranked_card_count.end(), 2) != ranked_card_count.end();

    if (static_cast<Card::Rank>(cards[0]) == Card::Rank::Ten and
        consecutive_values and all_same_suit)
      ranks.emplace_back(rank_pair_t{
          Hand::Rank::RoyalFlush,
          Card::Rank::Ace}); // for guaranteed winner, sub-ranks not needed
    else if (consecutive_values and all_same_suit)
      ranks = _singleRankHand(cards, Hand::Rank::StraightFlush);
    else if (has_four_of_a_kind) {
      const auto four_of_a_kind_rank = _rankOfRepeated(ranked_card_count, 4);
      ranks.emplace_back(
          rank_pair_t{Hand::Rank::FourOfAKind, four_of_a_kind_rank});

      _appendRemainingHighCards(ranks, cards, four_of_a_kind_rank);
    } else if (has_three_of_a_kind and has_a_pair)
      ranks = std::vector<rank_pair_t>{
          rank_pair_t{Hand::Rank::FullHouse,
                      _rankOfRepeated(ranked_card_count, 3)},
          rank_pair_t{Hand::Rank::FullHouse,
                      _rankOfRepeated(ranked_card_count, 2)}};
    else if (all_same_suit)
      ranks = _singleRankHand(cards, Hand::Rank::Flush);
    else if (consecutive_values)
      ranks = _singleRankHand(cards, Hand::Rank::Straight);
    else if (has_three_of_a_kind) {
      const auto three_of_a_kind_rank = _rankOfRepeated(ranked_card_count, 3);
      ranks.emplace_back(
          rank_pair_t{Hand::Rank::ThreeOfAKind, three_of_a_kind_rank});

      _appendRemainingHighCards(ranks, cards, three_of_a_kind_rank);
    } else if (has_two_pairs) {
      auto higher_pair_rank_val_it =
          std::find(ranked_card_count.rbegin(), ranked_card_count.rend(), 2);
      auto lower_pair_rank_val_it =
          std::find(higher_pair_rank_val_it, ranked_card_count.rend(), 2);
      auto unpaired_rank_val_it =
          std::find(ranked_card_count.begin(), ranked_card_count.end(), 1);
      ranks = std::vector<rank_pair_t>{
          rank_pair_t{Hand::Rank::TwoPairs,
                      static_cast<Card::Rank>(*higher_pair_rank_val_it)},
          rank_pair_t{Hand::Rank::TwoPairs,
                      static_cast<Card::Rank>(*lower_pair_rank_val_it)},
          rank_pair_t{Hand::Rank::HighCard,
                      static_cast<Card::Rank>(*unpaired_rank_val_it)}};
    } else if (has_a_pair) {
      const auto pair_rank = _rankOfRepeated(ranked_card_count, 2);
      ranks.emplace_back(rank_pair_t{Hand::Rank::OnePair, pair_rank});

      _appendRemainingHighCards(ranks, cards, pair_rank);
    } else
      ranks = _singleRankHand(cards, Hand::Rank::HighCard);

    return ranks;
  }

  const std::vector<rank_pair_t> _ranks;
};

// function prototypes
std::ifstream openTextFile(const std::string &filepath);
std::string readLine(std::ifstream &file);
std::pair<const Hand, const Hand> createHandsFromLine(const std::string &line);
Card convertCharPairToCard(const char &first, const char &second);

int main() {
  // quick test using example set of 5 hands from problem statement
  std::cout << "Player 1 wins the following: \n";
  std::cout << std::boolalpha;
  std::cout << "   hand 1: "
            << (Hand{Card{Card::Rank::Five, Card::Suit::Hearts},
                     Card{Card::Rank::Five, Card::Suit::Clubs},
                     Card{Card::Rank::Six, Card::Suit::Spades},
                     Card{Card::Rank::Seven, Card::Suit::Spades},
                     Card{Card::Rank::King, Card::Suit::Diamonds}} >
                Hand{Card{Card::Rank::Two, Card::Suit::Clubs},
                     Card{Card::Rank::Three, Card::Suit::Spades},
                     Card{Card::Rank::Eight, Card::Suit::Spades},
                     Card{Card::Rank::Eight, Card::Suit::Diamonds},
                     Card{Card::Rank::Ten, Card::Suit::Diamonds}})
            << '\n';
  std::cout << "   hand 2: "
            << (Hand{Card{Card::Rank::Five, Card::Suit::Diamonds},
                     Card{Card::Rank::Eight, Card::Suit::Clubs},
                     Card{Card::Rank::Nine, Card::Suit::Spades},
                     Card{Card::Rank::Jack, Card::Suit::Spades},
                     Card{Card::Rank::Ace, Card::Suit::Clubs}} >
                Hand{Card{Card::Rank::Two, Card::Suit::Clubs},
                     Card{Card::Rank::Five, Card::Suit::Clubs},
                     Card{Card::Rank::Seven, Card::Suit::Diamonds},
                     Card{Card::Rank::Eight, Card::Suit::Spades},
                     Card{Card::Rank::Queen, Card::Suit::Hearts}})
            << '\n';
  std::cout << "   hand 3: "
            << (Hand{Card{Card::Rank::Two, Card::Suit::Diamonds},
                     Card{Card::Rank::Nine, Card::Suit::Clubs},
                     Card{Card::Rank::Ace, Card::Suit::Spades},
                     Card{Card::Rank::Ace, Card::Suit::Hearts},
                     Card{Card::Rank::Ace, Card::Suit::Clubs}} >
                Hand{Card{Card::Rank::Three, Card::Suit::Diamonds},
                     Card{Card::Rank::Six, Card::Suit::Diamonds},
                     Card{Card::Rank::Seven, Card::Suit::Diamonds},
                     Card{Card::Rank::Ten, Card::Suit::Diamonds},
                     Card{Card::Rank::Queen, Card::Suit::Diamonds}})
            << '\n';
  std::cout << "   hand 4: "
            << (Hand{Card{Card::Rank::Four, Card::Suit::Diamonds},
                     Card{Card::Rank::Six, Card::Suit::Spades},
                     Card{Card::Rank::Nine, Card::Suit::Hearts},
                     Card{Card::Rank::Queen, Card::Suit::Hearts},
                     Card{Card::Rank::Queen, Card::Suit::Clubs}} >
                Hand{Card{Card::Rank::Three, Card::Suit::Diamonds},
                     Card{Card::Rank::Six, Card::Suit::Diamonds},
                     Card{Card::Rank::Seven, Card::Suit::Hearts},
                     Card{Card::Rank::Queen, Card::Suit::Diamonds},
                     Card{Card::Rank::Queen, Card::Suit::Spades}})
            << '\n';
  std::cout << "   hand 5: "
            << (Hand{Card{Card::Rank::Two, Card::Suit::Hearts},
                     Card{Card::Rank::Two, Card::Suit::Diamonds},
                     Card{Card::Rank::Four, Card::Suit::Clubs},
                     Card{Card::Rank::Four, Card::Suit::Diamonds},
                     Card{Card::Rank::Four, Card::Suit::Spades}} >
                Hand{Card{Card::Rank::Three, Card::Suit::Clubs},
                     Card{Card::Rank::Three, Card::Suit::Diamonds},
                     Card{Card::Rank::Three, Card::Suit::Spades},
                     Card{Card::Rank::Nine, Card::Suit::Spades},
                     Card{Card::Rank::Nine, Card::Suit::Diamonds}})
            << "\n\n";

  const std::string FILEPATH{
      "../../../solutions/051-100/Problem054/p054_poker.txt"};
  std::ifstream file = openTextFile(FILEPATH);

  unsigned short player1_score = 0;
  for (unsigned i = 0; i < 1000; i++) {
    const std::string line = readLine(file);
    const std::pair<const Hand, const Hand> both_player_hands =
        createHandsFromLine(line);

    if (both_player_hands.first > both_player_hands.second)
      player1_score++;
  }

  std::cout << "Player 1 won " << player1_score << " times.";

  file.close();
}

std::ifstream openTextFile(const std::string &filepath) {
  std::ifstream file(filepath);
  if (file.fail()) {
    std::cerr << "error opening the file. exiting" << std::endl;
    exit(1);
  }
  return file;
}

std::string readLine(std::ifstream &file) {
  std::string line;
  std::getline(file, line, '\n');
  return line;
}

Card convertCharPairToCard(const char &first, const char &second) {
  Card::Rank rank;
  Card::Suit suit;

  switch (first) {
  case '2':
    rank = Card::Rank::Two;
    break;
  case '3':
    rank = Card::Rank::Three;
    break;
  case '4':
    rank = Card::Rank::Four;
    break;
  case '5':
    rank = Card::Rank::Five;
    break;
  case '6':
    rank = Card::Rank::Six;
    break;
  case '7':
    rank = Card::Rank::Seven;
    break;
  case '8':
    rank = Card::Rank::Eight;
    break;
  case '9':
    rank = Card::Rank::Nine;
    break;
  case 'T':
    rank = Card::Rank::Ten;
    break;
  case 'J':
    rank = Card::Rank::Jack;
    break;
  case 'Q':
    rank = Card::Rank::Queen;
    break;
  case 'K':
    rank = Card::Rank::King;
    break;
  case 'A':
    rank = Card::Rank::Ace;
    break;
  default:
    rank = Card::Rank::Ace;
  }

  switch (second) {
  case 'C':
    suit = Card::Suit::Clubs;
    break;
  case 'S':
    suit = Card::Suit::Spades;
    break;
  case 'H':
    suit = Card::Suit::Hearts;
    break;
  case 'D':
    suit = Card::Suit::Diamonds;
    break;
  default:
    suit = Card::Suit::Diamonds;
  }

  return Card{rank, suit};
}

std::pair<const Hand, const Hand> createHandsFromLine(const std::string &line) {
  const Card card1{convertCharPairToCard(line[0], line[1])},
      card2{convertCharPairToCard(line[3], line[4])},
      card3{convertCharPairToCard(line[6], line[7])},
      card4{convertCharPairToCard(line[9], line[10])},
      card5{convertCharPairToCard(line[12], line[13])},
      card6{convertCharPairToCard(line[15], line[16])},
      card7{convertCharPairToCard(line[18], line[19])},
      card8{convertCharPairToCard(line[21], line[22])},
      card9{convertCharPairToCard(line[24], line[25])},
      card10{convertCharPairToCard(line[27], line[28])};
  const Hand hand1{card1, card2, card3, card4, card5},
      hand2{card6, card7, card8, card9, card10};
  return std::pair<const Hand, const Hand>{hand1, hand2};
}
