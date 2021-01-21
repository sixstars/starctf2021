# REV-RL_ENV
题目是围棋，是一个3*4的棋盘，需要走出一个双方平局的完美定式出来，实际上这个是有两个解的，因为最后是根据棋盘上的棋子计算的hash值来判断是否正确。所以是有镜像的两组解。分别为：
	{C2\_B2\_D2\_C3\_B1\_C1\_D1\_A2\_B3\_C1\_B1\_A3}
	{B1\_D2\_C2\_C1\_D2\_C3\_A2\_B2\_D1\_A2\_B1\_A3}

```
int main()
{
    std::cout << "Hello, RL!" << std::endl << "Flag: ";
    GoHash.Init(4, 3);
    GoBoard board(4, 3);

    board.play(board.pos(2, 0));
    board.play(board.pos(1, 0));
    board.play(board.pos(3, 0));
    board.play(board.pos(0, 0));
    board.play(board.pos(2, 2));
    board.play(board.pos(0, 2));
    board.play(board.pos(3, 2));
    //board.board_show();

    // *ctf{C2_B2_D2_C3_B1_C1_D1_A2_B3_C1_B1_A3}
    std::string input;
    std::cin >> input;
    if (input.size() < 5)
    {
        std::cout << "Sorry" << std::endl;
        return 0;
    }

    std::string prefix{input.data(), input.data() + 5};
    if (prefix != "*ctf{" || input[input.size() - 1] != '}')
    {
        std::cout << "Sorry" << std::endl;
        return 0;
    }

    std::string input2{input.data() + 5, input.data() + input.size() - 1};
    auto coords = split(input2, "_");
    if (coords.size() != 12)
    {
        std::cout << "Sorry" << std::endl;
        return 0;
    }

    int x, y;
    for (auto& coord : coords)
    {
        coord2xy(coord, x, y, 3);
        board.play(board.pos(x, y));
        //board.board_show();
    }
    //std::cout << std::hex << board.hash_board() << std::endl;
    auto zhash = board.hash_board();
    if (zhash == 0xf617f9e3a57d1259)
        std::cout << "Congratulation!!!" << std::endl;
    else
        std::cout << "Sorry" << std::endl;

    return 0;
}
```
