import os
import unittest

from dmath import is_prime, eratosthenes, prime_factors, euler_phi, gcd, cfr, approx_cfr, restricted_farey, farey, \
    number_of_summations, Dijkstra


def assertDictAlmostEqual(test_case, d0, d1):
    assert isinstance(test_case, unittest.TestCase)
    assert isinstance(d0, dict)
    assert isinstance(d1, dict)
    test_case.assertEqual(d0.keys(), d1.keys())
    for k, v in d0.items():
        test_case.assertAlmostEqual(v, d1[k])


unittest.TestCase.assertDictAlmostEqual = assertDictAlmostEqual


class TestIsPrime(unittest.TestCase):

    def test_first_ten_non_primes_are_non_prime(self):
        for x in (0, 1, 4, 6, 8, 9, 10, 12, 14, 15):
            self.assertFalse(is_prime(x))

    def test_first_ten_primes_are_prime(self):
        for x in (2, 3, 5, 7, 11, 13, 17, 19, 23, 29):
            self.assertTrue(is_prime(x))

    def test_is_prime_with_large_input(self):
        for x in (49968367, 49968371, 49968377):
            self.assertTrue(is_prime(x))
        self.assertTrue(is_prime(2**31-1))

    def test_is_not_prime_with_large_input(self):
        for x in (49968365, 49968373, 49968379):
            self.assertFalse(is_prime(x))
        self.assertFalse(is_prime(2**31-3))

    def test_is_prime_with_negative_input_raises_overflow_error(self):
        for x in (-1, -5, -33):
            with self.assertRaises(OverflowError):
                is_prime(x)


class TestEratosthenes(unittest.TestCase):

    def test_eratosthenes_up_to_ten(self):
        primes = {0: [],
                  1: [],
                  2: [2],
                  3: [2, 3],
                  4: [2, 3],
                  5: [2, 3, 5],
                  6: [2, 3, 5],
                  7: [2, 3, 5, 7],
                  8: [2, 3, 5, 7],
                  9: [2, 3, 5, 7],
                  10: [2, 3, 5, 7]}
        for number, primes_until_number in primes.items():
            self.assertEqual(eratosthenes(number), primes_until_number)

    def test_eratosthenes_for_primes_until_one_million(self):
        current_dir = os.path.dirname(__file__)
        filename = os.path.join(current_dir, "prime_list.txt")
        with open(filename, "r") as f:
            prime_list = [int(line.strip()) for line in f]
        self.assertEqual(eratosthenes(1000000), prime_list)

    def test_eratosthenes_with_negative_input_raises_overflow_error(self):
        for x in (-1, -5, -33):
            with self.assertRaises(OverflowError):
                eratosthenes(x)


class TestPrimeFactors(unittest.TestCase):

    def test_prime_factors_of_first_ten_numbers(self):
        first_ten_factors = {1: [(1, 1)],
                             2: [(2, 1)],
                             3: [(3, 1)],
                             4: [(2, 2)],
                             5: [(5, 1)],
                             6: [(2, 1), (3, 1)],
                             7: [(7, 1)],
                             8: [(2, 3)],
                             9: [(3, 2)],
                             10: [(2, 1), (5, 1)]}
        for number, factors in first_ten_factors.items():
            self.assertEqual(prime_factors(number), factors)

    def test_prime_factors_of_selected_numbers(self):
        factors_of_selected_numbers = {60: [(2, 2), (3, 1), (5, 1)],
                                       5400: [(2, 3), (3, 3), (5, 2)],
                                       1139269212: [(2, 2), (3, 4), (17, 2), (23, 3)]}
        for number, factors in factors_of_selected_numbers.items():
            self.assertEqual(prime_factors(number), factors)

    def test_prime_factors_of_zero_raises_runtime_error(self):
        with self.assertRaises(RuntimeError):
            prime_factors(0)

    def test_prime_factors_with_negative_input_raises_overflow_error(self):
        for x in (-1, -5, -33):
            with self.assertRaises(OverflowError):
                prime_factors(x)


