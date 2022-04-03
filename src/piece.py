blocked = "There's a piece in the path."
illegal_move = 'This piece does not move in this pattern.'


def check_knight(color, board, pos):
    '''
    Check if there is a knight of the opposite 'color' at
    position 'pos' on board 'board'.
    '''
    piece = board.board[pos[0]][pos[1]]
    if piece != None and piece.color != color and piece.name == 'N':
        return False
    return True


def check_diag_castle(color, board, start_pos, to_pos): 
    '''
    Checks the diagonal path from 'start_pos' (non-inclusive) to 'to_pos' (inclusive)
    on board 'board' for any threats from the opposite 'color'
    '''
    
    if abs(start_pos[0] - to_pos[0]) != abs(start_pos[1] - to_pos[1]):
        print(illegal_move)
        return False

    x_pos =  1 if to_pos[0] - start_pos[0] > 0 else -1
    y_pos = 1 if to_pos[1] - start_pos[1] > 0 else -1

    i = start_pos[0] + x_pos
    j = start_pos[1] + y_pos
    
    exists_piece = board.board[i][j] != None
    if exists_piece and (board.board[i][j].name == 'P' or board.board[i][j].name == 'K') and \
        board.board[i][j].color != color:
        return False

    while (i <= to_pos[0] if x_pos==1 else i >= to_pos[0]):
        if exists_piece and board.board[i][j].color != color:
            if board.board[i][j].name in ['B', 'Q']: 
                return False
            else:
                return True
        if exists_piece and board.board[i][j].color == color:
            return True
        i += x_pos
        j += y_pos
        exists_piece = board.board[i][j] != None

    return True


def check_diag(board, start_pos, to_pos):
    '''
    Checks if there are no pieces along the diagonal path from
    'start_pos' (non-inclusive) to 'to_pos' (non-inclusive).
    '''

    if abs(start_pos[0] - to_pos[0]) != abs(start_pos[1] - to_pos[1]):
        print(illegal_move)
        return False

    x_pos =  1 if to_pos[0] - start_pos[0] > 0 else -1
    y_pos = 1 if to_pos[1] - start_pos[1] > 0 else -1

    i = start_pos[0] + x_pos
    j = start_pos[1] + y_pos
    while (i < to_pos[0] if x_pos==1 else i > to_pos[0]):
        if board.board[i][j] != None:
            print(blocked)
            print('At: ' + str((i, j)))
            return False
        i += x_pos
        j += y_pos
    return True


def check_updown_castle(color, board, start_pos, to_pos):
    '''
    Checks if there are any threats from the opposite 'color' from 'start_pos' (non-inclusive)
    to 'to_pos' (inclusive) on board 'board'.
    '''
    
    x_pos = 1 if to_pos[0] - start_pos[0] > 0 else -1
    i = start_pos[0] + x_pos

    front_piece = board.board[i][start_pos[1]]
    if front_piece != None and front_piece.name == 'K' and front_piece.color != color:
        return False

    while (i <= to_pos[0] if x_pos == 1 else i >= to_pos[0]):
        if board.board[i][start_pos[1]] != None and board.board[i][start_pos[1]].color != color:
            if board.board[i][start_pos[1]].name in ['R', 'Q']:
                return False
            else:
                return True
        if board.board[i][start_pos[1]] != None and board.board[i][start_pos[1]].color == color:
            return True
        
    return True

def check_updown(board, start_pos, to_pos):
    '''
    Checks if there are no pieces along the vertical or horizontal path
    from 'start_pos' (non-inclusive) to 'to_pos' (non-inclusive).
    '''
    if start_pos[0] == to_pos[0]:
        smaller_y = start_pos[1] if start_pos[1] < to_pos[1] else to_pos[1]
        bigger_y = start_pos[1] if start_pos[1] > to_pos[1] else to_pos[1]

        for i in range(smaller_y + 1, bigger_y):
            if board.board[start_pos[0]][i] != None:
                print(blocked)
                print('At: ' + str(start_pos[0], i))
                return False
        return True
    else:
        smaller_x = start_pos[0] if start_pos[0] < to_pos[0] else to_pos[0]
        bigger_x = start_pos[0] if start_pos[0] > to_pos[0] else to_pos[0]

        for i in range(smaller_x + 1, bigger_x):
            if board.board[i][start_pos[1]] != None:
                print(blocked)
                return False
        return True



