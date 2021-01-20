import chess

class Heuristics:

    # The tables denote the points scored for the position of the chess pieces on the board.

    pTable = [
        [0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0],
        [5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0],
        [1.0,  1.0,  2.0,  3.0,  3.0,  2.0,  1.0,  1.0],
        [0.5,  0.5,  1.0,  2.5,  2.5,  1.0,  0.5,  0.5],
        [0.0,  0.0,  0.0,  2.0,  2.0,  0.0,  0.0,  0.0],
        [0.5, -0.5, -1.0,  0.0,  0.0, -1.0, -0.5,  0.5],
        [0.5,  1.0, 1.0,  -2.0, -2.0,  1.0,  1.0,  0.5],
        [0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0]]

    rTable = [
        [  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0],
        [  0.5,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  0.5],
        [ -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5],
        [ -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5],
        [ -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5],
        [ -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5],
        [ -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5],
        [  0.0,   0.0, 0.0,  0.5,  0.5,  0.0,  0.0,  0.0]]

    nTable = [
        [-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0],
        [-4.0, -2.0,  0.0,  0.0,  0.0,  0.0, -2.0, -4.0],
        [-3.0,  0.0,  1.0,  1.5,  1.5,  1.0,  0.0, -3.0],
        [-3.0,  0.5,  1.5,  2.0,  2.0,  1.5,  0.5, -3.0],
        [-3.0,  0.0,  1.5,  2.0,  2.0,  1.5,  0.0, -3.0],
        [-3.0,  0.5,  1.0,  1.5,  1.5,  1.0,  0.5, -3.0],
        [-4.0, -2.0,  0.0,  0.5,  0.5,  0.0, -2.0, -4.0],
        [-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0]]

    bTable = [
        [ -2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0],
        [ -1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0],
        [ -1.0,  0.0,  0.5,  1.0,  1.0,  0.5,  0.0, -1.0],
        [ -1.0,  0.5,  0.5,  1.0,  1.0,  0.5,  0.5, -1.0],
        [ -1.0,  0.0,  1.0,  1.0,  1.0,  1.0,  0.0, -1.0],
        [ -1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0, -1.0],
        [ -1.0,  0.5,  0.0,  0.0,  0.0,  0.0,  0.5, -1.0],
        [ -2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0]]

    qTable = [
        [ -2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0],
        [ -1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0],
        [ -1.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0],
        [ -0.5,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5],
        [  0.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5],
        [ -1.0,  0.5,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0],
        [ -1.0,  0.0,  0.5,  0.0,  0.0,  0.0,  0.0, -1.0],
        [ -2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0]]

    kTable = [
        [ -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0],
        [ -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0],
        [ -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0],
        [ -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0],
        [ -2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0],
        [ -1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0],
        [  2.0,  2.0,  0.0,  0.0,  0.0,  0.0,  2.0,  2.0],
        [  2.0,  3.0,  1.0,  0.0,  0.0,  1.0,  3.0,  2.0]]

    tables = {'K':kTable, 'k':kTable, 'Q':qTable, 'q':qTable, 'B':bTable, 'b':bTable, 'N':nTable, 'n':nTable, 'R':rTable, 'r':rTable, 'P':pTable, 'p':pTable}  
    values = {'K':900, 'k':900, 'Q':90, 'q':90, 'B':30, 'b':30, 'N':30, 'n':30, 'R':50, 'r':50, 'P':10, 'p':10}

    @staticmethod
    def evaluate(board):
        evl = 0
        for i in range(8):
            for j in range(8):
                pos = i * 8 + j
                if board.piece_type_at(pos) in range(1,7):
                    syb = board.piece_at(pos).symbol()
                    if 'A'<= syb and syb <= 'Z':
                        evl = evl + Heuristics.tables[syb][i][j] + Heuristics.values[syb]
                    else:
                        evl = evl - Heuristics.tables[syb][7 - i][j] - Heuristics.values[syb]
        return evl


class AI:

    INFINITE = 10000000

    @staticmethod
    def get_ai_move(chessboard, iswhite, steps, boards):
        best_move = chess.Move.null()
        if iswhite:
        	best_score = AI.INFINITE
        else:
        	best_score = -AI.INFINITE

        if chessboard.is_checkmate():
        	return best_move, 0
        
        for move in list(chessboard.legal_moves):
            copy = chessboard.copy()

            for cnt in range(0, len(boards)):
                if (boards[cnt].piece_type_at(move.to_square) == 6) and (boards[cnt].color_at(move.to_square) == iswhite):
                    return move, len(boards) - cnt

            copy = chessboard.copy()
            copy.push(move)

            if copy.is_checkmate():
            	return move, 0

            score = AI.alphabeta(copy, steps, -AI.INFINITE, AI.INFINITE, iswhite)

            if iswhite:
            	if (score < best_score):
                	best_score = score
                	best_move = move
            else:
            	if (score > best_score):
                	best_score = score
                	best_move = move

        return best_move, 0

    @staticmethod
    def minimax(board, depth, maximizing):
        if (depth == 0):
            return Heuristics.evaluate(board)

        if (maximizing):
            best_score = -AI.INFINITE
            for move in list(board.legal_moves):
                copy = board.copy()
                copy.push(move)
                score = AI.minimax(copy, depth - 1, False)
                best_score = max(best_score, score)

            return best_score 

        else:
            best_score = AI.INFINITE
            for move in list(board.legal_moves):
                copy = board.copy()
                copy.push(move)
                score = AI.minimax(copy, depth-1, True)
                best_score = min(best_score, score)

            return best_score

    @staticmethod
    def alphabeta(chessboard, depth, a, b, maximizing):
        if (depth == 0):
            return Heuristics.evaluate(chessboard)

        if (maximizing):
            best_score = -AI.INFINITE
            for move in list(chessboard.legal_moves):
                copy = chessboard.copy()
                copy.push(move)

                best_score = max(best_score, AI.alphabeta(copy, depth-1, a, b, False))
                a = max(a, best_score)
                if (b <= a):
                    break
            return best_score

        else:
            best_score = AI.INFINITE
            for move in list(chessboard.legal_moves):
                copy = chessboard.copy()
                copy.push(move)

                best_score = min(best_score, AI.alphabeta(copy, depth-1, a, b, True))
                b = min(b, best_score)
                if (b <= a):
                    break
            return best_score

def test():
	board = chess.Board()
	while not board.is_game_over():
		move, bk = AI.get_ai_move(board, False, 2)
		if move == chess.Move.null():
			break
		board.push(move)
		print(board)
		print('---')
		if board.is_game_over():
			break
		move, bk = AI.get_ai_move(board, True, 2)
		if move == chess.Move.null():
			break
		board.push(move)
		if board.is_game_over():
			break
		print(board)
		print('-----------')
