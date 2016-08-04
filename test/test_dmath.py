import unittest

from dmath import is_prime, prime_factors, eratosthenes, cfr, approx_cfr


class TestPrimeFunctions(unittest.TestCase):

    def test_is_prime(self):
        self.assertFalse(is_prime(0))
        self.assertFalse(is_prime(1))
        self.assertTrue(is_prime(2))
        self.assertTrue(is_prime(3))
        self.assertFalse(is_prime(4))
        self.assertTrue(is_prime(5))
        self.assertFalse(is_prime(6))
        self.assertTrue(is_prime(7))
        self.assertFalse(is_prime(8))
        self.assertFalse(is_prime(9))

    def test_prime_factors(self):
        self.assertEqual(prime_factors(7), [(7, 1)])
        self.assertEqual(prime_factors(9), [(3, 2)])
        self.assertEqual(prime_factors(60), [(2, 2), (3, 1), (5, 1)])

    def test_eratosthenes(self):
        self.assertEqual(eratosthenes(10), [2, 3, 5, 7])
        self.assertEqual(eratosthenes(28), [2, 3, 5, 7, 11, 13, 17, 19, 23])
        self.assertEqual(eratosthenes(29), [2, 3, 5, 7, 11, 13, 17, 19, 23, 29])
        self.assertEqual(eratosthenes(100), [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
                                             73, 79, 83, 89, 97])


class TestContinuedFractions(unittest.TestCase):

    def test_cfr(self):
        self.assertEqual(cfr(2), ([1, 2], 1))
        self.assertEqual(cfr(3), ([1, 1, 2], 2))
        self.assertEqual(cfr(7), ([2, 1, 1, 1, 4], 4))
        self.assertEqual(cfr(12), ([3, 2, 6], 2))
        self.assertEqual(cfr(13), ([3, 1, 1, 1, 1, 6], 5))

    def test_approx_cfr(self):
        self.assertEqual(approx_cfr(3, d=2), (17, 12))
        self.assertEqual(approx_cfr(3, cfrac=cfr(5)), (161, 72))


if __name__ == "__main__":
    unittest.main()