class Piece():
    '''
    A class to represent a piece in chess

    name legend:
        Pawn -> P
        Rook -> R
        Knight -> N
        Bishop -> B
        Queen -> Q
        King -> K
    '''
    def __init__(self, color):
        self.name = ''
        self.color = color

    def is_valid_move(self, board, start_pos, to_pos):
        return False

    def is_white(self):
        return self.color

    # used for easily printing any piece or piece subclass
    def __str__(self):
        if self.color:
            return self.name
        else:
            return '\033[94m' + self.name + '\033[0m'

class Rook(Piece):
    def __init__(self, color, first_move = True):
        '''
        Same as base class Piece, except 'first_move' is used to check
        if this rook can castle.
        '''
        super().__init__(color)
        self.name = 'R'
        self.first_move = first_move 

    def is_valid_move(self, board, start_pos, to_pos):
        if start_pos[0] == to_pos[0] or start_pos[1] == to_pos[1]:
            return check_updown(board, start_pos, to_pos)
        print(illegal_move)
        return False

class Knight(Piece):
    def __init__(self, color):
        super().__init__(color)
        self.name = 'N'

    def is_valid_move(self, board, start_pos, to_pos):
        if abs(start_pos[0] - to_pos[0]) == 2 and abs(start_pos[1] - to_pos[1]) == 1:
            return True
        if abs(start_pos[0] - to_pos[0]) == 1 and abs(start_pos[1] - to_pos[1]) == 2:
            return True
        print(illegal_move)
        return False

class Bishop(Piece):
    def __init__(self, color):
        super().__init__(color)
        self.name = 'B'

    def is_valid_move(self, board, start_pos, to_pos):
        return check_diag(board, start_pos, to_pos)

class Queen(Piece):
    def __init__(self, color):
        super().__init__(color)
        self.name = 'Q'

    def is_valid_move(self, board, start_pos, to_pos):
        # diagonal
        if abs(start_pos[0] - to_pos[0]) == abs(start_pos[1] - to_pos[1]):
            return check_diag(board, start_pos, to_pos)

        # up/down
        elif start_pos[0] == to_pos[0] or start_pos[1] == to_pos[1]:
            return check_updown(board, start_pos, to_pos)
        print(illegal_move)
        return False

