class CopyTest {
public:
	CopyTest(string data) : data_(data), copy_cnt(0) {
	}

	CopyTest(const CopyTest & other) {
		data_ = other.data_;
		copy_cnt = other.copy_cnt + 1;
	}

	CopyTest(CopyTest && other) noexcept {
		data_ = other.data_;
		copy_cnt = other.copy_cnt;
	}

	CopyTest& operator=(CopyTest&& other)  {
		data_ = other.data_;
		copy_cnt = other.copy_cnt;
	}

	auto begin() {
		return data_.begin();
	}

	auto end() {
		return data_.end();
	}

	string data_;
	int copy_cnt;
	using value_type = typename char;
};

bool operator==(const CopyTest & lhs, const CopyTest & rhs) {
	if (lhs.copy_cnt == rhs.copy_cnt) {
		return true;
	}
	return false;
}

bool operator<(const CopyTest & lhs, const CopyTest & rhs) {
	if (lhs.copy_cnt < rhs.copy_cnt) {
		return true;
	}