//
// oh_god_why_do_you_not_have_a_hash_for_pairs.h
// 2026-034-05
// daichess
//

#ifndef oh_god_why_do_you_not_have_a_hash_for_pairs_h
#define oh_god_why_do_you_not_have_a_hash_for_pairs_h

// snagged this snippet from reddit
template<class A,class B>
struct std::hash<std::pair<A,B>>{
	size_t operator() (const pair<A,B>& p) const {
		return std::rotl(hash<A>{}(p.first),1) ^
			   hash<B>{}(p.second);
	}
};

#endif /* oh_god_why_do_you_not_have_a_hash_for_pairs.h */