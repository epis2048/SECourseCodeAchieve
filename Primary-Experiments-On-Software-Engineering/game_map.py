# -*- coding: utf-8 -*-
#
from __future__ import print_function

import random
import sys



class GameMap(object):
    MAX_MAP_SIZE = 100

    def __init__(self, rows, cols):
        """Inits GameMap with row and column count."""
        assert isinstance(rows, int)
        assert isinstance(cols, int)
        assert 0 < rows <= self.MAX_MAP_SIZE
        assert 0 < cols <= self.MAX_MAP_SIZE
        self.size = (rows, cols,)
        self.cells = [[0 for col in range(cols)] for row in range(rows)]

    @property
    def rows(self):
        return self.size[0]

    @property
    def cols(self):
        return self.size[1]

    def reset(self, possibility=0.5):
        """Reset the map with random data."""
        for row in range(self.size[0]):
            for col in range(self.size[1]):
                if random.random() < possibility:
                    self.cells[row][col] = 1
                else:
                    self.cells[row][col] = 0

    def set(self, row, col, val):
        """Set specific cell in the map."""
        assert isinstance(row, int)
        assert isinstance(col, int)
        assert isinstance(val, int)
        self.cells[row][col] = val

    def get(self, row, col):
        """Set specific cell in the map."""
        assert isinstance(row, int)
        assert isinstance(col, int)
        return self.cells[row][col]

    def get_neighbor_count_map(self):
        """Get count of neighbors of every cell in the map.

        Returns:
            A grid contains every cell's neighbor count.
        """
        rtable = [[0 for col in range(self.size[1])] for row in range(self.size[0])]
        # 四个顶点
        rtable[0][0] = self.cells[0][1] + self.cells[1][1] + self.cells[1][0]
        rtable[0][col] = self.cells[1][col] + self.cells[1][col - 1] + self.cells[0][col - 1]
        rtable[row][0] = self.cells[row - 1][0] + self.cells[row][1] + self.cells[row - 1][1]
        rtable[row][col] = self.cells[row][col - 1] + self.cells[row - 1][col - 1] + self.cells[row - 1][col]
        # 四个边
        row = self.rows - 1
        for col in range(1, self.cols - 1):
            rtable[0][col] = self.cells[1][col - 1] + self.cells[1][col] + self.cells[1][col + 1] + self.cells[0][
                col - 1] + self.cells[0][col + 1]
            rtable[row][col] = self.cells[row - 1][col - 1] + self.cells[row - 1][col] + self.cells[row - 1][col + 1] + \
                               self.cells[row][col - 1] + self.cells[row][col + 1]
        col = self.cols - 1
        for row in range(1, self.rows - 1):
            rtable[row][0] = self.cells[row - 1][1] + self.cells[row][1] + self.cells[row + 1][1] + self.cells[row - 1][
                0] + self.cells[row + 1][0]
            rtable[row][col] = self.cells[row - 1][col - 1] + self.cells[row][col - 1] + self.cells[row + 1][col - 1] + \
                               self.cells[row - 1][col] + self.cells[row + 1][col]
            # rtable[row][col] = 4
        # 中间
        for row in range(1, self.rows - 1):
            for col in range(1, self.cols - 1):
                rtable[row][col] = self.cells[row - 1][col - 1] + self.cells[row - 1][col] + self.cells[row - 1][
                    col + 1]
                rtable[row][col] += self.cells[row][col - 1] + self.cells[row][col + 1]
                rtable[row][col] += self.cells[row + 1][col - 1] + self.cells[row + 1][col] + self.cells[row + 1][
                    col + 1]
        '''
        for row in range(0, self.rows):
            strr = ''
            for col in range(0, self.cols):
                strr += str(rtable[row][col]) + " "
            print strr
        print ""
        '''
        return rtable
        # return [[self.get_neighbor_count(row, col) for col in range(self.cols)] for row in range(self.rows)]

    def print_map(self, cell_maps=None, sep=' ', fd=sys.stdout):
        """Print the map to target file descriptor

        Args:
            cell_maps: mapping from cell value to a string that will be displayed.
            sep: separator between cells of the same row.
            fd: file descriptor, default standard output
        """
        if not cell_maps:
            cell_maps = ['0', '1']
        assert isinstance(cell_maps, list) or isinstance(cell_maps, dict)
        assert isinstance(sep, str)

        '''
        # ver 0
        for row in range(0, self.rows):
            strr = ''
            for col in range(0, self.cols):
                if self.cells[row][col] == 1:
                    strr += "*" + " "
                else:
                    strr += " " + " "
            print(strr)
        print("")
        
        # ver 1
        for row in range(0, self.rows):
            strr = ''
            for col in range(0, self.cols):
                if self.cells[row][col] == 1:
                    strr += "* "
                else:
                    strr += "  "
            print(strr)
        print("")
        
        # ver 2
        for row in range(0, self.rows):
            for col in range(0, self.cols):
                if self.cells[row][col] == 1:
                    print("* ", end='')
                else:
                    print("  ", end='')
            print("")
        print("")
        '''
        # ver 3
        strr = ''
        for row in range(0, self.rows):
            for col in range(0, self.cols):
                if self.cells[row][col] == 1:
                    strr += "* "
                else:
                    strr += "  "
            strr += "\n"
        print(strr)
