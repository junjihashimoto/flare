/**
 *	test_storage.cc
 *
 *	@author	Kiyoshi Ikehara <kiyoshi.ikehara@gree.net>
 */

#include <cppcutter.h>

#include <storage.h>

#define BSFT(r,c) ((int)((r)*37+(c)))
#define ABS(r) (((r)>=0)?(r):-(r))

using namespace std;
using namespace gree::flare;

namespace test_storage
{
	void setup()
	{
	}

	void teardown()
	{
	}

	void test_hash_algorithm_simple()
	{
		storage::hash_algorithm ha = storage::hash_algorithm_simple;
		storage::entry e;
		e.key = "";
		cut_assert_equal_int(0, e.get_key_hash_value("", ha));
		cut_assert_equal_int(55, e.get_key_hash_value("\1\2\3\4\5\6\7\10\11\12", ha));
		cut_assert_equal_int(ABS(70+108+97+114+101),	e.get_key_hash_value("Flare", ha));
		cut_assert_equal_int(0, e.get_key_hash_value("\0NOTUSED", ha));
	}

	void test_hash_algorithm_bitshift()
	{
		storage::hash_algorithm ha = storage::hash_algorithm_bitshift;
		storage::entry e;
		e.key = "";
		cut_assert_equal_int(19790217, e.get_key_hash_value("", ha));
		cut_assert_equal_int(ABS(BSFT(BSFT(BSFT(BSFT(BSFT(BSFT(19790217, 1), 2), 3), 4), 5), 6)),
												e.get_key_hash_value("\1\2\3\4\5\6", ha));
		cut_assert_equal_int(ABS(BSFT(BSFT(BSFT(BSFT(BSFT(19790217, 70), 108), 97), 114), 101)),
												e.get_key_hash_value("Flare", ha));
		cut_assert_equal_int(19790217, e.get_key_hash_value("\0NOTUSED", ha));
	}

	void test_hash_algorithm_crc32()
	{
		storage::hash_algorithm ha = storage::hash_algorithm_crc32;
		storage::entry e;
		e.key = "";
		cut_assert_equal_int(0, e.get_key_hash_value("", ha));
		cut_assert_equal_int(161824251, e.get_key_hash_value("Flare", ha));
		cut_assert_equal_int((int)(-3489101255LL&0xffffffffLL),
												e.get_key_hash_value("MINUS", ha));
		cut_assert_equal_int(0, e.get_key_hash_value("\0NOTUSED", ha));
	}

	void test_hash_algorithm_adler32()
	{
		storage::hash_algorithm ha = storage::hash_algorithm_adler32;
		storage::entry e;
		e.key = "";
		cut_assert_equal_int(1, e.get_key_hash_value("", ha));
		cut_assert_equal_int(92209643, e.get_key_hash_value("Flare", ha));
		cut_assert_equal_int((int)(-3827502261LL&0xffffffffLL),
												e.get_key_hash_value("MINUSminusMINUSminusMINUSminusMINUS", ha));
		cut_assert_equal_int(1, e.get_key_hash_value("\0NOTUSED", ha));
	}
}
// vim: foldmethod=marker tabstop=2 shiftwidth=2 noexpandtab autoindent
