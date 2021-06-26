from unittest import TestCase
from life_game import LifeGame
import mock

from mock import patch


class TestLifeGame(TestCase):
    def setUp(self):
        self.game = LifeGame(3, 3, possibility=0.5)
        self.game.game_map.reset()

    @patch('life_game.GameMap.get_neighbor_count_map', new=mock.Mock(return_value=[[3, 3, 3], [3, 3, 3], [3, 3, 3]]))
    def test_game_cycle(self):
        self.game.game_cycle()
        for row in range(0, 3):
            for col in range(0, 3):
                self.assertEqual(1, self.game.game_map.get(row, col))

    @patch('life_game.GameMap.get_neighbor_count_map', new=mock.Mock(return_value=[[9, 9, 9], [9, 9, 9], [9, 9, 9]]))
    def test_game_cycle2(self):
        self.game.game_cycle()
        for row in range(0, 3):
            for col in range(0, 3):
                self.assertEqual(0, self.game.game_map.get(row, col))

    @patch('life_game.GameMap.get_neighbor_count_map', new=mock.Mock(return_value=[[1, 1, 1], [1, 1, 1], [1, 1, 1]]))
    def test_game_cycle3(self):
        self.game.game_cycle()
        for row in range(0, 3):
            for col in range(0, 3):
                self.assertEqual(0, self.game.game_map.get(row, col))

    @patch('random.random', new=mock.Mock(return_value=0.3))
    @patch('life_game.GameMap.get_neighbor_count_map', new=mock.Mock(return_value=[[2, 2, 2], [2, 2, 2], [2, 2, 2]]))
    def test_game_cycle4(self):
        self.game.game_map.reset()
        self.game.game_cycle()
        for row in range(0, 3):
            for col in range(0, 3):
                self.assertEqual(1, self.game.game_map.get(row, col))

    @patch('random.random', new=mock.Mock(return_value=0.7))
    @patch('life_game.GameMap.get_neighbor_count_map', new=mock.Mock(return_value=[[2, 2, 2], [2, 2, 2], [2, 2, 2]]))
    def test_game_cycle5(self):
        self.game.game_map.reset()
        self.game.game_cycle()
        for row in range(0, 3):
            for col in range(0, 3):
                self.assertEqual(0, self.game.game_map.get(row, col))

