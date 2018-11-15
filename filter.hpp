
template <typename F> class Filter;

template <typename F> Filter(F) -> Filter<F>;

//ラムダ式や関数を保持するだけのクラス(Filterの実体)
template <class F> class Filter {
	F filter_func;
	public:
	Filter(F filter_func) : filter_func(filter_func) {}

	template<class T> auto operator()(const T& param) const {
		return filter_func(param);
	}
};

// (片方がFilterなら適用)
template <class T, class F> auto inline operator|(const T& target, const Filter<F>& filter) {
	return filter(target);
}

// (両方がFilterなら合成)
template <class T, class U> auto inline operator|(const Filter<T>& filter1, const Filter<U>& filter2) {
	return Filter{
		[=](auto param){
			return filter2(filter1(param));
		}
	};
}

