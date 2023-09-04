#pragma once

#include <iterator>

template <typename It1, typename It2>
class ZippedIterator {
public:
    ZippedIterator(){
    }
    ZippedIterator(It1& it1, It2& it2) {
        it1_ = it1;
        it2_ = it2;
    }
    ZippedIterator operator++() {
        ++it1_;
        ++it2_;
        return *this;
    }
    bool operator==(const ZippedIterator& other) const {
        return it1_ == other.it1_ && it2_ == other.it2_;
    }
    bool operator!=(const ZippedIterator& other) const {
        return !(*this == other);
    }
    auto operator*() {
        return std::make_pair(*it1_, *it2_);
    }
private:
    It1 it1_;
    It2 it2_;
};
template<typename T1, typename T2>
class Zipped {
public:
    Zipped() {
    }
    ZippedIterator<T1, T2> begin() {
        return begin_;
    }
    ZippedIterator<T1, T2> end() {
        return end_;
    }
    void MakeBegin(T1 it1, T2 it2) {
        begin_ = ZippedIterator<T1, T2>(it1, it2);
    }
    void MakeEnd(T1 it1, T2 it2) {
        end_ = ZippedIterator<T1, T2>(it1, it2);
    }

private:
    ZippedIterator<T1, T2> begin_ = ZippedIterator<T1, T2>();
    ZippedIterator<T1, T2> end_ = ZippedIterator<T1, T2>();
};
template <typename Sequence1, typename Sequence2>
auto Zip(const Sequence1& sequence1, const Sequence2& sequence2) {
    auto a_begin = std::begin(sequence1);
    auto b_begin = std::begin(sequence2);
    auto a_end = std::end(sequence1);
    auto b_end = std::end(sequence2);
    Zipped<decltype(a_begin), decltype(b_begin)> res;
    res.MakeBegin(a_begin, b_begin);
    while (a_begin != a_end && b_begin != b_end) {
        ++a_begin;
        ++b_begin;
    }
    res.MakeEnd(a_begin, b_begin);
    return res;
}