class TestEulerPhi(unittest.TestCase):

    def test_euler_phi_of_first_ten_numbers(self):
        first_ten_phis = {0: 0,
                          1: 1,
                          2: 1,
                          3: 2,
                          4: 2,
                          5: 4,
                          6: 2,
                          7: 6,
                          8: 4,
                          9: 6}
        for number, phi in first_ten_phis.items():
            self.assertEqual(euler_phi(number), phi)

    def test_euler_phi_of_selected_numbers(self):
        selected_phis = {60: 16,
                         5400: 1440,
                         1139269212: 341877888}
        for number, phi in selected_phis.items():
            self.assertEqual(euler_phi(number), phi)

    def test_euler_phi_with_negative_input_raises_overflow_error(self):
        for x in (-1, -5, -33):
            with self.assertRaises(OverflowError):
                euler_phi(x)


class TestGcd(unittest.TestCase):

    def test_gcd_of_first_ten_pairs(self):
        first_ten_pairs = {(1, 1): 1, (1, 2): 1, (1, 3): 1, (1, 4): 1, (1, 5): 1, (1, 6): 1, (1, 7): 1, (1, 8): 1, (1, 9): 1, (1, 10): 1,
                           (2, 2): 2, (2, 3): 1, (2, 4): 2, (2, 5): 1, (2, 6): 2, (2, 7): 1, (2, 8): 2, (2, 9): 1, (2, 10): 2,
                           (3, 3): 3, (3, 4): 1, (3, 5): 1, (3, 6): 3, (3, 7): 1, (3, 8): 1, (3, 9): 3, (3, 10): 1,
                           (4, 4): 4, (4, 5): 1, (4, 6): 2, (4, 7): 1, (4, 8): 4, (4, 9): 1, (4, 10): 2,
                           (5, 5): 5, (5, 6): 1, (5, 7): 1, (5, 8): 1, (5, 9): 1, (5, 10): 5,
                           (6, 6): 6, (6, 7): 1, (6, 8): 2, (6, 9): 3, (6, 10): 2,
                           (7, 7): 7, (7, 8): 1, (7, 9): 1, (7, 10): 1,
                           (8, 8): 8, (8, 9): 1, (8, 10): 2,
                           (9, 9): 9, (9, 10): 1,
                           (10, 10): 10}
        for pair, pair_gcd in first_ten_pairs.items():
            self.assertEqual(gcd(*pair), pair_gcd)

    def test_gcd_with_zeros(self):
        self.assertEqual(gcd(0, 0), 0)
        for x in range(1, 10):
            self.assertEqual(gcd(0, x), x)
            self.assertEqual(gcd(x, 0), x)

    def test_gcd_with_negative_input_raises_overflow_error(self):
        for x in (-1, -5, -33):
            with self.assertRaises(OverflowError):
                gcd(x, 1)
            with self.assertRaises(OverflowError):
                gcd(1, x)


class TestCrf(unittest.TestCase):

    def test_cfr_for_first_ten_non_squares(self):
        cfr_up_to_fifteen = {2: ([1, 2], 1),
                             3: ([1, 1, 2], 2),
                             5: ([2, 4], 1),
                             6: ([2, 2, 4], 2),
                             7: ([2, 1, 1, 1, 4], 4),
                             8: ([2, 1, 4], 2),
                             10: ([3, 6], 1),
                             11: ([3, 3, 6], 2),
                             12: ([3, 2, 6], 2),
                             13: ([3, 1, 1, 1, 1, 6], 5)}
        for number, number_cfr in cfr_up_to_fifteen.items():
            self.assertEqual(cfr(number), number_cfr)

    def test_cfr_with_squares_raises_runtime_error(self):
        for x in range(10):
            with self.assertRaises(RuntimeError):
                cfr(x*x)

    def test_cfr_with_negative_input_raises_overflow_error(self):
        for x in (-1, -5, -33):
            with self.assertRaises(OverflowError):
                cfr(x)


class TestApproxCfr(unittest.TestCase):

    def test_approx_cfr_with_number(self):
        self.assertEqual(approx_cfr(3, d=2), (17, 12))

    def test_approx_cfr_with_cfr(self):
        self.assertEqual(approx_cfr(3, cfrac=cfr(5)), (161, 72))

    def test_approx_cfr_with_negative_input_raises_overflow_error(self):
        for x in (-1, -5, -33):
            with self.assertRaises(OverflowError):
                approx_cfr(3, d=x)


