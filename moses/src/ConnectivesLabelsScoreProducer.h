// $Id$

#ifndef moses_ConnectivesLabelsScoreProducer_h
#define moses_ConnectivesLabelsScoreProducer_h

#include "FeatureFunction.h"

namespace Moses
{

/** Binary feature to detect presence of instances of:
 * (sourceConnective, Label, targetConnective)
 */
class ConnectivesLabelsScoreProducer : public StatelessFeatureFunction
{
public:
//	ConnectivesLabelsScoreProducer();
	ConnectivesLabelsScoreProducer(ScoreIndexManager &scoreIndexManager);


  std::string GetScoreProducerDescription(unsigned) const;
  std::string GetScoreProducerWeightShortName(unsigned) const;
  size_t GetNumScoreComponents() const;

  virtual void Evaluate(
    const TargetPhrase& phrase,
    ScoreComponentCollection* out) const;
};

}

#endif
