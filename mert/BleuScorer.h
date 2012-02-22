#ifndef MERT_BLEU_SCORER_H_
#define MERT_BLEU_SCORER_H_

#include <iostream>
#include <string>
#include <vector>

#include "Types.h"
#include "ScoreData.h"
#include "Scorer.h"
#include "ScopedVector.h"

using namespace std;

/**
 * Bleu scoring
 */
class BleuScorer: public StatisticsBasedScorer
{
public:
  explicit BleuScorer(const string& config = "");
  ~BleuScorer();

  virtual void setReferenceFiles(const vector<string>& referenceFiles);
  virtual void prepareStats(size_t sid, const string& text, ScoreStats& entry);
  virtual float calculateScore(const vector<int>& comps) const;

  virtual size_t NumberOfScores() const {
    return 2 * kLENGTH + 1;
  }

private:
  enum ReferenceLengthType {
    AVERAGE,
    SHORTEST,
    CLOSEST,
  };

  //Used to construct the ngram map
  struct CompareNgrams {
    bool operator()(const vector<int>& a, const vector<int>& b) const {
      size_t i;
      const size_t as = a.size();
      const size_t bs = b.size();
      for (i = 0; i < as && i < bs; ++i) {
        if (a[i] < b[i]) {
          //cerr << "true" << endl;
          return true;
        }
        if (a[i] > b[i]) {
          //cerr << "false" << endl;
          return false;
        }
      }
      //entries are equal, shortest wins
      return as < bs;;
    }
  };

  typedef map<vector<int>,int,CompareNgrams> counts_t;
  typedef map<vector<int>,int,CompareNgrams>::iterator counts_iterator;
  typedef map<vector<int>,int,CompareNgrams>::const_iterator counts_const_iterator;

  /**
   * Count the ngrams of each type, up to the given length in the input line.
   */
  size_t countNgrams(const string& line, counts_t& counts, unsigned int n);

  void dump_counts(counts_t& counts) const;

  const int kLENGTH;
  ReferenceLengthType m_ref_length_type;

  // data extracted from reference files
  ScopedVector<counts_t> m_ref_counts;
  vector<vector<size_t> > m_ref_lengths;

  // no copying allowed
  BleuScorer(const BleuScorer&);
  BleuScorer& operator=(const BleuScorer&);
};

#endif  // MERT_BLEU_SCORER_H_
