#ifndef _BITSET_H
#define _BITSET_H

namespace sizes {
	int sizeOfInt = sizeof(int)*8;
}

template <size_t N>
class bitset 
{
public:
	class reference 
	{
	public:
		friend class bitset;
		reference& operator=(const reference&);			
		reference& operator=(bool);
		reference& flip() noexcept;
		operator bool() const {  return value;}
		bool operator~() const noexcept { return ~value; }
	private:
		bitset* bits;
		std::size_t pos;
		bool value;
	};

	bitset();
	bitset(std::string, unsigned int, unsigned int);
	friend std::ostream& operator<<(std::ostream& os,const bitset& bt){
		os << bt.toBits();
		return os;
	}
	~bitset() { delete [] arr; }
	bitset(const bitset&);
	
	bitset& set();
	bitset& set(std::size_t, bool value = true);
	bitset& reset();
	bitset& reset(int);
	bitset& flip();
	bitset& flip(size_t);

	bool all() const noexcept;
	bool any() const noexcept;
	bool none() const noexcept;

	std::size_t count() const noexcept;
	std::size_t size() { return N; }

	bitset& operator&=(const bitset&) noexcept;
	bitset& operator|=(const bitset&) noexcept;
	bitset& operator^=(const bitset&) noexcept;

	bitset operator<<(std::size_t) const noexcept;
	bitset operator>>(std::size_t) const noexcept;
	bitset& operator<<=(std::size_t) noexcept;
	bitset& operator>>=(std::size_t) noexcept;

	bool operator==(const bitset&) const noexcept;
	bool operator!=(const bitset&) const noexcept;

	reference operator[] (std::size_t);
	bool operator[](std::size_t pos) const { return isTrue(pos); }
private:
	std::string toBits() const;
	bool isTrue(int) const;
	void shiftLeft();
	void shiftRight();

	reference curRef;
	std::size_t curPos;
	int* arr = new int[N / sizes::sizeOfInt]{};
	int _size = N / sizes::sizeOfInt;
};
#endif // _BITSET_H


