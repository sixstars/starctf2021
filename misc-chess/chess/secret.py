import chess
import ai

cnt = 0
res_F = 'Wrong command\n'
res_0 = 'Plz continue\n'
res_1 = 'Normal end\nTry to check mate as early as possible!\n'
res_2 = 'You lose!\nShe cheated!\nHint: Check her step!\n'
flag = '*CTF{1F_i_had_A_t!me_mAch1ne}\n'

boards = []

def proc(chessboard, comd):
	global cnt

	if cnt == 0:
		cnt = 1
		boards.append(chessboard.copy())

	lis = list(comd.split(' '))
	if len(lis) == 2:
		_from = int(lis[0])
		_to = int(lis[1])
		op = cnt - 1
		ed = cnt		
	elif len(lis) == 4:
		_from = int(lis[0])
		_to = int(lis[1])
		if lis[2].isdigit() and lis[3].isdigit():
			op = int(lis[2])
			ed = int(lis[3])
		else:
			return chessboard, -1
	else:
		return chessboard, -1

	if _from > 63 or _to > 63 or op > cnt - 1 or ed > cnt:
		return chessboard, -1

	mvstr = chess.SQUARE_NAMES[_from] + chess.SQUARE_NAMES[_to]

	if chess.Move.from_uci(mvstr) in boards[op].legal_moves:
		if op == cnt - 1:
			if ed == cnt:
				cnt = cnt + 1
				chessboard.push(chess.Move.from_uci(mvstr))
				boards.append(chessboard.copy())
				if chessboard.is_game_over():
					return chessboard, 1

				print(chessboard)

				aimove, aicnt = ai.AI.get_ai_move(chessboard, True, 2, boards)
				if aicnt > 0:
					print(aimove.from_square, aimove.to_square, cnt, cnt - aicnt)
					return chessboard, 2
				else:
					cnt = cnt + 1
					chessboard.push(aimove)
					boards.append(chessboard.copy())
					if chessboard.is_game_over():
						return chessboard, 1
				return chessboard, 0

			else:
				pp = boards[op].piece_at(_from)
				boards[op].remove_piece_at(_from)
				chessboard.remove_piece_at(_from)
				boards[ed].set_piece_at(_to, pp)
				chessboard.push(chess.Move.null())

				if boards[0].is_game_over():
					return chessboard, 3

				print(chessboard)

				aimove, aicnt = ai.AI.get_ai_move(chessboard, True, 2, boards)
				if aicnt > 0:
					print(aimove.from_square, aimove.to_square, cnt, cnt - aicnt)
					return chessboard, 2
				else:
					cnt = cnt + 1
					chessboard.push(aimove)
					boards.append(chessboard.copy())
					if chessboard.is_game_over():
						return chessboard, 1
				return chessboard, 0
		else:
			pp = boards[op].remove_piece_at(_from)
			boards[ed].set_piece_at(_to, pp)
			chessboard.push(chess.Move.null())

			boards[0].push(chess.Move.null())

			if boards[0].is_game_over():
				return chessboard, 3

			boards[0].push(chess.Move.null())

			print(chessboard)

			aimove, aicnt = ai.AI.get_ai_move(chessboard, True, 2, boards)

			if aicnt > 0:
				print(aimove.from_square, aimove.to_square, cnt, cnt - aicnt)
				return chessboard, 2
			else:
				cnt = cnt + 1
				chessboard.push(aimove)
				boards.append(chessboard.copy())
				if chessboard.is_game_over():
					return chessboard, 1
			return chessboard, 0
	else:
		if op % 2 == 1:
			boards[op].push(chess.Move.null())
			if chess.Move.from_uci(mvstr) in boards[op].legal_moves:
				pp = boards[op].remove_piece_at(_from)
				boards[ed].set_piece_at(_to, pp)

				boards[op].push(chess.Move.null())
				chessboard.push(chess.Move.null())
				boards[0].push(chess.Move.null())

				if boards[0].is_game_over():
					return chessboard, 3

				boards[0].push(chess.Move.null())


				print(chessboard)

				aimove, aicnt = ai.AI.get_ai_move(chessboard, True, 2, boards)

				if aicnt > 0:
					print(aimove.from_square, aimove.to_square, cnt, cnt - aicnt)
					return chessboard, 2
				else:
					cnt = cnt + 1
					chessboard.push(aimove)
					boards.append(chessboard.copy())
					if chessboard.is_game_over():
						return chessboard, 1
				return chessboard, 0

			else:
				return chessboard, -1
		else:
			return chessboard, -1
