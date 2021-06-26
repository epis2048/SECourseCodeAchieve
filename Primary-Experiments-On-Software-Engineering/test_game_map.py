from unittest import TestCase
import mock

from mock import patch

from game_map import GameMap


class TestGameMap(TestCase):
    def setUp(self):
        self.game_map = GameMap(40, 80)

    def test_init(self):
        self.assertEqual([[0 for col in range(80)] for row in range(40)], self.game_map.cells)
        self.assertEqual((40, 80,), self.game_map.size)

    def test_rows(self):
        self.assertEqual(40, self.game_map.rows)

    def test_cols(self):
        self.assertEqual(80, self.game_map.cols)

    def test_get_set(self):
        self.game_map.set(1, 1, 1)
        self.assertEqual(1, self.game_map.get(1, 1))

    @patch('random.random', new=mock.Mock(return_value=0.1))
    def test_reset(self):
        self.game_map.reset(possibility=0.5)
        for row in range(40):
            for col in range(80):
                self.assertEqual(1, self.game_map.get(row, col))

    @patch('random.random', new=mock.Mock(return_value=0.3))
    def test_get_neighbor_count_map(self):
        self.game_map.reset(possibility=0.5)
        mapcountmap = self.game_map.get_neighbor_count_map()
        for row in range(2, 39):
            for col in range(2, 79):
                self.assertEqual(8, mapcountmap[row][col])
        self.assertEqual(3, mapcountmap[0][0])
        self.assertEqual(3, mapcountmap[0][self.game_map.cols-1])
        self.assertEqual(3, mapcountmap[self.game_map.rows-1][0])
        self.assertEqual(3, mapcountmap[self.game_map.rows-1][self.game_map.cols-1])
        for row in range(2, 39):
            self.assertEqual(5, mapcountmap[row][0])
            self.assertEqual(5, mapcountmap[row][self.game_map.cols-1])
        for col in range(2, 39):
            self.assertEqual(5, mapcountmap[0][col])
            self.assertEqual(5, mapcountmap[self.game_map.rows-1][col])

    @patch('random.random', new=mock.Mock(return_value=0.3))
    def test_print_map(self):
        self.game_map.reset(possibility=0.5)
        self.game_map.print_map()

    @patch('random.random', new=mock.Mock(return_value=0.7))
    def test_print_map2(self):
        self.game_map.reset(possibility=0.5)
        self.game_map.print_map()
