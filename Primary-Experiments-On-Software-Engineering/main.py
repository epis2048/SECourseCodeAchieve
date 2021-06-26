#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#

from game_timer import GameTimer
from life_game import LifeGame
import profile


def main():
    map_rows = 40
    map_cols = 80
    timer_interval = 0
    game = LifeGame(map_rows, map_cols, possibility=0.5)
    game.print_map()
    timer = GameTimer(game.game_cycle, timer_interval)
    timer.start()
    return 0


if __name__ == '__main__':
    try:
        profile.run("main()")
    except KeyboardInterrupt:
        exit(0)
