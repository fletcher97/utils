#include "Log.hpp"

#include "Testable.tpp"
#include "TestCollection.hpp"

#include "Timer.hpp"

#include <iostream>

class bad
{
public:
	bad(void) {};
	~bad(void) {};
	bool mytrue(void) {return true;};
	bool myfalse(void) {return false;};
	bool inteq(int x, int y) {return x == y;};
	bool intneq(int x, int y) {return x != y;};
	int getmsg(void) {return 404;};
	int small(int x) {if (x>9){throw std::invalid_argument("Number too big");}return x;};
};

class badtest : public flt::Testable<badtest>, bad {
public:
	badtest(void) : flt::Testable<badtest>("badtest"), bad() {
		REGISTER(badtest, test_true)
		REGISTER(badtest, test_false)
		REGISTER(badtest, test_msg)
	};

	void test_true(void) {ASSERT(mytrue())};
	void test_false(void) {ASSERT(myfalse() == false)};
	void test_msg(void) {ASSERT_EQ(getmsg(), 44)};
};

class badtest2 : public flt::Testable<badtest2>, bad {
public:
	badtest2(void) : flt::Testable<badtest2>("badtest2"), bad() {
		REGISTER(badtest2, test_true)
		REGISTER(badtest2, test_false)
		REGISTER(badtest2, test_msg)
		REGISTER(badtest2, test_small)
		REGISTER(badtest2, test_small_throw1)
		REGISTER(badtest2, test_small_throw2)
	};

	void test_true(void) {ASSERT(mytrue())};
	void test_false(void) {ASSERT_EQ(myfalse(), false)};
	void test_msg(void) {ASSERT_EQ(getmsg(), 40)};
	void test_small(void) {ASSERT_EQ(small(1), 1)};
	void test_small_throw1(void) {ASSERT_THROW(small(9),std::invalid_argument)};
	void test_small_throw2(void) {ASSERT_THROW(small(10),std::invalid_argument)};
};

static long
check_timer(long x) {
	FLT_TIME("check_timer")
	long sum = 0;
	for (long i = 0; i < x; i++) {
		sum += i;
	}
	return sum;
}

static long
check_timer_reset(long x, long reset) {
	FLT_TIME("check_timer_reset")
	long sum = 0;
	for (long i = 0; i < x; i++) {
		if (i == reset) {FLT_TIME_RESET}
		sum += i;
	}
	return sum;
}

static long
check_timer_log(long x, long reset) {
	FLT_TIME("check_timer_log")
	long sum = 0;
	for (long i = 0; i < x; i++) {
		if (i == reset) {FLT_TIME_LOG}
		sum += i;
	}
	return sum;
}

static long
check_timer_get(long x, long reset) {
	FLT_TIME("check_timer_get")
	long sum = 0;
	for (long i = 0; i < x; i++) {
		if (i == reset) {LOG_DEBUG("Halfway at: " << FLT_TIME_GET)}
		sum += i;
	}
	return sum;
}

int
main(void)
{
	FLT_TIME("main")
	ADD_TEST(badtest)
	ADD_TEST(badtest2)

	flt::TestCollection::instance().test();
	flt::TestCollection::instance().report(std::cout);

	LOG_OPEN_FILE("test1.log")

	LOG_TRACE("Message abc ....")
	LOG_DEBUG("Message abc ....")
	LOG_INFO("Message abc ....")
	LOG_WARN("Message abc ....")
	LOG_ERROR("Message abc ....")
	LOG_FATAL("Message abc ....")

	LOG_OPEN_FILE("forbiden.log")
	LOG_OPEN_FILE("timer.log")

	check_timer(1);
	check_timer(10);
	check_timer(100);
	check_timer(1000);
	check_timer(10000);
	check_timer(100000);
	check_timer(1000000);
	check_timer(10000000);
	check_timer(100000000);
	check_timer(1000000000);

	check_timer_reset(1, 0);
	check_timer_reset(10, 5);
	check_timer_reset(100, 50);
	check_timer_reset(1000, 500);
	check_timer_reset(10000, 5000);
	check_timer_reset(100000, 50000);
	check_timer_reset(1000000, 500000);
	check_timer_reset(10000000, 5000000);
	check_timer_reset(100000000, 50000000);
	check_timer_reset(1000000000, 500000000);

	check_timer_log(1, 0);
	check_timer_log(10, 5);
	check_timer_log(100, 50);
	check_timer_log(1000, 500);
	check_timer_log(10000, 5000);
	check_timer_log(100000, 50000);
	check_timer_log(1000000, 500000);
	check_timer_log(10000000, 5000000);
	check_timer_log(100000000, 50000000);
	check_timer_log(1000000000, 500000000);

	check_timer_get(1, 0);
	check_timer_get(10, 5);
	check_timer_get(100, 50);
	check_timer_get(1000, 500);
	check_timer_get(10000, 5000);
	check_timer_get(100000, 50000);
	check_timer_get(1000000, 500000);
	check_timer_get(10000000, 5000000);
	check_timer_get(100000000, 50000000);
	check_timer_get(1000000000, 500000000);

	LOG_CLOSE_FILE
	return 0;
}
