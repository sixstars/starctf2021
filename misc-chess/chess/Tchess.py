import secret
import chess

board = chess.Board()
print('Win as soon as possible!')
print(board)
        
while True:
    comd = input('Plz input your next step like \'1 18\'\n')
    board, result = secret.proc(board, comd)
            
    if result == 0:
        print(secret.res_0)
        print(board)
    elif result == 1:
        print(secret.res_1)
        print(board.result())
        break
    elif result == 2:
        print(secret.res_2)
        break
    elif result == 3:
        print(secret.flag)
        break
    else:
        print(secret.res_F)
        break

