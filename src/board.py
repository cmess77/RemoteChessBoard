import piece

class Board():
    '''
    This will handle printing the board to the command line
    '''
    
    def __init__(self):
        '''
        Creates the chess board representation as a 2D list.
        '''
        self.board = []

        for i in range(8):
            self.board.append([None] * 8)

        self.board[7][0] = piece.Rook(True)
        self.board[7][1] = piece.Knight(True)
        self.board[7][2] = piece.Bishop(True)
        self.board[7][3] = piece.Queen(True)
        self.board[7][4] = piece.King(True)
        self.board[7][5] = piece.Bishop(True)
        self.board[7][6] = piece.Knight(True)
        self.board[7][7] = piece.Rook(True)

        for i in range(8):
            self.board[1][i] = piece.Pawn(True)
        
        self.board[0][0] = piece.Rook(False)
        self.board[0][1] = piece.Knight(False)
        self.board[0][2] = piece.Bishop(False)
        self.board[0][3] = piece.Queen(False)
        self.board[0][4] = piece.King(False)
        self.board[0][5] = piece.Bishop(False)
        self.board[0][6] = piece.Knight(False)
        self.board[0][7] = piece.Rook(False)

        for i in range(8):
            self.board[1][i] = piece.Pawn(False)
    
    def display_board(self):
        temp = ""
        for i in range(33):
            temp += "*"
        print(temp)
        for i in range(len(self.board)):
            tmp_str = "|"
            for j in self.board[i]:
                if j == None or j.name == 'GP':
                    tmp_str += "   |"
                elif len(j.name) == 2:
                    tmp_str += (" " + str(j) + "|")
                else:
                    tmp_str += (" " + str(j) + " |")
            print(tmp_str)
        temp = ""
        for i in range(33):
            temp += "*"
        print(temp)
