/*
 *  FeatureData.h
 *  mert - Minimum Error Rate Training
 *
 *  Created by Nicola Bertoldi on 13/05/08.
 *
 */

#ifndef MERT_FEATURE_DATA_H_
#define MERT_FEATURE_DATA_H_

using namespace std;

#include <vector>
#include <iostream>
#include <stdexcept>
#include "FeatureArray.h"

class FeatureData
{
private:
  size_t number_of_features;
  std::string features;
  bool _sparse_flag;

  map<std::string, size_t> featname2idx_; // map from name to index of features
  map<size_t, std::string> idx2featname_; // map from index to name of features

protected:
  featdata_t array_;
  idx2name idx2arrayname_; // map from index to name of array
  name2idx arrayname2idx_; // map from name to index of array

public:
  FeatureData();
  ~FeatureData() {}

  inline void clear() {
    array_.clear();
  }

  inline bool hasSparseFeatures() const {
    return _sparse_flag;
  }
  inline FeatureArray get(const std::string& idx) {
    return array_.at(getIndex(idx));
  }
  inline FeatureArray& get(size_t idx) {
    return array_.at(idx);
  }
  inline const FeatureArray& get(size_t idx) const {
    return array_.at(idx);
  }

  inline bool exists(const std::string& sent_idx) const {
    return exists(getIndex(sent_idx));
  }

  inline bool exists(int sent_idx) const {
    return (sent_idx > -1 && sent_idx < static_cast<int>(array_.size())) ? true : false;
  }

  inline FeatureStats& get(size_t i, size_t j) {
    return array_.at(i).get(j);
  }
  inline const FeatureStats&  get(size_t i, size_t j) const {
    return array_.at(i).get(j);
  }

  void add(FeatureArray& e);
  void add(FeatureStats& e, const std::string& sent_idx);

  inline size_t size() const {
    return array_.size();
  }
  inline size_t NumberOfFeatures() const {
    return number_of_features;
  }
  inline void NumberOfFeatures(size_t v) {
    number_of_features = v;
  }
  inline std::string Features() const {
    return features;
  }
  inline void Features(const std::string& f) {
    features = f;
  }

  void save(const std::string &file, bool bin=false);
  void save(ofstream& outFile, bool bin=false);
  inline void save(bool bin=false) {
    save("/dev/stdout", bin);
  }

  void load(ifstream& inFile);
  void load(const std::string &file);

  bool check_consistency() const;
  void setIndex();

  inline int getIndex(const std::string& idx) const {
    name2idx::const_iterator i = arrayname2idx_.find(idx);
    if (i != arrayname2idx_.end())
      return i->second;
    else
      return -1;
  }

  inline std::string getIndex(size_t idx) const {
    idx2name::const_iterator i = idx2arrayname_.find(idx);
    if (i != idx2arrayname_.end())
      throw runtime_error("there is no entry at index " + idx);
    return i->second;
  }

  bool existsFeatureNames() const {
    return (idx2featname_.size() > 0) ? true : false;
  }

  std::string getFeatureName(size_t idx) const {
    if (idx >= idx2featname_.size())
      throw runtime_error("Error: you required an too big index");
    map<size_t, std::string>::const_iterator it = idx2featname_.find(idx);
    if (it == idx2featname_.end()) {
      throw runtime_error("Error: specified id is unknown: " + idx);
    } else {
      return it->second;
    }
  }

  size_t getFeatureIndex(const std::string& name) const {
    map<std::string, size_t>::const_iterator it = featname2idx_.find(name);
    if (it == featname2idx_.end())
      throw runtime_error("Error: feature " + name + " is unknown");
    return it->second;
  }

  void setFeatureMap(const std::string& feat);

  /* For debugging */
  std::string ToString() const;
};

#endif  // MERT_FEATURE_DATA_H_
