/**
 * Description: Operation on 128bit Integer
*/

struct i128 {
	__int128 value;

	// Constructors
	i128() : value(0) {}
	i128(int x) : value(x) {}
	i128(long long x) : value(x) {}
	i128(__int128 x) : value(x) {}

	// GCD
	static i128 gcd(const i128 &a, const i128 &b) {
		__int128 x = a.value, y = b.value;
		while (y != 0) {
			__int128 temp = y;
			y = x % y;
			x = temp;
		}
		return i128(x);
	}

	i128 sqrt() const {
		if (value < 0) return i128(0); // Handle negative input
		if (value <= 1) return i128(value); // Handle 0 and 1
	
		__int128 low = 1;
		__int128 high = value;
		__int128 result = 0;
	
		while (low <= high) {
			__int128 mid = low + (high - low) / 2;
			__int128 quotient = value / mid; // Avoids overflow
	
			if (mid <= quotient) {
				// mid^2 <= value (mid is candidate)
				result = mid;
				low = mid + 1;
			} else {
				// mid^2 > value (adjust upper bound)
				high = mid - 1;
			}
		}
	
		return i128(result);
	}
	

	// Convert to string for output
	string to_string() const {
		if (value == 0) return "0";
		__int128 tmp = value;
		bool neg = tmp < 0;
		if (neg) tmp = -tmp;
		string res;
		while (tmp) {
			res += (char)('0' + tmp % 10);
			tmp /= 10;
		}
		if (neg) res += '-';
		reverse(res.begin(), res.end());
		return res;
	}

	// Convert from string for input
	static i128 from_string(const string &s) {
		__int128 res = 0;
		bool neg = false;
		size_t i = 0;
		if (s[0] == '-') {
			neg = true;
			i = 1;
		}
		for (; i < s.size(); i++) {
			res = res * 10 + (s[i] - '0');
		}
		return neg ? i128(-res) : i128(res);
	}

	// Operators
	i128 operator+(const i128 &b) const { return i128(value + b.value); }
	i128 operator-(const i128 &b) const { return i128(value - b.value); }
	i128 operator*(const i128 &b) const { return i128(value * b.value); }
	i128 operator/(const i128 &b) const { return i128(value / b.value); }
	i128 operator%(const i128 &b) const { return i128(value % b.value); }

	bool operator<(const i128 &b) const { return value < b.value; }
	bool operator>(const i128 &b) const { return value > b.value; }
	bool operator<=(const i128 &b) const { return value <= b.value; }
	bool operator>=(const i128 &b) const { return value >= b.value; }
	bool operator==(const i128 &b) const { return value == b.value; }
	bool operator!=(const i128 &b) const { return value != b.value; }

	// Input/Output
	friend ostream &operator<<(ostream &os, const i128 &b) {
		return os << b.to_string();
	}

	// Fix the conversion issue for integers (long long, int, etc.)
	friend istream &operator>>(istream &is, i128 &b) {
		string s;
		is >> s;
		b = from_string(s);
		return is;
	}
};