class TestRestrictedFarey(unittest.TestCase):

    def test_restricted_farey_generator(self):
        f = restricted_farey((1, 3), (1, 2), 8)
        for x in ((1, 3), (3, 8), (2, 5), (3, 7), (1, 2)):
            self.assertEqual(next(f), x)
        with self.assertRaises(StopIteration):
            next(f)

    def test_restricted_farey_of_zero_raises_runtime_error(self):
        with self.assertRaises(RuntimeError):
            next(restricted_farey((1, 3), (1, 2), 0))

    def test_restricted_farey_with_unreduced_fractions_raises_runtime_error(self):
        with self.assertRaises(RuntimeError):
            next(restricted_farey((2, 6), (1, 2), 8))
        with self.assertRaises(RuntimeError):
            next(restricted_farey((1, 3), (2, 4), 8))

    def test_restricted_farey_with_negative_input_raises_overflow_error(self):
        for x in (-1, -5, -33):
            with self.assertRaises(OverflowError):
                restricted_farey((x, 3), (1, 2), 8)
            with self.assertRaises(OverflowError):
                restricted_farey((1, x), (1, 2), 8)
            with self.assertRaises(OverflowError):
                restricted_farey((1, 3), (x, 2), 8)
            with self.assertRaises(OverflowError):
                restricted_farey((1, 3), (1, x), 8)
            with self.assertRaises(OverflowError):
                restricted_farey((1, 3), (1, 2), x)


class TestFarey(unittest.TestCase):

    def test_farey_generator(self):
        f = farey(4)
        for x in ((0, 1), (1, 4), (1, 3), (1, 2), (2, 3), (3, 4), (1, 1)):
            self.assertEqual(next(f), x)
        with self.assertRaises(StopIteration):
            next(f)

    def test_farey_up_to_ten(self):
        first_farey_sequences = {1: [(0, 1), (1, 1)],
                                 2: [(0, 1), (1, 2), (1, 1)],
                                 3: [(0, 1), (1, 3), (1, 2), (2, 3), (1, 1)],
                                 4: [(0, 1), (1, 4), (1, 3), (1, 2), (2, 3), (3, 4), (1, 1)],
                                 5: [(0, 1), (1, 5), (1, 4), (1, 3), (2, 5), (1, 2), (3, 5), (2, 3), (3, 4), (4, 5), (1, 1)],
                                 6: [(0, 1), (1, 6), (1, 5), (1, 4), (1, 3), (2, 5), (1, 2), (3, 5), (2, 3), (3, 4), (4, 5), (5, 6), (1, 1)]}
        for number, sequence in first_farey_sequences.items():
            self.assertEqual(list(farey(number)), sequence)

    def test_farey_series_of_zero_raises_runtime_error(self):
        with self.assertRaises(RuntimeError):
            next(farey(0))

    def test_farey_series_with_negative_input_raises_overflow_error(self):
        for x in (-1, -5, -33):
            with self.assertRaises(OverflowError):
                farey(x)


class TestNumberOfSummations(unittest.TestCase):

    def test_number_of_summations_with_examples(self):
        self.assertEqual(number_of_summations(range(11), 10), [1, 1, 2, 3, 5, 7, 11, 15, 22, 30, 42])
        self.assertEqual(number_of_summations([1, 2, 5, 10], 10), [1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 11])

    def test_number_of_summations_with_empty_candidates(self):
        self.assertEqual(number_of_summations([], 5), [1, 0, 0, 0, 0, 0])

    def test_number_of_summations_with_negative_input_raises_overflow_error(self):
        for x in (-1, -5, -33):
            with self.assertRaises(OverflowError):
                number_of_summations([1, 2, 3], x)
            with self.assertRaises(OverflowError):
                number_of_summations([1, x, 3], 5)


class TestDijsktra(unittest.TestCase):

    def test_dijkstra_example(self):
        edge_weights = {
            (1, 2): 7,
            (1, 3): 9,
            (1, 6): 14,
            (2, 3): 10,
            (2, 4): 15,
            (3, 4): 11,
            (3, 6): 2,
            (4, 5): 6,
            (5, 6): 9
        }
        inverted_edge_weights = {(b, a): c for (a, b), c in edge_weights.items()}
        edge_weights.update(inverted_edge_weights)

        dijkstra = Dijkstra(edge_weights)

        dijkstra.run(1)
        self.assertEqual(dijkstra.get_predecessors(), {2: 1, 3: 1, 4: 3, 5: 6, 6: 3})
        self.assertDictAlmostEqual(dijkstra.get_distances(), {1: 0, 2: 7, 3: 9, 4: 20, 5: 20, 6: 11})


if __name__ == "__main__":
    unittest.main()
