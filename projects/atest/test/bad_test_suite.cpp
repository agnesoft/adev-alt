import atest;

using atest::suite;
using atest::test;

static const auto s1 = suite("Bad suite throwing int", [] { //NOLINT(cert-err58-cpp)
    throw 1;
});

static const auto s2 = suite("Bad suite throwing std::logic_error", [] { //NOLINT(cert-err58-cpp)
    throw std::logic_error{"Really bad test suite"};
});

static const auto s3 = suite("Bad test suite", [] { //NOLINT(cert-err58-cpp)
    test("Bad test throwing int", [] {
        throw 1;
    });
    
    test("Bad test throwing std::logic_error", [] {
        throw std::logic_error{"Really bad test"};
    });
});
