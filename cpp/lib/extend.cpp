#include "extend.hpp"
#include "smith_waterman.hpp"

#define MIN(v1, v2) (((v1) > (v2)) ? (v2) : (v1))
#define MAX(v1, v2) (((v1) < (v2)) ? (v2) : (v1))

/* 
 *        ex) Query: G'TC'TGAA'CT'GAGC
 *            Data:  AG'TC'TGATGA'CT'GGGGAACTCGA
 *            Left Word:  'TC'
 *            Right Word: 'CT'
 * 
 *            Steps:
 *          1. Query: G'TC'                 -> score high enough? (extend left)
 *             Data:  G'TC'
 *          2. Query: G'TC'T                -> score high enough? (extend right)
 *             Data: G'TC'T
 *          3. Query: G'TC'TGAA             -> score high enough? (extend right more...)
 *             Data:  G'TC'TGAT
 *          4. Query: G'TC'TGAA--           -> score high enough? (add gaps)
 *             Data:  G'TC'TGATGA
 *          5. Query: G'TC'TGAA--'CT'       -> score high enough? (add right word)
 *             Data:  G'TC'TGATGA'CT'
 *          6. Query: G'TC'TGAA--'CT'GAGC   -> score high enough? (extend right more...)
 *             Data:  G'TC'TGATGA'CT'GGGG
 *          7. Done!
 */

std::string extend_and_score(AdjacentPair pair,
                              std::string query,
                              std::string data,
                              int32_t match,
                              int32_t mismatch,
                              int32_t gap,
                              int32_t minscore,
                              bool score,
                              bool printing)
{
    // find left most indices
	int32_t dleftindex  = MIN(pair.dindex1, pair.dindex2);
	int32_t qleftindex  = MIN(pair.qindex1, pair.qindex2);
	int32_t drightindex = MAX(pair.dindex1, pair.dindex2);
	int32_t qrightindex = MAX(pair.qindex1, pair.qindex2);

    // build string
    std::string qextended = query.substr(qleftindex, pair.length);
    std::string dextended = data.substr(dleftindex, pair.length);

    // extend left
	int32_t qexindex = qleftindex;
	int32_t dexindex = dleftindex;
    while (qexindex - 1 >= 0 && dexindex - 1 >= 0) {
		qexindex--; dexindex--;
        qextended = query[qexindex] + qextended;
        dextended = data[dexindex] + dextended;
        if (score && smith_waterman(qextended, dextended, match, mismatch, gap, true) < minscore)
        {
			return Blastn::Invalid;
        }
    }
	
    // extend left pair to the right
    qexindex = qleftindex + pair.length - 1;
    dexindex = dleftindex + pair.length - 1;
    while (qexindex + 1 < qrightindex) {
		qexindex++; dexindex++;
        qextended = qextended + query[qexindex];
        dextended = dextended + data[dexindex];
    }

    // extend right with gaps until qextended aligns with data
    while (dexindex + 1 < drightindex) {
		qexindex++; dexindex++;
        qextended = qextended + Blastn::SGap;
        dextended = dextended + data[dexindex];
    }

    // append the right pair
    qextended = qextended + query.substr(qrightindex, pair.length);
    dextended = dextended + data.substr(drightindex, pair.length);

    // extend right
    qexindex = qrightindex + pair.length - 1;
    dexindex = drightindex + pair.length - 1;
    while (qexindex + 1 < query.size() && dexindex + 1 < data.size()) {
		qexindex++; dexindex++;
        qextended = qextended + query[qexindex];
        dextended = dextended + data[dexindex];
        if (score && smith_waterman(qextended, dextended, match, mismatch, gap, true) < minscore)
        {
			return Blastn::Invalid;
        }
    }

    if (printing) {
        std::cout << "Data Ext:\t" << dextended << std::endl;
        std::cout << "Quer Ext:\t" << qextended << std::endl;
    }
    return qextended;
}