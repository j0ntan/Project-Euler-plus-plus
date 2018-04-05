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
 * Hand	 	  Player 1	 	    Player 2	 	  Winner
 *  1	 	5H 5C 6S 7S KD   2C 3S 8S 8D TD  Player 2
 *      Pair of Fives    Pair of Eights
 *
 *  2	 	5D 8C 9S JS AC   2C 5C 7D 8S QH  Player 1
 *    Highest card Ace  Highest card Queen
 *
 *  3	 	2D 9C AS AH AC   3D 6D 7D TD QD  Player 2
 *        Three Aces  Flush with Diamonds
 *
 *  4	 	4D 6S 9H QH QC   3D 6D 7H QD QS  Player 1
 *      Pair of Queens   Pair of Queens
 *    Highest card Nine Highest card Seven
 *
 *  5	 	2H 2D 4C 4D 4S   3C 3D 3S 9S 9D  Player 1
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
#include <iostream>
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

  bool operator<(const Card &rhs) const {
    return static_cast<unsigned short>(this->_rank) <
           static_cast<unsigned short>(rhs._rank);
  }

  bool hasRank(const Card::Rank &rank) const { return this->_rank == rank; }

  bool hasSuit(const Card::Suit &suit) const { return this->_suit == suit; }

  bool compareRank(const Card &other) const {
    return this->_rank == other._rank;
  }

  bool compareSuit(const Card &other) const {
    return this->_suit == other._suit;
  }

  unsigned short getRankValue() const {
    return static_cast<unsigned short>(this->_rank);
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
      : _cards(
            _sortedCards(std::vector<Card>{card1, card2, card3, card4, card5})),
        _rank(_getRank()) {}

  friend std::ostream &operator<<(std::ostream &os, const Hand &hand) {
    os << "{{\n"
       << hand._cards[0] << ", \n"
       << hand._cards[1] << ", \n"
       << hand._cards[2] << ", \n"
       << hand._cards[3] << ", \n"
       << hand._cards[4] << ", \n"
       << "rank: ";
    switch (hand._rank) {
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
    os << "\n}}";

    return os;
  }

private:
  std::vector<Card> _sortedCards(std::vector<Card> cards) {
    std::sort(cards.begin(), cards.end());
    return cards;
  }

  bool _checkAllCardsSameSuit() const {
    return _cards[0].compareSuit(_cards[1]) and
           _cards[1].compareSuit(_cards[2]) and
           _cards[2].compareSuit(_cards[3]) and
           _cards[3].compareSuit(_cards[4]);
  }

  bool _checkConsecutiveValues() const {
    return _cards[1].getRankValue() == _cards[0].getRankValue() + 1 and
           _cards[2].getRankValue() == _cards[1].getRankValue() + 1 and
           _cards[3].getRankValue() == _cards[2].getRankValue() + 1 and
           _cards[4].getRankValue() == _cards[3].getRankValue() + 1;
  }

  std::vector<unsigned short> _countRepeatedCards() const {
    std::vector<unsigned short> result(13, 0);

    for (auto c : _cards)
      result[c.getRankValue()]++;

    return result;
  }

  Hand::Rank _getRank() {
    const bool all_same_suit = _checkAllCardsSameSuit();
    const bool consecutive_values = _checkConsecutiveValues();
    std::vector<unsigned short> card_repetitions = _countRepeatedCards();
    const bool three_of_a_kind =
        std::find(card_repetitions.begin(), card_repetitions.end(), 3) !=
        card_repetitions.end();
    const bool one_pair =
        std::find(card_repetitions.begin(), card_repetitions.end(), 2) !=
        card_repetitions.end();

    if (_cards[0].hasRank(Card::Rank::Ten) and consecutive_values and
        all_same_suit)
      return Hand::Rank::RoyalFlush;
    else if (consecutive_values and all_same_suit)
      return Hand::Rank::StraightFlush;
    else if (std::find(card_repetitions.begin(), card_repetitions.end(), 4) !=
             card_repetitions.end())
      return Hand::Rank::FourOfAKind;
    else if (three_of_a_kind and one_pair)
      return Hand::Rank::FullHouse;
    else if (all_same_suit)
      return Hand::Rank::Flush;
    else if (consecutive_values)
      return Hand::Rank::Straight;
    else if (three_of_a_kind)
      return Hand::Rank::ThreeOfAKind;
    else if (std::find(
                 std::find(card_repetitions.begin(), card_repetitions.end(), 2),
                 card_repetitions.end(), 2) != card_repetitions.end())
      return Hand::Rank::TwoPairs;
    else if (one_pair)
      return Hand::Rank::OnePair;
    else
      return Hand::Rank::HighCard;
  }

  const std::vector<Card> _cards;
  const Hand::Rank _rank;
};

int main() {
  Card card1{Card::Rank::Ace, Card::Suit::Hearts},
      card2{Card::Rank::King, Card::Suit::Diamonds},
      card3{Card::Rank::Ace, Card::Suit::Diamonds},
      card4{Card::Rank::King, Card::Suit::Spades},
      card5{Card::Rank::Ten, Card::Suit::Diamonds};

  // quick test the classes, verify correct output
  std::cout << std::boolalpha;
  std::cout << card1 << " < " << card2 << " = " << (card1 < card2) << std::endl;
  std::cout << card3 << " < " << card4 << " = " << (card3 < card4) << std::endl
            << std::endl;

  std::cout << Hand{card1, card2, card3, card4, card5} << std::endl;
}
