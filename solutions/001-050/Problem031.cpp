/* Coin sums
 * In England the currency is made up of pound, £, and
 * pence, p, and there are eight coins in general circulation:
 *
 *      1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).
 *
 * It is possible to make £2 in the following way:
 *
 *      1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
 *
 * How many different ways can £2 be made using any number of
 * coins? */

#include <iostream>
#include <vector>
#include <algorithm>

unsigned countSubsetCombos(const std::pair<std::vector<uint8_t>,
        std::vector<uint8_t>> &set,
        unsigned subsetIdx);

int main() {
    // value of ea. coin type in pence
    const std::vector<uint8_t> penceVal
            {1,2,5,10,20,50,100,200};

    // coins needed for 200 pence equivalent
    const std::vector<uint8_t> coinLimit
            {200,100,40,20,4,2,1};

    // State space for set of coins,
    // paired for convinience
    const std::pair< std::vector<uint8_t>,
            std::vector<uint8_t> > coinSet
            {penceVal, coinLimit};

    /* Solution involves iterating over the num
     * of coins, starting with its max value. For
     * example, we begin with a single 2 pound coin.
     * Nothing more is needed to reach the target
     * (200 p), so we move on to the 1 pound coin. We
     * begin with the max value, 2 coins, which needs
     * nothing else. We decrease to 1 coin, and now we
     * iterate over the lesser value coins, adding until
     * we reach the target value. This continues until
     * we reach the 1 pence coin. Each combination that
     * equals the target is recorded. */

    // it's known that 200 1-pence coins
    // makes 200 pence, no more, no less
    auto combos = 1u;

    // iterate over coin type, forming subsets,
    // and count combos; start with 2 pence coin
    for( auto i=1u; i<penceVal.size(); ++i )
        combos += countSubsetCombos(coinSet, i);

    std::cout << "result: " << combos << std::endl;
}

void
distributeLeftovers(const std::pair<std::vector<uint8_t>,
        std::vector<uint8_t>> &set, unsigned &smallerIdx, uint8_t &leftover,
                    const unsigned &rep) {

    if( --smallerIdx != 0 ) distributeLeftovers(set, smallerIdx, leftover, rep);

    return;
}

unsigned countSubsetCombos(const std::pair<std::vector<uint8_t>,
        std::vector<uint8_t>> &set,
                           unsigned subsetIdx) {
    /* Unique coin combinations, with maximum value of 200 pence,
     * are formed from a subset of coin types. This subet
     * consists of the coin type corresponding with subsetIdx and
     * all lesser valued coins. The combinations begin with the
     * largest amount of the largest coin type. Further iterations
     * decrements this amount and uses lesser valued coins to
     * attempt to reach 200 pence. This repeats until the largest
     * coin type has a count of one. */

    static const uint8_t target = 200u;
    auto comboCount = 0u;

    // to reduce verbosity hereafter
    const auto &value = set.first;
    const auto &limit = set.second;

    // reverse iterate over largest coin count
    for( auto lcc=limit[subsetIdx]; lcc>0; --lcc ) {
        auto leftoverVal = static_cast<uint8_t>
                (target - lcc * value[subsetIdx]);
        auto smallerIdx = subsetIdx - 1;

        // repeat until the adjacent smaller coin value
        // reaches, but not exceeds, the leftover value
        auto reps = leftoverVal % value[smallerIdx];
        for( auto i=0u; i<=reps; ++i )
            distributeLeftovers(set, smallerIdx, leftoverVal, i);
        if( leftoverVal==0 ) ++comboCount;
    }

    return comboCount;
}
