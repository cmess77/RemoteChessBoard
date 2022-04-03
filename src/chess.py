class Chess():
    ''' 
    This will handle all of the "macro" type functions, handling moves,
    promotions, captures, etc.
    '''

    def __init__(self):
        self.board = board.Board()

        self.turn = True

