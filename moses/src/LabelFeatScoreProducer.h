// $Id$

#ifndef moses_ConnectivesLabelsScoreProducer_h
#define moses_ConnectivesLabelsScoreProducer_h

#include "FeatureFunction.h"

namespace Moses
{

/** Binary feature to detect presence of instances of:
 * (sourceConnective, Label, targetConnective)
 */
class LabelFeatScoreProducer : public StatelessFeatureFunction
{
public:
//	ConnectivesLabelsScoreProducer();
	LabelFeatScoreProducer(ScoreIndexManager &scoreIndexManager);


  std::string GetScoreProducerDescription() const;
  std::string GetScoreProducerWeightShortName() const;
  size_t GetNumScoreComponents() const;

  virtual void Evaluate(
    const TargetPhrase& phrase,
    ScoreComponentCollection* out) const;
};

}

#endif
