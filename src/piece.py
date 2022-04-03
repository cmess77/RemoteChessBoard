from tkinter import TOP
from tracemalloc import start


blocked = "There's a piece in the way."
illegal_move = "This move isn't possible"

class Piece():
    '''

    '''

    def __init__(self, color):
        self.name = ""
        self.color = color
    
    def is_move_valid(self, board, start_pos, to_pos):
        return False
    
    def is_white(self):
        return self.color
    
    def __str__(self):
        if self.color:
            return self.name
        else:
            return '\033[94m' + self.name + '\033[0m'

class Rook(Piece):
    def __init__(self, color, first_move = True):
        super().__init__(color)
        self.name = "R"
        self.first_move = first_move    
    
    def is_move_valid(self, board, start_pos, to_pos):
        if start_pos[0] == to_pos[0] or start_pos[1] == to_pos[1]:
            return check_up_down(board, start_pos, to_pos)
        print(illegal_move)
        return False

class Knight(Piece):
    def __init__(self, color):
        super().__init__(color)
        self.name = "N"

    def is_move_valid(self, board, start_pos, to_pos):
        if abs(start_pos[0] - to_pos[0]) == 2 and abs(start[1] - to_pos[1]) == 1:
            return True
        if abs(start_pos[0] - to_pos[0]) == 1 and abs(start[1] - to_pos[1]) == 2:
            return True
        print(illegal_move)
        return False

class Bishop(Piece):
    def __init__(self, color):
        super().__init__(color)
        self.name = "B"
    
    def is_move_valid(self, board, start_pos, to_pos):
        return check_diagonal(board, start_pos, to_pos)

class Queen(Piece):
    def __init__(self, color):
        super().__init__(color)
        self.name = "Q"

    def is_move_valid(self, board, start_pos, to_pos):
        if abs(start_pos[0] - to_pos[0]) == abs(start_pos[1] - to_pos[1]):
            return check_diagonal(board, start_pos, to_pos)

        elif start_pos[0] == to_pos[0] or start_pos[1] == to_pos[1]:
            return check_up_down(board, start_pos, to_pos)

        print(illegal_move)
        return False

