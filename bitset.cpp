#include <iostream>
#include <algorithm>

#include "bitset.h"

template <size_t N>
typename bitset<N>::reference bitset<N>::operator[](std::size_t pos)
{
	curRef.pos = pos;
	curRef.value = isTrue(pos);
	return curRef;
}

template<size_t N>
typename bitset<N>::reference& bitset<N>::reference::operator=(bool value)
{
	bits->set(pos, value);
	this->value = value;
	return *this;	
}

template<size_t N>
typename bitset<N>::reference& bitset<N>::reference::operator=(const bitset<N>::reference& other)
{
	bits->set(pos, other.value);
	this->value = other.value;
	return *this;
}

template<size_t N>
typename bitset<N>::reference& bitset<N>::reference::flip() noexcept
{
	~value; 
	bits->flip(pos);
	return *this;
}

template <size_t N>
bitset<N> operator&(const bitset<N>& bitset1, const bitset<N>& bitset2)
{
	bitset<N> andBitset = bitset1;
	andBitset &= bitset2;
	return andBitset;
}

template <size_t N>
bitset<N> operator|(const bitset<N>& bitset1, const bitset<N>& bitset2)
{
	bitset<N> orBitset = bitset1;
	orBitset |= bitset2;
	return orBitset;
}

template <size_t N>
bitset<N> operator^(const bitset<N>& bitset1, const bitset<N>& bitset2)
{
	bitset<N> xorBitset = bitset1;
	xorBitset ^= bitset2;
	return xorBitset;
}
	
template <size_t N>
void bitset<N>::shiftLeft()
{
	bool a{};
	bool b{};
	for (int i = 0; i <= _size; ++i) {
		a = arr[i] & 1;
		arr[i] <<= 1;
		arr[i] |= b;
		b = a;
	}
}

template <size_t N>
void bitset<N>::shiftRight()
{
	bool a{};
	bool b{};
	for (int i = 0; i <= _size; ++i) {
		a = arr[i] & 1;
		arr[i] >>= 1;
		arr[i] |= b;
		b = a;
	}
}

template <size_t N>
bool bitset<N>::operator==(const bitset& other) const noexcept
{
	bool flag = true;
	for (int i = 0; i <= _size; ++i) {
		if (arr[i/N] != other.arr[i/N]) {
			flag = false;
		}
	}
	return flag;
}

template <size_t N>
bool bitset<N>::operator!=(const bitset& other) const noexcept
{
	return !(*this == other);
}

template <size_t N>
bitset<N> bitset<N>::operator<<(std::size_t pos) const noexcept
{
	bitset<N> shiftedBitset = *this;
	for (int i = 0; i < pos; ++i) {
		shiftedBitset.shiftLeft();
	}
	return shiftedBitset;
}

template <size_t N>
bitset<N> bitset<N>::operator>>(std::size_t pos) const noexcept
{
	bitset<N> shiftedBitset = *this;
	for (int i = 0; i < pos; ++i) {
		shiftedBitset.shiftRight();
	}
	return shiftedBitset;
}

template <size_t N>
bitset<N>& bitset<N>::operator<<=(std::size_t pos) noexcept
{
	for (int i = 0; i < pos; ++i) {
		shiftLeft();
	}
	return *this;
}

template <size_t N>
bitset<N>& bitset<N>::operator>>=(std::size_t pos) noexcept
{
	for (int i = 0; i < pos; ++i) {
		shiftRight();
	}
	return *this;
}

template <size_t N>
bitset<N>::bitset(const bitset<N>& other)
{
	arr = new int[N/sizes::sizeOfInt];
	for (int i = 0; i <= N/sizes::sizeOfInt; ++i) {
		arr[i] = other.arr[i];
	}
}

template <size_t N>
bitset<N>& bitset<N>::operator^=(const bitset<N>& other) noexcept
{
	for (int i = 0; i <= _size; ++i) {
		arr[i / N] ^= other.arr[i];
	}
	return *this;
}

template <size_t N>
bitset<N>& bitset<N>::operator|=(const bitset<N>& other) noexcept
{
	for (int i = 0; i <= _size; ++i) {
		arr[i / N] |= other.arr[i];
	}
	return *this;
}

template <size_t N>
bitset<N>& bitset<N>::operator&=(const bitset<N>& other) noexcept
{
	for (int i = 0; i <= _size; ++i) {
		arr[i / N] &= other.arr[i];
	}
	return *this;
}

template <size_t N>
bool bitset<N>::none() const noexcept
{
	bool flag = true;
	for (int i = 0; i < N; ++i) {
		if (isTrue(i)) {
			flag = false;
		}
	}
	return flag;
}

template <size_t N>
bool bitset<N>::any() const noexcept
{
	bool flag = false;
	for (int i = 0; i < N; ++i) {
		if (isTrue(i)) {
			flag = true;
		}
	}
	return flag;
}

template <size_t N>
bool bitset<N>::all() const noexcept
{
	bool flag = true;
	for (int i = 0; i < N; ++i) {
		if (!isTrue(i)) {
			flag = false;
		}
	}
	return flag;
}

template <size_t N>
std::size_t bitset<N>::count() const noexcept
{
	int trueBits = 0;
	for (int i = 0; i < N; ++i) {
		if (isTrue(i)) {
			++trueBits;
		}
	}
	return trueBits;
}

template <size_t N>
bitset<N>& bitset<N>::flip(size_t pos)
{
	if (isTrue(pos)) {
		reset(pos);
	} else {
		set(pos);
	}
	return *this;
}

template <size_t N>
bitset<N>& bitset<N>::flip()
{
	for (int i = 0; i < N; ++i) {
		if (isTrue(i)) {
			reset(i);
		} else {
			set(i);
		}
	}
	return *this;
}	

template <size_t N>
bitset<N>& bitset<N>::reset(int pos)
{
	std::string bits = toBits();
	std::reverse(bits.begin(), bits.end());
	if (bits[pos] != '0') {
	arr[pos/sizes::sizeOfInt] ^= (1 << (pos % sizes::sizeOfInt));
	}	
	return *this;
}

template <size_t N>
bitset<N>& bitset<N>::reset()
{
	for (int i = 0; i <= _size; ++i) {
		arr[i] &= 0;
	}
	return *this;
}

template <size_t N>
std::string bitset<N>::toBits() const 
{
	std::string bits{};
	for (int i = 0; i < N; ++i) {
		if (isTrue(i)) {
			bits.insert(bits.begin(), '1');
		} else {
			bits.insert(bits.begin(), '0');
		}
	}
	return bits;
}	

template <size_t N>
bool bitset<N>::isTrue(int pos) const
{
	int shifted = 1;
	return arr[pos / N] & (shifted << (pos % sizes::sizeOfInt));
}

template <size_t N>
bitset<N>& bitset<N>::set()
{
	for (int i = 0; i < N; ++i) {
		arr[i / N] |= (1 << i % sizes::sizeOfInt); 
	}
	return *this;
}

template <size_t N>
bitset<N>& bitset<N>::set(std::size_t pos, bool value)
{
	if (pos >= N) {
		throw std::out_of_range("pos >= size");
	}

	if (value == 1) {
	arr[pos / sizes::sizeOfInt] |= static_cast<int>(value) << pos % sizes::sizeOfInt;
	} else {
			reset(pos);
		}
	return *this;
}

template <size_t N>
bitset<N>::bitset()
{
	curRef.bits = this;
	for (int i = 0; i <= _size; ++i) {
		arr[i] = 0;
	}
}