class King(Piece):
    def __init__(self, color, first_move = True):
        '''
        Same as base class Piece, except 'first_move' is used to check
        if this king can castle.
        '''
        super().__init__(color)
        self.name = 'K'
        self.first_move = first_move 
        
    def can_castle(self, board, start_pos, to_pos, right):
        '''
        Returns True if king at 'start_pos' can move to 'to_pos' on 'board'.
        '''

        # White castling to_pos the right
        if self.color and right:
            knight_attack = check_knight(self.color, board, (6, 3)) and \
                check_knight(self.color, board, (6, 4)) and \
                check_knight(self.color, board, (5, 4)) and \
                check_knight(self.color, board, (5, 5)) and \
                check_knight(self.color, board, (5, 6)) and \
                check_knight(self.color, board, (5, 7)) and \
                check_knight(self.color, board, (6, 7))
            if not knight_attack: 
                return False

            diags = check_diag_castle(self.color, board, (7, 5), (2, 0)) and \
                check_diag_castle(self.color, board, (7, 6), (1, 0)) and \
                check_diag_castle(self.color, board, (7, 5), (5, 7)) and \
                check_diag_castle(self.color, board, (7, 6), (6, 7))
            if not diags:
                return False

            updowns = check_updown_castle(self.color, board, (7, 5), (0, 5)) and \
                check_updown_castle(self.color, board, (7, 6), (0, 6))
            if not updowns: 
                return False

            board.board[to_pos[0]][to_pos[1]] = King(True, False) 
            board.board[to_pos[0]][to_pos[1]-1] = Rook(True, False) 
            board.board[start_pos[0]][start_pos[1]] = None
            board.board[7][7] = None
            return True
        
        # White castling to_pos the left
        if self.color and not right:
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

            diags = check_diag_castle(self.color, board, (7, 2), (5, 0)) and \
                check_diag_castle(self.color, board, (7, 3), (4, 0)) and \
                check_diag_castle(self.color, board, (7, 2), (2, 7)) and \
                check_diag_castle(self.color, board, (7, 3), (3, 7))
            if not diags:
                return False

            updowns = check_updown_castle(self.color, board, (7, 2), (0, 2)) and \
                check_updown_castle(self.color, board, (7, 3), (0, 3))
            if not updowns: 
                return False
            board.board[to_pos[0]][to_pos[1]] = King(True, False) 
            board.board[to_pos[0]][to_pos[1]+1] = Rook(True, False)
            board.board[start_pos[0]][start_pos[1]] = None
            board.board[7][0] = None

            return True

        # Black castling to_pos the right
        if not self.color and right:
            knight_attack = check_knight(self.color, board, (1, 3)) and \
                check_knight(self.color, board, (1, 4)) and \
                check_knight(self.color, board, (1, 7)) and \
                check_knight(self.color, board, (2, 4)) and \
                check_knight(self.color, board, (2, 5)) and \
                check_knight(self.color, board, (2, 6)) and \
                check_knight(self.color, board, (2, 7))
            if not knight_attack: 
                return False

            diags = check_diag_castle(self.color, board, (0, 5), (5, 0)) and \
                check_diag_castle(self.color, board, (0, 6), (6, 0)) and \
                check_diag_castle(self.color, board, (0, 5), (2, 7)) and \
                check_diag_castle(self.color, board, (0, 6), (1, 7))
            if not diags:
                return False

            updowns = check_updown_castle(self.color, board, (0, 2), (7, 2)) and \
                check_updown_castle(self.color, board, (0, 3), (7, 3))
            if not updowns: 
                return False

            board.board[to_pos[0]][to_pos[1]] = King(False, False)
            board.board[to_pos[0]][to_pos[1]-1] = Rook(False, False) 
            board.board[start_pos[0]][start_pos[1]] = None
            board.board[0][7] = None

            return True
        
        # Black castling to_pos the left
        if not self.color and not right:
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

            diags = check_diag_castle(self.color, board, (0, 2), (5, 7)) and \
                check_diag_castle(self.color, board, (0, 3), (4, 7)) and \
                check_diag_castle(self.color, board, (0, 2), (2, 0)) and \
                check_diag_castle(self.color, board, (0, 3), (3, 0))
            if not diags:
                return False

            updowns = check_updown_castle(self.color, board, (0, 2), (7, 2)) and \
                check_updown_castle(self.color, board, (0, 3), (7, 3))
            if not updowns: 
                return False

            board.board[to_pos[0]][to_pos[1]] = King(False, False)
            board.board[to_pos[0]][to_pos[1]+1] = Rook(False, False) 
            board.board[start_pos[0]][start_pos[1]] = None
            board.board[0][0] = None

            return True


    def is_valid_move(self, board, start_pos, to_pos):
        if self.first_move and abs(start_pos[1] - to_pos[1]) == 2 and start_pos[0] - to_pos[0] == 0:
            return self.can_castle(board, start_pos, to_pos, to_pos[1] - start_pos[1] > 0)

        if abs(start_pos[0] - to_pos[0]) == 1 or start_pos[0] - to_pos[0] == 0:
            if start_pos[1] - to_pos[1] == 0 or abs(start_pos[1] - to_pos[1]) == 1:
                self.first_move = False
                return True

        print(illegal_move)
        return False

class Pawn(Piece):
    def __init__(self, color):
        super().__init__(color)
        self.name = 'P'
        self.first_move = True

    def is_valid_move(self, board, start_pos, to_pos):
        if self.color:
            # diagonal move
            if start_pos[0] == to_pos[0] + 1 and (start_pos[1] == to_pos[1] + 1 or start_pos[1] == to_pos[1] - 1):
                if board.board[to_pos[0]][to_pos[1]] != None:
                    self.first_move = False
                    return True
                print('Cannot move diagonally unless taking.')
                return False

            # vertical move
            if start_pos[1] == to_pos[1]:
                if (start_pos[0] - to_pos[0] == 2 and self.first_move) or (start_pos[0] - to_pos[0] == 1):
                    for i in range(start_pos[0] - 1, to_pos[0] - 1, -1):
                        if board.board[i][start_pos[1]] != None:
                            print(blocked)
                            return False

                    self.first_move = False
                    return True

                print('Invalid move' + ' or ' + 'Cannot move forward twice if not first move.')
                return False

            print(illegal_move)
            return False

        else:
            if start_pos[0] == to_pos[0] - 1 and (start_pos[1] == to_pos[1] - 1 or start_pos[1] == to_pos[1] + 1):
                if board.board[to_pos[0]][to_pos[1]] != None:
                    self.first_move = False
                    return True
                print(blocked)
                return False
            if start_pos[1] == to_pos[1]:
                if (to_pos[0] - start_pos[0] == 2 and self.first_move) or (to_pos[0] - start_pos[0] == 1):
                    for i in range(start_pos[0] + 1, to_pos[0] + 1):
                        if board.board[i][start_pos[1]] != None:
                            print(blocked)
                            return False
                    
                    self.first_move = False
                    return True

                print('Invalid move' + ' or ' + 'Cannot move forward twice if not first move.')
                return False

            print(illegal_move)
            return False