class King(Piece):
    def __init__(self, color, first_move = True):
        super().__init__(color)
        self.name = "K"
        self.first_move = first_move
    def can_castle(self, board, start, to, right):
        # white castling king-side
        if self.color and right:
            # checking if under attack by a knight in any of the 
            # possible squares
            knight_attack = check_knight(self.color, board, (6, 3)) and \
                check_knight(self.color, board, (6, 4)) and \
                check_knight(self.color, board, (5, 4)) and \
                check_knight(self.color, board, (5, 5)) and \
                check_knight(self.color, board, (5, 6)) and \
                check_knight(self.color, board, (5, 7)) and \
                check_knight(self.color, board, (6, 7))
            if not knight_attack: 
                return False

            # checking if under attack by a piece on the diagonal
            diags = check_diag_castle(self.color, board, (7, 5), (2, 0)) and \
                check_diag_castle(self.color, board, (7, 6), (1, 0)) and \
                check_diag_castle(self.color, board, (7, 5), (5, 7)) and \
                check_diag_castle(self.color, board, (7, 6), (6, 7))
            if not diags:
                return False

            # checking if under attack by a piece  
            # the orthogonal directions
            updowns = check_updown_castle(self.color, board, (7, 5), (0, 5)) and \
                check_updown_castle(self.color, board, (7, 6), (0, 6))
            if not updowns: 
                return False

            board.board[to[0]][to[1]] = King(True, False) 
            board.board[to[0]][to[1]-1] = Rook(True, False) 
            board.board[start[0]][start[1]] = None
            board.board[7][7] = None
            return True
        
        # White castling queen-side
        if self.color and not right:
            # checking if under attack by a knight in any of the 
            # possible squares
            knight_attack = check_knight(self.color, board, (6, 0)) and \
                check_knight(self.color, board, (6, 1)) and \
                check_knight(self.color, board, (5, 1)) and \
                check_knight(self.color, board, (5, 2)) and \
                check_knight(self.color, board, (5, 3)) and \
                check_knight(self.color, board, (5, 4)) and \
                check_knight(self.color, board, (6, 4)) and \
                check_knight(self.color, board, (6, 5)) 
            if not knight_attack: 
                return False

            # checking if under attack by a piece on the diagonal
            diags = check_diag_castle(self.color, board, (7, 2), (5, 0)) and \
                check_diag_castle(self.color, board, (7, 3), (4, 0)) and \
                check_diag_castle(self.color, board, (7, 2), (2, 7)) and \
                check_diag_castle(self.color, board, (7, 3), (3, 7))
            if not diags:
                return False

            # checking if under attack by a piece  
            # the orthogonal directions
            updowns = check_updown_castle(self.color, board, (7, 2), (0, 2)) and \
                check_updown_castle(self.color, board, (7, 3), (0, 3))
            if not updowns: 
                return False
            
            board.board[to[0]][to[1]] = King(True, False) 
            board.board[to[0]][to[1]+1] = Rook(True, False)
            board.board[start[0]][start[1]] = None
            board.board[7][0] = None

            return True

        # Black castling king-side
        if not self.color and right:
            # checking if under attack by a knight in any of the 
            # possible squares
            knight_attack = check_knight(self.color, board, (1, 3)) and \
                check_knight(self.color, board, (1, 4)) and \
                check_knight(self.color, board, (1, 7)) and \
                check_knight(self.color, board, (2, 4)) and \
                check_knight(self.color, board, (2, 5)) and \
                check_knight(self.color, board, (2, 6)) and \
                check_knight(self.color, board, (2, 7))
            if not knight_attack: 
                return False

            # checking if under attack by a piece on the diagonal
            diags = check_diag_castle(self.color, board, (0, 5), (5, 0)) and \
                check_diag_castle(self.color, board, (0, 6), (6, 0)) and \
                check_diag_castle(self.color, board, (0, 5), (2, 7)) and \
                check_diag_castle(self.color, board, (0, 6), (1, 7))
            if not diags:
                return False

            # checking if under attack by a piece  
            # the orthogonal directions
            updowns = check_updown_castle(self.color, board, (0, 2), (7, 2)) and \
                check_updown_castle(self.color, board, (0, 3), (7, 3))
            if not updowns: 
                return False

            board.board[to[0]][to[1]] = King(False, False)
            board.board[to[0]][to[1]-1] = Rook(False, False) 
            board.board[start[0]][start[1]] = None
            board.board[0][7] = None

            return True
        
        # Black castling queen-side
        if not self.color and not right:
            # checking if under attack by a knight in any of the 
            # possible squares
            knight_attack = check_knight(self.color, board, (1, 0)) and \
                check_knight(self.color, board, (1, 1)) and \
                check_knight(self.color, board, (1, 4)) and \
                check_knight(self.color, board, (1, 5)) and \
                check_knight(self.color, board, (2, 1)) and \
                check_knight(self.color, board, (2, 2)) and \
                check_knight(self.color, board, (2, 3)) and \
                check_knight(self.color, board, (2, 4)) 
            if not knight_attack: 
                return False

            # checking if under attack by a piece on the diagonal
            diags = check_diag_castle(self.color, board, (0, 2), (5, 7)) and \
                check_diag_castle(self.color, board, (0, 3), (4, 7)) and \
                check_diag_castle(self.color, board, (0, 2), (2, 0)) and \
                check_diag_castle(self.color, board, (0, 3), (3, 0))
            if not diags:
                return False

            # checking if under attack by a piece  
            # the orthogonal directions
            updowns = check_updown_castle(self.color, board, (0, 2), (7, 2)) and \
                check_updown_castle(self.color, board, (0, 3), (7, 3))
            if not updowns: 
                return False

            board.board[to[0]][to[1]] = King(False, False)
            board.board[to[0]][to[1]+1] = Rook(False, False) 
            board.board[start[0]][start[1]] = None
            board.board[0][0] = None

            return True
    def is_move_valid(self, board, start_pos, to_pos):
        # checking castling move
        if self.first_move and abs(start_pos[1] - to_pos[1]) == 2 and start_pos[0] - to_pos[0] == 0:
            return self.can_castle(board, start_pos, to_pos, to_pos[1] - start[1] > 0)

        # checking if moving only 1 square in any direction
        if abs(start_pos[0] - to_pos[0]) == 1 or start_pos[0] - to_pos[0] == 0:
            if start_pos[1] - to_pos[1] == 0 or abs(start_pos[1] - to_pos[1]) == 1:
                self.first_move = False
                return True
        
        print(illegal_move)
        return False

class Pawn(Piece):
    def __init__(self, color):
        super().__init__(color)
        self.name = "P"
        self.first_move = True

    def is_valid_move(self, board, start, to):
        # white pawns
        if self.color:
            # diagonal moves
            if start[0] == to[0] + 1 and (start[1] == to[1] + 1 or start[1] == to[1] - 1):
                if board.board[to[0]][to[1]] != None:
                    self.first_move = False
                    return True
                print("Cannot move diagonally unless taking.")
                return False

            # vertical moves
            if start[1] == to[1]:
                if (start[0] - to[0] == 2 and self.first_move) or (start[0] - to[0] == 1):
                    for i in range(start[0] - 1, to[0] - 1, -1):
                        if board.board[i][start[1]] != None:
                            print(blocked)
                            return False
                print("Invalid move" + " or " + "Cannot move forward twice if not first move.")
                return False
            print(illegal_move)
            return False

        else:
            if start[0] == to[0] - 1 and (start[1] == to[1] - 1 or start[1] == to[1] + 1):
                if board.board[to[0]][to[1]] != None:
                    self.first_move = False
                    return True
                print(blocked)
                return False
            if start[1] == to[1]:
                if (to[0] - start[0] == 2 and self.first_move) or (to[0] - start[0] == 1):
                    for i in range(start[0] + 1, to[0] + 1):
                        if board.board[i][start[1]] != None:
                            print(blocked_path)
                            return False
                    # insert a GhostPawn
                    if to[0] - start[0] == 2:
                        board.board[start[0] + 1][start[1]] = GhostPawn(self.color)
                        board.black_ghost_piece = (start[0] + 1, start[1])
                    self.first_move = False
                    return True
                print("Invalid move" + " or " + "Cannot move forward twice if not first move.")
                return False
            print(incorrect_path)
            return False
