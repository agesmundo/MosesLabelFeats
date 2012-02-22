// $Id$

#include "LabelFeatScoreProducer.h"
#include "StaticData.h"


/*del?
#include "util/check.hh"
#include "FFState.h"
#include "WordsRange.h"
#include "TranslationOption.h"*/

namespace Moses
{

LabelFeatScoreProducer::LabelFeatScoreProducer(ScoreIndexManager &scoreIndexManager){
//	const_cast<ScoreIndexManager&> (StaticData::Instance().GetScoreIndexManager()).AddScoreProducer(this);
//	const_cast<StaticData&>(StaticData::Instance()).SetWeightsForScoreProducer(this, weights);
	scoreIndexManager.AddScoreProducer(this);
}

//ConnectivesLabelsScoreProducer::ConnectivesLabelsScoreProducer(ScoreIndexManager &scoreIndexManager)
//{
//  scoreIndexManager.AddScoreProducer(this);
//}

std::string LabelFeatScoreProducer::GetScoreProducerDescription(unsigned) const
{
  return "ConnectivesLabels";
}

std::string LabelFeatScoreProducer::GetScoreProducerWeightShortName(unsigned) const
{
  return "cntlbl";
}

size_t LabelFeatScoreProducer::GetNumScoreComponents() const
{
//  This function returns returns the number of features that the component uses
// |sourceConnectives| x |labels| x |targetConnectives|)
  return 1; //TODO : need to access list of possible connectives (source/target) and label set
}

void LabelFeatScoreProducer::Evaluate(const TargetPhrase& tp, ScoreComponentCollection* out) const
{
	std::vector<float> scores(this->GetNumScoreComponents() ,0);

	//TODO
	//set the features observed to 1
	//TODO: need to access the source phrase and the lables in the source.

	out->Assign(this,scores);
}

}
