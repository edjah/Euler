#pragma once

#include <set>
#include <unordered_map>
#include <utility>

template <typename KeyT, typename WeightT>
class priority_queue {
  public:
    void insert(const KeyT& key, const WeightT& weight) {
        queue_.insert({weight, key});
        map_.insert({key, weight});
    }

    void update_key(const KeyT& key, const WeightT& weight) {
        auto it = map_.find(key);
        if (it != map_.end()) {
            queue_.erase({it->second, it->first});
            queue_.insert({weight, it->first});
            it->second = weight;
        } else {
            queue_.insert({weight, key});
            map_.insert({key, weight});
        }
    }

    std::pair<KeyT, WeightT> top() {
        if (queue_.empty()) {
            throw std::runtime_error("Top of empty priority_queue");
        }
        auto it = queue_.begin();
        return {it->second, it->first};
    }

    std::pair<KeyT, WeightT> pop_top() {
        auto t = top();
        pop();
        return t;
    }

    void pop() {
        if (!queue_.empty()) {
            auto it = queue_.begin();
            map_.erase(it->second);
            queue_.erase(it);
        }
    }

  private:
    std::set<std::pair<WeightT, KeyT>> queue_;
    std::unordered_map<KeyT, WeightT> map_;
};
