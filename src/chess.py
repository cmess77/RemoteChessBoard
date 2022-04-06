import board
import piece
# import serial


class Chess():
    '''
    A class to represent the game of chess.
    '''

    def __init__(self):
        self.board = board.Board()

        self.turn = True


    def promotion(self, pos):
        pawn = None
        while pawn == None:
            promote = input('Promote pawn to [Q, R, N, B, P(or nothing)]: ')
            if promote not in ['Q', 'R', 'N', 'B', 'P', '']:
                print('Not a valid promotion')
            else:
                if promote == 'Q':
                    pawn = piece.Queen(True)
                elif promote == 'R':
                    pawn = piece.Rook(True)
                elif promote == 'N':
                    pawn = piece.Knight(True)
                elif promote == 'B':
                    pawn = piece.Bishop(True)
                elif promote == 'P' or promote == '': 
                    pawn = piece.Pawn(True)
        self.board.board[pos[0]][pos[1]] = pawn 


    def move(self, start_pos, to_pos):
        '''
        Moves a piece at 'start_pos' to 'to_pos'. Does nothing if there is no piece at the starting point.
        Does nothing if the piece at 'start_pos' belongs to the wrong color for the current turn.
        Does nothing if moving the piece from 'start_pos' to 'to_pos' is not a valid move.
        '''

        if self.board.board[start_pos[0]][start_pos[1]] == None:
            print('There is no piece to move at the start_pos place')
            return

        target_piece = self.board.board[start_pos[0]][start_pos[1]]
        if self.turn != target_piece.color:
            print("That's not your piece to move")
            return

        end_piece = self.board.board[to_pos[0]][to_pos[1]]
        is_end_piece = end_piece != None

        # Checks if a player's own piece is at the 'to_pos' coordinate
        if is_end_piece and self.board.board[start_pos[0]][start_pos[1]].color == end_piece.color:
            print("There's a piece in the path.")
            return

        if target_piece.is_valid_move(self.board, start_pos, to_pos):
            # Special check for if the move is castling
            # Board reconfiguration is handled in Piece
            if target_piece.name == 'K' and abs(start_pos[1] - to_pos[1]) == 2:
                print('castled')
                
                self.turn = not self.turn
                return
                
            if self.board.board[to_pos[0]][to_pos[1]]:
                print(str(self.board.board[to_pos[0]][to_pos[1]]) + ' taken.')


            self.board.board[to_pos[0]][to_pos[1]] = target_piece
            self.board.board[start_pos[0]][start_pos[1]] = None
            print(str(target_piece) + ' moved.')


            self.turn = not self.turn


def translate(s):
    '''
    Translates traditional board coordinates of chess into list indices
    '''
    try:
        row = int(s[1])
        col = s[0]
        if row < 1 or row > 8:
            print(s[0] + 'is not in the range from 1 - 8')
            return None
        if col < 'a' or col > 'h':
            print(s[1] + 'is not in the range from a - h')
            return None
        dict = {'a': 0, 'b': 1, 'c': 2, 'd': 3, 'e': 4, 'f': 5, 'g': 6, 'h': 7}
        return (8 - row, dict[col])
    except:
        print(s + "is not in the format '[number][letter]'")
        return None



if __name__ == '__main__':
    chess = Chess()
    chess.board.print_board()
    # ser = serial.Serial('/dev/ttyUSB0', 9600, timeout = 2)

    while True:
        # if chess.turn == True:
        #     start_pos = input('From: ')
        #     to_pos = input('To: ')
            
        #     start_pos = translate(start_pos)
        #     to_pos = translate(to_pos)

        #     if start_pos == None or to_pos == None:
        #         continue

        #     chess.move(start_pos, to_pos)

        #     # check for promotion pawns
        #     i = 0
        #     while i < 8:
        #         if not chess.turn and chess.board.board[0][i] != None and \
        #             chess.board.board[0][i].name == 'P':
        #             chess.promotion((0, i))
        #             break
        #         elif chess.turn and chess.board.board[7][i] != None and \
        #             chess.board.board[7][i].name == 'P':
        #             chess.promotion((7, i))
        #             break
        #         i += 1

        #     chess.board.print_board()
        start_pos = input('From: ')
        to_pos = input('To: ')
        
        start_pos = translate(start_pos)
        to_pos = translate(to_pos)

        if start_pos == None or to_pos == None:
            continue

        chess.move(start_pos, to_pos) # add serial functionality within move

        # check for promotion
        i = 0
        while i < 8:
            if not chess.turn and chess.board.board[0][i] != None and \
                chess.board.board[0][i].name == 'P':
                chess.promotion((0, i))
                break
            elif chess.turn and chess.board.board[7][i] != None and \
                chess.board.board[7][i].name == 'P':
                chess.promotion((7, i))
                break
            i += 1

        chess.board.print_board()

        # else:
            # continue

