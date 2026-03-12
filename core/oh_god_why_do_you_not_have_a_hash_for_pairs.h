//
// oh_god_why_do_you_not_have_a_hash_for_pairs.h
// 2026-034-05
// daichess
//

#ifndef oh_god_why_do_you_not_have_a_hash_for_pairs_h
#define oh_god_why_do_you_not_have_a_hash_for_pairs_h
#include <utility>
#include <functional>

// snagged this snippet from reddit
template<typename T> struct cust_hash;
template<class A,class B> struct cust_hash<std::pair<A,B>>{
	size_t operator() (const std::pair<A,B>& p) const {
		return std::rotl(std::hash<A>{}(p.first),5) ^ std::hash<B>{}(p.second);
	}
};

template<class A,class B,class C, class D> struct cust_hash<std::pair<std::pair<A,B>,std::pair<C,D>>>{
	size_t operator() (const std::pair<std::pair<A,B>,std::pair<C,D>>& p) const {
		return std::rotl(std::hash<A>{}(p.first.first),15) ^ std::rotl(std::hash<B>{}(p.first.second),10) ^ std::rotl(std::hash<C>{}(p.second.first),5) ^ std::hash<D>{}(p.second.second);
	}
};

typedef cust_hash<std::pair<int,int>> p_hash;
typedef cust_hash<std::pair<std::pair<int,int>,std::pair<int,int>>> q_hash;

#endif /* oh_god_why_do_you_not_have_a_hash_for_pairs.h */